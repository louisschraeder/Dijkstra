//
// Created by lschraed@id.hsos.de on 10.11.22.
//

#ifndef DIJKSTRA_DIJKSTRA_PQ_H
#define DIJKSTRA_DIJKSTRA_PQ_H

#include "Graph_pq.h"
#include "CompareDistance.h"
#include <tbb/parallel_for.h>
#include <oneapi/tbb/concurrent_priority_queue.h>
#include <queue>

using namespace std;

class Dijkstra_pq : public Graph_pq {
public:
    Dijkstra_pq(string input_file) : Graph_pq(input_file) {}

    void init(unsigned sourceNode) override {
        this->sourceNode = sourceNode;
        this->nodes.resize(this->adjacency_list.size());

        for (unsigned i = 1; i <= this->adjacency_list.size(); i++) {
            this->nodes[i] = new Node(i);
            this->nodes[i]->edges = this->adjacency_list[i];
        }
        // set distance of starting node to 0
        this->nodes[sourceNode]->dist = 0;
    }

    void sequential() override {
        priority_queue<Node*, vector<Node*>, CompareDistance> queue;

        Node* startNode = this->nodes[sourceNode];
        queue.push(startNode);


        while(!queue.empty()) {
            Node* currentNode = queue.top();
            queue.pop();

            if(!currentNode->visited) { // not visited, so take it
                currentNode->visited = true;

                for(Arc edge : currentNode->edges) {
                    if(!this->nodes[edge.next]->visited) {
                        unsigned newDistance = currentNode->dist + edge.weight;

                        if(this->nodes[edge.next]->dist > newDistance) {
                            this->nodes[edge.next]->dist = newDistance;
                            this->nodes[edge.next]->prev = currentNode;
                        }
                        queue.push(this->nodes[edge.next]);
                    }
                }
            }
        }
    }

    void parallel() override {
        oneapi::tbb::concurrent_priority_queue<Node*, CompareDistance> queue;

        Node* currentNode = this->nodes[sourceNode];
        queue.push(currentNode);

        while(!queue.empty()) {
            queue.try_pop(currentNode);

            if(!currentNode->visited) { // not visited, so take it
                currentNode->visited = true;

                auto node = this->nodes;
                // iterate through all neighbours of current visited node
                oneapi::tbb::parallel_for(oneapi::tbb::blocked_range<size_t>(0, node.size()),
                                          [&](const oneapi::tbb::blocked_range<size_t> &r) {
                                              Arc edge =  &currentNode->edges[i];

                                              for (size_t j = r.begin(); j != r.end(); j++) {
                                                  // if neighbouring node has not been visited yet: update distance
                                                  if(!this->nodes[edge.next]->visited) {
                                                      unsigned newDistance = currentNode->dist + edge.weight;

                                                      if(this->nodes[edge.next]->dist > newDistance) {
                                                          this->nodes[edge.next]->dist = newDistance;
                                                          this->nodes[edge.next]->prev = currentNode;
                                                      }
                                                      queue.push(this->nodes[edge.next]);
                                                  }
                                              }
                                          });


            }
        }
    }

};




#endif //DIJKSTRA_DIJKSTRA_PQ_H

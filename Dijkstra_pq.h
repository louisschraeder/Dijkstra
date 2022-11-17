//
// Created by lschraed@id.hsos.de on 10.11.22.
//

#ifndef DIJKSTRA_DIJKSTRA_PQ_H
#define DIJKSTRA_DIJKSTRA_PQ_H

#include "Graph.h"
#include <tbb/parallel_for.h>

class Dijkstra : public Graph {
public:
    Dijkstra(string input_file) : Graph(input_file) {}

    void init(unsigned sourceNode) override {
        this->sourceNode = sourceNode;
        this->distance.resize(this->adjacency_list.size());
        this->prev.resize(this->adjacency_list.size());
        this->visited.resize(this->adjacency_list.size());

        for (unsigned i = 0; i <= this->adjacency_list.size(); i++) {
            this->distance[i] = INFINITY;
            this->prev[i] = 0;
            this->visited[i] = false;
        }
        // set distance of starting node to 0
        this->distance[sourceNode] = 0;
    }

    void sequential() override {
        for (unsigned i = 1; i <= this->adjacency_list.size(); i++) {
            unsigned minNodeIndex = this->getNodeMinDist();
            this->visited[minNodeIndex] = true;
            auto arc = this->adjacency_list[minNodeIndex];

            // iterate through all neighbours of current visited node
            for (auto & j : arc) {
                // if neighbouring node has not been visited yet: update distance
                auto neighbour = j.next;
                auto neighbourDistance = j.weight;

                if (!this->visited[neighbour]) {
                    auto proposedDistance = this->distance[minNodeIndex] + neighbourDistance;

                    if (proposedDistance < this->distance[neighbour]) {
                        // update distance and set predecessors node
                        this->distance[neighbour] = proposedDistance;
                        this->prev[neighbour] = minNodeIndex;
                    }
                }
            }
        }
    }

    void parallel() override {
        for (unsigned i = 1; i < this->adjacency_list.size(); i++) {
            unsigned minNodeIndex = this->getNodeMinDist();
            this->visited[minNodeIndex] = true;
            auto node = this->adjacency_list[minNodeIndex];

            // iterate through all neighbours of current visited node
            oneapi::tbb::parallel_for(oneapi::tbb::blocked_range<size_t>(0, node.size()),
                                      [&](const oneapi::tbb::blocked_range<size_t> &r) {
                                          for (size_t j = r.begin(); j != r.end(); j++) {
                                              // if neighbouring node has not been visited yet: update distance
                                              auto neighbour = node[j].next;
                                              auto neighbourDistance = node[j].weight;

                                              if (!this->visited[neighbour]) {
                                                  auto proposedDistance =
                                                          this->distance[minNodeIndex] + neighbourDistance;

                                                  if (proposedDistance < this->distance[neighbour]) {
                                                      // update distance and set predecessors node
                                                      this->distance[neighbour] = proposedDistance;
                                                      this->prev[neighbour] = minNodeIndex;
                                                  }
                                              }
                                          }
                                      });
        }
    }
};


#endif //DIJKSTRA_DIJKSTRA_PQ_H

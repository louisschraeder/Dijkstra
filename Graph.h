//
// Created by Louis Schräder on 14.11.22.
//

#ifndef DIJKSTRA_GRAPH_H
#define DIJKSTRA_GRAPH_H

#define INFINITY UINT_MAX;

#include <string>
#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>
#include <climits>
#include <algorithm>
#include <iostream>

#include "Arc.h"

using namespace std;

class Graph {
public:
    Graph(string input_file) {
        this->input_file = input_file;
    }

    string input_file;
    vector<vector<Arc>> adjacency_list;
    vector<unsigned> distance;
    vector<unsigned> prev;
    vector<bool> visited;
    unsigned sourceNode;

    virtual void init(unsigned) = 0;
    virtual void sequential() = 0;
    virtual void parallel() = 0;

    void load_graph() {

        adjacency_list.clear();
        distance.clear();
        prev.clear();
        visited.clear();

        // .gr file is in format:
        // a U V W
        // U -> V (with weight W)

        ifstream ifs(input_file);
        string line;
        unsigned number_nodes;
        unsigned number_edges;

        while(getline(ifs, line)) {

            stringstream ss(line);
            string line_type;
            ss >> line_type;

            if(line_type == "p") {
                // p: this line contains info about number of nodes and arcs
                // p sp n m
                // n: number of nodes
                // m: number of arcs

                string sp;
                ss >> sp >> number_nodes >> number_edges;
                this->adjacency_list.resize(number_nodes);
            }

            if (line_type == "a") {
                unsigned U;
                unsigned V;
                unsigned W;
                ss >> U >> V >> W;

                this->adjacency_list[U].push_back(Arc(V, W));
            }
        }
    }

    unsigned getNodeMinDist() {
        unsigned min = INFINITY;
        unsigned index_min = -1;
        for (unsigned i = 1; i <= this->adjacency_list.size(); i++) {
            if (!this->visited[i] && this->distance[i] < min) {
                min = this->distance[i];
                index_min = i;
            }
        }
        return index_min;
    }

    void print(unsigned destination_index) {
        cout << this->sourceNode <<"-->" << destination_index << ": distance "
                  << this->distance[destination_index] << std::endl;
        vector<unsigned> path;
        unsigned current_index = destination_index;

        do {
            path.push_back(current_index);
            current_index = this->prev[current_index];
        } while (current_index != this->sourceNode);
        reverse(path.begin(), path.end());
        copy(path.begin(), path.end(), ostream_iterator<unsigned>(cout, " "));
    };
};

#endif //DIJKSTRA_GRAPH_H

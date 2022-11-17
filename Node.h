//
// Created by lschraed@id.hsos.de on 10.11.22.
//

#ifndef DIJKSTRA_NODE_H
#define DIJKSTRA_NODE_H

#include "Arc.h"
#include <vector>

using namespace std;

class Node {
public:
    unsigned id;
    unsigned dist;
    Node* prev;
    vector<Arc> edges;
    bool visited;

    Node(unsigned id) {
        this->id = id;
        this->edges = vector<Arc>();
        this->prev = NULL;
        this->dist = UINT_MAX;
        this->visited = false;
    }

    void addEdge(Arc &arc) {
        edges.push_back(arc);
    }


};

#endif //DIJKSTRA_NODE_H

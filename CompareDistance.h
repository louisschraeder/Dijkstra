//
// Created by lschraed@id.hsos.de on 17.11.22.
//

#ifndef DIJKSTRA_COMPAREDISTANCE_H
#define DIJKSTRA_COMPAREDISTANCE_H

#include "Node.h"

class CompareDistance {
public:
    bool operator()(const Node* n1, const Node* n2) const {
        //std::cout <<"comparing .. n1 " << n1->distanceToStartNode << " n2 " << n2->distanceToStartNode << std::endl;
        return n1->dist > n2->dist;
    }
};



#endif //DIJKSTRA_COMPAREDISTANCE_H

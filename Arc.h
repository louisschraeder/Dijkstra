//
// Created by lschraed@id.hsos.de on 10.11.22.
//

#ifndef DIJKSTRA_ARC_H
#define DIJKSTRA_ARC_H

class Arc{
public:
    unsigned weight;
    unsigned next;

    Arc(unsigned next, unsigned weight) {
        this->next = next;
        this->weight = weight;
    }
};

#endif //DIJKSTRA_ARC_H

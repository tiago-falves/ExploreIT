//
// Created by miguel on 09/05/20.
//

#ifndef CAL1920_MUTABLEPRIORITYQUEUE_H
#define CAL1920_MUTABLEPRIORITYQUEUE_H

#include <vector>
#include "Node.h"
#pragma once


using namespace std;

class MutablePriorityQueue {
    vector<Node *> H;
    void heapifyUp(unsigned i);
    void heapifyDown(unsigned i);
    inline void set(unsigned i, Node * x);
public:
    MutablePriorityQueue();
    void insert(Node * x);
    Node * extractMin();
    void decreaseKey(Node * x);
    bool empty();
};

#endif //CAL1920_MUTABLEPRIORITYQUEUE_H


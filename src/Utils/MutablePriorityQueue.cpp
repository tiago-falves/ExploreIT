//
// Created by miguel on 09/05/20.
//

// Index calculations
#include "MutablePriorityQueue.h"

#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

MutablePriorityQueue::MutablePriorityQueue() {
    H.push_back(nullptr);
}

bool MutablePriorityQueue::empty() {
    return H.size() == 1;
}

Node* MutablePriorityQueue::extractMin() {
    auto x = H[1];
    H[1] = H.back();
    H.pop_back();
    heapifyDown(1);
    x->queueIndex = 0;
    return x;
}

void MutablePriorityQueue::insert(Node *x) {
    H.push_back(x);
    heapifyUp(H.size()-1);
}

void MutablePriorityQueue::decreaseKey(Node *x) {
    heapifyUp(x->queueIndex);
}

void MutablePriorityQueue::heapifyUp(unsigned i) {
    auto x = H[i];
    while (i > 1 && x->getWeight() < H[parent(i)]->getWeight()) {
        set(i, H[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

void MutablePriorityQueue::heapifyDown(unsigned i) {
    auto x = H[i];
    while (true) {
        unsigned k = leftChild(i);
        if (k >= H.size())
            break;
        if (k+1 < H.size() && H[k+1]->getWeight() < H[k]->getWeight())
            ++k; // right child of i
        if ( ! (H[k]->getWeight() < x->getWeight()) )
            break;
        set(i, H[k]);
        i = k;
    }
    set(i, x);
}

void MutablePriorityQueue::set(unsigned i, Node * x) {
    H[i] = x;
    if(x!=NULL)
        x->queueIndex = i;
}
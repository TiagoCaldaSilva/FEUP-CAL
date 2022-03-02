/*
 * MutablePriorityQueue.h
 * A simple implementation of mutable priority queues, required by Dijkstra algorithm.
 *
 * Created on: 17/03/2018
 *      Author: João Pascoal Faria
 */

#ifndef SRC_MUTABLEPRIORITYQUEUE_H_
#define SRC_MUTABLEPRIORITYQUEUE_H_

#include <vector>
#include "graph/GraphElements.h"


// Index calculations
#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

class MutablePriorityQueue {
private:
	std::vector<Vertex *> H;

	void heapifyUp(unsigned i) {
        auto x = H[i];
        while (i > 1 && *x < *H[parent(i)]) {
            set(i, H[parent(i)]);
            i = parent(i);
        }
        set(i, x);
	}

	void heapifyDown(unsigned i) {
        auto x = H[i];
        while (true) {
            unsigned k = leftChild(i);
            if (k >= H.size())
                break;
            if (k+1 < H.size() && *H[k+1] < *H[k])
                ++k; // right child of i
            if ( ! (*H[k] < *x) )
                break;
            set(i, H[k]);
            i = k;
        }
        set(i, x);
	}

	inline void set(unsigned i, Vertex* x) {
        H[i] = x;
        x->queueIndex = i;
	}

public:
	MutablePriorityQueue() {
        H.push_back(nullptr);
        // indices will be used starting in 1
        // to facilitate parent/child calculations
	};

	void insert(Vertex * x) {
        H.push_back(x);
        heapifyUp(H.size() - 1);
	}

	Vertex* extractMin() {
        auto x = H[1];
        H[1] = H.back();
        H.pop_back();
        if(H.size() > 1) heapifyDown(1);
        x->queueIndex = 0;
        return x;
	}

	void decreaseKey(Vertex * x) {
        heapifyUp(x->queueIndex);
	}

	bool empty() {
	    return H.size() == 1;
	}
};

#endif /* SRC_MUTABLEPRIORITYQUEUE_H_ */

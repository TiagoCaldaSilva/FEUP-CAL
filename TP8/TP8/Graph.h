/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits>
#include <cmath>

template <class T> class Edge;
template <class T> class Graph;

constexpr auto INF = std::numeric_limits<double>::max();

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */
template <class T>
class Vertex {
    T info;
    std::vector<Edge<T> *> outgoing;  // adj
    std::vector<Edge<T> *> incoming;
    Edge<T> * addEdge(Vertex<T> *dest, double c, double f);
    Vertex(T in);

    bool visited;  // for path finding
    Edge<T> *path; // for path finding

public:
    T getInfo() const;
    std::vector<Edge<T> *> getAdj() const;
    friend class Graph<T>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {
}

template <class T>
Edge<T> *Vertex<T>::addEdge(Vertex<T> *dest, double c, double f) {
    Edge<T> * e = new Edge<T>(this, dest, c, f);
    this->outgoing.push_back(e);
    dest->incoming.push_back(e);
    return e;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
std::vector<Edge<T> *> Vertex<T>::getAdj() const {
    return this->outgoing;
}


/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
template <class T>
class Edge {
    Vertex<T> * orig;
    Vertex<T> * dest;
    double capacity;
    double flow;
    Edge(Vertex<T> *o, Vertex<T> *d, double c, double f=0);

public:
    double getFlow() const;
    Vertex<T> *getDest() const;

    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w, double f): orig(o), dest(d), capacity(w), flow(f){}

template <class T>
double Edge<T>::getFlow() const {
    return flow;
}

template <class T>
Vertex<T>* Edge<T>::getDest() const {
    return dest;
}


/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;

    Vertex<T> *findVertex(const T &inf) const;

    void resetFlows();

    bool findAugmentationPath(Vertex<T> *s, Vertex<T> *t);

    void testAndVisit(std::queue<Vertex<T> *> &q, Edge<T> *e, Vertex<T> *w, double residual);

    double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t);

    void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double flow);

public:
    std::vector<Vertex<T> *> getVertexSet() const;

    Vertex<T> *addVertex(const T &in);

    Edge<T> *addEdge(const T &sourc, const T &dest, double c, double f = 0);

    void fordFulkerson(T source, T target);

    std::vector<std::pair<Vertex<T> *, Edge<T> *>> findNextPath(Vertex<T> *source, Vertex<T> *target, double &minFlow, bool &found);

    Edge<T> *existsReverse(Vertex<T> *dest, Edge<T> *edge);

    std::vector<std::pair<Vertex<T> *, Edge<T> *>> getPath(std::vector<std::pair<Vertex<T> *, Edge<T> *>> path, double &minFlow);
};

template <class T>
Vertex<T> * Graph<T>::addVertex(const T &in) {
    Vertex<T> *v = findVertex(in);
    if (v != nullptr)
        return v;
    v = new Vertex<T>(in);
    vertexSet.push_back(v);
    return v;
}

template <class T>
Edge<T> * Graph<T>::addEdge(const T &sourc, const T &dest, double c, double f) {
    auto s = findVertex(sourc);
    auto d = findVertex(dest);
    if (s == nullptr || d == nullptr)
        return nullptr;
    else
        return s->addEdge(d, c, f);
}

template <class T>
Vertex<T>* Graph<T>::findVertex(const T & inf) const {
    for (auto v : vertexSet)
        if (v->info == inf)
            return v;
    return nullptr;
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/**
 * Finds the maximum flow in a graph using the Ford Fulkerson algorithm
 * (with the improvement of Edmonds-Karp).
 * Assumes that the graph forms a flow network from source vertex 's'
 * to sink vertex 't' (distinct vertices).
 * Receives as arguments the source and target vertices (identified by their contents).
 * The result is defined by the "flow" field of each edge.
 */
template <class T>
void Graph<T>::fordFulkerson(T source, T target) {
    // TODO
    /** Reset Flows */
    for(auto v: vertexSet) {
        for(auto edge: v->getAdj()) {
            edge ->flow = 0;
        }
    }

    Vertex<T> * start = findVertex(source);
    Vertex<T> * end = findVertex(target);

    while(true) {

        double minFlow = INF;   //Goal: find the min value
        bool found = false;     //found = true if there are paths from start to end available
        std::vector<std::pair<Vertex<T> *, Edge<T> *>> nextPath = findNextPath(start, end, minFlow, found);
       if(!found) break;

        for(auto elem: nextPath) {
            Edge<T> * newEdge;
            elem.second->capacity -= minFlow;

            /** elem.second->flow = INF if it isn't an original edge */
            if (elem.second->flow == INF) {
                existsReverse(elem.first, elem.second)->flow -= minFlow;
            } else {
                elem.second->flow = minFlow;
            }

            /** Add the flow that goes through the edge to the reverse edge */
            if(( newEdge = existsReverse(elem.first, elem.second)) != NULL) {
                newEdge->capacity += minFlow;
            } else {
                /** Add an edge to the graph (it isn't an original edge) */
                Edge<T> * temp = addEdge(elem.first->info, elem.second->orig->info, minFlow, INF);
            }
        }
    }

    /** Remove the edges that aren't original */
    for(auto v: vertexSet) {
        for(auto it = v->outgoing.begin(); it != v->outgoing.end(); it++) {
            if((*it)->getFlow() == INF) {
                v->outgoing.erase(it);
                it--;
            }
        }
    }
}

template <class T>
std::vector<std::pair<Vertex<T> *, Edge<T> *>> Graph<T>::findNextPath(Vertex<T> * source, Vertex<T> * target, double & minFlow, bool &found) {

    /** Reset visited field */
    for(auto v:vertexSet) {v->visited = false; }

    std::vector<std::pair<Vertex<T> *, Edge<T> *>> path;
    std::vector<Vertex<T> * > search;
    search.push_back(source);

    while(!search.empty()) {
        Vertex<T> * actual = search[0];
        search.erase(search.begin());

        for(auto edge: actual->outgoing) {
            /** Valid edge */
            if(!edge->dest->visited && edge->capacity > 0) {
                edge->dest->visited = true;
                search.push_back(edge->dest);
                path.insert(path.begin(), std::pair<Vertex<T> *, Edge<T> *>(edge->dest, edge));

                /** Valid path */
                if(edge->dest->info == target->info) {
                    found = true;
                    return getPath(path, minFlow);
                }
            }
        }
    }
    return path;
}

template <class T>
std::vector<std::pair<Vertex<T> *, Edge<T> *>> Graph<T>::getPath(std::vector<std::pair<Vertex<T> *, Edge<T> *>> path, double &minFlow) {
    std::vector<std::pair<Vertex<T> *, Edge<T> *>> realPath;
    Vertex<T> * next = path[0].first;

    for(auto elem:path) {
        Vertex<T> * actual = elem.first;
        /** Belongs to the path */
        if(actual->info == next->info) {
            minFlow = (elem.second->capacity < minFlow) ? elem.second->capacity:minFlow;
            realPath.push_back(elem);
            next = elem.second->orig;
        }
    }

    return realPath;
}

template <class T>
Edge<T> * Graph<T>::existsReverse(Vertex<T> * dest, Edge<T> * edge) {
    for(auto elem: dest->outgoing) {
        if(elem->dest->info == edge->orig->info) {
            return elem;
        }
    }
    return NULL;
}

#endif /* GRAPH_H_ */

/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <iostream>
#include "MutablePriorityQueue.h"


template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    T info;						// content of the vertex
    std::vector<Edge<T> > adj;		// outgoing edges

    double dist = 0;
    Vertex<T> *path = NULL;
    int queueIndex = 0; 		// required by MutablePriorityQueue

    bool visited = false;		// auxiliary field
    bool processing = false;	// auxiliary field

    void addEdge(Vertex<T> *dest, double w);

public:
    Vertex(T in);
    T getInfo() const;
    double getDist() const;
    Vertex *getPath() const;

    /** CREATE */
    void setDist(double dist){this->dist = dist;}
    void setPath(Vertex<T> * p){ path = p; }


    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set
    std::vector<std::vector<double>> dist;
    std::vector<std::vector<int>> parent;

public:
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;

    // Fp06 - single source
    void unweightedShortestPath(const T &s);    //TODO...
    void dijkstraShortestPath(const T &s);      //TODO...
    void bellmanFordShortestPath(const T &s);   //TODO...
    std::vector<T> getPath(const T &origin, const T &dest) const;   //TODO...

    // Fp06 - all pairs
    void floydWarshallShortestPath();   //TODO...
    std::vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    // TODO implement this

    std::queue<Vertex<T> *> aux;

    //Init
    for(Vertex<T>* vertex: vertexSet){
        vertex->setDist(0);
        vertex->setPath(NULL);
    }

    auto temp = findVertex(orig);
    aux.push(temp);

    while(!aux.empty()){
        temp = aux.front();
        aux.pop();
        for(Edge<T> edge:temp->adj){
            if(edge.dest->getDist() == 0 && edge.dest->getInfo() != orig) {
                aux.push(edge.dest);
                edge.dest->setDist(edge.dest->getDist() + 1);
                edge.dest->setPath(temp);
            }
        }
    }
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    // TODO implement this
    for(auto vertex:vertexSet){
        vertex->setDist(INT_MAX);
        vertex->setPath(NULL);
    }

    MutablePriorityQueue<Vertex<T>> aux;
    auto temp = findVertex(origin);
    aux.insert(temp);
    temp->setDist(0);

    while(!aux.empty()) {
        temp = aux.extractMin();
        for(auto edge:temp->adj) {
            if(edge.dest->getDist() > temp->getDist() + edge.weight){
                edge.dest->setDist(temp->getDist() + edge.weight);
                if(edge.dest->getPath() == NULL){ edge.dest->setPath(temp); aux.insert(edge.dest); }
                else{ edge.dest->setPath(temp); aux.decreaseKey(edge.dest); }
            }
        }
    }
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    // TODO implement this
    for(auto vertex:vertexSet) {
        vertex->setDist(INT_MAX);
        vertex->setPath(NULL);
    }

    auto org = findVertex(orig);
    org->setDist(0);

    for(int i = 1; i < vertexSet.size(); i++) {
        for(auto vertex: vertexSet) {
            for (auto edge:vertex->adj) {
                if (edge.dest->getDist() > vertex->getDist() + edge.weight){
                    edge.dest->setDist(vertex->getDist() + edge.weight);
                    edge.dest->setPath(vertex);
                }
            }
        }
    }
}


template<class T>
std::vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
    std::vector<T> res;
    // TODO implement this
    auto temporary = findVertex(dest);

    while(temporary->getInfo() != origin){
        res.insert(res.begin(), temporary->getInfo());
        temporary = temporary->getPath();
    }

    res.insert(res.begin(), temporary->getInfo());

    return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    // TODO implement this

    for(int i = 0; i < vertexSet.size(); i++){
        dist.push_back(std::vector<double>(vertexSet.size(), INF));
        parent.push_back(std::vector<int>(vertexSet.size(), -1));
        for(int j = 0; j < vertexSet.size(); j++){
            if(i == j) {
                dist[i][j] = 0;
                parent[i][j] = i;
            }
            else {
                for (auto edge:vertexSet[i]->adj) {
                    if (vertexSet[j]->getInfo() == edge.dest->getInfo()) {
                        dist[i][j] = edge.weight;
                        parent[i][j] = j;
                        break;
                    }
                }
            }
        }
    }

    for(int k = 0; k < vertexSet.size(); k++){
        for(int i = 0; i < vertexSet.size(); i++) {
            for(int j = 0; j < vertexSet.size(); j++){
                if(dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[i][k];
                }
            }
        }
    }
}

template<class T>
std::vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    std::vector<T> res;
    // TODO implement this
    int first = -1, final = -1;
    for(int i = 0; i < vertexSet.size(); i++) {
        if(vertexSet[i]->getInfo() == orig) first = i;
        if(vertexSet[i]->getInfo() == dest) final = i;
        if(first != -1 && final != -1) break;
    }

    int index = first;
    while(parent[index][final] != index) {
        res.push_back(vertexSet[index]->getInfo());
        index = parent[index][final];
    }
    res.push_back(vertexSet[index]->getInfo());

    return res;
}


#endif /* GRAPH_H_ */

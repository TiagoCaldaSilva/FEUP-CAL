#ifndef E_STAFETAS_GRAPH_H
#define E_STAFETAS_GRAPH_H

#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <iostream>
#include <utility>
#include <algorithm>

#include "GraphElements.h"
#include "../InputParameters.h"
#include "../entities/Vehicle.h"
#include "../MutablePriorityQueue.h"
#include "../interface/GraphDrawer.h"

constexpr auto INF = std::numeric_limits<double>::max();

class Graph {
public:
    /**
     * @brief Graph destructor
     */
    ~Graph();

    /**
     * @brief Execute the program
     * @param p Parameters that the graph should have to execute the program
     * @param gv GraphViewer used to display the graph
     */
    void run(const Parameters& p);
    /**
     * @brief Display the graph
     * @param gv GraphViewer used to display the graph
     * @param edges Edges to draw
     */
    void showResult(GraphDrawer& gd, const std::vector<Edge *>& edges) const;
private:
    /**
     * @brief Initialize the graph
     * @param p Parameters used to initialize the graph
     * @param gv GraphViewer used to display de graph
     */
    void initialize(const Parameters& p);
    /**
     * @brief Initialize the vertices of the graph
     * @param vSet Vertices that should be initialized
     * @param s Garage vertex Vertex that's to be initialized as the vehicles' garage (it's distance to the vehicles is initialized as 0)
     */
    static inline void initializeSingleSource(std::vector<Vertex *>& vSet, Vertex * s);
    /**
     * @brief Takes care of the program flow
     * @param singleVehicle True if the program should execute with a single vehicle, false otherwise
     * @param orderByDistance True if the program should only proceed with 1 vehicle, false if it should use all available
     */
    void proceed(const bool singleVehicle, const bool orderByDistance);
    /**
     * @brief Moves forward a vehicle
     * @param vToGo Vertex to go
     * @param vehicle Vehicle to move
     */
    void goForward(Vertex * vToGo, Vehicle * vehicle) const;

    /**
     * @brief Get the vehicle that has the nearest vertex
     * @return Vehicle that has the nearest vertex
     */
    Vehicle * refreshCurrentVehicle() const;

    /**
     * @brief Get a package by the pickUp vertex
     * @param pickUp PickUp vertex
     * @return Package with the pickUp vertex given if exists, nullptr otherwise
     */
    Package * findPackage(Vertex * pickUp) const;

    /**
     * @brief Calculate the shortest path to s
     * @param vSet Set of vertex to calculate the shortest path
     * @param s Vertex to calculate the distance to
     */
    void dijkstraShortestPath(std::vector<Vertex *>& vSet, Vertex * s);
    /**
     * @brief Get the distance from source to dest after after the dijkstraShortestPath algorithm
     * @param source Source vertex
     * @param dest Target vertex
     * @return Path from source to dest
     */
    static std::vector<Vertex *> getDijkstraPath(Vertex * source, Vertex * dest);

    /**
     * @brief TODO
     * @param vSte
     * @param s
     * @return
     */
    static bool bellmanFordShortestPath(std::vector<Vertex *>& vSte, Vertex * s);
    /**
     * @brief TODO
     * @param u
     * @param v
     * @param w
     */
    static inline void relax(Vertex * u, Vertex * v, double w);

    std::vector<std::vector<double>> dist;
    std::vector<std::vector<int>> prevVertex;
    /**
     * @brief
     */
    void floydWarshallShortestPath();

    /**
     * @brief Get the distance from source to dest after after the floydWarshallShortestPath algorithm
     * @param orig Source vertex
     * @param dest Target vertex
     * @return Path from orig to dest
     */
    [[maybe_unused]] std::vector<Vertex *> getFloydWarshallPath(Vertex * orig, Vertex * dest) const;
    /**
     * @brief Updates the distance field of each vertex
     * @param s Source vertex
     */
    void refreshDist(Vertex * s);
    /**
     * @brief TODO
     * @param vSet
     */
    [[maybe_unused]] void johnsonShortestPath(std::vector<Vertex *>& vSet);

    /**
     * @brief Uses the breadth-first search technique to check if the graph is connected
     * @param vSet vector of vertices of the graph
     * @return vector containing the vertices of the graph that are connected
     */
    [[maybe_unused]] std::vector<Vertex *> bfs(std::vector<Vertex *>& vSet) const;

    std::vector<Vertex *> vertexSet;
    std::vector<Vehicle *> vehicleSet;
    std::vector<Package *> packages;
    std::vector<Package *> rejectedPackages;
    std::vector<Package *> cantDeliver;

    Vertex * garage;
    double distanceToCharge;
};

#endif  // E_STAFETAS_GRAPH_H

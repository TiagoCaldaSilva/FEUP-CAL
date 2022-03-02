#ifndef PROJETO_VEHICLE_H
#define PROJETO_VEHICLE_H

#include <algorithm>
#include <iostream>
#include "Package.h"
#include "../MutablePriorityQueue.h"

class Vehicle {
public:
    /**
     * @brief Vehicle's constructor
     * @param maxAut Vehicle max autonomy
     * @param garage First and last vertex of the path
     */
    Vehicle(double maxAut, Vertex * garage);
    /**
     * Vehicle's destructor
     */
    ~Vehicle();

    /**
     * @brief Get the current autonomy
     * @return Current autonomy value
     */
    double getCurrAut() const;
    /**
     * @brief Get the max autonomy
     * @return Max autonomy value
     */
    double getMaxAut() const;

    /**
     * @brief Get the set of vertices where it should deliver packages
     * @return Vector with all the vehicle's deliver vertices
     */
    std::vector<Package *> getToDeliver() const;
    /**
     * @brief Get the set of vertices where it delivered packages
     * @return Vector with all the vehicle's delivered vertices
     */
    std::vector<Package *> getDelivered() const;

    /**
     * @brief Get the current path of the vehicle
     * @return Set of vertices where the vehicle already has been
     */
    std::vector<Vertex *> getPath() const;

    /**
     * @brief Get the vertex where the vehicle is positioned
     * @return Current vertex value
     */
    Vertex * getCurrVertex();
    /**
     * @brief Set a new position to the vehicle
     * @param newCurrVertex Vehicle's new position
     */
    void setCurrVertex(Vertex * newCurrVertex);

    /**
     * @brief Increases the vehicle autonomy to maxAut - distToCharge
     * @param distToCharge Distance to the charging vertex
     */
    void charge(double distToCharge);
    /**
     * @brief Decrease the vehicle autonomy after it move forward
     * @param value Value to decrease
     */
    void decreaseAut(double value);

    /**
     * @brief Assigned a package to the vehicle
     * @param package Package that should be assigned to the vehicle
     */
    void pickUpPackage(Package * package);

    /**
     * @brief Add a vertex to the set of vertices where the vehicle already has been
     * @param v Vertex to add
     */
    void addVertexToPath(Vertex * v);

    /**
     * @brief Get the set of vertices which the vehicle must deliver
     * @return toDeliver value
     */
    std::vector<Vertex *> getDeliveryVertexSet() const;

    /**
     * @brief Remove a package from toDeliver and add to the delivered set of packages
     * @param where Vertex where the package should be delivered
     */
    void deliverPackage(Vertex * where);

    /**
     * @brief Get the set of points of interest
     * @return Vector with the set of points of interest
     */
    const std::vector<Vertex *> &getVertexSetToGo() const;
    /**
     * @brief Set the set of points of interest
     * @param vertexSetToGo Vector with the points of interest
     */
    void setVertexSetToGo(const std::vector<Vertex *> &vertexSetToGo);

    /**
     * @brief Reorder the vertex set
     */
    void refreshPOI();
    /**
     * @brief Get the nearest point of interest
     * @return Vertex corresponding to the nearest point of interest
     */
    Vertex * getNearestPOI();
    /**
     * @brief Remove the nearest point of interest
     * @return Vertex corresponding to the nearest point of interest
     */
    Vertex * removeNearestPOI();
    /**
     * @brief Get the distance of the current vertex to the nearest point of interest
     * @return Distance to the nearest point of interest
     */
    double getNearestDistancePOI();
    /**
     * @brief Remove a vertex from the set of points of interest
     * @param vertex Vertex to remove
     */
    void removeVertexPOI(Vertex * vertex);
    /**
     * @brief Add a vertex to the set of points of interest
     * @param vertexPOI Vertex to add
     */
    void addVertexPOI(Vertex * vertexPOI);

    /**
     * @brief Check if a vehicle has autonomy to move to a vertex
     * @param dest Vertex to move to
     * @param chargeDistance Distance to charge if needed
     * @return True if the vehicle has enough autonomy, false otherwise
     */
    bool checkEnoughAutonomy(Vertex * dest, double chargeDistance) const;
    /**
     * @brief Add the distance the vehicle has travelled to the counter
     * @param d Distance the vehicle has travelled
     */
    void addDistance(double d);

    /**
     * @brief Find a package by the delivery vertex
     * @param vertex Delivery vertex
     * @return True if the vehicle has a package with that vertex to deliver, false otherwise
     */
    bool findPackage(Vertex * vertex) const;

    /**
     * @brief Get the vertices mutable queue
     * @return Vertices mutable queue
     */
    MutablePriorityQueue getQueue() const;

    /**
     * @brief Add a vertex to the queue
     * @param vertex Vertex to add
     */
    void addVertexToQueue(Vertex * vertex);

    /**
     * @brief Print the information of the vehicle's delivered packages
     */
    void showDeliveredPackages() const;

private:
    double currAut;
    const double maxAut;
    double distanceTraveled;

    std::vector<Package *> toDeliver;
    std::vector<Package *> delivered;

    Vertex * currVertex;
    std::vector<Vertex *> path;
    std::vector<Vertex *> vertexSetToGo;
    MutablePriorityQueue queue;
};

#endif //PROJETO_VEHICLE_H

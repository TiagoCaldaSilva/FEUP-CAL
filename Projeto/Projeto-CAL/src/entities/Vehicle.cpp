#include "Vehicle.h"

Vehicle::Vehicle(double maxAut, Vertex * garage)
: maxAut(maxAut), currAut(maxAut), distanceTraveled(0.0), currVertex(garage)
{
    path.push_back(garage);
    auto poiCmp = [](Vertex * v1, Vertex * v2){ return v1->getDist() > v2->getDist(); };
    std::make_heap(vertexSetToGo.begin(), vertexSetToGo.end(), poiCmp);
}
Vehicle::~Vehicle()
{
    auto packageGC = [](Package * p){ delete p; };
    std::for_each(delivered.begin(), delivered.end(), packageGC);
    std::for_each(toDeliver.begin(), toDeliver.end(), packageGC);
}

double Vehicle::getCurrAut() const { return currAut; }
double Vehicle::getMaxAut() const { return maxAut; }

std::vector<Package *> Vehicle::getToDeliver() const { return toDeliver; }
std::vector<Package *> Vehicle::getDelivered() const { return delivered; }

std::vector<Vertex *> Vehicle::getPath() const { return path; }

void Vehicle::charge(double distToCharge) {
    std::cout << "Charging: " << currAut - distToCharge << " back to " << maxAut << std::endl;
    currAut = maxAut;
    decreaseAut(distToCharge);
    path.push_back(new Vertex(Vertex::Type::CHARGING));
    addDistance(2 * distToCharge);
}

void Vehicle::decreaseAut(double value) { currAut -= value; }

void Vehicle::pickUpPackage(Package * package)
{
    toDeliver.push_back(package);
}

void Vehicle::deliverPackage(Vertex * where)
{
    for (int i = 0; i < toDeliver.size(); ++i)
    {
        if (*toDeliver[i]->getDelivery() == *where)
        {
            Vertex * newDelivery = new Vertex(where);
            toDeliver[i]->setDelivery(newDelivery);
            delivered.push_back(toDeliver[i]);
            toDeliver.erase(toDeliver.begin() + i);
            break;
        }
    }
}

Vertex * Vehicle::getCurrVertex() { return currVertex; }
void Vehicle::setCurrVertex(Vertex * newCurrVertex) { currVertex = newCurrVertex; }
void Vehicle::addVertexToPath(Vertex * v) {
    double distance = 0;
    if(!path.empty()) {
        if (path[path.size() - 1]->getType() != Vertex::Type::CHARGING)
            distance = v->getDist() - path[path.size() - 1]->getDist();
        else
            distance = v->getDist() - path[path.size() - 2]->getDist();
        addDistance(distance);
    }

    auto newVertex = new Vertex(v);

    path.push_back(newVertex);
    decreaseAut(distance);
    setCurrVertex(v);
}

std::vector<Vertex *> Vehicle::getDeliveryVertexSet() const
{
    std::vector<Vertex *> deliverySet;
    for (Package * package : toDeliver)
        deliverySet.push_back(package->getDelivery());
    return deliverySet;
}

const std::vector<Vertex *> &Vehicle::getVertexSetToGo() const { return vertexSetToGo; }
void Vehicle::setVertexSetToGo(const std::vector<Vertex *> &nextPOIs)
{
    vertexSetToGo = nextPOIs;
    auto poiCmp = [](Vertex * v1, Vertex * v2){ return v1->getDist() > v2->getDist(); };
    std::make_heap(vertexSetToGo.begin(),vertexSetToGo.end(), poiCmp);
}

void Vehicle::refreshPOI()
{
    auto poiCmp = [](Vertex *v1, Vertex *v2) { return v1->getDist() > v2->getDist(); };
    std::make_heap(vertexSetToGo.begin(), vertexSetToGo.end(), poiCmp);
}
Vertex * Vehicle::getNearestPOI() {
    Vertex * vertex = removeNearestPOI();
    addVertexPOI(vertex);
    return vertex;
}
double Vehicle::getNearestDistancePOI() { return getNearestPOI()->getDist(); }

Vertex * Vehicle::removeNearestPOI() {
    auto poiCmp = [](Vertex * v1, Vertex * v2){ return v1->getDist() > v2->getDist(); };
    std::pop_heap(vertexSetToGo.begin(), vertexSetToGo.end(), poiCmp);
    Vertex * nearestVertex = vertexSetToGo.back();
    vertexSetToGo.pop_back();
    return nearestVertex;
}

void Vehicle::removeVertexPOI(Vertex * vertex)
{
    auto removeVertex = [vertex](Vertex * v1){ return *v1 == *vertex; };
    vertexSetToGo.erase(std::remove_if(vertexSetToGo.begin(), vertexSetToGo.end(), removeVertex), vertexSetToGo.end());
}

void Vehicle::addVertexPOI(Vertex * vertexPOI)
{
    vertexSetToGo.push_back(vertexPOI);
    auto poiCmp = [](Vertex * v1, Vertex * v2){ return v1->getDist() > v2->getDist(); };
    std::push_heap(vertexSetToGo.begin(), vertexSetToGo.end(), poiCmp);
}


bool Vehicle::checkEnoughAutonomy(Vertex * d, double chargeDist) const { return d->getDist() <= (currAut - chargeDist); }
inline void Vehicle::addDistance(double d) { distanceTraveled += d; }

bool Vehicle::findPackage(Vertex * v) const {
    auto checkVertex = [v](Package * p){ return *p->getDelivery() == *v; };
    return std::any_of(toDeliver.begin(), toDeliver.end(), checkVertex);
}

MutablePriorityQueue Vehicle::getQueue() const { return queue; }
void Vehicle::addVertexToQueue(Vertex * v) { queue.insert(v); }

void Vehicle::showDeliveredPackages() const{
    std::cout << "Distance traveled = " << distanceTraveled << std::endl;
    auto print = [](Package * p) { std::cout << *p << std::endl; };
    std::for_each(delivered.begin(), delivered.end(), print);
}

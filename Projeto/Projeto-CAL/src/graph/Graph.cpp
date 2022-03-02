#include "Graph.h"

Graph::~Graph()
{
    for (Vertex * vertex : vertexSet)
    {
        for (Edge * edge : vertex->getAdj())
            delete edge;
        delete vertex;
    }

    for (Vehicle * vehicle : vehicleSet)
        delete vehicle;
}

void Graph::showResult(GraphDrawer& gd, const std::vector<Edge *>& edges) const { gd.drawGraph(vehicleSet, vertexSet, edges); }

/* -------- ALGORITHMS IMPLEMENTATION -------- */
void Graph::run(const Parameters& p)
{
    if (p.packages.empty() || p.vertexSet.empty() || p.edges.empty() || p.vertexSet.empty())
        throw std::invalid_argument("Invalid Parameters - cannot start the Algorithm");
    initialize(p);

    if(!packages.empty()) {
        const bool singleVehicle = vehicleSet.size() == 1;
        if (!singleVehicle)
            floydWarshallShortestPath();

        proceed(singleVehicle, p.orderByDistance);

        auto print = [](Vehicle *v)
        {
            std::cout << "Vehicle" << std::endl;
            for (auto vertex: v->getPath())
                std::cout << *vertex << std::endl;
            v->showDeliveredPackages();
            std::cout << std::endl;
        };
        std::for_each(vehicleSet.begin(), vehicleSet.end(), print);
    }

    if (!rejectedPackages.empty())
    {
        std::cout << "The vehicles aren't able to deliver the following packages:" << std::endl;
        for (Package * package: rejectedPackages)
            std::cout << *package << std::endl;
    }
}

void Graph::initialize(const Parameters& p) {
    vertexSet = p.vertexSet;

    distanceToCharge = p.distanceToCharge;

    garage = p.garage;
    if (garage == nullptr)
        throw std::invalid_argument("Invalid Parameters - cannot start the Algorithm");

    vehicleSet = std::vector<Vehicle *> (p.nV);
    auto setUpVehicle = [&p](){ auto v = new Vehicle(p.autonomy, p.garage); return v; };
    std::generate(vehicleSet.begin(), vehicleSet.end(), setUpVehicle);

    for (Vertex * v : vertexSet)
        if (v->getType() == Vertex::Type::PICKUP)
            for (Vehicle * vehicle : vehicleSet)
                vehicle->addVertexToQueue(v);

    for (Package * package: p.packages)
    {
        (std::find(vertexSet.begin(), vertexSet.end(), package->getPickUp()) != vertexSet.end()
         && std::find(vertexSet.begin(), vertexSet.end(), package->getDelivery()) != vertexSet.end()) ?
        packages.push_back(package) : cantDeliver.push_back(package);
    }

    for (Edge * edge: p.edges)
        edge->getOrig()->addEdge(edge);

    std::vector<Vertex *> connectedVertices = bfs(vertexSet);
    for(auto it = packages.begin(); it != packages.end(); it++) {
        auto pickUpInConnectedVertices = [it](Vertex * v1) { return *((*it)->getPickUp()) == *v1; };
        auto deliveryInConnectedVertices = [it](Vertex * v1) { return *((*it)->getDelivery()) == *v1; };
        auto pickUpIt = std::find_if(connectedVertices.begin(), connectedVertices.end(), pickUpInConnectedVertices);
        auto deliveryIt = std::find_if(connectedVertices.begin(), connectedVertices.end(), deliveryInConnectedVertices);
        if(pickUpIt == connectedVertices.end() || deliveryIt == connectedVertices.end()) {
            (*it)->getPickUp()->setType(Vertex::Type::INTERSECTION);
            (*it)->getDelivery()->setType(Vertex::Type::INTERSECTION);
            rejectedPackages.push_back(*it);
            packages.erase(it);
            --it;
        }
    }
}

void Graph::proceed(const bool singleVehicle, const bool orderByDistance)
{
    std::vector<Vertex *> vertexSetToGo;
    for (Vertex * vertex : vertexSet)
        if (vertex->getType() == Vertex::Type::PICKUP)
            vertexSetToGo.push_back(vertex);

    for (Vehicle * vehicle : vehicleSet)
        vehicle->setVertexSetToGo(vertexSetToGo);

    if (!singleVehicle) {
        refreshDist(garage);
        if (!orderByDistance) {
            int currPackage = 0;
            for (int i = 0; i < std::min(vehicleSet.size(), packages.size()); i++) {
                Package * currP = packages[currPackage];
                std::vector<Vertex *> currPath = getFloydWarshallPath(vehicleSet[i]->getCurrVertex(),
                                                                      currP->getPickUp());
                for (Vertex *vToGo : currPath) {
                    goForward(vToGo, vehicleSet[i]);

                    if (vToGo->getType() == Vertex::Type::PICKUP) {
                        vehicleSet[i]->pickUpPackage(findPackage(vToGo));
                        vehicleSet[i]->addVertexPOI(findPackage(vToGo)->getDelivery());

                        auto deleteVertex = [vToGo](Vehicle *v) { v->removeVertexPOI(vToGo); };
                        std::for_each(vehicleSet.begin(), vehicleSet.end(), deleteVertex);

                        break;
                    }
                }
                currPackage++;
            }
        }
    }

    Vehicle * currVehicle;
    bool finished;
    bool firstIter = true;
    do {
        std::vector<Vertex *> currPath;
        auto refreshHeaps = [](Vehicle * v){ v->refreshPOI(); };
        std::for_each(vehicleSet.begin(), vehicleSet.end(), refreshHeaps);

        currVehicle = firstIter ? vehicleSet.front() : refreshCurrentVehicle();
        firstIter = false;

        if (singleVehicle) {
            dijkstraShortestPath(vertexSet, currVehicle->getCurrVertex());
            if(!(*currVehicle->getCurrVertex() == *currVehicle->getNearestPOI()))
                currPath = getDijkstraPath(currVehicle->getCurrVertex(),  currVehicle->getNearestPOI());
        } else {
            currPath = getFloydWarshallPath(currVehicle->getCurrVertex(), currVehicle->getNearestPOI());
        }

        for (Vertex * vToGo : currPath) {
            goForward(vToGo, currVehicle);

            auto findVertex = [vToGo](Vertex * v){ return *v == *vToGo; };
            std::vector<Vertex *> currVertexSetToGo = currVehicle->getVertexSetToGo();
            if ((vToGo->getType() == Vertex::Type::PICKUP) &&
                    std::find_if(currVertexSetToGo.begin(), currVertexSetToGo.end(), findVertex) != currVertexSetToGo.end()) {

                currVehicle->pickUpPackage(findPackage(vToGo));
                currVehicle->addVertexPOI(findPackage(vToGo)->getDelivery());

                auto deleteVertex = [vToGo](Vehicle * v) { v->removeVertexPOI(vToGo); };
                std::for_each(vehicleSet.begin(), vehicleSet.end(), deleteVertex);

            } else if ((vToGo->getType() == Vertex::Type::DELIVERY) &&
                    std::find_if(currVertexSetToGo.begin(), currVertexSetToGo.end(), findVertex) != currVertexSetToGo.end()) {
                if (currVehicle->findPackage(vToGo)) {
                    currVehicle->deliverPackage(vToGo);
                    currVehicle->removeNearestPOI();
                }
            } else {
                if(currVehicle->getPath().back()->getType() != Vertex::Type::GARAGE)
                    currVehicle->getPath().back()->setType(Vertex::Type::INTERSECTION);
            }
        }

        if(!singleVehicle) refreshDist(currVehicle->getCurrVertex());

        auto poiEmpty = [](Vehicle * v){ return v->getVertexSetToGo().empty(); };
        finished = std::all_of(vehicleSet.begin(), vehicleSet.end(), poiEmpty);
    } while (!finished);

    if (singleVehicle) {
        dijkstraShortestPath(vertexSet, currVehicle->getCurrVertex());
        currVehicle->setVertexSetToGo(getDijkstraPath(currVehicle->getCurrVertex(), garage));
    } else {
        for (Vehicle * v : vehicleSet)
            v->setVertexSetToGo(getFloydWarshallPath(v->getCurrVertex(), garage));
    }

    /* All the vehicles must return to the garage */
    for (Vehicle * v : vehicleSet)
        if(!(*(v->getCurrVertex()) == *garage))
            for (Vertex *vToGo : v->getVertexSetToGo()) {
                goForward(vToGo, v);
                if(currVehicle->getPath().back()->getType() != Vertex::Type::GARAGE)
                    currVehicle->getPath().back()->setType(Vertex::Type::INTERSECTION);
            }
}

Vehicle * Graph::refreshCurrentVehicle() const {
    Vehicle * nextVehicle = nullptr;
    double minDistance = INF;

    for (Vehicle * vehicle : vehicleSet) {
        if(!vehicle->getVertexSetToGo().empty())
            if (vehicle->getNearestDistancePOI() < minDistance){
                minDistance = vehicle->getNearestDistancePOI();
                nextVehicle = vehicle;
            }
    }
    return nextVehicle;
}

void Graph::goForward(Vertex * vToGo, Vehicle * vehicle) const
{
    if (!vehicle->checkEnoughAutonomy(vToGo, distanceToCharge))
        vehicle->charge(distanceToCharge);
    vehicle->addVertexToPath(vToGo);
}

Package * Graph::findPackage(Vertex * v) const
{
    auto find = [v](Package * p){ return *p->getPickUp() == *v; };
    auto returnIt = std::find_if(packages.begin(), packages.end(), find);
    return returnIt == packages.end() ? nullptr : *returnIt;
}


/* -------- ALGORITHMS ROUTINES -------- */
void Graph::initializeSingleSource(std::vector<Vertex *>& vSet, Vertex * s)
{
    auto setVertex = [](Vertex * v) { v->setDist(); v->setPath(); };
    std::for_each(vSet.begin(), vSet.end(), setVertex);
    s->setDist(0.0);
}
void Graph::relax(Vertex * u, Vertex * v, double w)
{
    if (v->getDist() > u->getDist() + w)
    {
        v->setDist(u->getDist() + w);
        v->setPath(u);
    }
}

void Graph::dijkstraShortestPath(std::vector<Vertex *>& vSet, Vertex * s)
{
    initializeSingleSource(vSet, s);

    MutablePriorityQueue Q;
    Q.insert(s);

    while (!Q.empty())
    {
        Vertex * u = Q.extractMin();
        for (Edge * edge : u->getAdj())
        {
            Vertex * v = edge->getDest();
            double oldDist = v->getDist();
            if (oldDist > u->getDist() + edge->getWeight() &&
                    edge->getWeight() <= vehicleSet[0]->getMaxAut() - distanceToCharge)
            {
                v->setDist(u->getDist() + edge->getWeight());
                v->setPath(u);

                (oldDist == INF) ? Q.insert(v) : Q.decreaseKey(v);
            }
        }
    }
}
std::vector<Vertex *> Graph::getDijkstraPath(Vertex * source, Vertex * dest)
{
    std::vector<Vertex *> result;
    Vertex * temp = dest;
    do {
        result.insert(result.begin(), temp);
        temp = temp->getPath();
    } while (temp != source);

    return result;
}

bool Graph::bellmanFordShortestPath(std::vector<Vertex *>& vSet, Vertex * s)
{
    initializeSingleSource(vSet, s);

    for (std::size_t i = 1; i < vSet.size(); ++i)
        for (Vertex *u: vSet)
            for (Edge *e : u->getAdj())
                relax(u, e->getDest(), e->getWeight());

    for (Vertex * u : vSet)
        for (Edge * e : u->getAdj())
            if (e->getDest()->getDist() > u->getDist() + e->getWeight())
                return false;
    return true;
}

void Graph::floydWarshallShortestPath()
{
    const std::size_t nVert = vertexSet.size();
    dist = std::vector< std::vector<double> >(nVert, std::vector<double>(nVert, INF));
    prevVertex = std::vector< std::vector<int> >(nVert, std::vector<int>(nVert, -1));


    for (std::size_t i = 0; i < nVert; ++i)
    {
        for (std::size_t j = 0; j < nVert; ++j)
        {
            if(i == j) dist[i][j] = 0;
            else {
                for (Edge * e : vertexSet[i]->getAdj())
                {
                    if (vertexSet[j]->getId() == e->getDest()->getId())
                    {
                        dist[i][j] = e->getWeight();
                        break;
                    }
                }

            }

        }
    }

    for(int i = 0; i < vertexSet.size(); ++i) {
        for(int j = 0; j < vertexSet.size(); ++j) {
            if(dist[i][j] != INF) {
                prevVertex[i][j] = vertexSet[i]->getId();
            }
        }
    }

    for (std::size_t k = 0; k < nVert; ++k)
    {
        for (std::size_t i = 0; i < nVert; ++i)
        {
            for (std::size_t j = 0; j < nVert; ++j)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    prevVertex[i][j] = prevVertex[k][j];
                }
            }
        }
    }
}

std::vector<Vertex *> Graph::getFloydWarshallPath(Vertex * s, Vertex * d) const{
    std::vector<Vertex *> res;

    std::stack<Vertex *> stack;
    Vertex * tmp = d;
    do {
        stack.push(tmp);
        tmp = vertexSet[prevVertex[s->getId()][tmp->getId()]];
    } while(!(*s == *tmp));

    while (!stack.empty()){
        res.push_back(stack.top());
        stack.pop();
    }
    return res;
}

void Graph::refreshDist(Vertex * s) {
    for(auto vertex : vertexSet) {
        vertex->setDist(dist[s->getId()][vertex->getId()]);
    }
}

/*
 * TODO: Make a new list to copy all the vertices and then and a new vertex and a new Edge to every vertex
 * then use the right matrix and fill the values.
 * Btw, I don't know if i can even do this :sob:
 */
void Graph::johnsonShortestPath(std::vector<Vertex *>& vSet) {
    const std::size_t nV = vSet.size();
    std::vector<Vertex *> nVS;
    /* Dummy vector with connection to all the other ones by a 0 weight edge */
    nVS.push_back(new Vertex(Vertex::Type::INTERSECTION));
    for (Vertex * vertex : vSet)
    {
        nVS.push_back(new Vertex(vertex));
        Edge * edge = new Edge(UINT32_MAX, 0.0, nVS.front(), nVS.back());
        nVS.front()->addEdge(edge);
    }

    if (!bellmanFordShortestPath(nVS, nVS[0]))
        throw std::invalid_argument("Input has negative cycles");

    auto setHV = [](Vertex * v){ v->setH(v->getDist()); };
    std::for_each(nVS.begin(), nVS.end(), setHV);

    for (Vertex * v : nVS)
        for (Edge *e : v->getAdj())
            e->setWeight(e->getWeight() + e->getDest()->getH() - v->getH());

    /* Garbage Collection */
    auto edgeGC = [](Edge * e){ delete e; };
    std::for_each(nVS[0]->getAdj().begin(), nVS[0]->getAdj().end(), edgeGC);
    delete nVS.front();
    nVS.erase(nVS.begin());

    dist = std::vector< std::vector<double> > (nV, std::vector<double>(nV, INF));
    prevVertex = std::vector< std::vector<int> > (nV, std::vector<int>(nV, -1));
    for (std::size_t i = 0; i < nVS.size(); ++i)
    {
        dijkstraShortestPath(nVS, nVS[i]);
        for (std::size_t j = 0; j < nVS.size(); ++j)
        {
            dist[i][j] = nVS[i]->getDist() + nVS[j]->getH() - nVS[i]->getH();
            prevVertex[i][j] = static_cast<int>(nVS[j]->getPath()->getId());
        }
    }

    auto vertexGarbageCollector = [](Vertex * v){ delete v; };
    std::for_each(nVS.begin(), nVS.end(), vertexGarbageCollector);
}

std::vector<Vertex *> Graph::bfs(std::vector<Vertex *>& vSet) const
{
    auto setVisited = [](Vertex * v){ v->setVisit(false); };
    std::for_each(vSet.begin(), vSet.end(), setVisited);

    std::vector<Vertex *> res;
    if (!vSet.empty())
    {
        std::queue<Vertex *> Q;
        Q.push(vSet.front());
        while (!Q.empty())
        {
            Vertex *v = Q.front();
            Q.pop();
            v->setVisit(true);

            for (Edge *e : v->getAdj())
                if (!e->getDest()->isVisited() &&
                    e->getWeight() <= vehicleSet[0]->getMaxAut() - 2*distanceToCharge)
                        Q.push(e->getDest());

            res.push_back(v);
        }
    }
    return res;
}

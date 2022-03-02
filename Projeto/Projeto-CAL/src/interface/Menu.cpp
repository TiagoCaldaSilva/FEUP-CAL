#include "Menu.h"

void Menu::displayPackages() const
{
    std::size_t index = 0;
    for (const Package& aPackage : allPackages)
    {
        std::cout << index << ". " << aPackage << std::endl;
        ++index;
    }
}

void Menu::displayVertexSet(bool displayDisabledVertices) const
{
    if (displayDisabledVertices)
        for (Vertex *v : menuVertexSet)
            std::cout << '\t' << *v << std::endl;
    else {
        unsigned int counter = 0;
        for (Vertex *v : menuVertexSet) {
            if (v->isEnabled()) {
                std::cout << '\t' << counter << ". " << *v << std::endl;
                counter++;
            }
        }
    }
}
void Menu::displayEdgeSet() const
{
    for (Edge *e : menuEdgeSet)
        std::cout << '\t' << *e << std::endl;
}



void Menu::start(GraphDrawer& graphDrawer) {
    unsigned int option;
    do {
        std::cout << "Welcome to E-Stafetas interface" << std::endl << std::endl;
        std::cout << "What do you want to do?" << std::endl;
        std::cout << "\t1. Packages" << std::endl;
        std::cout << "\t2. Draft the route" << std::endl;
        std::cout << "\t3. Exit" << std::endl;

        std::cin >> option;
        switch (option) {
            case 1: packages(); break;
            case 2: route(graphDrawer); break;
            case 3: return;
            default: std::cerr << "Invalid input, please try again." << std::endl;
        }
    } while (true);
}

void Menu::packages() {
    std::vector<Vertex *> vS = getVertexSet();
    unsigned int option;

    do {
        std::cout << "What do you want to do?" << std::endl;
        std::cout << "\t1. Display packages" << std::endl;
        std::cout << "\t2. Add package" << std::endl;
        std::cout << "\t3. Remove package" << std::endl;
        std::cout << "\t4. Edit package" << std::endl;
        std::cout << "\t5. Back" << std::endl;

        std::cin >> option;

        switch (option) {
            case 1: displayPackages(); break;
            case 2:
                displayVertexSet(false);

                try {
                    std::cout << "Which vertex is the pick up one?" << std::endl;
                    std::size_t vertexPickupIndex;
                    std::cin >> vertexPickupIndex;

                    if (vS.at(vertexPickupIndex)->getType() != Vertex::Type::INTERSECTION)
                        throw std::invalid_argument("This vertex can't be a pick up point!");
                    else
                        vS.at(vertexPickupIndex)->setType(Vertex::Type::PICKUP);

                    std::cout << "Which vertex is the delivery one?" << std::endl;
                    std::size_t vertexDeliveryIndex;
                    std::cin >> vertexDeliveryIndex;

                    if (vS.at(vertexDeliveryIndex)->getType() != Vertex::Type::INTERSECTION) {
                        vS.at(vertexPickupIndex)->setType(Vertex::Type::INTERSECTION);
                        throw std::invalid_argument("This vertex can't be a delivery point!");
                    } else {
                        vS.at(vertexDeliveryIndex)->setType(Vertex::Type::DELIVERY);
                    }

                    allPackages.emplace_back(vS.at(vertexPickupIndex), vS.at(vertexDeliveryIndex));
                } catch (std::out_of_range& outOfRange) {
                    std::cerr << "Invalid Input!" << std::endl;
                } catch (std::invalid_argument& invalid_argument) {
                    std::cerr << invalid_argument.what() << std::endl;
                }
                break;
            case 3:
                displayPackages();

                std::cout << "Which package do you want to remove?" << std::endl;
                ssize_t packageIndex;
                std::cin >> packageIndex;

                try {
                    Package aPackage = allPackages.at(packageIndex);
                    aPackage.getPickUp()->setType(Vertex::Type::INTERSECTION);
                    aPackage.getDelivery()->setType(Vertex::Type::INTERSECTION);
                    allPackages.erase(allPackages.begin() + packageIndex);
                } catch (std::out_of_range& outOfRange) {
                    std::cerr << "Invalid Input!" << std::endl;
                }
                break;
            case 4:
                displayPackages();
                std::cout << "Which package do you want to edit?" << std::endl;
                std::size_t rmPackageIndex;
                std::cin >> rmPackageIndex;

                try {
                    if (allPackages.size() <= rmPackageIndex)
                        throw std::invalid_argument("Invalid Package id.");

                    displayVertexSet(false);
                    Vertex * pickUp;
                    Vertex * delivery;

                    std::cout << "Which vertex is the pick up one?" << std::endl;
                    std::size_t vertexPickupIndex;
                    std::cin >> vertexPickupIndex;

                    pickUp = allPackages.at(rmPackageIndex).getPickUp();
                    if (!(vS.at(vertexPickupIndex)->getType() == Vertex::Type::INTERSECTION) &&
                        !(*vS.at(vertexPickupIndex) == *allPackages.at(rmPackageIndex).getPickUp()))
                        throw std::invalid_argument("Invalid Vertex Type - not Vertex::Type::INTERSECTION");

                    std::cout << "Which vertex is the delivery one?" << std::endl;
                    std::size_t vertexDeliveryIndex;
                    std::cin >> vertexDeliveryIndex;

                    delivery = allPackages.at(rmPackageIndex).getDelivery();
                    if (!(vS.at(vertexDeliveryIndex)->getType() == Vertex::Type::INTERSECTION) &&
                        !(*vS.at(vertexDeliveryIndex) == *allPackages.at(rmPackageIndex).getDelivery()))
                        throw std::invalid_argument("Invalid Vertex Type - not Vertex::Type::INTERSECTION");

                    pickUp->setType(Vertex::Type::INTERSECTION);
                    delivery->setType(Vertex::Type::INTERSECTION);

                    vS.at(vertexPickupIndex)->setType(Vertex::Type::PICKUP);
                    vS.at(vertexDeliveryIndex)->setType(Vertex::Type::DELIVERY);

                    allPackages.at(rmPackageIndex).setPickUp(vS.at(vertexPickupIndex));
                    allPackages.at(rmPackageIndex).setDelivery(vS.at(vertexDeliveryIndex));

                } catch (std::out_of_range& outOfRange) {
                    std::cerr << "Invalid Input!" << std::endl;
                } catch (std::invalid_argument& invalidArgument) {
                    std::cerr << invalidArgument.what() << std::endl;
                }
                break;
            case 5: return;
            default: std::cerr << "Invalid input, please try again." << std::endl;
        }
    } while (true);
}


void Menu::route(GraphDrawer& graphDrawer) {
    std::vector<Vertex *> vS = getVertexSet();
    unsigned int option;

    do {
        std::cout << "What do you want to do?" << std::endl;
        std::cout << "\t1. Display vertex and edges" << std::endl;
        std::cout << "\t2. Enable/Disable vertex" << std::endl;
        std::cout << "\t3. Enable/Disable edge" << std::endl;
        std::cout << "\t4. Edit an edge" << std::endl;
        std::cout << "\t5. Run" << std::endl;
        std::cout << "\t6. Back" << std::endl;

        std::cin >> option;
        switch (option) {
            case 1:
                std::cout << "\t---------- Vertex ----------" << std::endl;
                displayVertexSet(true);
                std::cout << "\t----------- Edge -----------" << std::endl;
                displayEdgeSet();
                break;
            case 2:
                displayVertexSet(true);
                std::cout << "Which vertex do you want to enable/disable?" << std::endl;
                unsigned int vertexIndex;
                std::cin >> vertexIndex;

                try {
                    menuVertexSet.at(vertexIndex)->changeEnable();
                    if (!menuVertexSet.at(vertexIndex)->isEnabled())
                        disableVertex(menuVertexSet.at(vertexIndex));
                } catch (std::out_of_range& outOfRange) {
                    std::cerr << "Vertex not found!" << std::endl;
                }
                break;
            case 3:
                displayEdgeSet();
                std::cout << "Which edge do you want to enable/disable?" << std::endl;
                unsigned int edgeIndex;
                std::cin >> edgeIndex;

                try {
                    if (!menuEdgeSet.at(edgeIndex)->canBeEnabled())
                        std::cerr << "That edge can't be enabled" << std::endl;
                    else
                        menuEdgeSet.at(edgeIndex)->changeEnable();
                } catch (std::out_of_range& outOfRange) {
                    std::cerr << "Edge not found!" << std::endl;
                }
                break;
            case 4:
                displayEdgeSet();
                std::cout << "Which edge do you want to edit?" << std::endl;
                unsigned int edgeEditIndex;
                std::cin >> edgeEditIndex;

                std::cout << "What is the new weight of that edge?" << std::endl;
                double edgeWeight;
                std::cin >> edgeWeight;

                try {
                    menuEdgeSet.at(edgeEditIndex)->setWeight(edgeWeight);
                } catch (std::out_of_range& outOfRange) {
                    std::cerr << "Edge not found!" << std::endl;
                }
                break;
            case 5: {
                Parameters p;
                std::cout << "How many cars do you want to use?" << std::endl;
                std::cin >> p.nV;

                std::cout << "What is the max autonomy of each car?" << std::endl;
                std::cin >> p.autonomy;

                std::cout << "What is the distance to charge on each vertex?" << std::endl;
                std::cin >> p.distanceToCharge;

                bool validInput;
                do {
                    validInput = true;
                    std::cout << "Would you rather prioritize the minimization of the number of vehicles used over the minimization of the total distance travelled? [Y/N]" << std::endl;
                    char optionChosen;
                    std::cin >> optionChosen;

                    if (optionChosen == 'Y' || optionChosen == 'y')
                        p.orderByDistance = true;
                    else if (optionChosen == 'N' || optionChosen == 'n')
                        p.orderByDistance = false;
                    else {
                        std::cerr << "Invalid input!" << std::endl;
                        validInput = false;
                    }
                } while (!validInput);

                p.vertexSet = vS;
                p.edges = getEdgeSet();

                for (const Package& aPackage : allPackages)
                    p.packages.push_back(new Package(aPackage));

                displayVertexSet(false);
                std::cout << "Which vertex is the garage?" << std::endl;
                unsigned int garageVertex;
                std::cin >> garageVertex;

                try {
                    if (vS.at(garageVertex)->getType() != Vertex::INTERSECTION)
                        std::cerr << "Vertex can't be the garage!" << std::endl;
                    else {
                        vS.at(garageVertex)->setType(Vertex::Type::GARAGE);
                        p.garage = vS.at(garageVertex);
                    }
                } catch (std::out_of_range& outOfRange) {
                    std::cerr << "Invalid Input!" << std::endl;
                }

                try {
                    auto startTime = std::chrono::system_clock::now();
                    graph.run(p);
                    auto endTime = std::chrono::system_clock::now();

                    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
                    std::cout << "Elapsed Time was: " << elapsedTime.count() << " ms." << std::endl;

                    graph.showResult(graphDrawer, menuEdgeSet);

                } catch (std::invalid_argument& invalidArgument) {
                    std::cerr << invalidArgument.what() << std::endl;
                }

                break; }
            case 6: return;
            default: std::cerr << "Invalid input, please try again." << std::endl;
        }
    } while (true);
}

std::vector<Edge *> Menu::getEdgeSet() const
{
    std::vector<Edge *> enabledEdges;
    auto enabledEdge = [](Edge * e){ return e->isEnabled(); };
    std::copy_if(menuEdgeSet.begin(), menuEdgeSet.end(), std::back_inserter(enabledEdges), enabledEdge);
    return enabledEdges;
}

std::vector<Vertex *>& Menu::getAllVertexSet() { return menuVertexSet; }
std::vector<Vertex *> Menu::getVertexSet() const
{
    std::vector<Vertex *> enabledVertices;
    auto enabledVertex = [](Vertex * v){ return v->isEnabled(); };
    std::copy_if(menuVertexSet.begin(), menuVertexSet.end(), std::back_inserter(enabledVertices), enabledVertex);
    return enabledVertices;
}
void Menu::disableVertex(Vertex * v)
{
    auto disableEdge = [v](Edge * edge) {
        if(*(edge->getOrig()) == *v || *(edge->getDest()) == *v)
            edge->setEnabled(false);
    };
    std::for_each(menuEdgeSet.begin(), menuEdgeSet.end(), disableEdge);

    auto removePackage = [v](const Package& p){ return *p.getDelivery() == *v || *p.getPickUp() == *v; };
    auto packageIt = std::remove_if(allPackages.begin(), allPackages.end(), removePackage);
    allPackages.erase(packageIt, allPackages.end());
}

void Menu::addVertex(Vertex * v) { menuVertexSet.push_back(v); }
void Menu::addEdge(Edge * edge) { menuEdgeSet.push_back(edge); }

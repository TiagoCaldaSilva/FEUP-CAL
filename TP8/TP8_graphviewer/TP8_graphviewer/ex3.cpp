#include "graphviewer.h"
#include <iostream>
#include <fstream>
#include <sstream>      // std::stringstream

using namespace std;
using Node = GraphViewer::Node;
using Edge = GraphViewer::Edge;

void ex3() {
    // TODO
    GraphViewer gv;
    gv.setCenter(sf::Vector2f(300, 300));
    gv.createWindow(600, 600);

    int number, id, x, y, from, to;
    ifstream in;
    string text;
    stringstream  ss;

    in.open("../TP8_graphviewer/resources/map1/nodes.txt");
    if(!in.is_open()) {
        std::cout << "Error 1" << std::endl;
        exit(1);
    }
    getline(in, text);
    ss << text;
    ss >> number;
    ss.clear();
    for(int i = 0; i < number; i++) {
        getline(in, text);
        ss << text;
        ss >> id >> x >> y;

        gv.addNode(id, sf::Vector2f(x, y));
        ss.clear();
    }
    in.close();

    in.open("../TP8_graphviewer/resources/map1/edges.txt");
    if(!in.is_open()) {
        std::cout << "Error 2" << std::endl;
        exit(1);
    }
    getline(in, text);
    ss >> number;
    ss.clear();
    for(int i = 0; i < number; i++) {
        getline(in, text);
        ss << text;
        ss >> id >> from >> to;
        Node& nodeF = gv.getNode(from);
        Node& nodeT = gv.getNode(to);
        gv.addEdge(id, nodeF, nodeT, Edge::DIRECTED);
        ss.clear();
    }
    in.close();

    gv.join();

}


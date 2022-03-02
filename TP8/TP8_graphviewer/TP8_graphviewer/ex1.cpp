#include "graphviewer.h"

using namespace std;
using Node = GraphViewer::Node;
using Edge = GraphViewer::Edge;

void ex1() {
    // TODO
    /** Instantiate GraphViewer */
    GraphViewer gv;
    /** Set coordinates of window center */
    gv.setCenter(sf::Vector2f(300, 300));
    /** Create window */
    gv.createWindow(600, 600);
    /** Create node 0 */
    Node &node0 = gv.addNode(0, sf::Vector2f(200, 300));
    node0.setColor(GraphViewer::BLUE);
    node0.setLabel("Viana do Castelo");
    /** Create node 1 */
    Node &node1 = gv.addNode(1, sf::Vector2f(400, 300));
    node1.setColor(GraphViewer::BLUE);
    /** Create edge 0 */
    Edge &edge0 = gv.addEdge(0, node0, node1, Edge::UNDIRECTED);
    edge0.setColor(GraphViewer::BLACK);
    /** Remove node 1 */
    gv.removeNode(1);
    /** Create node 2 */
    Node &node2 = gv.addNode(2, sf::Vector2f(500, 300));
    node2.setColor(GraphViewer::GREEN);
    node2.setLabel("Porto");
    /** Create edge 1 */
    Edge &edge1 = gv.addEdge(1, node0, node2, Edge::UNDIRECTED);
    edge1.setLabel("A28");
    /** Make all edges yellow */
    for(Edge * edge: gv.getEdges())
        edge->setColor(GraphViewer::YELLOW);
    /** Set a background */
    gv.setBackground("../TP8_graphviewer/resources/background.png");
    /** Join viewer thread (blocks till window closed) */
    gv.join();
}

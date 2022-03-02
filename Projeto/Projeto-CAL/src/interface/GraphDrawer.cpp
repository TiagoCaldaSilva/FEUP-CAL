#include <zconf.h>
#include "GraphDrawer.h"

GraphDrawer::GraphDrawer(GraphDrawer::windowSize wSize, GraphDrawer::windowPosition wCenter) : winSize(wSize), winCenter(wCenter)
{
    graphViewerContext = new GraphViewer();
}

GraphDrawer::~GraphDrawer()
{
    delete graphViewerContext;
}

void GraphDrawer::reset()
{
    graphViewerContext->closeWindow();

    delete graphViewerContext;
    graphViewerContext = new GraphViewer();
    graphViewerContext->setCenter(sf::Vector2f(winCenter.width, winCenter.height));
}

void GraphDrawer::drawGraph(const std::vector<Vehicle *>& vSet, const std::vector<Vertex *>& vertexSet, const std::vector<Edge *>& edges)
{
    GraphViewer gv;

    gv.setBackgroundColor(GraphViewer::BLACK);

    for (const Vertex * v : vertexSet)
{
        sf::Vector2f vertexPosition(v->getVertexPosition().x, v->getVertexPosition().y);
        gv.addNode(v->getId(), vertexPosition);
    }

    unsigned int counter = 0;
/*
    std::vector<std::pair<unsigned int, std::pair<GraphViewer::Node, GraphViewer::Node>>> x;
*/
    for (const Vertex * v : vertexSet)
    {
        for (Edge *e : v->getAdj()) {
            GraphViewer::Node src = gv.getNode(v->getId());
            GraphViewer::Node dest = gv.getNode(e->getDest()->getId());
/*
            x.emplace_back(counter, std::make_pair(src, dest));
*/
            gv.addEdge(counter++, src, dest);
            gv.getEdge(counter - 1).setColor(GraphViewer::GRAY);
        }
    }


    for (Vehicle * v : vSet) {
        Vertex * oldVertex = v->getPath()[0];
        for (Vertex *vt : v->getPath()) {
            std::cout << *vt << std::endl;

/*            for(auto obj: x) {
                if(obj.second.first.getId() == oldVertex->getId() && obj.second.second.getId() == vt->getId()) {
                    GraphViewer::Edge e = gv.getEdge(obj.first);
                    e.setColor(Edge::ACTIVE_COLOR);
                    sleep(1);
                    e.setColor(GraphViewer::WHITE);
                }
            }*/
                switch (vt->getType()) {
                    case Vertex::Type::GARAGE:
                        gv.getNode(vt->getId()).setColor(GraphViewer::YELLOW);
                        break;
                    case Vertex::Type::PICKUP:
                        gv.getNode(vt->getId()).setColor(GraphViewer::MAGENTA);
                        break;
                    case Vertex::Type::DELIVERY:
                        gv.getNode(vt->getId()).setColor(GraphViewer::CYAN);
                    default:
                        break;
                }
        }
    }

    gv.setCenter(sf::Vector2f(winCenter.width, winCenter.height));
    gv.createWindow(winSize.width, winSize.height);
    gv.join();
}

void GraphDrawer::drawNodes(const std::vector<Vertex *>& vSet)
{
    for (const Vertex * v : vSet)
    {
        sf::Vector2f vertexPosition(v->getVertexPosition().x, v->getVertexPosition().y);
        graphViewerContext->addNode(v->getId(), vertexPosition);
        switch(v->getType()) {
            case Vertex::Type::GARAGE:
                graphViewerContext->getNode(v->getId()).setColor(GraphViewer::YELLOW);
                break;
            case Vertex::Type::INTERSECTION:
                graphViewerContext->getNode(v->getId()).setColor(GraphViewer::RED);
                break;
            case Vertex::Type::PICKUP:
                graphViewerContext->getNode(v->getId()).setColor(GraphViewer::MAGENTA);
                break;
            case Vertex::Type::DELIVERY:
                graphViewerContext->getNode(v->getId()).setColor(GraphViewer::CYAN);
            default:
                break;
        }
    }
}
void GraphDrawer::drawEdges(const std::vector<Vertex *>& vSet)
{
    for (const Vertex * v : vSet)
    {
        for (const Edge * e : v->getAdj())
        {
            GraphViewer::Node srcV = graphViewerContext->getNode(v->getId());
            GraphViewer::Node destV = graphViewerContext->getNode(e->getDest()->getId());
            graphViewerContext->addEdge(e->getId(), srcV, destV, GraphViewer::Edge::EdgeType::UNDIRECTED);
            graphViewerContext->getEdge(e->getId()).setColor(Edge::ACTIVE_COLOR);
        }
    }
}

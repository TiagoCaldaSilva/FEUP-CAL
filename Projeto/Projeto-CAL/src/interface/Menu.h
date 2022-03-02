#ifndef E_STAFETAS_MENU_H
#define E_STAFETAS_MENU_H

#include <iostream>
#include "../graph/Graph.h"
#include "../entities/Package.h"

class Menu {
public:
    /**
     * @brief Main function of Menu
     * @param graphViewerContext GraphViewer that will provide a possible graph display
     */
    void start(GraphDrawer& graphDrawer);
    /**
     * @brief Interface function that deals with the graph
     * @param graphViewerContext GraphViewer that will provide a possible graph display
     */
    void route(GraphDrawer& graphDrawer);
    /**
     * @brief Interface function that deals with the packages
     */
    void packages();
    /**
     * @brief Add a vertex to the vertexSet
     * @param v Vertex to add
     */
    void addVertex(Vertex * v);
    /**
     * @brief Add an edge to the edgeSet
     * @param edge Edge to add
     */
    void addEdge(Edge * edge);
    /**
     * @brief Get all the vertices
     * @return Vector with all the vertices
     */
    std::vector<Vertex *>& getAllVertexSet();

private:
    /**
     * @brief Display all the packages
     */
    void displayPackages() const;
    /**
     * @brief Display the vertices
     * @param displayDisabledVertices True if the disabled vertices should be displayed, false otherwise
     */
    void displayVertexSet(bool displayDisabledVertices) const;
    /**
     * @brief Display all the edges
     */
    void displayEdgeSet() const;
    /**
     * @brief Disable a vertex
     * @param v Vertex to disable
     */
    void disableVertex(Vertex * v);
    /**
     * @brief Get the enables vertices
     * @return Vector with the enabled vertices
     */
    std::vector<Vertex *> getVertexSet() const;
    /**
     * @brief Get the enabled edges
     * @return Vector with the enabled edges
     */
    std::vector<Edge *> getEdgeSet() const;

    Graph graph;
    std::vector<Vertex *> menuVertexSet;
    std::vector<Edge *> menuEdgeSet;
    std::vector<Package> allPackages;
};

#endif // E_STAFETAS_MENU_H

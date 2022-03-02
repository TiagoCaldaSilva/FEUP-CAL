#ifndef ESTAFETAS_GRAPHDRAWER_H
#define ESTAFETAS_GRAPHDRAWER_H

#include <thread>
#include <chrono>
#include <iostream>

#include <graphviewer.h>
#include "../graph/GraphElements.h"
#include "../entities/Vehicle.h"

class GraphDrawer {
public:
    struct windowSize { unsigned width; unsigned height; };
    struct windowPosition { unsigned width; unsigned height; };

    /**
     * @brief Constructor of the GraphDrawer class
     * @param wSize window size
     * @param wCenter center point of the window
     */
    GraphDrawer(GraphDrawer::windowSize wSize = { 1920, 1080 },
                GraphDrawer::windowPosition wCenter = { 300, 200 });
    /**
     * @brief Destructor of the GraphDrawer class
     */
    ~GraphDrawer();

    void drawGraph(const std::vector<Vehicle *>& vSet, const std::vector<Vertex *>& vertexSet, const std::vector<Edge *> &edge);

private:
    void reset();
    void drawNodes(const std::vector<Vertex *>& vSet);
    void drawEdges(const std::vector<Vertex *>& vSet);

    GraphViewer * graphViewerContext;
    GraphDrawer::windowSize winSize;
    GraphDrawer::windowPosition winCenter;
};

#endif  // ESTAFETAS_GRAPHDRAWER_H

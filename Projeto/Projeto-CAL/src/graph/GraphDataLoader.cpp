#include "GraphDataLoader.h"

inline double GraphDataLoader::calculateDistance(Vertex& srcNode, Vertex& destNode)
{
    Vertex::Position srcPos = srcNode.getVertexPosition();
    Vertex::Position destPos = destNode.getVertexPosition();

return std::sqrt(pow(destPos.x - srcPos.x, 2) + pow(destPos.y - srcPos.y, 2));
}

GraphDataLoader::GraphDataLoader(Menu &menu,
                                 const std::string_view &vertexFilePath,
                                 const std::string_view &edgesFilePath) :
vertexFile(vertexFilePath), edgesFile(edgesFilePath)
{
    loadVertices(menu);
    loadEdges(menu);
}

void GraphDataLoader::loadVertices(Menu &menu)
{
    char separator;
    std::ifstream vertexLoader(vertexFile);

    GraphViewer::id_t numberOfNodes;
    vertexLoader >> numberOfNodes;

    unsigned int counter = 0;
    for (GraphViewer::id_t node = 0; node < numberOfNodes; ++node)
    {
        GraphViewer::id_t ID;
        float x, y;
        vertexLoader >> separator >> ID >> separator >> x >> separator >> y >> separator;
        menu.addVertex(new Vertex(ID, counter++, {x, y}));
    }
    vertexLoader.close();
}
void GraphDataLoader::loadEdges(Menu &menu)
{
    char separator;
    std::ifstream edgeLoader(edgesFile);
    std::vector<Vertex *> graphVertexSet = menu.getAllVertexSet();

    GraphViewer::id_t numberOfEdges;
    edgeLoader >> numberOfEdges;

    for (GraphViewer::id_t edgeID = 0; edgeID < numberOfEdges; ++edgeID)
    {
        GraphViewer::id_t src, dest;
        edgeLoader >> separator >> src >> separator >> dest >> separator;

        Vertex * srcVertex = nullptr;
        Vertex * destVertex = nullptr;

        for (Vertex * vertex : graphVertexSet)
        {
            GraphViewer::id_t vertexId = vertex->getFileId();

            if (vertexId == src)
                srcVertex = vertex;
            else if (vertexId == dest)
                destVertex = vertex;
        }

        Edge * loadedEdge;
        try {
            double distance = calculateDistance(*srcVertex, *destVertex);
            loadedEdge = new Edge(edgeID, distance, srcVertex, destVertex);
        } catch (std::invalid_argument& invalidArgument) {
            std::cerr << invalidArgument.what() << std::endl;
        }

        menu.addEdge(loadedEdge);
    }
    edgeLoader.close();
}

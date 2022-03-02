#include "graph/Graph.h"
#include "graph/GraphDataLoader.h"

int main(int argc, char* argv[])
{
    Menu m;
    Graph graph;
    GraphDataLoader graphDataLoader(m, "../Graphs/GridGraphs/4x4/nodes.txt", "../Graphs/GridGraphs/4x4/edges.txt");
    //GraphDataLoader graphDataLoader(m, "../Graphs/Penafiel/penafiel_strong_nodes_xy.txt", "../Graphs/Penafiel/penafiel_strong_edges.txt");

    GraphDrawer gd({800, 600});
    m.start(gd);

    return 0;
}

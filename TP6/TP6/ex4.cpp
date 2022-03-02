#include "Graph.h"
#include "TestAux.h"

// Complete the functions on the Graph.h file

/// TESTS ///

TEST(TP6_Ex4, test_floydWarshall) {
    Graph<int> myGraph = CreateTestGraph();
    myGraph.floydWarshallShortestPath();
    checkSinglePath(myGraph.getfloydWarshallPath(1, 7), "1 2 4 5 7 ");
    checkSinglePath(myGraph.getfloydWarshallPath(5, 6), "5 7 6 ");
    checkSinglePath(myGraph.getfloydWarshallPath(7, 1), "7 6 4 3 1 ");
    checkSinglePath(myGraph.getfloydWarshallPath(2, 3), "2 4 3 ");
    checkSinglePath(myGraph.getfloydWarshallPath(2, 1), "2 4 3 1 ");
    checkSinglePath(myGraph.getfloydWarshallPath(7, 2), "7 6 4 3 1 2 ");
    checkSinglePath(myGraph.getfloydWarshallPath(5, 1), "5 7 6 4 3 1 ");
    checkSinglePath(myGraph.getfloydWarshallPath(6, 5), "6 4 5 ");
    checkSinglePath(myGraph.getfloydWarshallPath(3, 5), "3 1 2 4 5 ");

}

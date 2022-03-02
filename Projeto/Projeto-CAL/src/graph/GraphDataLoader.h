#ifndef ESTAFETAS_GRAPHDATALOADER_H
#define ESTAFETAS_GRAPHDATALOADER_H

#include <string>
#include <fstream>
#include <cmath>
#include "../interface/Menu.h"

class GraphDataLoader {
private:
    std::string vertexFile;
    std::string edgesFile;

    /**
     * @brief Load the vertices from a file
     * @param menu Menu where the vertices should be added
     */
    void loadVertices(Menu &menu);
    /**
     * @brief Load the edges from a file
     * @param menu Menu where the edges should be added
     */
    void loadEdges(Menu &menu);

    /**
     * @brief Calculate the distance between two vertices
     * @param srcNode Source vertex
     * @param destNode Destiny vertex
     * @return Distance between the vertices
     */
    static inline double calculateDistance(Vertex& srcNode, Vertex& destNode);
public:
    /**
     * @brief GraphDataLoader constructor
     * @param menu Menu where information should be loaded
     * @param vertexFilePath Path of the vertices file
     * @param EdgeFilePath Path of the edges file
     */
    GraphDataLoader(Menu& menu, const std::string_view& vertexFilePath, const std::string_view& EdgeFilePath);
};

#endif //ESTAFETAS_GRAPHDATALOADER_H

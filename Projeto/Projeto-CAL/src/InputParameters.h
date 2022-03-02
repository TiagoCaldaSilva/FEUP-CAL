#ifndef E_STAFETAS_UTILS_H_
#define E_STAFETAS_UTILS_H_

#include <vector>
#include "graph/GraphElements.h"
#include "entities/Package.h"

/**
 * @brief Struct with all the parameters
 *         that the graph needs to execute
 */
struct Parameters {
    unsigned int nV;
    double autonomy;
    double distanceToCharge;
    std::vector<Vertex *> vertexSet;
    std::vector<Edge *> edges;
    std::vector<Package *> packages;
    Vertex * garage;
    bool orderByDistance;
};

#endif  // E_STAFETAS_UTILS_H_

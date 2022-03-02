//
// Created by user on 18/05/2021.
//

#ifndef E_STAFETAS_GRAPHELEMENTS_H_
#define E_STAFETAS_GRAPHELEMENTS_H_

#include <string>
#include <vector>

#include <graphviewer.h>
#include <ostream>

class Vertex;

class Edge {
public:
    /**
     * @brief Edge's constructor
     * @param edgeID Edge ID
     * @param weight Edge weight
     * @param orig Origin vertex
     * @param dest Target vertex
     */
    Edge(GraphViewer::id_t edgeID, double weight, Vertex * orig, Vertex * dest);
    /**
     * @brief Edge's copy constructor
     * @param edge Edge to copy
     */
    explicit Edge(Edge* edge);
    /**
     * @brief Get the ID value
     * @return ID value
     */
    GraphViewer::id_t getId() const;
    /**
     * @brief Get the edge's weight
     * @return Weight value
     */
    double getWeight() const;
    /**
     * @brief Set a new value to the edge's weight
     * @param weight New value of edges weight
     */
    void setWeight(double weight);
    /**
     * @brief Get the target vertex of the edge
     * @return Target vertex
     */
    Vertex * getDest() const;
    /**
     * @brief Get the origin vertex of the edge
     * @return Origin vertex
     */
    Vertex * getOrig() const;
    /**
     * @brief Return if an edge can be enabled or not
     * @return True if both orig and dest are enabled, false otherwise
     */
    bool canBeEnabled() const;
    /**
     * @brief Get the enabled value of an edge
     * @return Enable value
     */
    bool isEnabled() const;
    /**
     * @brief Set a new enabled value
     * @param enableVal New enabled value
     */
    void setEnabled(bool enableVal);
    /**
     * @brief Changes the value of enabled to the opposite
     */
    void changeEnable();
    /**
     * @param edge Edge to be compared
     * @return True if the compared edges are equal, false otherwise
     */
    bool operator==(const Edge * edge) const;
    /**
     * @brief Writes the Edge to os
     * @param os Ostream to be written with the Edge's info
     * @param vertex Edge that should be used
     * @return os with the Edge's info
     */
    friend std::ostream &operator<<(std::ostream &os, const Edge &edge);

    static sf::Color ACTIVE_COLOR;

private:
    static GraphViewer::id_t ID;
    GraphViewer::id_t id;
    double weight;
    Vertex* orig;
    Vertex* dest;
    bool enabled;
};


class Vertex {
public:
    /**
     * @brief Enum with all the vertices types
     */
    enum Type { GARAGE, PICKUP, DELIVERY, INTERSECTION, CHARGING };
    /**
     * @brief Struct that defines the position of each vertex
     */
    struct Position { float x; float y; };
    /**
     * @brief Vertex's constructor
     * @param vertexID Vertex ID
     * @param vertexPosition Vertex position
     * @param vertexType Vertex type
     */
    Vertex(unsigned int fileID, GraphViewer::id_t vertexID, Vertex::Position vertexPosition, Vertex::Type vertexType = Vertex::Type::INTERSECTION);
    /**
     * @brief Vertex's constructor
     * @param vertexType Vertex type
     */
    explicit Vertex(Vertex::Type vertexType = Vertex::Type::CHARGING);
    /**
     * @brief Vertex's copy constructor
     * @param vertex Vertex to copy
     */
    explicit Vertex(const Vertex * vertex);
    /**
     * @brief Get the set of edges that are connected to the vertex
     * @return Vector with the vertex  connected edges
     */
    std::vector<Edge *> getAdj() const;
    /**
     * @brief Add a connected edge
     * @param edge Edge to add
     */
    void addEdge(Edge * edge);
    /**
     * @brief Get the vertex ID
     * @return Vertex ID value
     */
    GraphViewer::id_t getId() const;
    /**
     * @brief Get the vertex type
     * @return Vertex type value
     */
    Vertex::Type getType() const;
    /**
     * @brief Set the Vertex type
     * @param type New type value
     */
    void setType(const Vertex::Type &type);
    /**
     * @brief Get the vertex position
     * @return Vertex position
     */
    Vertex::Position getVertexPosition() const;
    /**
     * Get the vertex path
     * @return Vertex path
     */
    Vertex * getPath() const;
    /**
     * @brief Set the vertex path
     * @param path Vertex path
     */
    void setPath(Vertex * path = nullptr);
    /**
     * @brief Get the distance of the vertex to another after run the dijkstraShortestPath algorithm
     * @return Distance to another vertex
     */
    double getDist() const;
    /**
     * @brief Set a new distance value
     * @param dist New value of distance
     */
    void setDist(double dist = MAX_DIST);
    /**
     * @brief Get the ID of the vertex read from the graph file
     * @return Vertex ID according to its ID on the file read
     */
    unsigned int getFileId() const;
    /**
     * @brief Get the value computed by bellmanFordShortestPath algorithm to be used in johnsonShortestPath algorithm
     * @return value to be used in johnsonShortestPath algorithm
     */
    double getH() const;
    /**
     * @brief Set the value computed by bellmanFordShortestPath algorithm to be used in johnsonShortestPath algorithm
     * @param h      */
    void setH(double h = MAX_DIST);
    /**
     * @brief Get the visited value
     * @return True if a vertex was already visited, false otherwise
     */
    bool isVisited() const;
    /**
     * @brief Set a new visited value
     * @param visit New value of visited
     */
    void setVisit(bool visit);
    /**
     * @brief Get the enabled value
     * @return True if a vertex is enabled, false otherwise
     */
    bool isEnabled() const;
    /**
     * @brief Set a new enabled value
     * @param enableVal New value of enabled
     */
    void setEnabled(bool enableVal);
    /**
     * @brief Changes the value of enabled to the opposite
     */
    void changeEnable();
    /**
     * @brief Clear the vertex
     */
    void clear();
    /**
     * @param v1 Vertex to be compared
     * @return True if the compared vertices are equal, false otherwise
     */
    bool operator==(const Vertex & v1) const;
    /**
     * @brief
     * @param rhs Vertex to be compared
     * @return True if rhs.dist is lower than this->dist
     */
    bool operator<(const Vertex &rhs) const;
    /**
     * @brief Writes the Vertex to os
     * @param os Ostream to be written with the Vertex's info
     * @param vertex Vertex that should be used
     * @return os with the Vertex's info
     */
    friend std::ostream &operator<<(std::ostream &os, const Vertex &vertex);

    int queueIndex;
    static constexpr double MAX_DIST = std::numeric_limits<double>::max();
    static std::array<std::string, 5> typeStrings;
private:
    static GraphViewer::id_t ID;
    GraphViewer::id_t id;
    unsigned int fileID;

    Vertex * path;
    double dist;
    double h;

    bool visited;
    std::vector<Edge *> adj;

    Vertex::Type type;
    Vertex::Position position;

    bool enabled;
};

#endif // E_STAFETAS_GRAPHELEMENTS_H_

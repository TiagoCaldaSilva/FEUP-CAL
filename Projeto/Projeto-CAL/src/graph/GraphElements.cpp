#include "GraphElements.h"

// EDGE

sf::Color Edge::ACTIVE_COLOR = sf::Color::Magenta;

Edge::Edge(GraphViewer::id_t edgeID, double weight, Vertex * orig, Vertex * dest) :
id(edgeID), weight(weight), orig(orig), dest(dest)
{
    enabled = canBeEnabled();
    if (orig == nullptr || dest == nullptr)
        throw std::invalid_argument("Invalid arguments type with orig and dest");
}

Edge::Edge(Edge * edge) :
id(edge->id), weight(edge->weight), orig(edge->orig), dest(edge->dest), enabled(edge->enabled)
{}

GraphViewer::id_t Edge::getId() const { return id; }

double Edge::getWeight() const { return weight; }
void Edge::setWeight(double edgeWeight) { weight = edgeWeight; }

Vertex * Edge::getOrig() const { return orig; }
Vertex * Edge::getDest() const { return dest; }

bool Edge::canBeEnabled() const { return orig->isEnabled() && dest->isEnabled(); }
bool Edge::isEnabled() const { return enabled; }
void Edge::setEnabled(bool enableVal) { enabled = enableVal; }
void Edge::changeEnable() { enabled ? setEnabled(false) : setEnabled(true); }

std::ostream &operator<<(std::ostream &os, const Edge &edge)
{
    os << "Id: " << edge.getId() << " | From: " << edge.orig->getId() << " | To: " << edge.dest->getId()
    << " | W: " << edge.weight << " | Enabled: " << edge.enabled;
    return os;
}
bool Edge::operator==(const Edge * edge) const { return orig == edge->orig and dest == edge->dest and weight == edge->weight; }

// VERTEX

static std::array<std::string, 5> typeStrings = { "GARAGE", "PICKUP", "DELIVERY", "INTERSECTION", "CHARGING" };

Vertex::Vertex(unsigned int fileID, GraphViewer::id_t vertexID, Vertex::Position vertexPosition, Vertex::Type vertexType) :
id(vertexID), path(nullptr), dist(MAX_DIST), h(MAX_DIST), position(vertexPosition), type(vertexType), visited(false), enabled(true), fileID(fileID)
{
    enabled = true;
}
Vertex::Vertex(const Vertex * vertex) : id(vertex->id), path(vertex->path), dist(vertex->dist), h(vertex->h),
adj(vertex->adj), position(vertex->position), type(vertex->type), visited(vertex->visited), enabled(vertex->enabled), fileID(vertex->fileID)
{}
Vertex::Vertex(Vertex::Type vertexType) :
id(UINT32_MAX), path(nullptr), dist(MAX_DIST), h(MAX_DIST), position({0 , 0}), type(vertexType), visited(false), enabled(true), fileID(UINT32_MAX)
{}

GraphViewer::id_t Vertex::getId() const { return id; }

void Vertex::addEdge(Edge *edge) { adj.push_back(edge); }
std::vector<Edge *> Vertex::getAdj() const { return adj; }

Vertex::Position Vertex::getVertexPosition() const { return position; }

Vertex::Type Vertex::getType() const { return type; }
void Vertex::setType(const Vertex::Type &vertexType) { type = vertexType; }

Vertex *Vertex::getPath() const { return path; }
void Vertex::setPath(Vertex* previousVertex) { path = previousVertex; }

double Vertex::getDist() const { return dist; }
void Vertex::setDist(double vertexDist) { dist = vertexDist; }

double Vertex::getH() const { return h; }
void Vertex::setH(double hVertex) { h = hVertex; }

bool Vertex::isVisited() const { return visited; }
void Vertex::setVisit(bool visit) { visited = visit; }

bool Vertex::isEnabled() const { return enabled; }
void Vertex::setEnabled(bool enableVal)
{
    enabled = enableVal;
    if (!enabled)
        for (Edge * edge: adj)
            edge->setEnabled(false);
}
void Vertex::changeEnable() { enabled ? setEnabled(false) : setEnabled(true); }

void Vertex::clear()
{
    adj.clear();
    visited = false;
    dist = MAX_DIST;
    path = nullptr;
    type = Vertex::Type::INTERSECTION;
}

bool Vertex::operator==(const Vertex &v1) const { return id == v1.id; }
bool Vertex::operator<(const Vertex &rhs) const { return dist < rhs.dist; }
std::ostream &operator<<(std::ostream &os, const Vertex &vertex) {
    os << "id: " << vertex.id << " | position: " << vertex.position.x << ", " << vertex.position.y
    << " | enabled: " << vertex.enabled << " | type: " << typeStrings.at(vertex.type);
    return os;
}

unsigned int Vertex::getFileId() const {
    return fileID;
}

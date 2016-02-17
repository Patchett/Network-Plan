#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <utility>
#include "Edge.hpp"

#include <unordered_map>
/**
 * Represents a Vertex in a graph.
 *
 * Vertices are connected to other Vertices via Edges. Each Vertex
 * maintains a collection of all Edges that originate from it.
 */
class Vertex
{
    // Graph needs access to Edge map for Dijkstra/Prim algorithms.
    friend class UndirectedGraph;

public:
    /**
     * Initialize the Vertex with the given name.
     */
    Vertex(const std::string &name);

    /**
     * Add an edge to this Vertex. If an edge already exists to the given
     * vertex, updates the cost and length of the edge to match the
     * passed parameters.
     */
    bool addEdge(Vertex *to, unsigned int cost, unsigned int length);

    /**
     * Returns the Vertex's name.
     */
    const std::string &getName() const;

    /**
     * Gets the Vertex's distance value.
     */
    unsigned int getDistance() const;

    /**
     * Sets the Vertex's distance value.
     */
    void setDistance(unsigned int distance);

    /**
     * Gets the Vertex's visited state.
     */
    bool wasVisited() const;

    /**
     * Sets the Vertex's visited state.
     */
    void setVisited(bool visited);

    /**
     * Clears all edges from this Vertex.
     */
    void clearEdges();

    /**
     * Gets total cost of all edges terminating at this Vertex.
     */
    unsigned int totalEdgeCost() const;

private:
    /**
     * Returns a reference to the internal map of Edges.
     * Used by UndirectedGraph for Dijkstra/Prim algorithms.
     */
    const std::unordered_map<std::string, Edge> &getEdges() const;

    /**
     * Name of this Vertex.
     */
    std::string name;

    /**
     * Distance of this Vertex from initial Vertex.
     * Used by Dijkstra's algorithm.
     */
    unsigned int distance;

    /**
     * Whether this node has been visited.
     * Used by Prim's algorithm.
     */
    bool visited;

    /**
     * Map of adjacent Vertex name to Edge describing the adjacency.
     */
    std::unordered_map<std::string, Edge> edges;
};

#endif

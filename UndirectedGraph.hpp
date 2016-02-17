#ifndef UNDIRECTEDGRAPH_HPP
#define UNDIRECTEDGRAPH_HPP

#include <string>
#include <unordered_map>

#include "Vertex.hpp"

/**
 * Implements an undirected graph. Any edge in the graph
 * represents a bidirectional connection between two vertices.
 *
 * Implements methods for producing a minimum spanning tree of the
 * graph, as well as calculating the total length of the shortest
 * paths between each pair of vertices.
 */
class UndirectedGraph {
public:
    /**
     * Constructs an empty UndirectedGraph with no vertices and
     * no edges.
     */
    UndirectedGraph();

    /**
     * Destructs an UndirectedGraph.
     */
    ~UndirectedGraph();

    /**
     * Inserts an edge into the graph. If an edge already exists between
     * the vertices, updates the cost and length of the edge to match the
     * passed parameters.
     *
     * If either of the named vertices does not exist, it is created.
     */
    void addEdge(const std::string &from, const std::string &to,
                 unsigned int cost, unsigned int length);

    /**
     * Returns the total cost of all edges in the graph.
     *
     * Since this graph is undirected, is calcualted as the cost
     * of all Edges terminating at all Vertices, divided by 2.
     */
    unsigned int totalEdgeCost() const;

    /**
     * Removes all edges from the graph except those necessary to
     * form a minimum cost spanning tree of all vertices using Prim's
     * algorithm.
     *
     * The graph must be in a state where such a spanning tree
     * is possible. To call this method when a spanning tree is
     * impossible is undefined behavior.
     */
    UndirectedGraph *minSpanningTree();

    /**
     * Determines the combined distance from the given Vertex to all
     * other Vertices in the graph using Dijkstra's algorithm.
     *
     * Returns max possible distance if the given Vertex does not appear
     * in the graph, or if any of the Vertices in the graph are not
     * reachable from the given Vertex. Otherwise, returns the combined
     * distance.
     */
    unsigned int totalDistance(const std::string &from);

    /**
     * Determines the combined distance from all Vertices to all other
     * Vertices in the graph.
     *
     * Returns max possible distance if the graph is not connected.
     */
    unsigned int totalDistance();

private:
    /**
     * Comparison functor for use with Dijkstra's algorithm. Allows Vertices
     * to be added to a priority queue more than once, with different weights.
     *
     * Each pair represents a Vertex and its weight when it was added to the
     * queue. This guarantees that the weight used to order the Vertices in
     * the queue never changes (a required invariant of a priority queue),
     * even though the weight of the Vertex itself may change.
     *
     * Returns true if left's weight when it was inserted into the queue is
     * higher than right's weight when it was inserted into the queue.
     */
    class DijkstraVertexComparator {
    public:
        bool operator()(const std::pair<Vertex *, unsigned int> &left,
                        const std::pair<Vertex *, unsigned int> &right);
    };

    /**
     * Map of vertex name to Vertex.
     */
    std::unordered_map<std::string, Vertex *> vertices;
};

#endif

#include "UndirectedGraph.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"
#include <queue>
#include <vector>
#include <limits>
#include <utility>
#include <iostream>
#include <unordered_map>

using namespace std;

/**
* Constructs an empty UndirectedGraph with no vertices and
* no edges.
*/
UndirectedGraph::UndirectedGraph() { }

/**
 * Destructs an UndirectedGraph.
 */
UndirectedGraph::~UndirectedGraph()
{
    for (auto &currentVertex : vertices) {
        currentVertex.second->clearEdges();
        delete currentVertex.second;
    }
    vertices.clear();
}

/**
 * Inserts an edge into the graph. If an edge already exists between
 * the vertices, updates the cost and length of the edge to match the
 * passed parameters.
 *
 * If either of the named vertices does not exist, it is created.
 */
void UndirectedGraph::addEdge(const std::string &from, const std::string &to,
                              unsigned int cost, unsigned int length)
{
    if (!(vertices[from])) { // The from Vertex does not exist, create a new one
        Vertex *newFrom = new Vertex(from);
        vertices[from] = newFrom;
    }

    if (!(vertices[to])) { // The to Vertex does not exist, create a new one
        Vertex *newTo = new Vertex(to);
        vertices[to] = newTo;
    }

    // Add 2 edges to the graph, one going from->to and the other going to->from
    // Do this to simulate an undirected graph
    vertices[from]->addEdge(vertices[to], cost, length);
    vertices[to]->addEdge(vertices[from], cost, length);
}

/**
 * Returns the total cost of all edges in the graph.
 *
 * Since this graph is undirected, is calcualted as the cost
 * of all Edges terminating at all Vertices, divided by 2.
 */
unsigned int UndirectedGraph::totalEdgeCost() const
{
    unsigned int total = 0;
    // Iterate through the adjacency list of each vertex in the graph and add
    // the sum of its edges to a total. Divide the total by 2 because the graph
    // is undirected
    for (auto zod : vertices) {
        total += zod.second->totalEdgeCost();
    }
    return total / 2;
}

/**
 * Removes all edges from the graph except those necessary to
 * form a minimum cost spanning tree of all vertices using Prim's
 * algorithm.
 *
 * The graph must be in a state where such a spanning tree
 * is possible. To call this method when a spanning tree is
 * impossible is undefined behavior.
 */

// Prim - MST
UndirectedGraph *UndirectedGraph::minSpanningTree()
{
    // Priority queue for the edges
    priority_queue<Edge> neighborEdges;
    // This graph will be the MST
    UndirectedGraph *MST = new UndirectedGraph();
    // Set the visited field of all vertices to false
    for (auto &vertIterator : vertices) {
        vertIterator.second->setVisited(false);
    }
    // Pick an arbitrary start vertex
    auto &currentVert = *vertices.begin();
    currentVert.second->setVisited(true);
    // Iterate through currentVert's adjacency list and push the edges
    // onto the queue
    for (auto &currentEdge : currentVert.second->getEdges()) {
        neighborEdges.push(currentEdge.second);
    }
    while (!(neighborEdges.empty())) {
        // Get the edge on the top of the queue
        auto popEdge = neighborEdges.top();
        neighborEdges.pop();
        // Check if the vertex that the edge points to has been visited
        if (popEdge.getTo()->wasVisited() != true) {
            // Set visited to true
            popEdge.getTo()->setVisited(true);
            // Add the new edge to the MST
            MST->addEdge(popEdge.getFrom()->getName(),
                         popEdge.getTo()->getName(), popEdge.getCost(), popEdge.getLength());
            // Push all edges on To's adjacency list onto the priority queue if
            // the vertex that the edge points to has not been visited
            for (auto &toEdge : popEdge.getTo()->getEdges()) {
                if (!(toEdge.second.getTo()->wasVisited())) {
                    neighborEdges.push(toEdge.second);
                }
            }
        }
    }
    return MST;
}

/**
 * Determines the combined distance from the given Vertex to all
 * other Vertices in the graph using Dijkstra's algorithm.
 *
 * Returns max possible distance if the given Vertex does not appear
 * in the graph, or if any of the Vertices in the graph are not
 * reachable from the given Vertex. Otherwise, returns the combined
 * distance.
 */

// Dijkstra - Shortest Path
unsigned int UndirectedGraph::totalDistance(const std::string &from)
{
    if (vertices[from] == nullptr) {
        return std::numeric_limits<unsigned int>::max();
    }
    unsigned int maxDistance = 0;
    priority_queue<pair<Vertex *, unsigned int>, vector<pair<Vertex *, unsigned int>>,
                   DijkstraVertexComparator> lengths;
    // Set the visited field of all vertices to false
    for (auto &currentVert : vertices) {
        currentVert.second->setVisited(false);
        currentVert.second->setDistance(std::numeric_limits<unsigned int>::max());
    }
    vertices[from]->setDistance(0);
    // Enqueue the start vertex
    lengths.push(make_pair(vertices[from], 0));
    while (lengths.size() > 0) {
        // Dequeue a vertex from lengths
        auto curr = lengths.top();
        lengths.pop();
        // The dequeued vertex has not been visited
        if (!(curr.first->wasVisited())) {
            // Set the dequeued vertex's visited field to true
            curr.first->setVisited(true);
            // Iterate through the dequeued vertex's adj. list.
            for (auto &adjVertex : curr.first->getEdges()) {
                // The next adjacent vertex was not visited
                if (!(adjVertex.second.getTo()->wasVisited())) {
                    // Calculate the new distance to the current vertex in the adj. list
                    unsigned int newLength = ((curr.first->getDistance()) + (adjVertex.second.getLength()));
                    // The new distance is less than the vertex's current distance
                    if (newLength < (adjVertex.second.getTo()->getDistance())) {
                        adjVertex.second.getTo()->setDistance(newLength);
                        // Push this edge onto the queue
                        lengths.push(make_pair(adjVertex.second.getTo(), adjVertex.second.getTo()->getDistance()));
                    }
                }
            }
        }
    }
    // Calculate the total distance of all shortest paths for this vertex
    for (auto &currVert : vertices) {
        maxDistance += currVert.second->getDistance();
    }
    return maxDistance;
}

/**
 * Determines the combined distance from all Vertices to all other
 * Vertices in the graph.
 *
 * Returns max possible distance if the graph is not connected.
 */
unsigned int UndirectedGraph::totalDistance()
{
    unsigned int totalDistance = 0;
    // Run Dijkstra's algorithm on all vertices in the graph
    for (auto &currentVertex : vertices) {
        totalDistance += this->totalDistance(currentVertex.first);
    }
    // Return the sum of all shortest paths
    return totalDistance;
}

bool UndirectedGraph::DijkstraVertexComparator::operator()(const std::pair<Vertex *, unsigned int> &left,
        const std::pair<Vertex *, unsigned int> &right)
{
    // Deterministic way to deal with ties
    if (left.second == right.second) {
        return ((left.first->getName()) > (right.first->getName()));
    }
    return left.second > right.second;
}

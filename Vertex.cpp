#include "Vertex.hpp"
#include <utility>
#include <iostream>
#include <iomanip>
#include <unordered_map>

using namespace std;

const std::string &Vertex::getName() const
{
    return this->name;
}

Vertex::Vertex(const std::string &name)
{
    this->name = name;
    visited = false;
}

bool Vertex::addEdge(Vertex *to, unsigned int cost, unsigned int length)
{
    // This edge already exists
    if (edges.find(to->getName()) != edges.end())
    {
        // Update the fields of the edge
        edges.at(to->getName()).setCost(cost);
        edges.at(to->getName()).setLength(length);
        return false;
    }
    else // The edge does not exist
    {
        // create a new edge
        edges[to->getName()] = Edge(this, to, cost, length);
        return true;
    }
}

unsigned int Vertex::getDistance() const
{
    return distance;
}

void Vertex::setDistance(unsigned int distance)
{
    this->distance = distance;
}

bool Vertex::wasVisited() const
{
    return visited;
}

void Vertex::setVisited(bool visited)
{
    this->visited = visited;
}

void Vertex::clearEdges()
{
    edges.clear();
}

unsigned int Vertex::totalEdgeCost() const
{
    unsigned int total = 0;
    // Iterate through the edges unordered_map and calculate the total cost
    // of all edges
    for (auto &zod : edges)
    {
        total += zod.second.getCost();
    }
    return total;
}

const std::unordered_map<std::string, Edge> &Vertex::getEdges() const
{
    return edges;
}

#include "Edge.hpp"
#include "Vertex.hpp"
#include <unordered_map>

Edge::Edge(Vertex *from, Vertex *to, unsigned int cost,
           unsigned int length)
{
    this->from = from;
    this->to = to;
    this->cost = cost;
    this->length = length;
}

Vertex *Edge::getFrom() const
{
    return from;
}
Vertex *Edge::getTo() const
{
    return to;
}

void Edge::setCost(unsigned int cost)
{
    this->cost = cost;
}

unsigned int Edge::getCost() const
{
    return cost;
}

void Edge::setLength(unsigned int length)
{
    this->length = length;
}

unsigned int Edge::getLength() const
{
    return length;
}

bool Edge::operator<(const Edge &right) const
{
    // Deterministic way to deal with ties
    if(this->cost == right.cost)
    {
        return ((this->getTo()->getName()) > (right.getTo()->getName()));
    }
    return ((this->cost) > right.cost);
}

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "UndirectedGraph.hpp"

using namespace std;
/**
 * Entry point into the netplan program.
 *
 * -Reads a file from the filesystem according to the specification for
 *  PA3, creating an UndirectedGraph.
 * -Finds the total cost & ping time of the graph as presented in the input
 *  file.
 * -Determines the minimum cost graph from the original graph.
 * -Finds the total cost & ping time of the minimum cost graph.
 * -Finds the change of cost & ping time from the original graph to the
 *  minimum cost graph.
 * -Prints the results to stdout.
 *
 * Usage:
 *   ./netplan infile
 *
 */
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " infile" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream in(argv[1]);
    if (!in)
    {
        std::cerr << "Unable to open file for reading." << std::endl;
        return EXIT_FAILURE;
    }

    // Check if input file is empty
    in.seekg(0, ios::end);
    streampos end = in.tellg();
    in.seekg(0, ios::beg);
    streampos beg = in.tellg();
    if (beg == end)
    {
        cout << "0" << endl;
        cout << "0" << endl;
        cout << "0" << endl;
        cout << "0" << endl;
        cout << "0" << endl;
        cout << "0" << endl;
        in.close();
        return 0;
    }

    string from;
    string to;
    unsigned int cost;
    unsigned int latency;
    // Total cost of creating all possible network links
    unsigned int totalCost = 0;
    // Cost of building the MST
    unsigned int MSTCost = 0;
    // Total latency to send a packet between all pairs of computers
    unsigned int totalDistance = 0;
    unsigned int MSTDistance = 0;

    // This will be the graph from the original input file
    UndirectedGraph *originalGraph = new UndirectedGraph();
    // Build the graph based on the contents of the input file
    in.seekg(0, in.beg);
    while (in >> from && in >> to && in >> cost && in >> latency)
    {
        originalGraph->addEdge(from, to, cost, latency);
        if (in.peek() == -1) break;
    }
    // Get the total cost of all edges in the original graph
    totalCost = originalGraph->totalEdgeCost();
    // #1
    cout << totalCost << endl;
    // Find the MST of the original graph
    UndirectedGraph *MST = originalGraph->minSpanningTree();
    // Find the cost of all edges in the MST
    MSTCost = MST->totalEdgeCost();
    // #2
    cout << MSTCost << endl;
    // #3
    cout << totalCost - MSTCost << endl;

    // Run Dijkstra on all vertices in the original graph and return the
    // sum of all shortest paths
    totalDistance += originalGraph->totalDistance();
    // #4
    cout << totalDistance << endl;

    // Run Dijkstra on all vertices in the MST and return the sum of all shortest
    // paths
    MSTDistance += MST->totalDistance();
    // #5
    cout << MSTDistance << endl;
    // #6
    cout << MSTDistance - totalDistance << endl;

    delete MST;
    delete originalGraph;

    return EXIT_SUCCESS;
}

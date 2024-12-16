#include <iostream>
#include "adjMatrix.h"

int main() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);


    // std::cout << "Adjacency Matrix of the graph:" << std::endl;
    // g.print();

    // std::cout << "Topological Sort (DFS): ";
    // g.topSort();

    // std::cout << "Topological Sort (Kahn's Algorithm): ";
    // g.topSortKahn();
    // std::cout << std::endl;

    // std::cout << "Cycle Detection in Directed Graph: ";
    // if (g.isCycledDirected()) {
    //     std::cout << "Cycled Graph!!" << std::endl;
    // } else {
    //     std::cout << "Acyclic Graph!!" << std::endl;
    // }

    // std::cout << "BFS starting from vertex 2: ";
    // g.BFS(2);
    // std::cout << std::endl;

    // std::cout << "DFS (Iterative) starting from vertex 2: ";
    // g.DFS_Iterative(2);
    // std::cout << std::endl;

    // std::cout << "DFS (Recursive) starting from vertex 2: ";
    // g.DFS_Recursive(2);
    // std::cout << std::endl;

    // std::cout << "Shortest Path from 5 to 1: ";
    // std::vector<int> path = g.ShortestPath(5, 1);
    // for (int v : path) {
    //     std::cout << v << " ";
    // }
    // std::cout << std::endl;

    // std::cout << "All paths from 5 to 1:" << std::endl;
    // std::vector<std::vector<int>> allPaths = g.getAllPaths(5, 1);
    // for (const auto& p : allPaths) {
    //     for (int v : p) {
    //         std::cout << v << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << "Number of Connected Components: ";
    // int components = g.DFS_ExtraCase();
    // std::cout << components << std::endl;

    // std::cout << "TopSort result(DFS)." << std::endl;
    // //we should have acycled directed graph for topSort
    // g.topSort(); 
    // std::cout << std::endl;

    std::cout << "Kahn's algorithm result." << std::endl;
    //we should have acycled directed graph for Kahn's algorithm
    g.topSortKahn();
    std::cout << std::endl;

    // std::cout << "Strongly Connected Components with Kosaraju's algorithm:\n";
    // for (const auto& scc : g.Kosaraju()) {
    //     for (int v : scc) {
    //         std::cout << v << " ";
    //     }
    // }
    // std::cout << std::endl;

    return 0;
}

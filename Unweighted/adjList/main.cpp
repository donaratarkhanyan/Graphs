#include <iostream>
#include "adjList.h"

int main() {
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 4);
    g.addEdge(1, 5);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 6);

    //std::cout << "Undirected graph." << std::endl;
    //std::cout << "Directed graph." << std::endl;
    //std::cout << "Acycled directed graph." << std::endl;
    g.print();

    //std::cout << "BFS result(directed graph)." << std::endl;
    //std::cout << "BFS result(undirected graph)." << std::endl;
    // g.BFS(3);
    // std::cout << std::endl;

    // std::cout << "DFS Recursive result(directed graph)." << std::endl;
    //std::cout << "DFS Recursive result(undirected graph)." << std::endl;
    // g.DFS_Recursive(3);
    // std::cout << std::endl;

    // std::cout << "DFS Iterative result(directed graph)." << std::endl;
    //std::cout << "DFS Iterative result(undirected graph)." << std::endl;
    // g.DFS_Iterative(3);
    // std::cout << std::endl;

    // std::cout << "Transpose directed graph" << std::endl;
    //std::cout << "Transpose undirected graph" << std::endl;
    // g.transpose();
    // g.print();
    // std::cout << std::endl;

    // std::cout << "Shortest path of this graph." << std::endl;
    // std::vector<int> result = g.ShortestPath(0, 5);
    // for (auto v : result) {
    //     std::cout << v << " ";
    // }
    // std::cout << std::endl;

    // std::cout << "Nodes count of 2nd level from 0." << std::endl;
    // std::cout << g.nthLevelNodeCount(0, 4) << std::endl;
    // std::cout << std::endl;

    // std::cout << "All paths from 1 to 3." << std::endl;
    // g.getAllPaths(1, 3);
    // std::cout << std::endl;

    // if(g.isCycledDirected()) {
    //     std::cout << "There is Cycled directed graph." << std::endl;
    //     std::cout << std::endl;
    // } else if (g.isCycledUndirected()) {
    //     std::cout << "There is Cycled undirected graph." << std::endl;
    //     std::cout << std::endl;
    // }
    // std::cout << "DFS extra case: " << g.DFS_ExtraCase() << std::endl;
    // std::cout << std::endl;

    // std::cout << "TopSort result(DFS)." << std::endl;
    // //we should have acycled directed graph for topSort
    // g.topSort(); 
    // std::cout << std::endl;

    // std::cout << "Kahn's algorithm result." << std::endl;
    // //we should have acycled directed graph for Kahn's algorithm
    // g.topSortKahn();
    // std::cout << std::endl;

    // std::cout << "Strongly Connected Components with Kosaraju's algorithm:\n";
    // for (const auto& scc : g.Kosaraju()) {
    //     for (int v : scc) {
    //         std::cout << v << " ";
    //     }
    // }
    // std::cout << std::endl;


    std::cout << "Strongly Connected Components with Tarjan's algorithm:\n";
    for (const auto& scc : g.Tarjan()) {
        for (int v : scc) {
            std::cout << v << " ";
        }
    }
    std::cout << std::endl;
}




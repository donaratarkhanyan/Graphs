#include <iostream>
#include "adjMatrix.h"

int main()
{
    Graph g(6);
    g.addEdge(0, 1, 6);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 3, 4);
    g.addEdge(1, 4, 3);
    g.addEdge(1, 5, 5);
    g.addEdge(2, 5, 10);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 3, 2);

    std::cout << "Display the graph." << std::endl;
    g.print();
    std::cout << std::endl;

    std::cout << "BFS of Weighted graph." << std::endl;
    g.BFS(0);
    std::cout << std::endl;

    // std::cout << "DFS Iterative of Weighted graph." << std::endl;
    // g.DFS_Iterative(0);
    // std::cout << std::endl;

    // std::cout << "DFS Recursive of Weighted graph." << std::endl;
    // g.DFS_Recursive(0);
    // std::cout << std::endl;

    // std::cout << "Transposed graph." << std::endl;
    // g.transpose();
    // g.print();
    // std::cout << std::endl;

    // std::cout << "SSSP for this Graph."<< g.ShortestPath(1, 2) << std::endl;
    // std::cout << std::endl;

    // std::cout << "Count of 2nd level nodes from 0 level:  "<< g.nthLevelNodeCount(0, 2) << std::endl;4

    // std::cout << "All path from x to y." << std::endl;
    // std::vector<std::vector<int>> allPaths = g.getAllPaths(0, 5);
    // for (const auto& path : allPaths) {
    //     for (int vertex : path) {
    //         std::cout << vertex << "  ";
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << std::endl;   


    // if (g.isCycledUndirected()) {
    //     std::cout << "We have undirected cycled graph!!!" << std::endl;
    // } else if (g.isCycledDirected()) {
    //     std::cout << "We have directed cycled graph!!!" << std::endl;
    // }

    // std::cout << "TopSort result: ";
    // g.topSort();
    // std::cout << std::endl; 


    // std::cout << "Kahn's result." << std::endl;
    // std::vector<int> result = g.topSortKahn();
    // for (int i = 0; i < result.size(); ++i) {
    //     std::cout << result[i] << " ";
    // }
    // std::cout << std::endl;   

    // std::cout << "Tarjan's algorithm:" << std::endl;
    // std::vector<std::vector<int>> result = g.Tarjan();
    // for (auto u : result) {
    //     for (int vertex : u) {
    //         std::cout << vertex << "  ";
    //     }
    // }
    // std::cout << std::endl;   
}



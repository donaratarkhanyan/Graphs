#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <map>  
#include <climits>
#include "DisjointSet.h"

class Graph
{
public:
    Graph(int n);
    void addVertex();
    void addEdge(int u, int v, double weight);  
    void BFS(int start) const;
    void DFS_Iterative(int start) const;
    void DFS_Recursive(int start) const;
    void print() const;
    void transpose();
    int ShortestPath(int start, int level);
    int nthLevelNodeCount (int src, int level) const;
    std::vector<std::vector<int>> getAllPaths(int src, int dest);
    bool isCycledDirected();
    bool isCycledUndirected();
    int DFS_ExtraCase();
    int BFS_ExtraCase();
    void topSort();
    std::vector<int> topSortKahn();
    std::vector<std::vector<int>> Kosaraju();
    std::vector<std::vector<int>> Tarjan();
    void Dijkstra(int source);
    void Bellman_Ford(int source);
    int PrimsAlgorithm(int src) const;
    int KruskalsAlgorithm() const;

private:
    int numVertices;
    std::vector<std::vector<std::pair<int, int>>> adjList;

    void dfsHelper(int start, std::vector<bool>& visit) const;
    void topSortSSSP(int i, std::vector<bool>& visited, std::stack<int>& Stack);
    void allPathHelper(int src, int dest, std::vector<int>& currPath, std::vector<bool>& visit, std::vector<std::vector<int>>& allPaths);
    bool dfsisCycledDirected(int source, std::vector<bool>& visit, std::vector<bool>& recstack);
    bool dfsisCycledUndirected(std::vector<bool>& visit, int source, int parent);
    void dfsExtraCases(int source, std::vector<bool>& visit);
    void bfsExtraCases(int start, std::vector<bool>& visited);
    void dfstopSort(int source, std::vector<bool>& visit, std::stack<int>& s);
    void fillInOrder(int src, std::stack<int>& s, std::vector<bool>& visit);
    void scc_transpose();
    void scc_dfs(int src, std::vector<bool>& visit, std::vector<int>& component);
    void dfs_tarjan(int u, int& time, std::vector<int>& ids, std::vector<int>& low, std::stack<int>& st, std::vector<bool>& inStack, std::vector<std::vector<int>>& scc);
};

#endif  // GRAPH_H

#ifndef ADJ_MATRIX_H
#define ADJ_MATRIX_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

class Graph
{
public:
    Graph(int n);                                               
    void addVertex();                                           
    void addEdge(int src, int dest);                            
    void removeEdge (int src, int dest);                        
    void BFS(int start) const;                                  
    void DFS_Iterative(int start) const;                              
    void DFS_Recursive(int start) const;                        
    void print() const;                                                
    void transpose();                                           
    std::vector<int> ShortestPath(int start, int end);                         
    std::vector<int> nthLevelNodeCount (int src, int level);
    std::vector<std::vector<int>> getAllPaths(int src, int dest) const;  
    bool isCycledDirected();
    bool isCycledUndirected();
    int DFS_ExtraCase();
    void topSort();
    void topSortKahn(); 
    std::vector<std::vector<int>> Kosaraju();       
private:
    int numVertices;
    std::vector<std::vector<int>> adjMatrix;
    void dfsHelper(int start, std::vector<bool>& visit) const;
    void allPathHelper(int src, int dest, std::vector<int>& currPath, std::vector<bool>& visited, std::vector<std::vector<int>>& allPaths) const;
    bool dfsisCycledDirected(int source, std::vector<bool>& visit, std::vector<bool>& recstack);
    bool dfsisCycledUndirected(std::vector<bool>& visit, int source, int parent);
    void dfsExtraCases(int source, std::vector<bool>& visit);
    void dfstopSort(int source, std::vector<bool>& visit, std::stack<int>& s);
    void fillInOrder(int src, std::vector<bool>& visit, std::stack<int>& s);
    void scc_dfs(int src, std::vector<bool>& visit, std::vector<int>& component);
    void scc_transpose();
};

#endif // ADJ_MATRIX_H
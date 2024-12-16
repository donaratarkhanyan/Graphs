#include "adjMatrix.h"

Graph::Graph(int n) 
    : numVertices(n)
    , adjMatrix (n, std::vector<std::pair<int, int>>(n, {0, 0}))
{}

void Graph::addVertex()
{
    ++numVertices;
    adjMatrix.resize(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        adjMatrix[i].resize(numVertices, {0, 0});
    }
}

void Graph::addEdge(int u, int v, double weight)
{
    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
        adjMatrix[u][v] = {1, weight};
        adjMatrix[v][u] = {1, weight};
    }
}

void Graph::print() const
{
    for (int i = 0; i < numVertices; ++i) {
        for (auto j : adjMatrix[i]) {
            std::cout << "{" << j.first << ", " << j.second << "} "; 
        }
        std::cout << std::endl;
    }
}

void Graph::BFS(int start) const
{
    std::vector<bool> visit (numVertices, false);
    std::queue<int> q;

    q.push(start);
    visit[start] = true;

    while (!q.empty()) {
        int tmp = q.front();
        std::cout << tmp << " ";
        q.pop();        
        for (auto i : adjMatrix[tmp]) {
            if (adjMatrix[tmp][i].first == 1 && !visit[i.first]) {
                q.push(i.first);
                visit[i.first] = true;
            }
        }
    }
}

 


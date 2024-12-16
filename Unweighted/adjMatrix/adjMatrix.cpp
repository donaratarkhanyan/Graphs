#include "adjMatrix.h"

Graph::Graph(int n)
    : numVertices{n}
    , adjMatrix{} 
{
    adjMatrix.resize(numVertices, std::vector<int>(numVertices, 0));
}

void Graph::addVertex() {
    ++numVertices;
    adjMatrix.resize(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        adjMatrix[i].resize(numVertices);
    }
}

void Graph::addEdge(int src, int dest) {
    if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
        adjMatrix[src][dest] = 1;
        adjMatrix[dest][src] = 1;
    }
}

void Graph::removeEdge(int src, int dest) {
    if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
        adjMatrix[src][dest] = 0;
    }
}

void Graph::BFS(int start) const {
    std::vector<bool> visit(numVertices, false);
    std::queue<int> q;

    visit[start] = true;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        std::cout << current << " ";
        q.pop();
        for (int u = 0; u < numVertices; ++u) {
            if (!visit[u] && adjMatrix[current][u] == 1) {
                visit[u] = true;
                q.push(u);
            }
        }
    }
}

void Graph::DFS_Iterative(int start) const {
    std::vector<bool> visit(numVertices, false);
    std::stack<int> s;

    visit[start] = true;
    s.push(start);

    while (!s.empty()) {
        int current = s.top();
        std::cout << current << " ";
        s.pop();
        for (int u = 0; u < numVertices; ++u) {
            if (adjMatrix[current][u] == 1 && !visit[u]) {
                visit[u] = true;
                s.push(u);
            }
        }
    }
}

void Graph::DFS_Recursive(int start) const {
    std::vector<bool> visit(numVertices, false);
    dfsHelper(start, visit);
    std::cout << std::endl;
}

void Graph::dfsHelper(int start, std::vector<bool>& visit) const {
    visit[start] = true;
    std::cout << start << " ";
    for (int u = 0; u < numVertices; ++u) {
        if (adjMatrix[start][u] == 1 && !visit[u]) {
            dfsHelper(u, visit);
        }
    }
}

void Graph::print() const {
    for (int i = 0; i < adjMatrix.size(); ++i) {
        for (int j = 0; j < adjMatrix[i].size(); ++j) {
            std::cout << adjMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::transpose() {
    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) {
            std::swap(adjMatrix[i][j], adjMatrix[j][i]);
        }
    }
}

std::vector<int> Graph::ShortestPath(int start, int end)
{
    std::vector<bool> visit (numVertices, false);
    std::vector<int> parent (numVertices, -1);
    std::queue<int> q;

    visit[start] = true;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        if (current == end) {
            std::vector<int> path;
            for (int v = end; v != -1; v = parent[v]) {
                path.push_back(v);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }
        for (int u : adjMatrix[current]) {
            if (!visit[u] && adjMatrix[current][u] == 1) {
                visit[u] = true;
                parent[u] = current;
                q.push(u);
            }
        }
    }
    return {};
}

std::vector<std::vector<int>> Graph::getAllPaths(int src, int dest) const
{
    if (src < 0 || src > adjMatrix.size() -  1 || dest < 0 || dest > adjMatrix.size() - 1) {
        std::cout << "src or dest" << std::endl;
        exit(1);
    }

    std::vector<bool> visit(numVertices, false);
    std::vector<std::vector<int>> allPaths;
    std::vector<int> currPath;
    allPathHelper(src, dest, currPath, visit, allPaths);
    return allPaths;
}

void Graph::allPathHelper(int src, int dest, std::vector<int>& currPath, std::vector<bool>& visit, std::vector<std::vector<int>>& allPaths) const
{
    visit[src] = true;
    currPath.push_back(src);
    
    if (src == dest) {
        allPaths.push_back(currPath);
    } else {
        for (auto i : adjMatrix[src]) {
            if (!visit[i] && adjMatrix[src][i] == 1) {
                allPathHelper(i, dest, currPath, visit, allPaths);  
            }
        }
    }
    visit[src] = false;
    currPath.pop_back();
}

bool Graph::isCycledDirected()
{
    std::vector<bool> visit (numVertices, false);
    std::vector<bool> recStack (numVertices, false);
    for (int i = 0; i < numVertices; ++i) {
        if (!visit[i]) {
            if (dfsisCycledDirected(i, visit, recStack)) {
                return true;
            }
        }
    }
    return false;
}

bool Graph::dfsisCycledDirected(int source, std::vector<bool>& visit, std::vector<bool>& recstack)
{
    visit[source] = true;
    recstack[source] = true;
    for (auto u : adjMatrix[source]) {
        if (!visit[u] && adjMatrix[source][u] == 1) {
            if (dfsisCycledDirected(u, visit, recstack)) {
                return true;
            } 
        } else if (recstack[u]) {
            return true;
        }
    }
    recstack[source] = false;
    return false;
}

bool Graph::isCycledUndirected()
{
    std::vector<bool> visit (numVertices, false);
    int parent = -1;
    for (int i = 0; i < numVertices; ++i) {
        if (!visit[i]) {
            if (dfsisCycledUndirected(visit, i, parent)) {
                return true;
            }
        }
    }
    return false;
}

bool Graph::dfsisCycledUndirected(std::vector<bool>& visit, int source, int parent)
{
    visit[source] = true;
    for (auto n : adjMatrix[source]) {
        if (!visit[n] && adjMatrix[source][n] == 1) {
            if (dfsisCycledUndirected(visit, n, source)) {
                return true;
            }
        } else if (n != parent) {
            return true;
        }
    }
    return false;
}

int Graph::DFS_ExtraCase()
{
    std::vector<bool> visit (numVertices, false);
    int ComponentCount = 0;
    for (int i = 0; i < numVertices; ++i) {
        if (!visit[i]) {
            dfsExtraCases(i, visit);
            ComponentCount++;
        }
    }
    return ComponentCount;
}

void Graph::dfsExtraCases(int source, std::vector<bool>& visit) 
{
    visit[source] = true;
    for (int i = 0; i < numVertices; ++i) {
        if (!visit[i] && adjMatrix[source][i] == 1) {
            dfsExtraCases(i, visit);
        }
    }
}

// std::vector<int> nthLevelNodeCount (int src, int level)
// {
    
// }

void Graph::topSort() 
{
    std::vector<bool> visited(numVertices, false);
    std::stack<int> s;

    for (int i = 0; i < numVertices; ++i) {
        if (!visited[i]) {
            dfstopSort(i, visited, s);
        }
    }

    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
}

void Graph::dfstopSort(int source, std::vector<bool>& visited, std::stack<int>& s) {
    visited[source] = true;

    for (auto v : adjMatrix[source]) {
        if (!visited[v]) {
            dfstopSort(v, visited, s);
        }
    }

    s.push(source);
}


void Graph::topSortKahn()
{
    if (isCycledDirected()) {
        std::cout << "Cycled Graph!!" << std::endl;
        return;
    }

    std::vector<int> inDegree(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        for (auto u : adjMatrix[i]) {
            if (adjMatrix[i][u] == 1) {
                inDegree[u]++;
            }
        }
    }

    std::queue<int> q;
    for (int i = 0; i < numVertices; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    std::vector<int> result;
    while(!q.empty()) {
        int n = q.front();
        q.pop();
        result.push_back(n);
        for (auto i : adjMatrix[n]) {
            if (adjMatrix[n][i] == 1) {
                inDegree[i]--;
                if (inDegree[i] == 0) {
                    q.push(i);
                }
            }
        }
    }
    if (result.size() != numVertices) {
        std::cout << "Cycled Graph!!" << std::endl;
        return;
    }

    for (int i = 0; i < result.size(); ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

std::vector<std::vector<int>> Graph::Kosaraju()
{
    std::vector<bool> visit (numVertices, false);
    std::stack<int> s;
    for (int i = 0; i < numVertices; ++i) {
        if (!visit[i]) {
            fillInOrder(i, visit, s);
        }
    }

    scc_transpose();
    visit.assign(numVertices, false);
    std::vector<std::vector<int>> scc;

    while (!s.empty()) {
        int v = s.top();
        s.pop();
            if (!visit[v]) {
                std::vector<int> component;
                scc_dfs(v, visit, component);
                scc.push_back(component);
            }
        }
    return scc;
}

void Graph::fillInOrder(int src, std::vector<bool>& visit, std::stack<int>& s)
{
    visit[src] = true;
    for (auto u : adjMatrix[src]){
        if (!visit[u] && adjMatrix[src][u] == 1) {
            fillInOrder(u, visit, s);
        }
    }
    s.push(src);
}

void Graph::scc_transpose()
{
    Graph tmp(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        for (auto j : adjMatrix[i]){
            tmp.adjMatrix[j].push_back(i);
        }
    }
    *this = tmp;
}

void Graph::scc_dfs(int src, std::vector<bool>& visit, std::vector<int>& component)
{
    visit[src] = true;
    component.push_back(src);
    for (auto u : adjMatrix[src]) {
        if (!visit[u] && adjMatrix[src][u]) {
            scc_dfs(u, visit, component);
        }
    }
}
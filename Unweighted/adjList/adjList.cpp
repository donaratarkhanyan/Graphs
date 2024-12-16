#include "adjList.h"

Graph::Graph(int n)
    : numVertices {n}
    , adjList {}
{
    adjList.resize(numVertices);
}

void Graph::addVertex() 
{
    ++numVertices;
    adjList.resize(numVertices);
}

void Graph::addEdge(int source , int dest)
{
    if (source < 0 || dest < 0) {
        std::cout << "Invalid vertex index" << std::endl;
        return;
    } else if (source >= adjList.size() || dest >= adjList.size()) {
        std::cout << "Invalid vertex index" << std::endl;
        return;
    }
    adjList[source].push_back(dest); 
    adjList[dest].push_back(source);
}  

void Graph::BFS(int start) const 
{
    std::vector<bool> visit (numVertices, false);
    std::queue<int> q;
    visit[start] = true;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        std::cout << u << " ";
        q.pop();
        for (int v : adjList[u]) {
            if (!visit[v]){
                visit[v] = true;
                q.push(v);
            }
        }
    }
}

void Graph::DFS_Iterative(int start) const
{
    std::vector<bool> visit (numVertices, false);   
    std::stack<int> s;
    visit[start] = true;
    s.push(start);
    while (!s.empty()) {
        int v = s.top();
        std::cout <<  v << " ";
        s.pop();
        for (int u : adjList[v]) {
            if (!visit[u]) {
                s.push(u);
                visit[u] = true;
            }
        }
    }
}


void Graph::DFS_Recursive(int start) const
{
    std::vector<bool> visit (numVertices, false);   
    dfsHelper(start, visit);
    std::cout << std::endl;
}

void Graph::dfsHelper(int start, std::vector<bool>& visit) const
{
    visit[start] = true;
    std::cout << start << " ";
    for (int v : adjList[start]) {
        if (!visit[v]) {
            dfsHelper(v, visit);
        }
    }
}

void Graph::print() const
{
    for(int i = 0; i < adjList.size(); ++i) {
        std::cout << i << " -> ";
        for(int j = 0; j < adjList[i].size(); ++j) {
            std::cout << adjList[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::transpose()
{
    Graph g(numVertices);
    for (int i = 0; i < numVertices; i++) {
        for (int j : adjList[i]) {
            g.adjList[j].push_back(i);
        }
    }
    this -> adjList = g.adjList;
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
        for (int u : adjList[current]) {
            if (!visit[u]) {
                visit[u] = true;
                parent[u] = current;
                q.push(u);
            }
        }
    }
    return {};
}


int Graph::nthLevelNodeCount(int src, int level) const
{
    if (level < 0) {
        throw std::invalid_argument("Invalid Level!!!");
    }
    std::vector<bool> visit (numVertices, false);
    std::queue<std::pair<int, int>> q;
    int count = 0;

    q.push({src, 0});
    visit[src] = true;
    while (!q.empty()) {
        auto [currVertex, currLevel] = q.front();
        q.pop();
        if (currLevel == level) {
           ++count; 
        } else if (currLevel < level) {
            for (auto u : adjList[currVertex]) {
                if (!visit[u]) {
                    visit[u] = true;
                    q.push({u, currLevel + 1});
                }
            }
        }   
    }
    return count;
}

void Graph::getAllPaths(int src, int dest) const {
    std::vector<bool> visit(numVertices, false);
    std::vector<std::vector<int>> allPaths;
    std::vector<int> currPath;
    allPathHelper(src, dest, currPath, visit, allPaths);
    for (const auto& path : allPaths) {
        for (int vertex : path) {
            std::cout << vertex << "  ";
        }
        std::cout << std::endl;
    }
}

void Graph::allPathHelper(int src, int dest, std::vector<int>& currPath, std::vector<bool>& visit, std::vector<std::vector<int>>& allPaths) const {
    visit[src] = true;
    currPath.push_back(src);

    if (src == dest) {
        allPaths.push_back(currPath);
    } else {
        for (int neighbor : adjList[src]) {
            if (!visit[neighbor]) {
                allPathHelper(neighbor, dest, currPath, visit, allPaths);
            }
        }
    }
    visit[src] = false;
    currPath.pop_back();
}



bool Graph::isCycledDirected()
{
    std::vector<bool> visit(numVertices, false);
    std::vector<bool> recStack(numVertices, false);

    for (int i = 0; i < numVertices; ++i) {
        if (!visit[i]) {
            if (dfsisCycledDirected(i, visit, recStack)) {
                return true;
            }
        }
    }
    return false;
}

bool Graph::dfsisCycledDirected(int source, std::vector<bool>& visit, std::vector<bool>& recStack)
{
    visit[source] = true;
    recStack[source] = true;
    for (auto i : adjList[source]) {
        if (!visit[i]) {
            if (dfsisCycledDirected(i, visit, recStack)) {
                return true;
            }
        } else if (recStack[i]) {
            return true;
        }
    }
    recStack[source] = false;
    return false;
}

bool Graph::isCycledUndirected()
{
    std::vector<bool> visit (numVertices, false);
    int parent = -1;
    for (int i = 0; i < numVertices; ++i) {
        if (!visit[i]) {
            if(dfsisCycledUndirected(visit, i, parent)) {
                return true;
            }
        }
    }
    return false;
}

bool Graph::dfsisCycledUndirected(std::vector<bool>& visit, int source, int parent)
{
    visit[source] = true;
    for (auto i : adjList[source]) {
        if (!visit[i]) {
            if (dfsisCycledUndirected(visit, i, source)) {
                return true;
            }
        } else if (i != parent) {
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
        if (!visit[i]) {
            dfsExtraCases(i, visit);
        }
    }   
}

void Graph::topSort() {
    if (isCycledDirected()) {
        std::cout << "Cycled Graph!!" << std::endl;
        return;
    }

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

    for (auto v : adjList[source]) {
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

    std::vector<int> inDegree(numVertices, 0);
    for (int i = 0; i < numVertices; ++i) {
        for (auto u : adjList[i]) {
            inDegree[u]++;
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
        for (auto i : adjList[n]) {
            inDegree[i]--;
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }
    }
    if (result.size() != numVertices) {
        std::cout << "Cycled Graph!!" << std::endl;
        return;
    }

    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;
}

std::vector<std::vector<int>> Graph::Kosaraju() {
    std::vector<bool> visit(numVertices, false);
    std::stack<int> s;

    for (int i = 0; i < numVertices; ++i) {
        if (!visit[i]) {
            fillInOrder(i, s, visit);
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

void Graph::fillInOrder(int src, std::stack<int>& s, std::vector<bool>& visit) {
    visit[src] = true;
    for (auto v : adjList[src]) {
        if (!visit[v]) {
            fillInOrder(v, s, visit);
        }
    }
    s.push(src);
}

void Graph::scc_dfs(int v, std::vector<bool>& visit, std::vector<int>& component) {
    visit[v] = true;
    component.push_back(v);
    for (auto i : adjList[v]) {
        if (!visit[i]) {
            scc_dfs(i, visit, component);
        }
    }
}

void Graph::scc_transpose() {
    Graph tmp(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        for (auto j : adjList[i]) {
            tmp.adjList[j].push_back(i);
        }
    }
    *this = tmp;
}

std::vector<std::vector<int>> Graph::Tarjan()
{
    std::vector<int> ids(numVertices, -1), low(numVertices, -1);
    std::vector<std::vector<int>> scc;
    std::vector<bool> inStack(numVertices, false);
    std::stack<int> st;
    int time = 0;
    for (int i = 0; i < numVertices; ++i) {
        if (ids[i] == -1) {
            dfs_tarjan(i, time, ids, low, st, inStack, scc);
        }
    }
    return scc;
}

void Graph::dfs_tarjan(int u, int& time, std::vector<int>& ids, std::vector<int>& low, std::stack<int>& st, std::vector<bool>& inStack, std::vector<std::vector<int>>& scc)
{
    ids[u] = low[u] = ++time;
    inStack[u] = true;
    st.push(u);

    for (int v : adjList[u]) {
        if (ids[v] == -1) {
            dfs_tarjan(v, time, ids, low, st, inStack, scc);
            low[u] = std::min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = std::min(low[u], ids[v]);
        }
    }

    if (low[u] == ids[u]) {
        std::vector<int> component;
        while (st.top() != u) {
            int v = st.top();
            st.pop();
            component.push_back(v);
            inStack[v] = false;
        }
        component.push_back(u);
        st.pop();
        inStack[u] = false;
        scc.push_back(component);
    }
}



#include "adjList.h"

Graph::Graph(int n) 
    : numVertices(n) 
    , adjList(n) 
{
    adjList.resize(numVertices);
}

void Graph::addVertex()
{
    ++numVertices;
    adjList.resize(numVertices);
}

void Graph::addEdge(int u, int v, double weight)
{
    adjList[u].push_back({v, weight});
    //adjList[v].push_back({u, weight});
}

void Graph::BFS(int start) const
{
    std::vector<bool> visit (numVertices, false);
    std::queue<int> q;
    visit[start] = true;
    q.push(start);

    while (!q.empty()) {
        int tmp = q.front();
        std::cout << tmp << " ";
        q.pop();
        for (auto i : adjList[tmp]) {
            if (!visit[i.first]) {
                visit[i.first] = true;
                q.push(i.first);
            }
        }
    }
    std::cout << std::endl;
}

void Graph::DFS_Iterative(int start) const
{
    std::vector<bool> visit(numVertices, false);
    std::stack<int> st;

    visit[start] = true;
    st.push(start);

    while (!st.empty()) {
        int tmp = st.top();
        std::cout << tmp << " ";
        st.pop();
        for (auto i : adjList[tmp]) {
            if (!visit[i.first]) {
                visit[i.first] = true;
                st.push(i.first);
            }
        }
    }
    std::cout << std::endl;
}

void Graph::DFS_Recursive(int start) const
{
    std::vector<bool> visit(numVertices, false);
    dfsHelper(start, visit);
    std::cout << std::endl;
}

void Graph::dfsHelper(int start, std::vector<bool>& visit) const
{
    visit[start] = true;
    std::cout << start << " ";
    for (auto i : adjList[start]) {
        if(!visit[i.first]) {
            dfsHelper(i.first, visit);
        }
    }
}

void Graph::print() const
{
    for (int i = 0; i < numVertices; ++i) {
        std::cout << i << " -> ";
        for (auto j : adjList[i]) {
            std::cout << "{" << j.first << ", " << j.second << "}";
        }
        std::cout << std::endl;
    }
}

void Graph::transpose()
{
    Graph tmp(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        for (auto [j, w] : adjList[i]) {
            tmp.adjList[j].push_back({i, w});
        }
    }
    *this = tmp;  
}


void Graph::topSortSSSP(int v, std::vector<bool>& visited, std::stack<int>& Stack) 
{
    visited[v] = true;
    for (auto u : adjList[v]) {
        if (!visited[u.first]) {
            topSortSSSP(u.first, visited, Stack);
        }
    }
    Stack.push(v);
}

int Graph::ShortestPath(int start, int level)
{
    std::vector<bool> visit(numVertices, false);
    std::stack<int> st;
    for (int i = 0; i < numVertices; ++i) {
        if (!visit[i]) {
            topSortSSSP(i, visit, st);
        }
    }
    std::vector<int> dist(numVertices, INT_MAX);
    dist[start] = 0;

    while (!st.empty()) {
        int tmp = st.top();
        st.pop();

        if (dist[tmp] != INT_MAX) {
            for (auto& u : adjList[tmp]) {
                if (dist[tmp] + u.second < dist[u.first]) {
                    dist[u.first] = dist[tmp] + u.second;
                }
            }
        }
    }
    int res = dist[level] - dist[start];
    if (res < 0 || res == INT_MAX) {
        std::cerr << "Don't way!" << std::endl;
        exit(0);
    }
    return res;
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
                if (!visit[u.first]) {
                    visit[u.first] = true;
                    q.push({u.first, currLevel + 1});
                }
            }
        }
    }
    return count;
}

std::vector<std::vector<int>> Graph::getAllPaths(int src, int dest)
{
    std::vector<bool> visit (numVertices, false);
    std::vector<int> currpath;
    std::vector<std::vector<int>> allpaths;
    allPathHelper(src, dest, currpath, visit, allpaths);
    return allpaths;
}

void Graph::allPathHelper(int src, int dest, std::vector<int>& currPath, std::vector<bool>& visit, std::vector<std::vector<int>>& allPaths)
{
    visit[src] = true;
    currPath.push_back(src);

    if (src == dest) {
        allPaths.push_back(currPath);
    } else {
        for (auto u : adjList[src]) {
            if (!visit[u.first]) {
                allPathHelper(u.first, dest, currPath, visit, allPaths);
            }
        }
    }
    visit[src] = false;
    currPath.pop_back();
}           

bool Graph::isCycledDirected()
{
    std::vector<bool> visit (numVertices, false);
    std::vector<bool> recstack (numVertices, false);

    for (int i = 0; i < numVertices; ++i) {
        if (!visit[i]) {
            if (dfsisCycledDirected(i, visit, recstack)) {
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

    for (auto u : adjList[source]) {
        if (!visit[u.first]) {
            if (dfsisCycledDirected(u.first, visit, recstack)){
                return true;
            }
        } else if (recstack[u.first]) {
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
    for (int i = 0; i < numVertices; ++i){
        if (!visit[i]){
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
    for (auto u : adjList[source]) {
        if (!visit[u.first]) {
            if (dfsisCycledUndirected(visit, u.first, parent)) {
                return true;
            }
        } else if (u.first != parent) {
            return true;
        }
    }
    return false;
}   

int Graph::DFS_ExtraCase()
{
    std::vector<bool> visit (numVertices, false);
    int count = 0;
    for (int i = 0; i < numVertices; ++i) {
        if (!visit[i]) {
            dfsExtraCases(i, visit);
            ++count;
        }
    }
    return count;
}

void Graph::dfsExtraCases(int source, std::vector<bool>& visit)
{
    visit[source] = true;
    for (auto u : adjList[source]) {
        if (!visit[u.first]) {
            dfsExtraCases(u.first, visit);
        }
    }
}

int Graph::BFS_ExtraCase() {
    std::vector<bool> visited(numVertices, false);
    int count = 0;

    for (int i = 0; i < numVertices; ++i) {
        if (!visited[i]) {
            bfsExtraCases(i, visited);
            ++count;
        }
    }

    return count;
}

void Graph::bfsExtraCases(int start, std::vector<bool>& visited) {
    std::queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (auto u : adjList[v]) { 
            if (!visited[u.first]) {
                visited[u.first] = true;
                q.push(u.first);
            }
        }
    }
}

void Graph::topSort()
{   
    std::vector<bool> visit(numVertices, false);
    std::stack<int> s;

    for (int i = 0; i < numVertices; ++i) {
        if (!visit[i]) {
           dfstopSort(i, visit, s);
        }
    }
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
}

void Graph::dfstopSort(int source, std::vector<bool>& visit, std::stack<int>& s)
{
    visit[source] = true;
    for (auto u : adjList[source]) {
        if (!visit[u.first]) {
            dfstopSort(u.first, visit, s);
        }
    }

    s.push(source);
}

std::vector<int> Graph::topSortKahn()
{
    std::vector <int> inDegree (numVertices, 0);
    for (int i = 0; i < numVertices; ++i) {
        for (auto u : adjList[i]) {
            if (inDegree[i] == 0) {
                ++inDegree[i];
            }
        }
    }

    std::queue <int> q;
    for (int i = 0; i < numVertices; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    std::vector<int> result;
    while (!q.empty()) {
        int tmp = q.front();
        q.pop();
        result.push_back(tmp);

        for (auto u : adjList[tmp]) {
            if (--inDegree[u.first] == 0) {
                q.push(u.first);
            }
        }
    }

    if (result.size() != numVertices) {
        throw std::invalid_argument("We have cycled graph!!!");
    }
    return result;
}

std::vector<std::vector<int>> Graph::Kosaraju()
{
    std::vector<bool> visit (numVertices, false);
    std::stack<int> s;
    for (int i = 0; i < numVertices; ++i) {
        if (!visit[i]) {
            fillInOrder(i, s, visit);
        }
    }

    scc_transpose();
    visit.assign(numVertices, false);
    std::vector<std::vector<int>> scc;

    while(!s.empty()){
        int tmp = s.top();
        s.pop();

        for (auto u : adjList[tmp]){
            if (!visit[u.first]) {
                std::vector<int> path;
                scc_dfs(u.first, visit, path);
                scc.push_back(path);
            }
        }
    }
    return scc;
}

void Graph::fillInOrder(int src, std::stack<int>& s, std::vector<bool>& visit)
{
    visit[src] = true;
    for (auto u : adjList[src]) {
        if (!visit[u.first]) {
            fillInOrder(u.first, s, visit);
        }
    }
    s.push(src);
}

void Graph::scc_transpose()
{
    Graph tmp(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        for (auto [j, w] : adjList[i]) {
            tmp.adjList[j].push_back({i, w});
        }
    }
    *this = tmp;
}

void Graph::scc_dfs(int src, std::vector<bool>& visit, std::vector<int>& component)
{
    visit[src] = true;
    component.push_back(src);
    for (auto i : adjList[src]) {
        if (!visit[i.first]) {
            scc_dfs(i.first, visit, component);
        }
    }
}

std::vector<std::vector<int>> Graph::Tarjan()
{
    std::vector <int> ids (numVertices, -1);
    std::vector <int> low (numVertices, -1);
    std::vector <bool> Onstack (numVertices, false);
    std::vector<std::vector<int>> scc;
    std::stack <int> s;
    int time = 0;
    for (int i = 0; i < numVertices; ++i) {
        if (ids[i] == -1) {
            dfs_tarjan(i, time, ids, low, s, Onstack, scc);
        }
    }
    return scc;
}

void Graph::dfs_tarjan(int u, int& time, std::vector<int>& ids, std::vector<int>& low, std::stack<int>& st, std::vector<bool>& onStack, std::vector<std::vector<int>>& scc)
{
    ids[u] = low[u] = ++time;
    onStack[u] = true;
    st.push(u);

    for (auto v : adjList[u]) {
        if (ids[v.first] == -1) {
            dfs_tarjan(v.first, time, ids, low, st, onStack, scc);
        }
        if (onStack[v.first] == true){
            low[u] = std::min(low[u], low[v.first]);
        }
    }
    
    if (low[u] == ids[u]) {
        std::vector<int> res;
        while (st.top() != u) {
            int tmp = st.top();
            onStack[tmp] = false;
            st.pop();
            res.push_back(tmp);
        }
        int tmp = st.top();
        onStack[tmp] = false;
        st.pop();
        res.push_back(tmp);
        scc.push_back(res);
    }

}

void Graph::Dijkstra(int source) {
    std::vector<int> dist(numVertices, INT_MAX);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto v : adjList[u]) {
            if (dist[u] + v.second < dist[v.first]) {
                dist[v.first] = dist[u] + v.second;
                pq.push({dist[v.first], v.first});
            }
        }
    }

    for (int i = 0; i < numVertices; ++i) {
        std::cout << dist[i] << " ";
    }
    std::cout << std::endl;
}


void Graph::Bellman_Ford(int source) {
    std::vector<int> dist(numVertices, INT_MAX);
    dist[source] = 0;
    for (int j = 1; j <= numVertices - 1; ++j) {
        for (int i = 0; i < numVertices; ++i){
            for (auto u : adjList[i]){ 
                if (dist[i] != INT_MAX && dist[i] + u.second < dist[u.first]){
                    dist[u.first] = dist[i] + u.second;
                }
            }
        }
    }
    
    for (int i = 0; i < numVertices; ++i){
        for (auto u : adjList[i]){ 
            if (dist[i] != INT_MAX && dist[i] + u.second < dist[u.first]){
                std::cerr << "ERROR from Bellman-ford!!!!" << std::endl;
                return;
            }
        }
    }
    for (int i = 0; i < dist.size(); ++i){
        std::cout << dist[i] << " ";
    }
    std::cout << std::endl;
}

int Graph::PrimsAlgorithm(int src) const
{
    if (src < 0 || src >= adjList.size()) {
        std::cerr << "Invalid source to start: " << std::endl;
        exit(1);
    }

    int n = adjList.size();
    std::vector<bool> inMST (n, false);
    std::vector<int> dist (n, std::numeric_limits<int>::max());

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});
    int MSTWeight = 0;

    while (!pq.empty()) {
        auto [weight, u] = pq.top();
        pq.pop();
        if (inMST[u]) continue;

        inMST[u] = true;
        MSTWeight += weight;

        for (const auto& [v, nextWeight] : adjList[u]) {
            if (!inMST[v] && nextWeight < dist[v]) {
                dist[v] = nextWeight;
                pq.push({dist[v], v});
            }
        }
    }

    return MSTWeight;
}


int Graph::KruskalsAlgorithm() const
{
    std::vector<std::pair<int, std::pair<int, int>>> edges;
    int n = adjList.size();
    for (int u = 0; u < n; ++u) {
        for (const auto& [v, weight] : adjList[u]) {
            edges.push_back({weight, {u, v}});
        }
    }

    std::sort(edges.begin(), edges.end());

    DisjointSet uf(n);
    int totalWeight = 0;

    for (const auto& [weight, edge] : edges) {
        int u = edge.first;
        int v = edge.second;

        if (uf.find(u) != uf.find(v)) {
            uf.unify(u, v);
            totalWeight += weight;
        }
    }

    return totalWeight; 

}
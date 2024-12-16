#ifndef DISJOINTSET_H
#define DISJOINTSET_H
#include <vector>

class Disjointset {
public:
    Disjointset(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);

        if (x != y) {
            if (rank[x] > rank[y]) {
                parent[y] = x;
            } else if (rank[x] < rank[y]) {
                parent[x] = y;
            } else {
                parent[y] = x;
                rank[x]++;
            }
            return true;  // Union was successful
        }
        return false;  // No union performed
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

#endif // DISJOINTSET_H
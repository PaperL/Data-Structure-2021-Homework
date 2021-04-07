//
// Created by Frank's Laptop on 2021/3/1.
//

#include <cstdio>
#include <cstring>

using namespace std;

int n, m;
struct nodeType {
    int w = 0;
    int e = 0;
    char c1 = 0, c2 = 0;
} node[100008];
char visited[100008];

int edgep = 0; // edge下标 [1,edgep] 范围内有效
struct edgeType {
    int fr = 0;
    int to = 0;
    int nxt = 0;
} edge[400008];

inline int qread(int &_k) {
    char _c = getchar();
    int _sign = 1;
    _k = 0;
    while (_c < 48 || _c > 57) {
        if (_c == '-')_sign = -1;
        _c = getchar();
    }
    while (_c >= 48 && _c <= 57) {
        _k = (_k << 3) + (_k << 1) - 48 + _c;
        _c = getchar();
    }
    printf("%d\n", _sign * _k);
    return (_sign * _k);
}

inline void addEdge(const int &k1, const int &k2) {
    edge[++edgep].fr = k1;
    edge[edgep].to = k2;
    edge[edgep].nxt = node[k1].e;
    node[k1].e = edgep;
}


void preDfs(int p, char fc1, char fc2) {

}

void preSolve() {
    memset(visited, 0, n + 1);
    preDfs(1, 0, 1);
}


void solve(int city1, int city2) {

}


int main() {
    qread(n);
    qread(m);
    for (int i = 0; i < n; ++i)qread(node[i].w);
    int k1, k2;
    for (int i = 0; i < m; ++i) {
        qread(k1);
        qread(k2);
        addEdge(k1, k2);
        addEdge(k2, k1);
    }
    preSolve();

    int q, k3;
    qread(q);
    while (q--) {
        qread(k1);
        qread(k2);
        qread(k3);
        if (k1 == 0)node[k2].w = k3;
        else solve(k2, k3);
    }
    return 0;
}
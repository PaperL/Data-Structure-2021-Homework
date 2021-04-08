//
// Created by Frank's Laptop on 2021/4/7.
//

#include <cstdio>
#include <cstring> // memcpy

namespace PTF {
// Here is PaperL's Template Function
// Version: 0.44
// Update Time: 2021.4.2

    template<typename T1, typename T2>
    struct sameType {
        constexpr operator bool() {
            return false;
        }
    };

    template<typename T>
    struct sameType<T, T> {
        constexpr operator bool() {
            return true;
        }
    };

    template<typename T>
    inline T qRead() {
        T _k;
        qRead(_k);
        return _k;
    }

    template<typename T>
    inline void qRead(T &_k) {
        char _c = getchar();
        bool _sign = false;
        _k = 0;
        while (_c < '0' || _c > '9') {
            if (_c == '-') _sign = true;
            _c = getchar();
        }
        while (_c >= '0' && _c <= '9') {
            _k = _k * 10 - 48 + _c;
            _c = getchar();
        }
        if (_sign) _k = -_k;
    }

    template<typename T, typename... argL>
    inline void qRead(T &_k, argL &... _argList) {
        qRead(_k);
        qRead(_argList...);
    }

    template<typename T>
    inline void qWrite(T _k) {
        if constexpr(sameType<T, char>()) {
            putchar(_k);
            return;
        } else if constexpr(sameType<T, const char *>() || sameType<T, char *>()) {
            size_t _p = 0;
            while (_k[_p] != '\0')putchar(_k[_p++]);
            return;
        } else if (_k != 0) {
            int _p = 0;
            char _c[24];
            if (_k < 0)putchar('-'), _k = -_k;
            while (_k) _c[_p++] = _k % 10 + 48, _k /= 10;
            while (_p--)putchar(_c[_p]);
        } else putchar('0');
    }

    template<typename T, typename... argL>
    inline void qWrite(T _k, argL ... _argList) {
        qWrite(_k);
        qWrite(_argList...);
    }

    template<typename T, typename... argL>
    inline void qWrite(const char _s, T _k, argL... _argList) {
        qWrite(_k);
        putchar(_s);
        if (sizeof...(_argList) != 0)
            qWrite(_s, _argList...);
    }

    template<typename T>
    inline T maxN(const T &_x, const T &_y) { return (_x > _y) ? _x : _y; }

    template<typename T, typename... argL>
    inline T maxN(const T &_x, const T &_y, const argL &... _argList) {
        return ((_x > _y) ? maxN(_x, _argList...) : maxN(_y, _argList...));
    }

    template<typename T>
    inline T minN(const T &_x, const T &_y) { return (_x < _y) ? _x : _y; }

    template<typename T, typename... argL>
    inline T minN(const T &_x, const T &_y, const argL &... _argList) {
        return ((_x < _y) ? minN(_x, _argList...) : minN(_y, _argList...));
    }
}
using namespace PTF;

#define MAXN 6008
#define INF (1e9+7)

int n, totW;
int fa[MAXN], w[MAXN], v[MAXN];
int dp[MAXN][MAXN];
int dfsP, dfsId[MAXN], next[MAXN];

struct Edge {
    int to;
    int next;
} edge[MAXN];
int edgep, head[MAXN];

inline void addEdge(const int &fr, const int &to) {
    edge[++edgep].to = to;
    edge[edgep].next = head[fr];
    head[fr] = edgep;
}

void dfs(int p) {
    int tmp = dfsP;
    dfsId[dfsP++] = p;
    for (int ep = head[p]; ep; ep = edge[ep].next) {
        const int &to = edge[ep].to;
        dfs(to);
    }
    next[tmp] = dfsP;
}

int main() {
    qRead(n, totW);
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= totW; ++j)
            dp[i][j] = -INF;
    for (int i = 1; i <= n; ++i) {
        qRead(fa[i], w[i], v[i]);
        addEdge(fa[i], i);
    }
    dfs(0);

    for (int i = 0; i <= n; ++i) {// i为dfs序
        for (int j = 0; j <= totW; ++j)
            dp[next[i]][j] = maxN(dp[next[i]][j], dp[i][j]);
        for (int j = 0; j <= totW - w[dfsId[i]]; ++j)
            dp[i + 1][j + w[dfsId[i]]] = maxN(dp[i + 1][j + w[dfsId[i]]], dp[i][j] + v[dfsId[i]]);
    }

    qWrite(dp[n + 1][totW], '\n');

    return 0;
}

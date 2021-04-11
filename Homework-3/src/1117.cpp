//
// Created by Frank's Laptop on 2021/4/9.
//

#pragma region BASIC

#include <algorithm> // sort

#define PAPERL_DEBUG

#pragma region PaperL_Header
#ifndef PTL_PTF_H
#define PTL_PTF_H

#include <cstdio>

namespace PTF {
// Here is PaperL's Template Function
// Version: 0.50
// Update Time: 2021.4.11

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
    inline void swapT(T &_x, T &_y) {
        T _temp(_x);
        _x = _y;
        _y = _temp;
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
}

#endif //PTL_PTF_H
#pragma endregion
using namespace PTF;

#define MAXN 100008
#define MAXMQ 200008
#define INF 1e9+7

int n, m, q;
int ans[MAXMQ];
#pragma endregion

#pragma region EDGE
int e1[MAXN]; // e1[i]: 从1号点到i号点路径长(即边权前缀和)
struct eqType {
    int t, u, v, w; // t 为类型(0修改, !0询问), w 为贡献(相对于一类边节省的距离)
    eqType(int _t = 0, int _u = 0, int _v = 0, int _w = 0) : t(_t), u(_u), v(_v), w(_w) {}
    bool operator<(const eqType &other) const { return ((u > other.u) || (u == other.u && t < other.t)); }
} eq[MAXMQ << 1];
int eqN;
#pragma endregion

#pragma region BIT
int tree[MAXN << 1];
inline int lowBit(const int &x) { return (x & -x); }
inline void update(int x, int k) {
    for (; x <= n; x += lowBit(x))
        tree[x] = minN(tree[x], k);
}
inline int query(int x) {
    int ret = INF;
    for (; x; x -= lowBit(x))
        ret = minN(ret, tree[x]);
    return ret;
}
#pragma endregion

int main() {
    qRead(n, m);
    for (int i = 1; i <= n; ++i)tree[i] = INF;
    for (int i = 2; i <= n; ++i) {
        qRead(e1[i]);
        e1[i] += e1[i - 1];
    }
    for (int i = 1; i <= m; ++i) {
        int u, v, c;
        qRead(u, v, c);
        eq[++eqN] = eqType(0, u, v, e1[u] - e1[v] + c);
    }
    qRead(q);
    for (int i = 1; i <= q; ++i) {
        int u, v;
        qRead(u, v);
        if (u != v) eq[++eqN] = eqType(i, u, v, (u < v) ? (e1[v] - e1[u]) : INF);
        else ans[i] = 0;
    }
    std::sort(eq + 1, eq + eqN + 1);

    for (int i = 1; i <= eqN; ++i) {
        if (eq[i].t == 0) update(eq[i].v, eq[i].w);
        else ans[eq[i].t] = minN(eq[i].w, e1[eq[i].v] - e1[eq[i].u] + query(eq[i].v));
    }

    for (int i = 1; i <= q; ++i)
        qWrite(ans[i], '\n');
    return 0;
}
//
// Created by Frank's Laptop on 2021/4/9.
//

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

//#define PAPERL_DEBUG

#define MAXN 100008
#define MODN (long long int)(1e9+7)
#define LCAN 17

struct sPair {
    int fir = 0, sec = 0;
};

int n, w[MAXN], del[MAXN];
long long int ans[MAXN];

struct edgeType {
    int fr, to;
    int nxt;
} edge[MAXN << 1];
int edgeP = 0, headEdge[MAXN];

inline void addEdge(int fr, int to) {
    edge[++edgeP].fr = fr;
    edge[edgeP].to = to;
    edge[edgeP].nxt = headEdge[fr];
    headEdge[fr] = edgeP;
}

int grp[MAXN];
sPair grpDia[MAXN];
long long int diaL[MAXN];
int fa[MAXN][LCAN], ws[MAXN][LCAN], dep[MAXN]; // ws 点权和

int findGrp(int p) {
    if (grp[p] == p)return p;
    return grp[p] = findGrp(grp[p]);
}

void initDfs(int p) {
    dep[p] = dep[fa[p][0]] + 1;
    for (int ep = headEdge[p]; ep; ep = edge[ep].nxt) {
        const int &to = edge[ep].to;
        if (to != fa[p][0]) {
            fa[to][0] = p;
            ws[to][0] = w[to];
            initDfs(to);
        }
    }
}

inline int lcaL(int x, int y) {
    //printf("<%d,%d>\n", x, y);
    if (dep[x] < dep[y])swapT(x, y);
    int sum = 0;
    for (int i = LCAN - 1; i >= 0; --i)
        if (dep[fa[x][i]] >= dep[y])
            sum += ws[x][i], x = fa[x][i];
    if (x == y)return sum + w[x];
    for (int i = LCAN - 1; i >= 0; --i)
        if (fa[x][i] != fa[y][i]) {
            sum += ws[x][i] + ws[y][i];
            x = fa[x][i], y = fa[y][i];
        }
    sum += ws[x][0] + ws[y][0] + w[fa[x][0]];
    return sum;
}

inline long long int pow(long long int x, int y) {
    long long int ret = 1;
    while (y) {
        if (y & 1) ret = ret * x % MODN;
        x = x * x % MODN;
        y >>= 1;
    }
    return ret;
}

inline void merge(int u, int v, int time) {

    // 并查集+lca 根据两树4直径端点选2得新直径
    int gu = findGrp(u), gv = findGrp(v);
#ifdef PAPERL_DEBUG
    printf("merge[%d]:: u:%d v:%d gu:%d gv:%d\n", time, u, v, gu, gv);
#endif
    grp[gu] = gv;
    ans[time] = ans[time + 1]
                * pow(diaL[gu], MODN - 2) % MODN
                * pow(diaL[gv], MODN - 2) % MODN;
#ifdef PAPERL_DEBUG
    printf("ans[time]: %lld\n", ans[time]);
#endif
    int l1 = lcaL(grpDia[gu].fir, grpDia[gv].fir),
            l2 = lcaL(grpDia[gu].sec, grpDia[gv].sec),
            l3 = lcaL(grpDia[gu].fir, grpDia[gv].sec),
            l4 = lcaL(grpDia[gu].sec, grpDia[gv].fir);
#ifdef PAPERL_DEBUG
    printf("l1:%d l2:%d l3:%d l4:%d\n", l1, l2, l3, l4);
#endif
    int k = maxN(l1, l2, l3, l4);
    sPair tp;
    if (diaL[gu] > k) k = diaL[gu], tp = grpDia[gu];
    else if (diaL[gv] > k) k = diaL[gv], tp = grpDia[gv];
    else if (k == l1) tp.fir = grpDia[gu].fir, tp.sec = grpDia[gv].fir;
    else if (k == l2) tp.fir = grpDia[gu].sec, tp.sec = grpDia[gv].sec;
    else if (k == l3) tp.fir = grpDia[gu].fir, tp.sec = grpDia[gv].sec;
    else if (k == l4) tp.fir = grpDia[gu].sec, tp.sec = grpDia[gv].fir;
    ans[time] = ans[time] * k % MODN;
    diaL[gv] = k;
    grpDia[gv] = tp;
}

int main() {
    qRead(n);
    ans[n] = 1;
    for (int i = 1; i <= n; ++i) {
        qRead(w[i]);
        diaL[i] = w[i];
        ans[n] = ans[n] * w[i] % MODN;
        // 并查集及(森林)直径 初始化
        grp[i] = grpDia[i].fir = grpDia[i].sec = i;
    }
    for (int i = 1; i < n; ++i) {
        int u, v;
        qRead(u, v);
        addEdge(u, v);
        addEdge(v, u);
    }
    initDfs(1);
    for (int j = 1; j < LCAN; ++j) {
        for (int i = 1; i <= n; ++i) {
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
            ws[i][j] = ws[i][j - 1] + ws[fa[i][j - 1]][j - 1];
        }
    }

    for (int i = 1; i < n; ++i)
        qRead(del[i]);

    for (int i = n - 1; i >= 1; --i)
        merge(edge[del[i] << 1].to, edge[del[i] << 1].fr, i);

    for (int i = 1; i <= n; ++i)qWrite(ans[i], '\n');
    return 0;
}
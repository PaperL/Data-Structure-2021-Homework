//
// Created by PaperL on 2021/3/27.
//

#include <cstdio>
#include <cstring>
#include <utility> // pair

//#define PAPERL_DEBUG
#define MAXN 2004
#define MINK -1e9

using namespace std;

namespace PTF {
// Here is PaperL's Template Function
// Version: 0.4
// Update Time: 2021.3.28

    template<typename T1, typename T2>
    struct sameType {
        operator bool() {
            return false;
        }
    };

    template<typename T>
    struct sameType<T, T> {
        operator bool() {
            return true;
        }
    };

    template<typename T>
    inline T qRead() {
        char _c = getchar();
        bool _sign = false;
        T _k = 0;
        while (_c < '0' || _c > '9') {
            if (_c == '-') _sign = true;
            _c = getchar();
        }
        while (_c >= '0' && _c <= '9') {
            _k = (_k << 3) + (_k << 1) - 48 + _c;
            _c = getchar();
        }
        if (_sign) _k = -_k;
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
            _k = (_k << 3) + (_k << 1) - 48 + _c;
            _c = getchar();
        }
        if (_sign) _k = -_k;
    }

    template<typename T, typename... argL>
    inline void qRead(T &_k, argL &... argList) {
        qRead(_k);
        qRead(argList...);
    }

    template<typename T>
    inline void qWrite(T _k) {
        if (_k != 0) {
            int _p = 0;
            char _c[24];
            if (_k < 0)putchar('-'), _k = -_k;
            while (_k) _c[_p++] = _k % 10 + 48, _k /= 10;
            while (_p--)putchar(_c[_p]);
        } else putchar('0');
    }

    template<typename T, typename... argL>
    inline void qWrite(T _k, argL ... argList) {
        qWrite(_k);
        qWrite(argList...);
    }

    template<typename T, typename... argL>
    inline void qWrite(const char _s, T _k, argL... argList) {
        qWrite(_k);
        putchar(_s);
        if (sizeof...(argList) != 0)
            qWrite(_s, argList...);
    }

    template<typename T>
    inline T maxN(const T &x, const T &y) { return (x > y) ? x : y; }

    template<typename T, typename... argL>
    inline T maxN(const T &x, const T &y, const argL &... argList) {
        return ((x > y) ? maxN(x, argList...) : maxN(y, argList...));
    }
}
using namespace PTF;

int t, maxp, w;
int ap, bp, as, bs;
int dp[MAXN][MAXN];
int head, tail;
pair<int, int> q[MAXN];

int main() {
    qRead(t, maxp, w);
    int i, j, k;
    for (i = 0; i <= maxp; ++i)dp[0][i] = MINK;
    dp[0][0] = 0;
    for (i = 1; i <= t; ++i) {
        qRead(ap, bp, as, bs);
        head = tail = 0;
        for (j = 0; j <= maxp; ++j)
            dp[i][j] = dp[i - 1][j];
        for (j = 0; j <= maxp; ++j) {
            k = dp[maxN(0, i - w - 1)][j] + j * ap;
            while (head < tail && t >= q[tail - 1].first)--tail;
            q[tail++] = make_pair(k, j);
            while (head < tail && j - q[head].second > as)++head;
            dp[i][j] = maxN(dp[i][j], q[head].first - j * ap);
        }
        head = tail = 0;
        for (j = maxp; j >= 0; --j) {
            k = dp[maxN(0, i - w - 1)][j] + j * bp;
            while (head < tail && t >= q[tail - 1].first)--tail;
            q[tail++] = make_pair(k, j);
            while (head < tail && q[head].second - j > bs)++head;
            dp[i][j] = maxN(dp[i][j], q[head].first - j * bp);
        }
    }

    int ans = 0;
    for (i = 0; i <= maxp; ++i)ans = maxN(ans, dp[t][i]);
    qWrite(ans);
    putchar(10);
    return 0;
}
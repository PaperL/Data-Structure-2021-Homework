//
// Created by Frank's Laptop on 2021/3/29.
//

#include <cstdio>

using namespace std;

namespace PTF {
// Here is PaperL's Template Function
// Version: 0.4
// Update Time: 2021.3.28

    template<typename T1, typename T2>
    struct sameType {
        operator bool() { return false; }
    };

    template<typename T>
    struct sameType<T, T> {
        operator bool() { return true; }
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
    inline void qRead(T &_k, argL &...argList) {
        qRead(_k);
        qRead(argList...);
    }

    template<typename T>
    inline void qWrite(T _k) {
        if (_k != 0) {
            int _p = 0;
            char _c[24];
            if (_k < 0) putchar('-'), _k = -_k;
            while (_k) _c[_p++] = _k % 10 + 48, _k /= 10;
            while (_p--) putchar(_c[_p]);
        } else
            putchar('0');
    }

    template<typename T, typename... argL>
    inline void qWrite(T _k, argL... argList) {
        qWrite(_k);
        qWrite(argList...);
    }

    template<typename T, typename... argL>
    inline void qWrite(const char _s, T _k, argL... argList) {
        qWrite(_k);
        putchar(_s);
        if (sizeof...(argList) != 0) qWrite(_s, argList...);
    }

    template<typename T>
    inline T maxN(const T &x, const T &y) {
        return (x > y) ? x : y;
    }

    template<typename T, typename... argL>
    inline T maxN(const T &x, const T &y, const argL &...argList) {
        return ((x > y) ? maxN(x, argList...) : maxN(y, argList...));
    }
}  // namespace PTF
using namespace PTF;

#define PAPERL_DEBUG
#define ll long long int
#define MAXN 2008
#define INF 1e9

int t, maxp, w;
int dp[MAXN][MAXN], fore[MAXN];
int q[MAXN], head, tail;

int main() {
    qRead(t, maxp, w);
    int i, j;

    for (i = 0; i <= t; ++i)
        for (j = 0; j <= maxp; ++j)
            dp[i][j] = -INF;
    dp[0][0] = 0;
    fore[0] = 0;
    for (i = 1; i <= maxp; ++i)fore[i] = -INF;

    int ap, bp, as, bs, ans = -INF;
    for (i = 1; i <= t; ++i) {
        qRead(ap, bp, as, bs);
        head = 0, tail = 0;
        for (j = 0; j <= maxp; ++j) {
            while (head < tail && fore[q[tail - 1]] + q[tail - 1] * ap
                                  <= fore[j] + j * ap)
                --tail;
            while (head < tail && q[head] + as < j) ++head;
            q[tail++] = j;
            dp[i][j] = maxN(dp[i][j], fore[q[head]] + (q[head] - j) * ap);
        }
        head = 0, tail = 0;
        for (j = maxp; j >= 0; --j) {
            while (head < tail && fore[q[tail - 1]] + q[tail - 1] * bp
                                  <= fore[j] + j * bp)
                --tail;
            while (head < tail && q[head] > j + bs) ++head;
            q[tail++] = j;
            dp[i][j] = maxN(dp[i][j], fore[q[head]] + (q[head] - j) * bp);
            ans = maxN(ans, dp[i][j]);
        }
        if (i > w) {
            for (j = 0; j <= maxp; ++j)
                fore[j] = maxN(fore[j], dp[i - w][j]);
        }
    }
    qWrite(ans);

    return 0;
}

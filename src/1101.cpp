//
// Created by PaperL on 2021/3/28.
//

#include <cstdio>
#include <utility> // pair

#define PAPERL_DEBUG

using namespace std;

namespace PTF {
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

#define MAXN 1000008
#define ll long long int

int n, a, b, c;
int sum[MAXN];

int head, tail;
pair<ll, ll> q[MAXN];

ll dp[MAXN];

inline double f(const pair<ll, ll> &k1, const pair<ll, ll> &k2) {
    return (double(k1.second - k2.second) / double(k1.first - k2.first));
}

int main() {
    qRead(n, a, b, c);
    int i, k;
    sum[0] = 0;
    for (i = 1; i <= n; ++i)
        qRead(k), sum[i] = sum[i - 1] + k;

    head = 0, tail = 1;
    q[0] = make_pair(0, 0);
    dp[0] = 0;
    pair<ll, ll> tp;

    for (i = 1; i <= n; ++i) {
        while (head + 1 < tail && (f(q[head], q[head + 1]) > 2 * a * sum[i]))++head;
        dp[i] = (ll)q[head].second - (ll)q[head].first * 2 * a * sum[i]
                + (ll)a * sum[i] * sum[i] + (ll)b * sum[i] + c;
        tp = make_pair(sum[i], (ll)dp[i] + (ll)a * sum[i] * sum[i] - (ll)b * sum[i]);
        while (head + 1 < tail && f(q[tail - 1], q[tail - 2]) < f(tp, q[tail - 1])) --tail;
        q[tail++] = tp;
    }
    qWrite(dp[n]);
    putchar(10);
    return 0;
}
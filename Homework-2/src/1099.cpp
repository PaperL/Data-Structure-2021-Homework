//
// Created by PaperL on 2021/3/27.
//

#include <cstdio>
#include <cstring>

//#define PAPERL_DEBUG

using namespace std;

template<typename T>
inline void qread(T &_k) {
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
inline void qread(T &_k, argL &... argList) {
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
    qread(argList...);
}

template<typename T>
inline T max2(const T &x, const T &y) { return (x > y) ? x : y; }

const int nMax = 1000000;
long long int sum[nMax], dp[nMax][2];
int q[nMax], head, tail;

int main() {
    int m, n, i, k;
    qread(n, m, k);
    sum[0] = k;
    for (i = 1; i < n; ++i) {
        qread(k);
        sum[i] = sum[i - 1] + k;
    }
#ifdef PAPERL_DEBUG
    printf("sum[i]: ");
    for (int ii = 0; ii < n; ++ii)
        printf("%d, ", sum[ii]);
    putchar(10);
#endif
    q[0] = -1;
    q[1] = 0;
    head = 0, tail = 2;
    dp[0][0] = 0;
    dp[0][1] = sum[0];
    for (i = 1; i < n; ++i) {
        while (head < tail && q[head] + m < i)++head;
        dp[i][0] = max2(dp[i - 1][0], dp[i - 1][1]);
        if (q[head] != -1)
            dp[i][1] = dp[q[head]][0] + (sum[i] - sum[q[head]]);
        else dp[i][1] = dp[q[head]][0] + sum[i];
        while (head < tail && dp[q[tail - 1]][0] - sum[q[tail - 1]]
                              <= dp[i][0] - sum[i])
            --tail;
        q[tail++] = i;
#ifdef PAPERL_DEBUG
        printf("i: %d,\tfront: %d,\tback: %d\n", i, q[head], q[tail - 1]);
#endif
    }
#ifdef PAPERL_DEBUG
    printf("dp[i][0]: ");
    for (int ii = 0; ii < n; ++ii)
        printf("%d, ", dp[ii][0]);
    printf("\ndp[i][1]: ");
    for (int ii = 0; ii < n; ++ii)
        printf("%d, ", dp[ii][1]);
    putchar(10);
#endif
    printf("%lld\n", max2(dp[n - 1][0], dp[n - 1][1]));
    return 0;
}
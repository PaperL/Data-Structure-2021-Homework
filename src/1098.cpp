//
// Created by Frank's Laptop on 2021/3/26.
//

#include <cstdio>
#include <cstring>

//#define PAPERL_DEBUG

using namespace std;

int n;
int h[500001];
int maxQ[500001], minQ[500001];
int maxH = 0, maxT = 1, minH = 0, minT = 1;

template<typename T>
inline void qread(T &_k) {
    static char _c = getchar();
    static bool _sign = false;
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

inline int max2(const int &x, const int &y) { return (x > y) ? x : y; }

int main() {
    qread(n);
    int i, j, ans = 0;
    for (i = 0; i < n; ++i)qread(h[i]);
    maxQ[0] = 0;
    minQ[0] = 0;
    for (i = 1; i < n; ++i) {
        while (maxH < maxT && h[i] > h[maxQ[maxT - 1]]) --maxT;
        maxQ[maxT++] = i;
        while (minH < minT && h[i] <= h[minQ[minT - 1]]) --minT; // 注意两个 while 的 h[i] 比较符不同
        minQ[minT++] = i;
        // j: 对于 maxQ 队末元素对应的 minQ 元素的最小序号
        // 此处 j 的获取可能还是 n^2
        if (maxT - maxH >= 2) {
            for (j = minT - 1; j >= minH; --j)
                if (minQ[j] < maxQ[maxT - 2])
                    break;
            ++j;
#ifdef PAPERL_DEBUG
            printf("cp:%d\n", j);
            printf("cp2: %d %d = %d\n", maxQ[maxT - 1], minQ[j], maxQ[maxT - 1] - minQ[j]);
#endif
            ans = max2(ans, maxQ[maxT - 1] - minQ[j]);
        } else ans = max2(ans, maxQ[maxH] - minQ[minH]);
#ifdef PAPERL_DEBUG
        printf("i: %d, tans: %d~%d = %d\n",
               i, minQ[minH], maxQ[maxH], maxQ[maxH] - minQ[minH]);
        printf("max[%d, %d): ", maxH, maxT);
        for (int ii = maxH; ii < maxT; ++ii)printf("%d, ", h[maxQ[ii]]);
        putchar(10);
        printf("min[%d, %d): ", minH, minT);
        for (int ii = minH; ii < minT; ++ii)printf("%d, ", h[minQ[ii]]);
        printf("\n==================\n");
#endif
    }

    printf("%d\n", (ans == 0) ? 0 : (ans + 1));
    return 0;
}
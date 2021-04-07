//
// Created by Frank's Laptop on 2021/3/15.
//

#include <cstdio>
#include <cstring>

using namespace std;

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

int main() {
    int n, m;
    qread(n);
    qread(m);
    int *a = new int[n + 1];
    int *exist = new int[m + 1];
    memset(exist, 0, sizeof(int) * (m + 1));
    int count = 0;
    for (int i = 0; i < n; ++i)
        qread(a[i]);
    for (int i = 0; i < m; ++i)
        if (!exist[a[i]]++)++count;
    if (count == m)
        printf("%d %d\n", 1, m);
    else {
        int min = 1e9, minl = -1, minr = -1, l = 0, r = m - 1;
        for (int i = m; i < n; ++i) {
            ++r;
            if (!exist[a[i]]++)++count;
            if (count == m) {
                do --exist[a[l]];
                while (exist[a[l++]]);
                // printf("t: %d %d\n", l - 1, r);
                if (r - l + 2 < min) {
                    min = r - l + 2;
                    minl = l - 1, minr = r; // 闭区间
                }
                --count;
            }
        }
        printf("%d %d\n", minl + 1, minr + 1);
    }
    delete[] a;
    delete[] exist;
    return 0;
}
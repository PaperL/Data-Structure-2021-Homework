//
// Created by PaperL on 2021/2/26.
//

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

int fun(int step, int tot, int bound) {
    if (tot == 1)return 0;
    else if (tot == 2)return (1 - (step & 1));
    else {
        int nStep = step % (2 * tot - 2);
        int tBound = (2 * tot - nStep - 2 + bound - 1) % (tot - 1);
        int tAns = fun(step, tot - 1, tBound);
        int Ans = ((abs(bound - abs((nStep) - bound)
                        + (tot - bound - 1)) - (tot - bound - 1) + tot) % tot);
        if (nStep >= bound && nStep < (bound + tot - 1))
            Ans = (Ans + tot - (tAns + 1)) % tot;
        else Ans = (Ans + (tAns + 1)) % tot;
        return Ans;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    cout << fun(m - 1, n, n - 1) + 1 << endl;
    return 0;
}


// 瞎改改
/*
#include <cstdio>
using namespace std;

inline int _abs(const int &k) { return ((k >= 0) ? k : (-k)); }

inline int __abs(const int &x) {
    static int y;
    y = x >> 31;
    return (x ^ y) - y;  // or: (x+y)^y
}

int step;
int funRet3, funRet2;
const int funRet4[12] = {3, 0, 3, 2, 3, 2, 1, 2, 1, 0, 1, 0};
const int funRet5[24] = {4, 2, 1, 1, 0, 0, 0, 3, 2, 2, 4, 4,
                         0, 2, 3, 3, 4, 4, 4, 1, 2, 2, 0, 0};

int fun(const int &tot, const int &bound) {
    if (tot < 4) {
        if (tot == 3)
            return funRet3;
        else if (tot == 2)
            return funRet2;
        return 0;
    } else {
        int nStep = step % ((tot << 1) - 2);
        if (nStep >= bound && nStep < (bound + tot - 1))
            return (
                    ((__abs(-__abs(nStep - bound) + tot - 1) + bound + 1) + tot -
                     fun(tot - 1, ((tot << 1) - nStep + bound - 3) % (tot - 1)) -
                     1) %
                    tot);
        else
            return (
                    ((__abs(-__abs(nStep - bound) + tot - 1) + bound + 1) +
                     fun(tot - 1, ((tot << 1) - nStep + bound - 3) % (tot - 1)) +
                     1) %
                    tot);
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    // n = 4;
    // for (m = 1; m <= 10000; ++m) {
    step = m - 1;
    if (n == 4) {
        printf("%d\n", funRet4[step % 12]);
        return 0;
    } else if (n == 5) {
        printf("%d\n", funRet5[step % 24]);
        return 0;
    }
    funRet3 = 2 - step % 4 / 2 * 2;
    funRet2 = 1 - (step & 1);
    printf("%d\n", (fun(n, n - 1) + 1));
    //   if (m % 1000 == 0) getchar();
    //}
    return 0;
}*/
//
// Created by Frank's Laptop on 2021/3/1.
//

#include <cstdio>
#include <cstring>

//#define _debug

int m, n, a, b, c, d;
int map[1008][1008];
int sum[1008][1008];
int lsSum[1008][1008];
int lmSum[1008][1008];
int cmSum[1008][1008];

inline int qread(int &_k) {
    char _c = getchar();
    int _sign = 1;
    _k = 0;
    while (_c < 48 || _c > 57) {
        if (_c == '-')_sign = -1;
        _c = getchar();
    }
    while (_c >= 48 && _c <= 57) {
        _k = (_k << 3) + (_k << 1) - 48 + _c;
        _c = getchar();
    }
    //printf("%d\n", _sign * _k);
    return (_sign * _k);
}

inline void getMin(const int *data, int dl, int rl, int *ans) {
    // dl for data length, rl for range length
#ifdef _debug
    printf("dl: %d, rl: %d\n", dl, rl);
    for (int ii = 0; ii < dl; ++ii)
        printf("%d\t", data[ii]);
    putchar(10);
#endif

    int cnt = 0, qHead = 0, qTail = 0; // cnt = 1 照顾 main 下标格式
    static int queue[1008];
    memset(queue, 0, sizeof(int) * (dl + 1));
    int i;
    for (i = 0; i < rl - 1; ++i) {
        while (qHead < qTail && data[i] <= data[queue[qTail - 1]])--qTail;
        queue[qTail++] = i;
    }
    for (i = rl - 1; i < dl; ++i) {
        while (qHead < qTail && data[i] <= data[queue[qTail - 1]])--qTail;
        queue[qTail++] = i;
        while (queue[qHead] < i - rl + 1)++qHead;
        ans[cnt++] = data[queue[qHead]];
    }
}

inline void getMin2(const int *data, int dl, int dln, int rl, int *ans) {
    // this function is for two-dimensional array
    // dl for data line number, dln for data line element number, rl for range length
#ifdef _debug
    printf("2=>dl: %d, rl: %d\n", dl, rl);
    for (int ii = 0; ii < dl; ++ii)
        printf("%d\t", data[ii * dln]);
    putchar(10);
#endif

    int cnt = 0, qHead = 0, qTail = 0; // cnt = 1 照顾 main 下标格式
    static int queue[1008];
    memset(queue, 0, sizeof(int) * (dl + 1));
    int i;
    for (i = 0; i < rl - 1; ++i) {
        while (qHead < qTail && data[i * dln] <= data[queue[qTail - 1] * dln])--qTail;
        queue[qTail++] = i;
    }
    for (i = rl - 1; i < dl; ++i) {
        while (qHead < qTail && data[i * dln] <= data[queue[qTail - 1] * dln])--qTail;
        queue[qTail++] = i;
        while (queue[qHead] < i - rl + 1)++qHead;
        ans[(cnt++) * dln] = data[queue[qHead] * dln];
    }
}

int main() {
    qread(m);
    qread(n);
    qread(b);
    qread(a);
    qread(d);
    qread(c);
    int i, j;
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
            qread(map[i][j]);
    sum[1][1] = map[1][1];
    for (j = 1; j <= m; ++j)
        sum[1][j] = sum[1][j - 1] + map[1][j];
    for (i = 1; i <= n; ++i)
        sum[i][1] = sum[i - 1][1] + map[i][1];
    for (i = 2; i <= n; ++i)
        for (j = 2; j <= m; ++j)
            sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + map[i][j];

    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m - d + 1; ++j)
            lsSum[i][j] = sum[i + c - 1][j + d - 1] + sum[i - 1][j - 1]
                          - sum[i - 1][j + d - 1] - sum[i + c - 1][j - 1]; // line small matrix sum
    } // lsSum[1..n][1..m-d+1]
    for (i = 2; i <= n - c + 1; ++i)
        getMin(lsSum[i] + 2, m - d - 1, b - d - 1, lmSum[i] + 2); // line min small matrix sum
    // lmSum[1..n][1..] 自此坐标起向右长度为 b 的区间中 长度为 d 的区间和最大值
    for (j = 2; j <= m - b + 2; ++j) // column min small matrix sum
        getMin2(lmSum[2] + j, n - c - 1, 1008, a - c - 1, cmSum[2] + j);
    // cmSum[][] 此坐标为左上顶点的 a,b 矩阵范围内, c,d 矩阵最小值
#ifdef _debug
    printf("lsSum:\n");
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            printf("%d\t", lsSum[i][j]);
        }
        putchar(10);
    }
    putchar(10);

    printf("lmSum:\n");
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            printf("%d\t", lmSum[i][j]);
        }
        putchar(10);
    }
    putchar(10);

    printf("cmSum:\n");
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            printf("%d\t", cmSum[i][j]);
        }
        putchar(10);
    }
    putchar(10);

    printf("FINAL\n");
#endif
    int ans = -1, bSum, sSum, ansi, ansj, ansp, ansq, ansCsum;
    for (i = 1; i <= n - a + 1; ++i) {
        for (j = 1; j <= m - b + 1; ++j) {
            bSum = sum[i - 1 + a][j - 1 + b] + sum[i - 1][j - 1] - sum[i - 1][j - 1 + b] - sum[i - 1 + a][j - 1];
            if (bSum - cmSum[i + 1][j + 1] > ans) {
                ans = bSum - cmSum[i + 1][j + 1];
                ansCsum = cmSum[i + 1][j + 1];
                ansi = i, ansj = j;
            }
            //printf("%d\t", bSum);
        }
        //putchar(10);
    }
#ifdef _debug
    printf("\ni: %d, j: %d, ans: %d, ansCsum: %d FINAL2\n", ansi, ansj, ans, ansCsum);
#endif
    bool flag = false;
    for (i = ansi + 1; i <= ansi + a - c - 1; ++i) {
        for (j = ansj + 1; j <= ansj + b - d - 1; ++j) {
            sSum = sum[i - 1 + c][j - 1 + d] + sum[i - 1][j - 1] - sum[i - 1][j - 1 + d] - sum[i - 1 + c][j - 1];
            if (sSum == ansCsum) {
                ansp = i, ansq = j;
                flag = true;
                break;
            }
#ifdef _debug
            printf("%d\t", sSum);
#endif
        }
        if (flag)break;
#ifdef _debug
        putchar(10);
#endif
    }
    printf("%d %d\n%d %d\n", ansj, ansi, ansq, ansp);
    return 0;
}

/*
#include <cstdio>

int m, n, a, b, c, d;
int map[1008][1008];
int sum[1008][1008];
int tsSum[1008][1008];

inline int qread(int &_k) {
    char _c = getchar();
    int _sign = 1;
    _k = 0;
    while (_c < 48 || _c > 57) {
        if (_c == '-')_sign = -1;
        _c = getchar();
    }
    while (_c >= 48 && _c <= 57) {
        _k = (_k << 3) + (_k << 1) - 48 + _c;
        _c = getchar();
    }
    //printf("%d\n", _sign * _k);
    return (_sign * _k);
}

int main() {
    qread(m);
    qread(n);
    qread(b);
    qread(a);
    qread(d);
    qread(c);
    int i, j;
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
            qread(map[i][j]);
    sum[1][1] = map[1][1];
    for (j = 1; j <= m; ++j)
        sum[1][j] = sum[1][j - 1] + map[1][j];
    for (i = 1; i <= n; ++i)
        sum[i][1] = sum[i - 1][1] + map[i][1];
    for (i = 2; i <= n; ++i)
        for (j = 2; j <= m; ++j)
            sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + map[i][j];
    const int bbi = n - a + 1, bbj = m - b + 1;
    const int sbi = a - c - 1, sbj = b - d - 1;
    int p, q, pt, qt;
    int bSum, sSum;

    int Ans = -1, ansi, ansj, ansp, ansq;
    for (i = bbi - 1; i >= 0; --i) {
        for (j = bbj - 1; j >= 0; --j) {
            bSum = sum[i + a][j + b] + sum[i][j] - sum[i][j + b] - sum[i + a][j];
            //printf("i:%d, j:%d, bSum:%d\n", i, j, bSum);
            if (bSum <= Ans)continue;
            pt = i + sbi;
            qt = j + sbj;
            for (p = i + 1; p <= pt; ++p) {
                for (q = j + 1; q <= qt; ++q) {
                    if (tsSum[p][q] == 0) {
                        tsSum[p][q] = sSum = sum[p + c][q + d] + sum[p][q] - sum[p][q + d] - sum[p + c][q];
                        //printf("new %d %d\n", p, q);
                    } else sSum = tsSum[p][q];
                    //printf("p:%d, q:%d, sSum:%d\n", p, q, sSum);
                    if (bSum - sSum > Ans) {
                        Ans = bSum - sSum;
                        ansi = i;
                        ansj = j;
                        ansp = p;
                        ansq = q;
                    }
                }
            }
        }
    }
    printf("%d %d\n%d %d\n", ansj + 1, ansi + 1, ansq + 1, ansp + 1);
    return 0;
}
*/
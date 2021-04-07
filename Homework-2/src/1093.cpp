//
// Created by Frank's Laptop on 2021/3/22.
//

#include <cstdio>
#include <cstring>

//#define PAPERL_DEBUG

using namespace std;

int data[1001][1001];
int min[1001][1001];
int max[1001][1001];
int n, m, a;

const int BIGINT = 1e9 + 1;
const int SMALLINT = -1;

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

void operateLine(int dx, int dy, int posX, int posY, int l, bool minFlag, int da[][1001], int ma[][1001]) {
    const int minK = minFlag ? 1 : -1;
    int head = 1, tail = 1;
    int queue[1001];
    int queueP[1001];
    int ansX = posX, ansY = posY;
    int i;
    for (i = 0; i < a - 1; ++i) {
        while (head < tail && da[posX][posY] * minK <= queue[tail - 1] * minK)--tail;
        queueP[tail] = posX * dx + posY * dy;
        queue[tail++] = da[posX][posY];
        posX += dx, posY += dy;
    }
    for (i = a - 1; i < l; ++i) {
        while (head < tail && da[posX][posY] * minK <= queue[tail - 1] * minK)--tail;
        queueP[tail] = posX * dx + posY * dy;
        queue[tail++] = da[posX][posY];
        while (queueP[head] < i - a + 1) ++head;
        ma[ansX][ansY] = queue[head];
        //printf("=>%d, ",queue[head]);
        ansX += dx, ansY += dy;
        posX += dx, posY += dy;
    }
    //putchar(10);
}

int main() {
    qread(n);
    qread(m);
    qread(a);
    int i, j;
    for (i = 0; i < n; ++i)
        for (j = 0; j < m; ++j) {
            qread(data[i][j]);
            min[i][j] = BIGINT;
            max[i][j] = SMALLINT;
        }

    for (i = 0; i < n; ++i)
        operateLine(0, 1, i, 0, m, true, data, min);
#ifdef PAPERL_DEBUG
    printf("\n===\n");
    for (int ii = 0; ii < n; ++ii) {
        for (int jj = 0; jj < m; ++jj)
            printf("%d ", min[ii][jj]);
        putchar(10);
    }
    printf("==================\n\n");
#endif
    for (j = 0; j <= m - a; ++j)
        operateLine(1, 0, 0, j, n, true, min, min);
#ifdef PAPERL_DEBUG
    printf("\n===\n");
    for (int ii = 0; ii < n; ++ii) {
        for (int jj = 0; jj < m; ++jj)
            printf("%d ", min[ii][jj]);
        putchar(10);
    }
    printf("==================\n\n");
#endif
    for (i = 0; i < n; ++i)
        operateLine(0, 1, i, 0, m, false, data, max);
#ifdef PAPERL_DEBUG
    printf("\n===\n");
    for (int ii = 0; ii < n; ++ii) {
        for (int jj = 0; jj < m; ++jj)
            printf("%d ", max[ii][jj]);
        putchar(10);
    }
    printf("==================\n\n");
#endif
    for (j = 0; j <= m - a; ++j)
        operateLine(1, 0, 0, j, n, false, max, max);
#ifdef PAPERL_DEBUG
    printf("\n===\n");
    for (int ii = 0; ii < n; ++ii) {
        for (int jj = 0; jj < m; ++jj)
            printf("%d ", max[ii][jj]);
        putchar(10);
    }
    printf("==================\n\n");
#endif

    int ans = BIGINT;
    for (i = 0; i <= n - a; ++i)
        for (j = 0; j <= m - a; ++j)
            ans = (max[i][j] - min[i][j] < ans) ? (max[i][j] - min[i][j]) : ans;
    printf("%d\n", ans);

    return 0;
}
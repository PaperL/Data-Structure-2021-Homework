//
// Created by PaperL on 2021/2/27.
//

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

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

int n, m;
char map[100][100];
int dx, dy; // Destination's X Y

const int dir[2][4] = {{0, 1, 0,  -1},
                       {1, 0, -1, 0}};
// 右 下 左 上

int sh, st; // bfsStack Head/Tail
char bfsStack[2][10000];
char bfsVisited[100][100];

int qh = 0, qt = 0;
int bbfsQueue[5][100000]; // px py bx by step
char bbfsVisited[100][100];

inline bool checkPos(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m) return false;
    else if (map[x][y] == 0)return false;
    else return true;
}

bool livingPos(int x, int y) {
    if (!checkPos(x, y))return false;
    if (x == dx && y == dy)return true;

    int cnt = 0;
    char result[4] = {0, 0, 0, 0};
    for (int i = 0; i < 4; ++i)
        if (checkPos(x + dir[0][i], y + dir[1][i])) {
            ++cnt;
            result[i] = 1;
        }
    if (cnt >= 3)return true;
    else if (cnt <= 1)return false;
    else return (result[0] == result[2]);
}

bool bfs(int ax, int ay, int bx, int by, int ox, int oy) {
    // From A to B, O is obstacle
    if (!checkPos(ax, ay) || !checkPos(bx, by)) return false;
    if (ax == bx && ay == by)return true;
    sh = st = 0;
    memset(bfsVisited, 0, sizeof(bfsVisited));
    bfsStack[0][0] = ax, bfsStack[1][0] = ay;
    bfsVisited[ax][ay] = 1;
    bfsVisited[ox][oy] = 1; // O 就不做其他检查了
    while (sh <= st) {
        for (int i = 0; i < 4; ++i) {
            const int &tx = bfsStack[0][sh] + dir[0][i];
            const int &ty = bfsStack[1][sh] + dir[1][i];
            if (checkPos(tx, ty) && !bfsVisited[tx][ty]) {
                if (tx == bx && ty == by)return true;
                bfsStack[0][++st] = tx;
                bfsStack[1][st] = ty;
                bfsVisited[tx][ty] = 1;
            }
        }
        ++sh;
    }
    return false;
}

void draw(int x1, int y1, int x2, int y2) {
    for (int ii = 0; ii < n; ++ii) {
        for (int jj = 0; jj < m; ++jj) {
            if (ii == x1 && jj == y1)putchar('P');
            else if (ii == x2 && jj == y2)putchar('B');
            else if (ii == dx && jj == dy)putchar('D');
            else putchar(map[ii][jj] == 0 ? '#' : ' ');
        }
        putchar('\n');
    }
}

int main() {
    char tc;
    int px, py, bx, by; // Player/Box's X Y

    qread(n);
    qread(m);
    getchar();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            tc = getchar();
            if (tc == 'S') map[i][j] = 0;           // Wall
            else {
                map[i][j] = 1;
                // if (tc == 'w')map[i][j] = 1;     // Blank
                if (tc == 'M')px = i, py = j;       // Spawn Point
                else if (tc == 'P')bx = i, by = j;  // Box
                else if (tc == 'K')dx = i, dy = j;  // Destination
            }
        }
        getchar();
        getchar();
    }
    memset(bbfsVisited, 0, sizeof(bbfsVisited));
    bbfsQueue[0][0] = px, bbfsQueue[1][0] = py;
    bbfsQueue[2][0] = bx, bbfsQueue[3][0] = by;
    bbfsQueue[4][0] = 0;
    int ptx, pty, btx, bty;
    // draw(px, py, bx, by);
    while (qh <= qt) {
        px = bbfsQueue[0][qh], py = bbfsQueue[1][qh];
        bx = bbfsQueue[2][qh], by = bbfsQueue[3][qh];
        //cout << "px: " << px << ", py: " << py << endl;
        //cout << "bx: " << bx << ", by: " << by << endl;
        //draw(px, py, bx, by);
        //putchar('\n');
        for (int i = 0; i < 4; ++i) {
            btx = bx + dir[0][i], bty = by + dir[1][i];
            ptx = bx - dir[0][i], pty = by - dir[1][i];
            //cout << "btx: "<< btx << ", bty: "<< bty << endl;
            //cout << "ptx: "<< ptx << ", pty: "<< pty << endl;
            if (livingPos(btx, bty) && !(bbfsVisited[btx][bty] & (1 << i))) {
                //cout << "cp1" << endl;
                if (bfs(px, py, ptx, pty, bx, by)) {
                    //cout << "cp2" << endl;
                    if (btx == dx && bty == dy) {
                        cout << bbfsQueue[4][qh] + 1 << endl;
                        return 0;
                    }
                    ++qt;
                    bbfsQueue[0][qt] = bx, bbfsQueue[1][qt] = by;
                    bbfsQueue[2][qt] = btx, bbfsQueue[3][qt] = bty;
                    bbfsQueue[4][qt] = bbfsQueue[4][qh] + 1;
                    bbfsVisited[btx][bty] |= 1 << i;
                    //cout << "cp3" << endl;
                }
            }
            //cout << "cp4" << endl;
        }
        ++qh;
    }

    cout << "NO" << endl;
    return 0;
}
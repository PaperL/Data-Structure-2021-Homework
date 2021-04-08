//
// Created by Frank's Laptop on 2021/4/8.
//

#include <cstdio>

namespace PTF {
// Here is PaperL's Template Function
// Version: 0.44
// Update Time: 2021.4.2

    template<typename T1, typename T2>
    struct sameType {
        constexpr operator bool() {
            return false;
        }
    };

    template<typename T>
    struct sameType<T, T> {
        constexpr operator bool() {
            return true;
        }
    };

    template<typename T>
    inline T qRead() {
        T _k;
        qRead(_k);
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
            _k = _k * 10 - 48 + _c;
            _c = getchar();
        }
        if (_sign) _k = -_k;
    }

    template<typename T, typename... argL>
    inline void qRead(T &_k, argL &... _argList) {
        qRead(_k);
        qRead(_argList...);
    }

    template<typename T>
    inline void qWrite(T _k) {
        if constexpr(sameType<T, char>()) {
            putchar(_k);
            return;
        } else if constexpr(sameType<T, const char *>() || sameType<T, char *>()) {
            size_t _p = 0;
            while (_k[_p] != '\0')putchar(_k[_p++]);
            return;
        } else if (_k != 0) {
            int _p = 0;
            char _c[24];
            if (_k < 0)putchar('-'), _k = -_k;
            while (_k) _c[_p++] = _k % 10 + 48, _k /= 10;
            while (_p--)putchar(_c[_p]);
        } else putchar('0');
    }

    template<typename T, typename... argL>
    inline void qWrite(T _k, argL ... _argList) {
        qWrite(_k);
        qWrite(_argList...);
    }

    template<typename T, typename... argL>
    inline void qWrite(const char _s, T _k, argL... _argList) {
        qWrite(_k);
        putchar(_s);
        if (sizeof...(_argList) != 0)
            qWrite(_s, _argList...);
    }

    template<typename T>
    inline T maxN(const T &_x, const T &_y) { return (_x > _y) ? _x : _y; }

    template<typename T, typename... argL>
    inline T maxN(const T &_x, const T &_y, const argL &... _argList) {
        return ((_x > _y) ? maxN(_x, _argList...) : maxN(_y, _argList...));
    }

    template<typename T>
    inline T minN(const T &_x, const T &_y) { return (_x < _y) ? _x : _y; }

    template<typename T, typename... argL>
    inline T minN(const T &_x, const T &_y, const argL &... _argList) {
        return ((_x < _y) ? minN(_x, _argList...) : minN(_y, _argList...));
    }
}
using namespace PTF;

using namespace std;

unsigned long long int ans = 1, Cmn[21];
int m, l;
char s1[32], s2[32];

void solve(int fl, int fr, int bl, int br) {
    if (fl == fr)return;
    //printf("%d %d %d %d\n", fl, fr, bl, br);
    int tl, tr, cnt = 0;
    for (tl = fl; tl <= fr; ++tl)
        for (tr = bl; tr <= br; ++tr)
            if (s1[tl] == s2[tr]) {
                ++cnt;
                solve(tl + 1, tl + 1 + tr - bl, bl, tr - 1);
                fl += tr - bl + 1;
                bl = tr + 1;
                break;
            }
    ans *= Cmn[cnt];
}

int main() {
    qRead(m);
    Cmn[0] = 1;
    for (int i = 1; i <= m; ++i)Cmn[i] = Cmn[i - 1] * (m - i + 1) / i;

    char c = getchar();
    while (c < 'a' || c > 'z')c = getchar();
    l = 0;
    while (c >= 'a' && c <= 'z') {
        s1[++l] = c;
        c = getchar();
    }
    while (c < 'a' || c > 'z')c = getchar();
    for (int i = 1; i <= l; ++i) {
        s2[i] = c;
        c = getchar();
    }
    solve(2, l, 1, l - 1);

    qWrite(ans, '\n');
}

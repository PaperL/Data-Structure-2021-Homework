//
// Created by Frank's Laptop on 2021/4/1.
//

#include <cstdio>
#include <cstring>

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

class st {
public:
    int *data, *lz;

    st() : data(nullptr), lz(nullptr) {}

    ~st() {
        delete[]data;
        delete[]lz;
    }

    void build(int n) {
        data = new int[n * 3];
        lz = new int[n * 3];
        data[1] = 0;
        lz[1] = 0;
    }

    inline void pushup(int p) { data[p] = data[p << 1] + data[p << 1 | 1]; }

    inline void pushdown(int p, int l, int r) {
        if (lz[p] == -1)return;
        int mid = (l + r) >> 1;
        data[p << 1] = (mid - l) * lz[p];
        data[p << 1 | 1] = (r - mid) * lz[p];
        lz[p << 1] = lz[p << 1 | 1] = lz[p];
        lz[p] = -1;
    }

    void update(int p, int l, int r, int tl, int tr, int k) {
        if (tl <= l && tr >= r) {
            data[p] = (r - l) * k;
            lz[p] = k;
        } else {
            pushdown(p, l, r);
            int mid = (l + r) >> 1;
            if (tl < mid) update(p << 1, l, mid, tl, tr, k);
            if (tr > mid) update(p << 1 | 1, mid, r, tl, tr, k);
            pushup(p);
        }
    }

    int query(int p, int l, int r, int tl, int tr) {
        if (lz[p] != -1) {
            if (lz[p]) {
                r = PTF::minN(r, tr);
                l = PTF::maxN(l, tl);
                return (r - l);
            } else return 0;
        } else if (tl <= l && tr >= r)
            return data[p];
        else {
            pushdown(p, l, r);
            int mid = (l + r) >> 1;
            if (tr <= mid)return query(p << 1, l, mid, tl, tr);
            if (tl >= mid)return query(p << 1 | 1, mid, r, tl, tr);
            return query(p << 1, l, mid, tl, tr) + query(p << 1 | 1, mid, r, tl, tr);
        }
    }

} letterTree[26];

int n, m;

int main() {
    int op, l, r, i, j, p, cnt;
    char c;
    PTF::qRead(n, m);
    for (i = 0; i < 26; ++i)letterTree[i].build(n);
    do { c = getchar(); } while (c < 'a' || c > 'z');
    for (i = 0; i < n; ++i) {
        letterTree[c - 'a'].update(1, 0, n, i, i + 1, 1);
        c = getchar();
    }

    while (m--) {
        PTF::qRead(l, r, op);
        --l;
        if (op == 1) {
            p = l;
            for (i = 0; i < 26; ++i) {
                cnt = letterTree[i].query(1, 0, n, l, r);
                if (cnt) {
                    letterTree[i].update(1, 0, n, l, r, 0);
                    letterTree[i].update(1, 0, n, p, p + cnt, 1);
                    p += cnt;
                }
            }
        } else {
            p = r;
            for (i = 0; i < 26; ++i) {
                cnt = letterTree[i].query(1, 0, n, l, r);
                if (cnt) {
                    letterTree[i].update(1, 0, n, l, r, 0);
                    letterTree[i].update(1, 0, n, p - cnt, p, 1);
                    p -= cnt;
                }
            }
        }
    }

    for (i = 0; i < n; ++i) {
        for (j = 0; j < 26; ++j) {
            if (letterTree[j].query(1, 0, n, i, i + 1)) {
                putchar('a' + j);
                break;
            }
        }
    }
    putchar(10);
    return 0;
}
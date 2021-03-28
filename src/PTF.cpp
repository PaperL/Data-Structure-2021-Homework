#include <cstdio>
using namespace std;

namespace PTF {
// Here is PaperL's Template Function
// Version: 0.4
// Update Time: 2021.3.28

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
    inline T qRead() {
        char _c = getchar();
        bool _sign = false;
        T _k = 0;
        while (_c < '0' || _c > '9') {
            if (_c == '-') _sign = true;
            _c = getchar();
        }
        while (_c >= '0' && _c <= '9') {
            _k = (_k << 3) + (_k << 1) - 48 + _c;
            _c = getchar();
        }
        if (_sign) _k = -_k;
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

#define PAPERL_DEBUG

int main() {

    return 0;
}
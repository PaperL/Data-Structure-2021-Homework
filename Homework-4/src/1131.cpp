//
// Created by Frank's Laptop on 2021/4/12.
//

// 03 提高组原题

#pragma region PaperL_Header
#ifndef PTL_PTF_H
#define PTL_PTF_H

#include <cstdio>
#include <exception>
#include <ios>

namespace PTF {
#pragma region PTF_DESCRIPTION
/*
 * "PaperL's Template Function"
 *
 * Version: 1.01
 * Last Update Time: 2021.4.13
 * Last Update Content:
 *      修正 qRead 读到意外 EOF 导致死循环的问题, 返回 std::ios_base::failure
 * Going to develop:
 *      IO 函数支持浮点, qRead 函数支持字符
 *      增加 PTF_ALGORITHM
 *
 */
#pragma endregion PTF_DESCRIPTION

#pragma region PTF_TYPE

    template<typename T1, typename T2>
    struct sameTypeJudge {
        static constexpr bool _value = false;
    };

    template<typename T>
    struct sameTypeJudge<T, T> {
        static constexpr bool _value = true;
    };

    template<typename T1, typename T2>
    constexpr bool sameType = sameTypeJudge<T1, T2>::_value;

#pragma endregion PTF_TYPE

#pragma region PTF_MEMORY

    template<typename T>
    inline void swapT(T &_x, T &_y) {
        T _temp(_x);
        _x = _y;
        _y = _temp;
    }

    template<typename T>
    inline void setT(T _array[], const T &_value, size_t _n) {
        for (size_t _p = 0; _p < _n; _p++)
            _array[_p] = _value;
    }

#pragma endregion PTF_MEMORY

#pragma region PTF_MATH

    template<typename T, T _zero = 0>
    inline T absT(const T &_k) { return ((_k >= _zero) ? (_k) : (-_k)); }

    // 注意 maxN 使用了 operator >
    template<typename T>
    inline T maxN(const T &_first, const auto &... _argList) {
        static_assert((sameType<decltype(_argList), const T &> && ...), "Call maxN with different type arguments.");
        const T *_maxArg = &_first;
        ((_maxArg = (_argList > *_maxArg) ? (&_argList) : (_maxArg)), ...);
        return *_maxArg;
    }

    template<typename T>
    inline T minN(const T &_first, const auto &... _argList) {
        static_assert((sameType<decltype(_argList), const T &> && ...), "Call minN with different type arguments.");
        const T *_minArg = &_first;
        ((_minArg = (_argList < *_minArg) ? (&_argList) : (_minArg)), ...);
        return *_minArg;
    }

#pragma endregion PTF_MATH

#pragma region PTF_IO
//  注意 qRead 及相关函数仅支持 整形
//  注意 qWrite 及相关函数仅支持 字符/整形

    inline void qRead(auto &_k) {
        int _c = getchar();
        bool _sign = false;
        _k = 0;
        while (_c < '0' || _c > '9') {
            if (_c < 0 || _c > 255)
                throw std::ios_base::failure("In PTF: qRead get unexpected character (may be EOF)\n");
            if (_c == '-') _sign = true;
            _c = getchar();
        }
        while (_c >= '0' && _c <= '9') {
            _k = _k * 10 - 48 + _c; // 此处位运算替代 *10 可能不一定更快
            _c = getchar();
        }
        if (_sign) _k = -_k;
    }

    template<typename T>
    inline T qRead() {
        T _k;
        qRead(_k);
        return _k;
    }

    // c++20 fold expression
    inline void qRead(auto &... _argList) { (qRead(_argList), ...); }

    template<typename T>
    inline void qWrite(T _k) {
        if constexpr(sameType<T, char> || sameType<T, const char>) putchar(_k);
        else if constexpr(sameType<T, const char *> || sameType<T, char *>) printf("%s", _k);
        else if (_k != 0) {
            int _p = 0;
            char _c[24];
            if (_k < 0)putchar('-'), _k = -_k;
            while (_k) _c[_p++] = _k % 10 + 48, _k /= 10;
            while (_p--)putchar(_c[_p]);
        } else putchar('0');
    }

    inline void qWrite(auto ... _argList) { (qWrite(_argList), ...); }

    // _s for split character(other type is also acceptable)
    inline void qWriteS(auto _s, auto... _argList) { ((qWrite(_argList), qWrite(_s)), ...); }

    // _eol for end of line character
    inline void qWriteL(char _eol, auto... _argList) { (qWrite(_argList), ...), qWrite(_eol); }

    // 注意最后 _eol 之前无 _s
    inline void qWriteSL(auto _s, auto _eol, auto _first, auto... _argList) {
        qWrite(_first), ((qWrite(_s), qWrite(_argList)), ...), qWrite(_eol);
    }

#pragma endregion PTF_IO
}

#endif //PTL_PTF_H
#pragma endregion PaperL_Header

using namespace PTF;
#define MAXN 64

int f[MAXN][MAXN];
int fRoot[MAXN][MAXN];
int n;

void dfsRoot(int l, int r) {
    if (l > r)return;
    qWrite(fRoot[l][r],' ');
    dfsRoot(l, fRoot[l][r] - 1);
    dfsRoot(fRoot[l][r] + 1, r);
}

int main() {
    qRead(n);
    for (int i = 1; i <= n; i++) {
        qRead(f[i][i]);
        f[i][i - 1] = f[i + 1][i] = 1;
        fRoot[i][i] = i;
    }

    for (int dl = 2; dl <= n; dl++) // 区间长
        for (int l = 1; l <= n - dl + 1; l++) // 区间起点
            for (int root = l; root <= l + dl - 1; root++) {
                int t = f[l][root - 1] * f[root + 1][l + dl - 1] + f[root][root];
                if (t > f[l][l + dl - 1]) f[l][l + dl - 1] = t, fRoot[l][l + dl - 1] = root;
            }

    qWrite(f[1][n],'\n');
    dfsRoot(1, n);
    putchar(10);
    return 0;
}
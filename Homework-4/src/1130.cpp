//
// Created by Frank's Laptop on 2021/4/12.
//

#pragma region PaperL_Header
#ifndef PTL_PTF_H
#define PTL_PTF_H

#include <cstdio>
#include <cassert>
#include <stdexcept>
#include <type_traits>
#include <iostream>

namespace PTF {
#pragma region PTF_DESCRIPTION
/*
 * "PaperL's Template Function"
 *
 * Version: 1.18
 * Last Stable Version: 1.01
 * Last Update Time: 2021.4.15
 * Last Update Content:
 *      正在研究如何让函数支持修改右值(&&)
 *      由于本人电脑 Clion 因不明原因不再支持 remove_cvref 故弃用或改用 remove_cv
 * Going to develop:
 *      IO 函数对 const char* 支持有问题！
 *      让同一函数同时支持数组和指针
 *      IO 函数支持浮点
 *      增加 PTF_ALGORITHM
 *      增加 PTF_MATH 三角函数、快速幂等计算函数
 */
#pragma endregion PTF_DESCRIPTION

#pragma region PTF_TYPE

    // std::is_same_v<T1,T2>

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
    inline void setT(T &_array, const auto &_value, size_t _n = 0) {
        static_assert(std::is_array_v<T> || std::is_pointer_v<T>,
                      "In PTF: setT get first argument of not array type");
        static_assert(sameType<decltype(_value), std::remove_all_extents_t<T>> ||
                      sameType<decltype(_value), std::remove_pointer_t<T>>,
                      "In PTF: setT get array and value of different type");
        if constexpr (std::is_array_v<T>)
            for (auto &_item:_array)_item = _value;
        else if constexpr (std::is_pointer_v<T>) {
            for (size_t _p = 0; _p < _n; _p++)
                _array[_p] = _value;
        }
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

    template<typename T>
    inline void qRead(T &_k) {
        static_assert(!std::is_const_v<T>,
                      "In PTF: qRead get unexpected const argument");
        if constexpr(sameType<T, char>) _k = getchar();
        else if constexpr (sameType<T, char *>) {
            size_t _p = 0;
            int _c = getchar();
            while (_c == ' ' || _c == '\n' || _c == '\r') {
                if (_c < 0 || _c > 255)
                    throw std::runtime_error("In PTF: qRead get unexpected character (may be EOF)\n");
                _c = getchar();
            }
            _k[0] = _c;
            while (_k[_p] != ' ' && _k[_p] != '\n' && _k[_p] != '\r' && _k[_p] != '\0')
                _k[++_p] = getchar();
            _k[_p] = '\0';
        }
        else if constexpr (sameType<std::remove_extent_t<T>, char>) {
            size_t _p = 0;
            const size_t _l = std::extent_v<T>;
            _k[_p] = getchar();
            while (_k[_p] != ' ' && _k[_p] != '\n' && _k[_p] != '\r' && _k[_p] != '\0' && _p < _l)
                _k[++_p] = getchar();
            _k[_p] = '\0';
        }
        else if constexpr(std::is_integral_v<T>) {
            int _c = getchar();
            bool _sign = false;
            _k = 0;
            while (_c < '0' || _c > '9') {
                if (_c < 0 || _c > 255)
                    throw std::runtime_error("In PTF: qRead get unexpected character (may be EOF)\n");
                if (_c == '-') _sign = true;
                _c = getchar();
            }
            while (_c >= '0' && _c <= '9') {
                _k = _k * 10 - 48 + _c; // 此处位运算替代 *10 可能不一定更快
                _c = getchar();
            }
            if (_sign) _k = -_k;
        }
        else static_assert(sameType<T, std::remove_reference_t<T>[1]>,
                           "In PTF: qRead get argument of unexpected type\n");
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
    inline void qWrite(const T &_k) {
        if constexpr(sameType<T, char>) putchar(_k);
        else if constexpr (sameType<T, char *>)
            for (size_t _p = 0; _k[_p] != '\0'; _p++) putchar(_k[_p]);
        else if constexpr (sameType<std::remove_extent_t<T>, char>)
            for (size_t _p = 0, _l = std::extent_v<T>; _k[_p] != '\0' && _p < _l; _p++) putchar(_k[_p]);
        else if constexpr (std::is_integral_v<T>) {
            if (_k == 0) putchar('0');
            else {
                size_t _p = 0;
                T _ck(_k);
                char _c[32];
                if constexpr (std::is_signed_v<T>)
                    if (_ck < 0) putchar('-'), _ck = -_ck;
                while (_ck) _c[_p++] = _ck % 10 + 48, _ck /= 10;
                while (_p--) putchar(_c[_p]);
            }
        }
        else static_assert(sameType<T, std::remove_cv<T>[1]>,
                           "In PTF: qWrite get argument of unexpected type\n");
    }

    inline void qWrite(const auto &... _argList) { (qWrite(_argList), ...); }

    // _s for split character(other type is also acceptable)
    inline void qWriteS(const auto &_s, const auto &... _argList) { ((qWrite(_argList), qWrite(_s)), ...); }

    // _eol for end of line character
    inline void qWriteL(const auto &_eol, const auto &... _argList) { (qWrite(_argList), ...), qWrite(_eol); }

    // 注意最后 _eol 之前无 _s
    inline void qWriteSL(const auto &_s, const auto &_eol, const auto &_first, const auto &... _argList) {
        qWrite(_first), ((qWrite(_s), qWrite(_argList)), ...), qWrite(_eol);
    }

#pragma endregion PTF_IO
}

#endif //PTL_PTF_H
#pragma endregion PaperL_Header

#pragma region BASIC

using namespace PTF;

#define MAXK 30008

int K, M;
int p2, p4, p;
long long int num[MAXK];
char ans[1000000];
int ansp = 0;

#pragma endregion

inline void solve(long long int &k) {
    char c[10];
    int cp = 0;
    while (k) c[cp++] = k % 10, k /= 10;
    while (cp--) {
        while (ansp && M && c[cp] > ans[ansp]) --ansp, --M;
        ans[++ansp] = c[cp];
    }
}

int main() {
    qRead(K, M);
    p = p2 = p4 = num[1] = 1;
    while (p < K) {
        if ((num[p2] << 1 | 1) < ((num[p4] << 2) + 5))
            num[++p] = (num[p2++]) << 1 | 1;
        else num[++p] = ((num[p4++]) << 2) + 5;
    }
    for (int i = 1; i <= K; ++i) qWrite(num[i]);
    putchar(10);
    for (int i = 1; i <= K; ++i) solve(num[i]);
    for (int i = 1; i <= ansp; ++i) putchar(ans[i] + '0');
    return 0;
}
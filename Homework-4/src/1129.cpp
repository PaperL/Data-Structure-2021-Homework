//
// Created by Frank's Laptop on 2021/4/12.
//

#pragma region PaperL_Header
#ifndef PTL_PTF_H
#define PTL_PTF_H

#include <cstdio>
#include <cstdlib>

namespace PTF {
#pragma region PTF_DESCRIPTION
/*
 * "PaperL's Template Function"
 *
 * Version: 1.01
 * Last Update Time: 2021.4.13
 * Last Update Content:
 *      修正 qRead 解决 EOF 的问题
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
            if (_c < 0 || _c > 255) exit(-1);
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

#pragma region BASIC

#include <queue>

#define MAXN 200008

using namespace PTF;

int n;

int ans[2][MAXN], ansP;

#pragma endregion

#pragma region LINKED_LIST

struct LLNode {
    bool ava = true; // available
    char g = -1; // gender
    int a = 0; // dance level
    int pre = 0, nxt = 0;
} ll[MAXN];

#pragma endregion

#pragma region PRIORITY_QUEUE

struct PQElement {
    int da = 0, id1 = 0, id2 = 0;

    bool operator<(const PQElement &other) const { return (da > other.da || (da == other.da && id1 > other.id1)); }
};

std::priority_queue<PQElement> pq;

#pragma endregion

inline void del(const int &id1, const int &id2) {
    int pp = ll[id1].pre, pn = ll[id2].nxt;
    ll[id1].ava = false, ll[id2].ava = false;
    if (pp != 0 && pn != 0) {
        ll[pp].nxt = pn, ll[pn].pre = pp;
        if (ll[pp].ava && ll[pn].ava && ll[pp].g != ll[pn].g)
            pq.push((PQElement) {absT(ll[pp].a - ll[pn].a), pp, pn});
    } else {
        if (pp == 0) ll[pn].pre = 0;
        if (pn == 0) ll[pp].nxt = 0;
    }
}

int main() {
    qRead(n);
    if (n == 0) {
        printf("0\n");
        return 0;
    }
    char c = getchar();
    while (c != 'B' && c != 'G') c = getchar();
    for (int i = 1; i <= n; ++i) {
        ll[i].pre = i - 1, ll[i].nxt = i + 1;
        ll[i].g = (c == 'B') ? 0 : 1;
        c = getchar();
    }
    ll[n].nxt = 0;
    for (int i = 1; i <= n; ++i)qRead(ll[i].a);

    for (int i = 1; i < n; ++i) {
        if (ll[i].g != ll[i + 1].g)
            pq.push((PQElement) {absT(ll[i].a - ll[i + 1].a), i, i + 1});
    }
    PQElement now;
    while (!pq.empty()) {
        now = pq.top();
        const int &id1 = now.id1, &id2 = now.id2;
        pq.pop();
        if (ll[id1].ava && ll[id2].ava) {
            ans[0][++ansP] = id1, ans[1][ansP] = id2;
            del(id1, id2);
        }
    }

    qWriteL('\n', ansP);
    for (int i = 1; i <= ansP; ++i)
        qWriteSL(' ', '\n', ans[0][i], ans[1][i]);
    return 0;
}
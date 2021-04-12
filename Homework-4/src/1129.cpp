//
// Created by Frank's Laptop on 2021/4/12.
//

#pragma region PaperL_Header
#ifndef PTL_PTF_H
#define PTL_PTF_H

#include <cstdio>

namespace PTF {
#pragma region PTF_DESCRIPTION
/*
 * "PaperL's Template Function"
 *
 * Version: 1.0
 * Last Update Time: 2021.4.12
 * Last Update Content:
 *      修改带分隔符的 qWrite 函数分隔符传参方式(参数->形参)
 *      扩展 qWrite 函数功能(支持行末符, 分隔字符串)
 *      采用简写函数模板(c++20)重写部分函数
 *      采用 pragma region 整理代码
 *      用 fold expression 及制约函数(c++20) 重写部分函数
 *          0.8 版本之前的 IO 函数会传参 n^2 数量级次, 极大影响效率
 *      采用变量模板(c++14)重写 PTF_TYPE
 *      新增 absT, setT 函数
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
        char _c = getchar();
        bool _sign = false;
        _k = 0;
        while (_c < '0' || _c > '9') {
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

#define MAXN 20008

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

    bool operator<(const PQElement &other) const {
        return (da > other.da || (da == other.da && id1 > other.id1));
    }
};

std::priority_queue<PQElement> pq;

#pragma endregion

int main() {
    qRead(n);
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
    while (!pq.empty()) {
        const auto now = pq.top();
        pq.pop();
        if (!(ll[now.id1].ava && ll[now.id2].ava))continue;
        ans[0][++ansP] = now.id1, ans[1][ansP] = now.id2;
        ll[now.id1].ava = ll[now.id2].ava = false;

        if (ll[now.id1].pre != 0 && ll[now.id1].nxt != 0) {
            ll[ll[now.id1].pre].nxt = ll[now.id1].nxt;
            ll[ll[now.id1].nxt].pre = ll[now.id1].pre;
            if (ll[ll[now.id1].pre].ava && ll[ll[now.id1].nxt].ava
                && ll[ll[now.id1].pre].g != ll[ll[now.id1].nxt].g)
                pq.push((PQElement) {absT(ll[ll[now.id1].pre].a - ll[ll[now.id1].nxt].a),
                                     ll[now.id1].pre,
                                     ll[now.id1].nxt});
        } else {
            if (ll[now.id1].pre == 0) ll[ll[now.id1].nxt].pre = 0;
            if (ll[now.id1].nxt == 0) ll[ll[now.id1].pre].nxt = 0;
        }
    }

    qWriteL('\n', ansP);
    for (int i = 1; i <= ansP; ++i)
        qWriteSL(' ', '\n', ans[0][i], ans[1][i]);
    return 0;
}
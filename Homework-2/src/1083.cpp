//
// Created by PaperL on 2021/2/27.
//

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

char isElement[208][208];

char isSubElement[208][208];

bool checkSet(char *, int, int);

bool checkElement(char *s, int beg, int end) {
    if (end - beg == 1) {
        return true;
    } else if (beg >= end) {
        return false;
    } else {
        if (isElement[beg][end] != 0)
            return (isElement[beg][end] == 2);
        else {
            bool tans = checkSet(s, beg, end);
            isElement[beg][end] = tans ? 2 : 1;
            return tans;
        }
    }
}

bool checkSubElementList(char *s, int beg, int end) {
    if (isSubElement[beg][end] != 0)return (isSubElement[beg][end] == 2);
    if (checkElement(s, beg, end)) {
        isSubElement[beg][end] = 2;
        return true;
    }
    for (int i = beg; i < end; ++i) {
        if (s[i] == ',') {
            if (checkElement(s, beg, i) && checkSubElementList(s, i + 1, end)) {
                isSubElement[beg][end] = 2;
                return true;
            }
        }
    }
    isSubElement[beg][end] = 1;
    return false;
}

/*bool checkElementList(char *s, int beg, int end) {
    if (beg == end) {
        return true;
    } else if (beg > end) {
        return false;
    } else {
        bool tans = checkSubElementList(s, beg, end);
        return tans;
    }
}*/

bool checkSet(char *s, int beg, int end) {
    if (beg >= end) return false;
    if (s[beg] == '{' && s[end - 1] == '}') {
        ++beg;
        --end;
        if (beg == end) return true;
        else if (beg > end) return false;
        else return checkSubElementList(s, beg, end);
    } else return false;
}

int main() {
    int t;
    char s[208];
    cin >> t;
    for (int ti = 1; ti <= t; ++ti) {
        memset(s, 0, sizeof(s));
        memset(isElement, 0, sizeof(isElement));
        memset(isSubElement,0,sizeof(isSubElement));
        scanf("%s", s);
        printf("Word #%d: %s\n", ti, (checkSet(s, 0, strlen(s))) ? "Set" : "No Set");
    }
    return 0;
}
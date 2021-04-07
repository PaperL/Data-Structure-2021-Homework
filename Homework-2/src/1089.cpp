//
// Created by PaperL on 2021/2/27.
//

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

#define Uint unsigned int
#define Ull unsigned long long

using namespace std;

Uint t, n, m;
Uint like[64], dislike[64];

/* Debug 函数
void bp(Ull k) {
    while (k) {
        cout << (k & 1);
        k >>= 1;
    }
    cout << endl;
}

inline int bitCnt(Ull k) {
    int cnt = 0;
    while (k) {
        if (k & 1)++cnt;
        k >>= 1;
    }
    return cnt;
}*/

bool dfs(int consideringDish, Ull satisfiedPerson, int SPNumber, Uint selectedDish) {
    //cout << consideringDish << ", " << SPNumber << ": ";
    //bp(satisfiedPerson);
    //bp(selectedDish);
    if (SPNumber == m)return true;
    else if (consideringDish == n)return false;
    Ull SSP = satisfiedPerson, NSP = satisfiedPerson;
    int SSPN = SPNumber, NSPN = SPNumber;
    // select
    for (int i = 0; i < m; ++i) {
        if (like[i] & ((Uint) 1 << (Uint) consideringDish)) {
            if (!(SSP & ((Ull) 1 << (Ull) i))) {
                SSP |= ((Ull) 1 << (Ull) i);
                ++SSPN;
            }
        } else if (dislike[i] & ((Uint) 1 << (Uint) consideringDish)) {
            if (!(NSP & ((Ull) 1 << (Ull) i))) {
                NSP |= ((Ull) 1 << (Ull) i);
                ++NSPN;
            }
        }
    }
    if (SSPN > SPNumber && dfs(consideringDish + 1, SSP, SSPN, selectedDish | (1 << consideringDish)))
        return true;
    return dfs(consideringDish + 1, NSP, NSPN, selectedDish);
}

int main() {
    int k;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        memset(like, 0, sizeof(Uint) * m);
        memset(dislike, 0, sizeof(Uint) * m);
        for (Uint i = 0; i < m; ++i) {
            do {
                cin >> k;
                if (k > 0)like[i] |= (Uint) 1 << (Uint) (k - 1);
                else dislike[i] |= (Uint) 1 << (Uint) (-k - 1);
            } while (getchar() != '\r');    // todo 此处由于OJ数据行末为 CR LF, 而又在 linux 下评测,所以不同于正常判断方式
            getchar();                      // todo 如需正常评测应将 line75 改为 '\n', line76 删去
        }
        if (dfs(0, 0, 0, 0))cout << "Bingo!" << endl;
        else cout << "Sigh..." << endl;
    }

    return 0;
}
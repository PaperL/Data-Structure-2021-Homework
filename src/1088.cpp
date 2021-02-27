//
// Created by PaperL on 2021/2/26.
//

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

int fun(int step, int tot, int bound) {
    if (tot == 1)return 0;
    else if (tot == 2)return (1 - (step & 1));
    else {
        int nStep = step % (2 * tot - 2);
        int tBound = (2 * tot - nStep - 2 + bound - 1) % (tot - 1);
        int tAns = fun(step, tot - 1, tBound);
        int Ans = ((abs(bound - abs((nStep) - bound)
                        + (tot - bound - 1)) - (tot - bound - 1) + tot) % tot);
        if (nStep >= bound && nStep < (bound + tot - 1))
            Ans = (Ans + tot - (tAns + 1)) % tot;
        else Ans = (Ans + (tAns + 1)) % tot;
        return Ans;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    cout << fun(m - 1, n, n - 1) + 1 << endl;
    return 0;
}
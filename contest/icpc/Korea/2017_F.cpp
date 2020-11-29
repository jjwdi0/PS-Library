#include <bits/stdc++.h>
using namespace std;

int N, M;

pair<int, int> f(int x, int y) {
    int length = 1 << x;
    int square = length * length / 4;
    if(x == 0) return pair<int, int>(1, 1);
    pair<int, int> res;
    if(1 <= y && y <= square) {
        res = f(x - 1, y);
        return pair<int, int>(res.second, res.first);
    }
    else if(square < y && y <= 2 * square) {
        res = f(x - 1, y - square);
        return pair<int, int>(res.first, res.second + (1 << (x - 1)));
    }
    else if(2 * square < y && y <= 3 * square) {
        res = f(x - 1, y - 2 * square);
        return pair<int, int>(res.first + length / 2, res.second + length / 2);
    }
    else {
        res = f(x - 1, y - 3 * square);
        return pair<int, int>(length + 1 - res.second, length / 2 + 1 - res.first);
    }
}

int main() {
    scanf("%d %d", &N, &M);
    int cnt = 0;
    while(N) cnt++, N /= 2;
    auto it = f(cnt - 1, M);
    printf("%d %d\n", it.first, it.second);
}

#include <bits/stdc++.h>
using namespace std;

int N, D[50005][2];
vector<int> v[50005];

int f(int x, int y, int p = 0) {
    if(D[x][y]) return D[x][y];
    D[x][y] = y;
    for(auto it : v[x]) {
        if(p == it) continue;
        if(y == 0) D[x][y] += max(f(it, 0, x), f(it, 1, x));
        else D[x][y] += f(it, 0, x);
    }
    return D[x][y];
}

int main() {
    scanf("%d", &N);
    for(int i=1, x, y; i<N; i++) {
        scanf("%d %d", &x, &y);
        v[x].push_back(y), v[y].push_back(x);
    }
    printf("%d\n", max(f(1, 0), f(1, 1)));
}

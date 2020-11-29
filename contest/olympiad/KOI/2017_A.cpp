#include <bits/stdc++.h>
using namespace std;

struct Z { int x, y, c; };

int A, B, C, D;
map<int, int> m[100005];
queue<Z> q;

void f(int x, int y, int c) {
    if(x == 0 && y == 0) return;
    if(m[x][y] == 0) m[x][y] = c, q.push({ x, y, c });
}

int main() {
    scanf("%d %d %d %d", &A, &B, &C, &D);
    if(C == 0 && D == 0) return puts("0"),0;
    q.push({ 0,0,0 });
    while(!q.empty()) {
        int x = q.front().x, y = q.front().y, c = q.front().c; q.pop();
        f(A, y, c + 1);
        f(x, B, c + 1);
        f(0, y, c + 1);
        f(x, 0, c + 1);
        if(x + y > A) f(A, y - (A - x), c + 1);
        else f(x + y, 0, c + 1);
        if(x + y > B) f(x - (B - y), B, c + 1);
        else f(0, x + y, c + 1);
    }
    printf("%d\n", m[C][D] ? m[C][D] : -1);
}

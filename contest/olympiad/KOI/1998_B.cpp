#include <bits/stdc++.h>
using namespace std;

struct Z { int x, y, z; Z() {} Z(int X, int Y, int Z) { x = X, y = Y, z = Z; } };

int N, D[55][55][2];
char A[55][55];
queue<Z> q;

bool can(int x, int y) { return !(x < 1 || y < 1 || x > N || y > N || A[x][y] == '1'); }

int main() {
    scanf("%d", &N);
    for(int i=1; i<=N; i++) scanf("%s", A[i] + 1);
    int sx, sy, sd, ex, ey, ed;
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) {
        if(i <= N - 2 && A[i][j] == 'B' && A[i+1][j] == 'B' && A[i+2][j] == 'B') sx = i + 1, sy = j, sd = 0;
        if(i <= N - 2 && A[i][j] == 'E' && A[i+1][j] == 'E' && A[i+2][j] == 'E') ex = i + 1, ey = j, ed = 0;
        if(j <= N - 2 && A[i][j] == 'B' && A[i][j+1] == 'B' && A[i][j+2] == 'B') sx = i, sy = j + 1, sd = 1;
        if(j <= N - 2 && A[i][j] == 'E' && A[i][j+1] == 'E' && A[i][j+2] == 'E') ex = i, ey = j + 1, ed = 1;
    }
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) if(A[i][j] != '0' && A[i][j] != '1') A[i][j] = '0';
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) D[i][j][0] = D[i][j][1] = 1e9;
    D[sx][sy][sd] = 0;
    q.push(Z(sx, sy, sd));
    while(!q.empty()) {
        int x = q.front().x, y = q.front().y, z = q.front().z; q.pop();
        if(x == ex && y == ey && z == ed) return !printf("%d\n", D[x][y][z]);
        if(z == 0) {
            if(can(x - 2, y) && can(x - 1, y) && can(x, y) && D[x-1][y][0] > D[x][y][0] + 1) q.push(Z(x - 1, y, 0)), D[x-1][y][0] = D[x][y][0] + 1;
            if(can(x, y) && can(x + 1, y) && can(x + 2, y) && D[x+1][y][0] > D[x][y][0] + 1) q.push(Z(x + 1, y, 0)), D[x+1][y][0] = D[x][y][0] + 1;
            if(can(x - 1, y - 1) && can(x, y - 1) && can(x + 1, y - 1) && D[x][y-1][0] > D[x][y][0] + 1) q.push(Z(x, y - 1, 0)), D[x][y-1][0] = D[x][y][0] + 1;
            if(can(x - 1, y + 1) && can(x, y + 1) && can(x + 1, y + 1) && D[x][y+1][0] > D[x][y][0] + 1) q.push(Z(x, y + 1, 0)), D[x][y+1][0] = D[x][y][0] + 1;
            if(can(x - 1, y - 1) && can(x - 1, y) && can(x - 1, y + 1) && can(x, y - 1) &&
               can(x, y) && can(x, y + 1) && can(x + 1, y - 1) && can(x + 1, y) && can(x + 1, y + 1) && D[x][y][1] > D[x][y][0] + 1) q.push(Z(x, y, 1)), D[x][y][1] = D[x][y][0] + 1;
        }
        else {
            if(can(x, y - 2) && can(x, y - 1) && can(x, y) && D[x][y-1][1] > D[x][y][1] + 1) q.push(Z(x, y - 1, 1)), D[x][y-1][1] = D[x][y][1] + 1;
            if(can(x, y) && can(x, y + 1) && can(x, y + 2) && D[x][y+1][1] > D[x][y][1] + 1) q.push(Z(x, y + 1, 1)), D[x][y+1][1] = D[x][y][1] + 1;
            if(can(x - 1, y - 1) && can(x - 1, y) && can(x - 1, y + 1) && D[x-1][y][1] > D[x][y][1] + 1) q.push(Z(x - 1, y, 1)), D[x-1][y][1] = D[x][y][1] + 1;
            if(can(x + 1, y - 1) && can(x + 1, y) && can(x + 1, y + 1) && D[x+1][y][1] > D[x][y][1] + 1) q.push(Z(x + 1, y, 1)), D[x+1][y][1] = D[x][y][1] + 1;
            if(can(x - 1, y - 1) && can(x - 1, y) && can(x - 1, y + 1) && can(x, y - 1) &&
               can(x, y) && can(x, y + 1) && can(x + 1, y - 1) && can(x + 1, y) && can(x + 1, y + 1) && D[x][y][0] > D[x][y][1] + 1) q.push(Z(x, y, 0)), D[x][y][0] = D[x][y][1] + 1;
        }
    }
    puts("0");
}

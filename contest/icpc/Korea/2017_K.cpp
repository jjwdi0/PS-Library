#include <bits/stdc++.h>
using namespace std;

int N, mxX, mxY, mnX, mnY, curX, curY, dir;

int main() {
    scanf("%d", &N);
    for(int i=1, x, y; i<=N; i++) {
        scanf("%d %d", &x, &y);
        if(dir == 0) printf("%d ", mxX - curX + 1), curX = mxX + 1, mxX++;
        if(dir == 1) printf("%d ", curY - mnY + 1), curY = mnY - 1, mnY--;
        if(dir == 2) printf("%d ", curX - mnX + 1), curX = mnX - 1, mnX--;
        if(dir == 3) printf("%d ", mxY - curY + 1), curY = mxY + 1, mxY++;
        dir += y;
        if(dir < 0) dir += 4;
        if(dir > 3) dir -= 4;
    }
}

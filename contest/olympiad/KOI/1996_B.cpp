#include <bits/stdc++.h>
using namespace std;

int N, D[103][103];
int adj[103], ans;

int main() {
    scanf("%d", &N);
    for(int i=0, x, y; i<N; i++) {
        scanf("%d %d", &x, &y);
        adj[x] = y, adj[y] = x;
    }
    for(int i=1; i<=100; i++) for(int j=1; i+j<=100; j++) {
        int s = j, e = i + j;
        D[s][e] = max(D[s+1][e], D[s][e-1]);
        if(adj[s] == e) D[s][e] = max(D[s][e], D[s+1][e-1] + 1);
        if(adj[s] < e && s < adj[s]) D[s][e] = max(D[s][e], D[s+1][adj[s]-1] + D[adj[s]+1][e] + 1);
        if(adj[e] < e && s < adj[e]) D[s][e] = max(D[s][e], D[adj[e]+1][e-1] + D[s][adj[e]-1] + 1);
    }
    printf("%d\n", D[1][100]);
}

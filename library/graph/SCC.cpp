#include <bits/stdc++.h>
using namespace std;

int N, M, cnt;
vector<int> v[40006], rev[40006];
vector<int> dfn, rem;
bool visited[40006];
int SCC[40006]; // SCC[x] := SCC number node x is belonging

void add_edge(int s, int e) { v[s].push_back(e), rev[e].push_back(s); }
void dfs(int x) {
    visited[x] = 1;
    for(int it : v[x]) if(!visited[it]) dfs(it);
    dfn.push_back(x);
}
void rev_dfs(int x, int num) {
    visited[x] = 1;
    SCC[x] = num;
    for(int it : rev[x]) if(!visited[it]) rev_dfs(it, num);
}
int NOT(int x) { return x > N ? x - N : x + N; } // For 2-SAT
void makeSCC() {
    // Suppose all edges were added already
    int V = N * 2; // In case of 2-SAT.
    for(int i=1; i<=V; i++) if(!visited[i]) dfs(i);
    memset(visited, 0, sizeof(visited));
    for(int i=(int)dfn.size()-1; i>=0; i--) if(!visited[dfn[i]]) rev_dfs(dfn[i], ++cnt);
}
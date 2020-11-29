#include <bits/stdc++.h>
using namespace std;

int N, M, cnt, SCC[10006];
vector<int> v[10006], rev[10006], dfn;
bool chk[10006];

void add_edge(int s, int e) { v[s].push_back(e), rev[e].push_back(s); }

void dfs(int x) {
    chk[x] = 1;
    for(int it : v[x]) if(!chk[it]) dfs(it);
    dfn.push_back(x);
}

void rdfs(int x, int num) {
    chk[x] = 1;
    SCC[x] = num;
    for(int it : rev[x]) if(!chk[it]) rdfs(it, num);
}

int NOT(int x) { return x > N ? x - N : x + N; }

int main() {
    scanf("%d %d", &N, &M);
    for(int i=1, x, y, z; i<=M; i++) {
        char a, b, c;
        scanf("%d %c %d %c %d %c", &x, &a, &y, &b, &z, &c);
        int e1 = (a == 'R' ? x + N : x);
        int e2 = (b == 'R' ? y + N : y);
        int e3 = (c == 'R' ? z + N : z);
        add_edge(NOT(e2), e1), add_edge(NOT(e1), e2);
        add_edge(NOT(e3), e2), add_edge(NOT(e2), e3);
        add_edge(NOT(e1), e3), add_edge(NOT(e3), e1);
    }
    for(int i=1; i<=N+N; i++) if(!chk[i]) dfs(i);
    memset(chk, 0, sizeof(chk));
    for(int i=(int)dfn.size()-1; i>=0; i--) if(!chk[dfn[i]]) rdfs(dfn[i], ++cnt);
    for(int i=1; i<=N; i++) if(SCC[i] == SCC[i + N]) return puts("-1"),0;
    for(int i=1; i<=N; i++) printf("%c", SCC[i] > SCC[i + N] ? 'B' : 'R');
}

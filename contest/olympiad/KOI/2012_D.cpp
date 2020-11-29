#include <bits/stdc++.h>
#define y1 AmazingVariable
using namespace std;

struct Stick {
    int x1, y1, x2, y2;
    Stick() {}
    Stick(int _x1, int _y1, int _x2, int _y2) { x1 = _x1, y1 = _y1, x2 = _x2, y2 = _y2; }
}A[3003];

int N, cnt;
int FALSE;
vector<int> v[6006], rev[6006];
vector<int> dfn, rem;
bool visited[6006];
int SCC[6006];

void add_edge(int s, int e) { v[s].push_back(e), rev[e].push_back(s); }

int single(int x) { return x > 0 ? 1 : (x < 0 ? -1 : 0); }

int ccw(int x1, int y1, int x2, int y2, int x3, int y3) { return single(x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2); }

bool is_cross(int i, int j) { return
    ccw(A[i].x1, A[i].y1, A[i].x2, A[i].y2, A[j].x1, A[j].y1) *
    ccw(A[i].x1, A[i].y1, A[i].x2, A[i].y2, A[j].x2, A[j].y2) == -1 &&
    ccw(A[j].x1, A[j].y1, A[j].x2, A[j].y2, A[i].x1, A[i].y1) *
    ccw(A[j].x1, A[j].y1, A[j].x2, A[j].y2, A[i].x2, A[i].y2) == -1;
}

void dfs(int x) {
    visited[x] = 1;
    for(int it : v[x]) {
        if(!visited[it]) dfs(it);
    }
    dfn.push_back(x);
}

void rev_dfs(int x, int num) {
    visited[x] = 1;
    SCC[x] = num;
    for(int it : rev[x]) {
        if(!visited[it]) rev_dfs(it, num);
    }
}

int main() {
    scanf("%d", &N);
    FALSE = 3 * N;
    for(int i=1; i<=N*3; i++) scanf("%d %d %d %d", &A[i].x1, &A[i].y1, &A[i].x2, &A[i].y2);
    for(int i=1; i<=N; i++) {
        int e1 = 3 * i - 2, e2 = 3 * i - 1, e3 = 3 * i;
        add_edge(e1 + FALSE, e2);
        add_edge(e1 + FALSE, e3);
        add_edge(e2 + FALSE, e1);
        add_edge(e2 + FALSE, e3);
        add_edge(e3 + FALSE, e1);
        add_edge(e3 + FALSE, e2);
    }
    for(int i=1; i<=3*N; i++) for(int j=i+1; j<=3*N; j++) if(is_cross(i, j)) add_edge(i, j + FALSE), add_edge(j, i + FALSE);
    for(int i=1; i<=FALSE*2; i++) if(!visited[i]) dfs(i);
    memset(visited, 0, sizeof(visited));
    for(int i=(int)dfn.size()-1; i>=0; i--) if(!visited[dfn[i]]) rev_dfs(dfn[i], ++cnt);
    for(int i=1; i<=FALSE; i++) {
        if(SCC[i] == SCC[i + FALSE]) return puts("-1"),0;
        if(SCC[i] < SCC[i + FALSE]) rem.push_back(i);
    }
    printf("%d\n", (int)rem.size());
    for(int it : rem) printf("%d ", it);
}

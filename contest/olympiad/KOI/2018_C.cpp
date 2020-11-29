#include <bits/stdc++.h>
#define ROOT 450
using namespace std;
using pr = pair<int, int>;
using tr = pair<int, pr>;
using ll = long long;
 
int R, N, ans;
pr A[200005];
tr B[200005];
vector<int> v;
int comp[200005];
vector<int> comp2[ROOT];
 
struct seg_tree {
    int tree[ROOT*4], base;
    void init(int x) { for(base=1; base<x; base<<=1); for(int i=1; i<=base*2; i++) tree[i] = 0; }
    void update(int x, int y) {
        x += base - 1;
        tree[x] = y, x /= 2;
        while(x) tree[x] = max(tree[x*2], tree[x*2+1]), x /= 2;
    }
    int RMQ(int s, int e) {
        s += base - 1, e += base - 1;
        int res = 0;
        while(s < e) {
            if(s & 1) res = max(res, tree[s++]);
            if(!(e & 1)) res = max(res, tree[e--]);
            s >>= 1, e >>= 1;
        }
        if(s == e) res = max(res, tree[s]);
        return res;
    }
} S[ROOT];
 
vector<tr> bucket[ROOT];
 
int main() {
    scanf("%d %d", &R, &N);
    if(R == 2) {
        for(int i=1; i<=N; i++) scanf("%d", &A[i].first);
        for(int i=1; i<=N; i++) scanf("%d", &A[i].second);
        sort(A+1, A+N+1);
        for(int i=1; i<=N; i++) {
            auto it = lower_bound(v.begin(), v.end(), A[i].second);
            if(it == v.end()) v.push_back(A[i].second);
            else *it = A[i].second;
        }
        printf("%d\n", v.size());
    }
    else {
        for(int i=0; i<=N/ROOT; i++) S[i].init(ROOT);
        for(int i=1; i<=N; i++) scanf("%d", &B[i].first);
        for(int i=1; i<=N; i++) scanf("%d", &B[i].second.first);
        for(int i=1; i<=N; i++) scanf("%d", &B[i].second.second);
        sort(B+1, B+N+1);
        for(int i=1; i<=N; i++) comp[i] = B[i].second.first;
        sort(comp+1, comp+N+1);
        for(int i=1; i<=N; i++) B[i].second.first = (int)( lower_bound(comp+1, comp+N+1, B[i].second.first) - comp );
        for(int i=1; i<=N; i++) comp[i] = B[i].second.second;
        sort(comp+1, comp+N+1);
        for(int i=1; i<=N; i++) B[i].second.second = (int)( lower_bound(comp+1, comp+N+1, B[i].second.second) - comp );
 
        int ans = 0;
 
        for(int i=1; i<=N; i++) comp2[B[i].second.first/ROOT].push_back(B[i].second.second);
        for(int i=0; i<=N/ROOT; i++) sort(comp2[i].begin(), comp2[i].end());
 
        for(int i=1; i<=N; i++) {
            int idx = B[i].second.first / ROOT;
            int mx = 1;
            for(int j=0; j<idx; j++) {
                mx = max(mx, S[j].RMQ(1, (int)(upper_bound(comp2[j].begin(), comp2[j].end(), B[i].second.second) - comp2[j].begin()) ) + 1);
            }
            for(auto it : bucket[idx]) {
                if(it.second.first < B[i].second.first && it.second.second < B[i].second.second) mx = max(mx, it.first + 1);
            }
            bucket[idx].push_back(tr(mx, B[i].second));
            S[idx].update((int)(lower_bound(comp2[B[i].second.first/ROOT].begin(), comp2[B[i].second.first/ROOT].end(), B[i].second.second) - comp2[B[i].second.first/ROOT].begin()) + 1, mx);
            ans = max(ans, mx);
        }
        printf("%d\n", ans);
    }
}
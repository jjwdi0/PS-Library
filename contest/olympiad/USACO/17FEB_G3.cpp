#include <bits/stdc++.h>
#define SQRT 223
using namespace std;
typedef long long ll;

struct query {
    int l, r, ti;
    query() {l = r = 0;}
    query(int _l, int _r) {l = _l, r = _r;}
    bool operator < (const query &A) const {
        return l / SQRT == A.l / SQRT ? r < A.r : l < A.l;
    }
}T[50003];

int N, A[100005], k, c[50003], cnt;
vector<int> v[50003];
ll ans;

void f(int add, int x) {
    c[x] += add;
    if(c[x] & 1) cnt++;
    else cnt--;
}

int main() {
    scanf("%d", &N);
    for(int i=1; i<=N*2; i++) scanf("%d", A+i), v[A[i]].push_back(i);
    for(int i=1; i<=N; i++) T[i-1] = query(v[i][0], v[i][1]);
    sort(T, T+N);
    int l = 1, r = 0;
    for(int i=0; i<N; i++) {
        while(r < T[i].r) f(1, A[++r]);
        while(r > T[i].r) f(-1, A[r--]);
        while(l < T[i].l) f(-1, A[l++]);
        while(l > T[i].l) f(1, A[--l]);
        ans += (ll)cnt;
    }
    printf("%lld\n", ans / 2LL);
}
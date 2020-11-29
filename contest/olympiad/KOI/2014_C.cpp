#include <stdio.h>
#include <vector>
#define INF (1LL)<<58
#define sz(x) ((int)(x).size())
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pr;

struct CHT{
    vector<pr> v;
    int ind = 0;
    double cross(pr X, pr Y) {return (double)(X.second - Y.second) / (Y.first - X.first);}
    void push(ll m, ll b) {
        while(sz(v) >= 2 && cross(v[sz(v)-2], v[sz(v)-1]) > cross(v[sz(v)-1], {m, b})) v.pop_back();
        v.push_back({m, b});
    }
    ll q(double x) {
        while(ind < sz(v) - 1 && cross(v[ind], v[ind+1]) <= x) ind++;
        return v[ind].first * x + v[ind].second;
    }
}cht1, cht2;
int N, A[1000003], S1[1000003], S2[1000003];
ll D1[1000003], D2[1000003];
  
int main() {
    scanf("%d", &N);
    for(int i=1; i<=N; i++) scanf("%d", A+i), S1[i] = S1[i-1] + A[i];
    for(int i=N; i>0; i--) S2[i] = S2[i+1] + A[i];
    cht1.push(0, 0);
    for(int i=1; i<=N; i++) {
        if(!A[i]) D1[i] = D1[i-1];
        else {
            D1[i] = cht1.q(i) + (ll)(S1[i] + 1) * i;
            cht1.push(-S1[i], D1[i]);
        }
    }
    cht2.push(0, 0);
    for(int i=N; i>0; i--) {
        if(!A[i]) D2[i] = D2[i+1];
        else {
            D2[i] = cht2.q(N - i + 1) + (ll)(S2[i] + 1) * (N - i + 1);
            cht2.push(-S2[i], D2[i]);
        }
    }
    ll ans = INF;
    for(int i=0; i<N; i++) ans = min(ans, D1[i] + D2[i+1]);
    printf("%lld", ans);
}
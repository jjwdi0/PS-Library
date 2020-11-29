#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N;
ll ans;
vector<int> v[100005];

int main() {
    scanf("%d", &N);
    for(int i=1, x, y; i<=N; i++) {
        scanf("%d %d", &x, &y);
        v[y].push_back(x);
    }
    for(int i=1; i<=N; i++) sort(v[i].begin(), v[i].end());
    for(int i=1; i<=N; i++) {
        if((int)v[i].size() <= 1) continue;
        for(int j=0; j<v[i].size(); j++) {
            if(j == 0) ans += v[i][j+1] - v[i][j];
            else if(j == (int)v[i].size() - 1) ans += v[i][j] - v[i][j-1];
            else ans += min(v[i][j] - v[i][j-1], v[i][j+1] - v[i][j]);
        }
    }
    printf("%lld\n", ans);
}

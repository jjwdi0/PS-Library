#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, F[100005], S[100005];
ll M;
deque<int> dq;

int main() {
    scanf("%d %lld", &N, &M);
    ll cnt = 0LL;
    for(int i=1; i<=N; i++) scanf("%d %d", F+i, S+i);
    int j = 1, ans = 1e9;
    for(int i=1; i<=N; i++) {
        while(j <= N && cnt < M) {
            cnt += F[j];
            while(!dq.empty() && dq.front() <= i) dq.pop_front();
            while(!dq.empty() && S[dq.back()] <= S[j]) dq.pop_back();
            dq.push_back(j);
            j++;
        }
        if(cnt < M) break;
        ans = min(ans, S[dq.front()]);
        cnt -= F[i];
    }
    printf("%d\n", ans);
}

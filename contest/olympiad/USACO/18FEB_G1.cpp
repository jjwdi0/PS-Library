#include <bits/stdc++.h>
using namespace std;
using pr = pair<int, int>;
using tr = pair<int, pr>;

int N, B, A[100005], output[100005], ans = 0;
set<pr> s;
set<int> num;
multiset<int> ms;
tr Q[100005];

void add(int x) {
    if((int)num.size() == 0) { num.insert(x); return; }
    auto it = num.lower_bound(x);
    auto it2 = it;
    if(it == num.end()) {
        it2--;
        ms.insert(x - *it2);
    }
    else if(it == num.begin()) {
        ms.insert(*it - x);
    }
    else {
        it2--;
        auto it3 = ms.find(*it - *it2);
        ms.erase(it3);
        ms.insert(*it - x), ms.insert(x - *it2);
    }
    num.insert(x);
    ans = *ms.rbegin();
}

bool cmp(const tr &X, const tr &Y) { return X.second < Y.second; }

int main() {
    scanf("%d %d", &N, &B);
    for(int i=1; i<=N; i++) scanf("%d", A+i), s.insert(pr(A[i], i));
    for(int i=1; i<=B; i++) scanf("%d %d", &Q[i].second.first, &Q[i].second.second), Q[i].first = i;
    sort(Q+1, Q+B+1, cmp);
    for(int i=1, j; i<=N; ) {
        j = i;
        while(j <= N && Q[i].second.first == Q[j].second.first) j++;
        for(auto it : s) {
            if(it.first <= Q[i].second.first) add(it.second);
            else break;
        }
        s.erase(s.begin(), s.upper_bound(pr(Q[i].second.first, 1e9)));
        for(int k=i; k<j; k++) output[Q[k].first] = (ans <= Q[k].second.second);
        i = j;
    }
    for(int i=1; i<=B; i++) printf("%d\n", output[i]);
}

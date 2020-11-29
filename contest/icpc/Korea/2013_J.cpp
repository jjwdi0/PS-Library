#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }

int T, N;
vector<ll> v;

int main() {
	int ans = 0;
	for(int i=1; i<=600; i++) for(int j=i+1; j<=600; j++) {
		ll x = 2LL * i * j, y = 1LL * j * j - 1LL * i * i;
		if(x + y > 500000 || gcd(x, y) > 1) continue;
		v.push_back(x + y);
	}
	sort(v.begin(), v.end());
	for(int i=1; i<v.size(); i++) v[i] += v[i-1];
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &N);
		N >>= 1;
		printf("%d\n", upper_bound(v.begin(), v.end(), N) - v.begin());
	}
}

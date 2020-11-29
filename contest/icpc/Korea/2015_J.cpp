#include <bits/stdc++.h>
using namespace std;

bool t[1003];
int T, N;
vector<int> v;

int main() {
	scanf("%d", &T);
	for(int i=2; i*i<=1000; i++) for(int j=i*i; j<=1000; j+=i) t[j] = 1;
	for(int i=2; i<=1000; i++) if(!t[i]) v.push_back(i);
	while(T--) {
		scanf("%d", &N);
		bool f = false;
		for(auto i : v) {
			if(f) break;
			for(auto j : v) {
				if(f) break;
				for(auto k : v) {
					if(i + j + k == N) f = true, printf("%d %d %d\n", i, j, k);
				}
			}
		}
	}
}
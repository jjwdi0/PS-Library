#include <bits/stdc++.h>
using namespace std;

int T, N, M;

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &N, &M);
		string x = "", y = "", str = "";
		for(int i=0,t; i<M; i++) {
			scanf("%d", &t);
			x += to_string(t);
		}
		for(int i=0,t; i<M; i++) {
			scanf("%d", &t);
			y += to_string(t);
		}
		for(int i=0, t; i<N; i++) {
			scanf("%d", &t);
			str += to_string(t);
		}
		str += str;
		int cnt = 0;
		for(int i=0; i<str.length()/2; i++) if(str.substr(i, M) >= x && str.substr(i, M) <= y) cnt++;
		printf("%d\n", cnt);
	}
}
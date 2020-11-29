#include <bits/stdc++.h>
using namespace std;

int N, P[1000003], f[1000003], k, p;

void get_failure() {
	for(int i=1; i<N; i++) {
		int j = i;
		while(f[j-1] && P[f[j-1]] != P[i]) j = f[j-1];
		f[i] = f[j-1] + (P[f[j-1]] == P[i]);
	}
}

int main() {
    scanf("%d", &N);
    for(int i=0; i<N; i++) scanf("%d", P+i);
    reverse(P, P + N);
    get_failure();
    k = N - 1, p = 1;
    for(int i=1; i<N; i++) if(k + p > N - f[i] || (k + p == N - f[i] && p > i + 1 - f[i])) k = N - i - 1, p = i + 1 - f[i];
    printf("%d %d\n", k, p);
}

#include <bits/stdc++.h>
#define MOD 10007
using namespace std;

int T, N, D1[50005] = {0, 1}, D2[50005] = {0, 1, 12, 75, 384, 1805, 8100};

int main() {
	scanf("%d", &T);
	for(int i=2; i<=50000; i++) D1[i] = (D1[i-1] * 4 - D1[i-2] + MOD * MOD) % MOD;
	for(int i=7; i<=50000; i++) D2[i] = (D2[i-1] * 10 - D2[i-2] * 35 + D2[i-3] * 52 - D2[i-4] * 35 + D2[i-5] * 10 - D2[i-6] + MOD * MOD) % MOD;
	while(T--) scanf("%d", &N), printf("%d %d\n", D1[N], D2[N]);
}

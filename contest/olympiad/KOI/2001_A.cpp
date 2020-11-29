#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;

int T, N, M, A[1003], B[1003], S1[555555], S2[555555], sz1, sz2;
ll ans;

int main() {
	scanf("%d", &T); scanf("%d", &N);
	for(int i = 1; i <= N; i++) {
		scanf("%d", A + i); int sum = 0;
		for(int j = i; j >= 1; j--) sum += A[j], S1[sz1++] = sum;
	}
	scanf("%d", &M);
	for(int i = 1; i <= M; i++) {
		scanf("%d", B + i); int sum = 0;
		for(int j = i; j >= 1; j--) sum += B[j], S2[sz2++] = sum;
	}
	sort(S1, S1 + sz1); sort(S2, S2 + sz2); reverse(S2, S2 + sz2);
	int I = 0, J = 0;
	while(I < sz1 && J < sz2) {
		if(S1[I] + S2[J] > T) J++;
		else if(S1[I] + S2[J] < T) I++;
		else {
			int i = I, j = J;
			while(S1[i] == S1[I] && i < sz1) i++;
			while(S2[j] == S2[J] && j < sz2) j++;
			ans += (ll)(i - I) * (ll)(j - J); I = i, J = j;
		}
	}
	printf("%lld", ans);
}

#include <bits/stdc++.h>
using namespace std;

struct BIT {
    int tree[100005], base;
    void init(int x) { base = x; }
    void add(int x, int y) { while(x <= base) tree[x] += y, x += x & -x; }
    int q(int x) {
        int res = 0;
        while(x) res += tree[x], x -= x & -x;
        return res;
    }
} bit;

int N, A[100005];

int main() {
	scanf("%d", &N);
	bit.init(N);
	for(int i=1; i<=N; i++) scanf("%d", A+i);
	bit.add(A[N], 1);
	for(int i=N-1; i; i--) {
        if(A[i] > A[i+1]) {
            printf("%d\n", i);
            for(int j=1; j<=i; j++) {
                printf("%d ", i - j + bit.q(A[j]));
                bit.add(A[j], 1);
            }
            return 0;
        }
        else bit.add(A[i], 1);
	}
}

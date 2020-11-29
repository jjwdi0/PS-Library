#include <stdio.h>
#include <map>
using namespace std;

struct BIT {
    int tree[500005], base;
    void init(int x) { base = x; }
    void add(int x, int y) { while(x <= base) tree[x] += y, x += x & -x; }
    int q(int x) {
        int res = 0;
        while(x) res += tree[x], x -= x & -x;
        return res;
    }
}bit;

int N, A[500005];
map<int, int> m;

int main() {
    scanf("%d", &N);
    bit.init(N);
    for(int i=1; i<=N; i++) scanf("%d", A+i), m[A[i]] = i;
    int idx = 1;
    for(pair<int, int> it : m) A[it.second] = idx++;
    for(int i=1; i<=N; i++) {
        printf("%d\n", bit.q(N) - bit.q(A[i]) + 1);
        bit.add(A[i], 1);
    }
}

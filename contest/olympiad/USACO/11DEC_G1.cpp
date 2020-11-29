#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;

int N, B[20005];
map<int, int> A[5];

bool cmp(const int &x, const int &y) {
	int cnt = 0;
	for(int i = 0; i < 5; i++) cnt += (A[i][x] < A[i][y]);
	return cnt >= 3;
}

int main() {
	scanf("%d", &N);
	for(int i = 0; i < 5; i++) for(int j = 0, x; j < N; j++) scanf("%d", &x), B[j] = x, A[i][x] = j;
	sort(B, B + N, cmp); for(int i = 0; i < N; i++) printf("%d\n", B[i]);
}
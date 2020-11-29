#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int, int> pr;
typedef pair<pr, int> tr;

int M, N, mx;
tr A[500003];
queue<int> q;
bool output[500005];

int main() {
    scanf("%d %d", &M, &N);
    for(int i=1; i<=N; i++) {
        scanf("%d %d", &A[i].first.first, &A[i].first.second);
        if(A[i].first.first > A[i].first.second) A[i].first.second += M;
        A[i].second = i;
    }
    sort(A+1, A+N+1);
    for(int i=1; i<=N; ) {
        int j = i;
        while(j <= N && A[i].first.first == A[j].first.first) j++; j--;
        if(mx < A[j].first.second) q.push(j), mx = A[j].first.second;
        i = j + 1;
    }
    while(A[q.front()].first.second <= mx - M) q.pop();
    while(!q.empty()) output[A[q.front()].second] = 1, q.pop();
    for(int i=1; i<=N; i++) if(output[i]) printf("%d ", i);
}

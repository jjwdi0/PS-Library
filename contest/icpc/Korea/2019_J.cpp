#include <bits/stdc++.h>
using namespace std;

int N;

int main() {
    scanf("%d", &N);
    for(int i=3, j=1, ans=0; i<=N; i+=j+j, ans+=2, j<<=1) {
        if(i + j - 1 >= N) return !printf("%d\n", ans);
        else if(i + j + j - 1 >= N) return !printf("%d\n", ans + 1);
    }
}

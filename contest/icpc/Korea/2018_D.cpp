#include <bits/stdc++.h>
using namespace std;

int N;
char A[35];

int main() {
    scanf("%d", &N);
    for(int i=0; i<N; i++) {
        for(int j=0; j<35; j++) A[j] = 0;
        scanf("%s", A);
        int len = strlen(A);
        if(A[len-1] == 'a' || A[len-1] == 'o' || A[len-1] == 'u') A[len] = 's';
        else if(A[len-1] == 'i' || A[len-1] == 'y') A[len-1] = 'i', A[len] = 'o', A[len+1] = 's';
        else if(A[len-1] == 'l' || A[len-1] == 'r' || A[len-1] == 'v') A[len] = 'e', A[len+1] = 's';
        else if(A[len-1] == 'n') A[len-1] = 'a', A[len] = 'n', A[len+1] = 'e', A[len+2] = 's';
        else if(A[len-2] == 'n' && A[len-1] == 'e') A[len-2] = 'a', A[len-1] = 'n', A[len] = 'e', A[len+1] = 's';
        else if(A[len-1] == 't' || A[len-1] == 'w') A[len] = 'a', A[len+1] = 's';
        else A[len] = 'u', A[len+1] = 's';
        puts(A);
    }
}

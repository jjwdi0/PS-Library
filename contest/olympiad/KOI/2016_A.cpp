#include <stdio.h>
#include <algorithm>
using namespace std;

int dp[110][50];
int s[110];

int main() {
    int n,m;
    int ans = 1e9;

    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d",&s[i]);
    if(n == m) {
        printf("0");
        return 0;
    }
    for(int i=0;i<=n;i++) for(int j=0;j<=49;j++) dp[i][j]=1e9;
    dp[0][0] = 0;
    for(int i=1;i<=n;i++) {
        int c = 0;
        for(int j=1;j<=m;j++) {
            if(i == s[j]) c = 1;
        }
        if(i == 1 && c == 0) dp[i][0]=10;
        else if(c == 0) {
            for(int j=0;j<=40;j++) {
                if(j >= 2 && i >= 5) {
                    dp[i][j] = min({dp[i-1][j]+10,dp[i-3][j-1]+25,dp[i-5][j-2]+37,dp[i-1][j+3]});
                }
                else if(j >= 1 && i >= 3) {
                    dp[i][j] = min({dp[i-1][j]+10,dp[i-3][j-1]+25,dp[i-1][j+3]});
                }
                else {
                    dp[i][j] = min({dp[i-1][j]+10,dp[i-1][j+3]});
                }
            }
        }
        else {
            for(int j=0;j<=40;j++) {
                if(j>=2&&i>=5) {
                    dp[i][j] = min({dp[i-1][j],dp[i-3][j-1]+25,dp[i-5][j-2]+37});
                }
                else if(j>=1&&i>=3) {
                    dp[i][j] = min({dp[i-1][j],dp[i-3][j-1]+25});
                }
                else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
    }
    for(int i=0;i<=40;i++) if(ans>dp[n][i]) ans=dp[n][i];
    printf("%d", ans * 1000);
    return 0;
}

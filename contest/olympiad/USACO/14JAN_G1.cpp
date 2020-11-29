#include <bits/stdc++.h>
#define all(x) (x).begin()+1,(x).end()
#define sz(x) ((int)(x).size())
using namespace std;
typedef long long ll;
typedef pair<int, int> pr;

int ccw(int x1, int y1, int x2, int y2, int x3, int y3) {
    ll r = (ll)x1 * (ll)y2 + (ll)x2 * (ll)y3 + (ll)x3 * (ll)y1;
    r -= (ll)x2 * (ll)y1 + (ll)x3 * (ll)y2 + (ll)x1 * (ll)y3;
    return r > 0LL ? 1 : (r < 0LL ? -1 : 0);
}

struct point {
    int x, y;
    int team;
    bool operator < (const point &A) const { return ccw(0, 0, x, y, A.x, A.y) < 0; }
}A[50003], B[50003];

int N;
vector<point> v1, v2;
vector<point> AC, BC;

int f(point a, point b, point c) { return ccw(a.x, a.y, b.x, b.y, c.x, c.y); }
int c(point a, point b, point c) { return min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x) && min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y); }

int main() {
    scanf("%d", &N);
    int idx1 = 0, idx2 = 0;
    for(int i=0; i<N; i++) {
        scanf("%d %d", &A[i].x, &A[i].y);
        A[i].team = 1;
        if(pr(A[i].x, A[i].y) < pr(A[idx1].x, A[idx1].y)) idx1 = i;
    }
    for(int i=0; i<N; i++) {
        scanf("%d %d", &B[i].x, &B[i].y);
        B[i].team = 2;
        if(pr(B[i].x, B[i].y) < pr(B[idx2].x, B[idx2].y)) idx2 = i;
    }
    swap(A[idx1], A[0]), swap(B[idx2], B[0]);
    int cx1 = A[0].x, cx2 = B[0].x, cy1 = A[0].y, cy2 = B[0].y;
    for(int i=0; i<N; i++) {
        A[i].x -= cx1, A[i].y -= cy1;
        B[i].x -= cx2, B[i].y -= cy2;
    }
    sort(A + 1, A + N);
    sort(B + 1, B + N);
    for(int i=0; i<N; i++) {
        while(sz(v1) >= 2 && f(v1[sz(v1)-2], v1[sz(v1)-1], A[i]) >= 0) v1.pop_back();
        v1.push_back(A[i]);
        while(sz(v2) >= 2 && f(v2[sz(v2)-2], v2[sz(v2)-1], B[i]) >= 0) v2.pop_back();
        v2.push_back(B[i]);
    }
    int sc1 = 0, sc2 = 0;
    for(int i=0; i<N; i++) {
        A[i].x += cx1, A[i].y += cy1;
        B[i].x += cx2, B[i].y += cy2;
    }
    for(int i=0; i<sz(v1); i++) AC.push_back(v1[i]);
    for(int i=0; i<sz(v2); i++) BC.push_back(v2[i]);
    for(auto &it : AC) it.x += cx1, it.y += cy1;
    for(auto &it : BC) it.x += cx2, it.y += cy2;
    for(int i=0; i<N; i++) {
        if(pr(cx1, cy1) > pr(B[i].x, B[i].y)) continue;
        AC.push_back(B[i]);
    }
    for(int i=0; i<N; i++) {
        if(pr(cx2, cy2) > pr(A[i].x, A[i].y)) continue;
        BC.push_back(A[i]);
    }
    for(auto &it : AC) it.x -= cx1, it.y -= cy1;
    for(int i=0; i<sz(BC); i++) BC[i].x -= cx2, BC[i].y -= cy2;
    sort(all(AC));
    sort(all(BC));
    AC.push_back(AC[0]);
    BC.push_back(BC[0]);
    for(int i=0; i<sz(AC)-1;) {
        int j = i + 1;
        while(AC[j].team == 2) j++;
        for(int k=i+1; k<j; k++) sc1 += (f(AC[i], AC[k], AC[j]) > 0 || (f(AC[i], AC[k], AC[j]) == 0 && c(AC[i], AC[j], AC[k])));
        i = j;
    }
    for(int i=0; i<sz(BC)-1;) {
        int j = i + 1;
        while(BC[j].team == 1) j++;
        for(int k=i+1; k<j; k++) sc2 += (f(BC[i], BC[k], BC[j]) > 0 || (f(BC[i], BC[k], BC[j]) == 0 && c(BC[i], BC[j], BC[k])));
        i = j;
    }
    printf("%d %d\n", sc1, sc2);
}

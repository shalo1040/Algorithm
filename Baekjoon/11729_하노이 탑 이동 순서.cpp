// [11729] 하노이 탑 이동 순서 : https://www.acmicpc.net/problem/11729
#include <cstdio>

//n번 원판을 from에서 to로 옮긴다.
void solve(int n, int from, int to) {
    if(n == 1) {
        printf("%d %d\n", from, to);
        return;
    }
    //n-1개 원판을 from에서 6-from-to로 옮긴다.
    solve(n-1, from, 6-from-to);
    //n번째 원판을 from에서 to로 옮긴다.
    printf("%d %d\n", from, to);
    //6-from-to로 옮겼던 n-1개 원판을 to로 옮긴다.
    solve(n-1, 6-from-to, to);
}
int main() {
    int k;
    scanf("%d", &k);
    printf("%d\n", (1<<k) - 1);     //2^k - 1
    solve(k, 1, 3);     //k번 원판을 목적지에 놓는다.
    return 0;
}
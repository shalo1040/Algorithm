// [14889] 스타트와 링크 : https://www.acmicpc.net/problem/14889
#include <cstdio>

int n, ans = 1234;
int map[21][21];
bool visit[21];

int abs(int x) { return (x < 0) ? -x : x; }
//dfs
void solve(int x = 0, int cnt = 0) {
	//팀원(cnt)이 n/2로 다 구성되었으면 합을 구한다.
    if(cnt == n/2) {
        int result1 = 0, result2 = 0;
        for(int i = 0; i < n; i++) {
            if(visit[i]) {	//팀1
                for(int j = i+1; j < n; j++) {
                    if(visit[j]) result1 += map[i][j] + map[j][i];
                }
            } else {		//팀2
                for(int j = i+1; j < n; j++) {
                    if(!visit[j]) result2 += map[i][j] + map[j][i];
                }
            }
        }
        //최솟값 구한다.
        if(ans > abs(result1 - result2)) ans = abs(result1 - result2);
    }
    //아직 팀이 구성되지 않았으면 dfs
    for(int i = x+1; i < n; i++) {
        visit[i] = true;
        solve(i, cnt+1);
        visit[i] = false;
    }
}
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            scanf("%d", &map[i][j]);
    }
    solve();
    printf("%d", ans);
    return 0;
}
/*
아래는 순열 조합으로 푼 코드이다.

#include <cstdio>
#include <algorithm>
using namespace std;

int n, ans = 1234;
int map[21][21];

void solve() {
	int arr[n+1];	//(인덱스 1부터 시작)
	//팀1
	for(int i = 1; i <= n/2; i++)
		arr[i] = 0;
	//팀2
	for(int i = n/2+1; i <= n; i++)
		arr[i] = 1;
	do {
	    int result1 = 0, result2 = 0;
	    for(int i = 1; i <= n; i++) {
	        if(arr[i] == 0) {
	            for(int j = 1; j <= n; j++) {
	                if(arr[j] == 0)
	                    result1 += map[i][j];
	            }
	        } else {
	            for(int j = 1; j <= n; j++) {
	                if(arr[j] == 1)
	                    result2 += map[i][j];
	            }
	        }
	    }
		ans = min(ans, abs(result1 - result2));
	} while(next_permutation(arr+1, arr + n+1));
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++)
			scanf("%d", &map[i][j]);
	}
	solve();
	printf("%d", ans);
	return 0;
}
*/
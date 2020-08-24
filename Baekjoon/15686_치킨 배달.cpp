// [15686] 치킨 배달 : https://www.acmicpc.net/problem/15686
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct {
	int y, x;
} Pos;
int n, m, ans = 0xfffffff;
vector<Pos> home, chicken;

//절댓값
int abs(int a) { return (a < 0) ? -a : a; }
//완전탐색
void solve() {
	//arr가 1이면 폐점하지 않는 치킨집임을 의미
	//arr의 모든 순열을 탐색
	int arr[chicken.size()];
	memset(arr, 0, sizeof(arr));
	for(int i = 0; i < m; i++) arr[i] = 1;
	do {
		int sum = 0;
		for(int i = 0; i < home.size(); i++) {
			int minVal = 0xfffffff;
			for(int j = 0; j < chicken.size(); j++) {
				if(arr[j] == 0) continue;
				minVal = min(minVal, abs(home[i].y - chicken[j].y) + abs(home[i].x - chicken[j].x));
			}
			sum += minVal;
		}
		ans = min(ans, sum);
		//폐점하지 않는 치킨집의 수와 현재 치킨집의 수가 같다면 바로 리턴
		if(m == chicken.size()) return;
	} while(prev_permutation(arr, arr+chicken.size()));
}
int main() {
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			int input;
			scanf("%d", &input);
			switch(input) {
				case 0: break;
				case 1: home.push_back({i, j}); break;
				case 2: chicken.push_back({i, j}); break;
			}
		}
	}
	solve();
	printf("%d", ans);
	return 0;
}
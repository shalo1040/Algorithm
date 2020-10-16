// [2112] 보호필름 : https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5V1SYKAaUDFAWu
#include <cstdio>
#include <vector>
using namespace std;

int testcase, d, w, k, ans = 2e9;
vector<vector<int>> map;

int min(int a, int b) { return (a < b) ? a : b; }
bool check() {
	for (int i = 0; i < w; i++) {
		bool flag = false;
		int repeat = 1, prev = map[0][i];
		for (int j = 1; j < d; j++) {
			if (map[j][i] == prev) {
				repeat++;
				if (repeat >= k) { flag = true; break; }
			} else {
				prev = map[j][i];
				repeat = 1;
			}
			if (!flag && d - j - 1 + repeat < k) return false;
		}
		if (!flag) return false;
	}
	return true;
}
void solve(int idx, int sum, vector<bool> &isInject) {
	if (sum > k || sum >= ans) return;
	if (check()) { ans = min(ans, sum); return; }
	for (int i = idx; i < d; i++) {
		if (isInject[i]) continue;
		vector<int> save = map[i];
		isInject[i] = true;
		map[i] = vector<int>(w, 0);
		solve(i, sum + 1, isInject);
		map[i] = vector<int>(w, 1);
		solve(i, sum + 1, isInject);
		map[i] = save;
		isInject[i] = false;
	}
}
int main() {
	scanf("%d", &testcase);
	for (int t = 1; t <= testcase; t++) {
		scanf("%d %d %d", &d, &w, &k);
		map = vector<vector<int>>(d, vector<int>(w, 0));
		ans = 2e9;
		for (int i = 0; i < d; i++) {
			for (int j = 0; j < w; j++)
				scanf("%d", &map[i][j]);
		}
		vector<bool> isInject(d, false);
		if (k == 1) ans = 0;
		else solve(0, 0, isInject);
		printf("#%d %d\n", t, ans);
	}
	return 0;
}
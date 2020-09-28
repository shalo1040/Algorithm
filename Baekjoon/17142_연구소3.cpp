// [17142] 연구소 3 : https://www.acmicpc.net/problem/17142
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 2e9;
int n, m, ans = INF, cnt;
vector<vector<int>> map;
vector<pair<int, int>> virus;
vector<int> arr;

int dir[][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

int min(int a, int b) { return (a<b) ? a : b; }
void solve() {
    vector<vector<int>> tmp = map;
	vector<vector<bool>> visit(n, vector<bool>(n,false));
	queue<pair<int, int>> q;
	for(int i = 0; i < virus.size(); i++) {
		if(arr[i]) {
			q.push({virus[i].first, virus[i].second});
			visit[virus[i].first][virus[i].second] = 1;
		}
	}
	int time = 0, space = cnt;
	while(!q.empty()) {
	    if(!space) { ans = min(ans, time); break; }
	    int size = q.size();
	    while(size--) {
    		int y = q.front().first;
    		int x = q.front().second;
    		q.pop();
    		for(int i = 0; i < 4; i++) {
    			int ny = y + dir[i][0];
    			int nx = x + dir[i][1];
    			if(ny<0 || ny>=n || nx<0 || nx>=n) continue;
    			if(visit[ny][nx] || tmp[ny][nx] == 1) continue;
    			if(tmp[ny][nx] == 2 || !tmp[ny][nx]) {
    			    if(!tmp[ny][nx]) space--;
    				q.push({ny, nx});
    				visit[ny][nx] = 1;
    				tmp[ny][nx] = 3;
    			}
    		}
	    }
	    time++;
	}
}
int main() {
	scanf("%d %d", &n, &m);
	map = vector<vector<int>>(n, vector<int>(n,0));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
			if(map[i][j] == 2)
				virus.push_back({i, j});
			if(!map[i][j]) cnt++;
		}
	}
	arr = vector<int>(virus.size(), 0);
	fill(arr.end()-m, arr.end(), 1);	//바이러스 m개 선택
	do {
		solve();
	} while(next_permutation(arr.begin(), arr.end()));
	(ans == INF) ? printf("-1") : printf("%d", ans);
	return 0;
}
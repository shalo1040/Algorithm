// [1005] ACM Craft : https://www.acmicpc.net/problem/1005
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int MAX = 1001;
int T, N, K, W;
int buildings[2][MAX];	// 0행: 건물 짓는 데 걸리는 시간, 1행: 진입차수
vector<vector<int>> map;	//건물들 간 관계 저장

int solve() {
	vector<bool> visit(N+1, false);
	priority_queue<pair<int, int>> q;	// {건물 번호, 걸린 시간}
	for(int i = 1; i <= N; i++) {
		//진입차수 0이면 큐에 삽입
		if(!buildings[1][i]) {
			q.push({-buildings[0][i], i});
			visit[i] = true;
		}
	}
	while(!q.empty()) {
		int time = -q.top().first;
		int build = q.top().second;
		q.pop();
		//목표 건물이면 리턴
		if(build == W) return time;
		//연관된 노드들의 진입차수 -1
		for(int i = 0; i < map[build].size(); i++)
			buildings[1][map[build][i]]--;
		map[build].clear();
		//진입차수 0이면 큐에 삽입
		for(int i = 1; i <= N; i++) {
			if(!visit[i] && !buildings[1][i]) {
				q.push({-(time + buildings[0][i]), i});
				visit[i] = true;
			}
		}
	}
	return -1;
}
int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &N, &K);
		map = vector<vector<int>>(N+1);
		for(int i = 1; i <= N; i++) {
			scanf("%d", &buildings[0][i]);
			buildings[1][i] = 0;
		}
		for(int i = 0; i < K; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			map[x].push_back(y);
			buildings[1][y]++;
		}
		scanf("%d", &W);
		printf("%d\n", solve());
	}
}
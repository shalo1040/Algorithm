// [1504] 특정한 최단 경로 : https://www.acmicpc.net/problem/1504
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#define INF 0xfffffff
using namespace std;

//N: 정점의 개수, E: 간선의 개수
int N, E, v1, v2;
int map[801][801];

//다익스트라 알고리즘
vector<int> solve(int start) {
	vector<int> dist(N+1, INF);
	dist[start] = 0;
	priority_queue<pair<int, int>> pq;
	pq.push({0, start});
	while(!pq.empty()) {
		int distance = -pq.top().first;
		int cur = pq.top().second;
		pq.pop();
		for(int i = 1; i <= N; i++) {
			int nextDist = map[cur][i];
			if(nextDist == 0) continue;
			if(dist[i] > dist[cur] + nextDist) {
				dist[i] = dist[cur] + nextDist;
				pq.push({-dist[i], i});
			}
		}
	}
	return dist;
}
int main() {
	scanf("%d %d", &N, &E);
	while(E--) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		map[a][b] = map[b][a] = c;
	}
	scanf("%d %d", &v1, &v2);
	vector<int> distFromStart = solve(1);
	vector<int> distFromV1 = solve(v1);
	vector<int> distFromV2 = solve(v2);
	/*
	경로1 : 1 -> v1 -> v2 -> N
	경로2 : 1 -> v2 -> v1 -> N
	*/
	long long int ans = min(distFromStart[v1] + distFromV1[v2] + distFromV2[N], distFromStart[v2] + distFromV2[v1] + distFromV1[N]);
	if(ans >= INF) printf("-1");
	else printf("%lld", ans);
	return 0;
}
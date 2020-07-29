// [1238] 파티 : https://www.acmicpc.net/problem/1238
#include <cstdio>
#include <vector>
#include <queue>
#define INF 0xfffffff
using namespace std;

//N: 학생 수, M: 단방향 길의 수, X: 파티 장소
int N, M, X;
//{목적지, 걸리는 시간}
vector<pair<int, int>> vectorToHome[1001];
vector<pair<int, int>> vectorToStart[1001];
//집까지 가는 시간 + 파티 장소로 가는 시간
int totalTime[1001];

//다익스트라 알고리즘
void solve(int start, vector<pair<int, int>> v[1001]) {
	vector<int> dist(N+1, INF);
	dist[start] = 0;
	//{거리, 마을 번호}
	priority_queue<pair<int, int>> pq;
	pq.push({0, start});
	while(!pq.empty()) {
	    int time = -pq.top().first;
	    int cur = pq.top().second;
	    pq.pop();
	    for(int i = 0; i < v[cur].size(); i++) {
	        int next = v[cur][i].first;
	        int nextTime = v[cur][i].second;
	        if(dist[next] > dist[cur] + nextTime) {
	            dist[next] = dist[cur] + nextTime;
	            pq.push({-nextTime, next});
	        }
	    }
	}
	for(int i = 1; i <= N; i++)
	    totalTime[i] += dist[i];
}
int main() {
	scanf("%d %d %d", &N, &M, &X);
	while(M--) {
		int from, to, time;
		scanf("%d %d %d", &from, &to, &time);
		vectorToHome[from].push_back({to, time});
		vectorToStart[to].push_back({from, time});
	}
	//파티 장소 -> 집으로 가는 최단 시간
	solve(X, vectorToHome);
	//집 -> 파티 장소로 가는 최단 시간
	solve(X, vectorToStart);
	int maxTime = 0;
    for(int i = 1; i <= N; i++) {
        if(maxTime < totalTime[i])
            maxTime = totalTime[i];
    }
	printf("%d", maxTime);
	return 0;
}
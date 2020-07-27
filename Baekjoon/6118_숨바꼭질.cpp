// [6118] 숨바꼭질 : https://www.acmicpc.net/problem/6118
#include <cstdio>
#include <vector>
#include <queue>
#define INF 0xfffffff
using namespace std;

//N: 헛간의 개수, M: 길의 개수
int N, M;
vector<int> link[20001];

//다익스트라 알고리즘
void solve() {
	vector<int> dist(N+1, INF);
	dist[1] = 0;
	//{거리, 헛간 번호}
	priority_queue<pair<int, int>> pq;
	pq.push({0, 1});
	while(!pq.empty()) {
		int distance = -pq.top().first;
		int pos = pq.top().second;
		pq.pop();
		for(int i = 0; i < link[pos].size(); i++) {
			int newDist = distance + 1;
			int newPos = link[pos][i];
			if(dist[newPos] > newDist) {
				dist[newPos] = newDist;
				pq.push({-newDist, newPos});
			}
		}
	}
	for(int i = N-1; i >=0; i--) {
	    if(dist[i+1] != INF)
		    pq.push({dist[i+1], i+1});
	}
	int ansNum = pq.top().second;
	int ansDist = pq.top().first;
	int ansCount = 1;
	pq.pop();
	while(!pq.empty()) {
		if(pq.top().first != ansDist)
			break;
		ansCount++;
		ansNum = pq.top().second;
		pq.pop();
	}
	printf("%d %d %d", ansNum, ansDist, ansCount);
}

int main() {
	scanf("%d %d", &N, &M);
	while(M--) {
		int a, b;
		scanf("%d %d", &a, &b);
		link[a].push_back(b);
		link[b].push_back(a);
	}
	solve();
	return 0;
}
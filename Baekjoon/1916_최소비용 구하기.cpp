// [1916] 최소비용 구하기 : https://www.acmicpc.net/problem/1916
#include <cstdio>
#include <vector>
#include <queue>
#define INF 0xfffffff
using namespace std;

//N: 도시의 개수, M: 버스의 개수
int N, M;
vector<pair<int, int>> cost[1001];  //{비용, 노드 번호}

//다익스트라 알고리즘
void solve(int start, int end) {
    //각 노드까지의 비용 배열 dist를 INF로 초기화
	vector<int> dist(N+1, INF);
	//시작 노드에서 시작 노드까지의 비용은 0
	dist[start] = 0;
	//{비용, 노드 번호}를 담을 우선순위 큐 선언
	priority_queue<pair<int, int>> pq;
	pq.push({-dist[start], start});
	while(!pq.empty()) {
		int price = -pq.top().first;
		int pos = pq.top().second;
		pq.pop();
		for(int i = 0; i < cost[pos].size(); i++) {
			int nextPrice = dist[pos] + cost[pos][i].first;
			int nextPos = cost[pos][i].second;
			if(dist[nextPos] > nextPrice) {
				dist[nextPos] = nextPrice;
				pq.push({-nextPrice, nextPos});
			}
		}
	}
	printf("%d", dist[end]);
}

int main() {
	scanf("%d %d", &N, &M);
	while(M--) {
		int from, to, price;
		scanf("%d %d %d", &from, &to, &price);
		cost[from].push_back({price, to});
	}
	int start, end;
	scanf("%d %d", &start, &end);
	solve(start, end);
	return 0;
}
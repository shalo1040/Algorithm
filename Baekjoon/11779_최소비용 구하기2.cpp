// [11779] 최소비용 구하기 2 : https://www.acmicpc.net/problem/11779
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 1010, INF = 987654321;
int city, bus, from, to;
int cost[MAX], route[MAX];
vector<pair<int, int>> map[MAX];
vector<int> trace;

void solve() {
	priority_queue<pair<int, int>> pq;
	pq.push({0, from});
	cost[from] = 0;
	while(!pq.empty()) {
		int price = -pq.top().first;
		int start = pq.top().second;
		pq.pop();
		for(int i = 0; i < map[start].size(); i++) {
		    int next = map[start][i].first;
		    int cos = map[start][i].second;
		    if(cost[next] > price + cos) {
		        cost[next] = price + cos;
		        route[next] = start;
		        pq.push({-cost[next], next});
		    }
		}
	}
	int pos = to;
	while(pos) {
		trace.push_back(pos);
		pos = route[pos];
	}
}
int main() {
	scanf("%d %d", &city, &bus);
	for(int i = 1; i <= city; i++) cost[i] = INF;
	for(int i = 0; i < bus; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		map[a].push_back({b, c});
	}
	scanf("%d %d", &from, &to);
	solve();
	printf("%d\n%d\n", cost[to], trace.size());
	for(int i = trace.size() - 1; i >= 0; i--)
	    printf("%d ", trace[i]);
	return 0;
}
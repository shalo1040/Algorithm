// [9205] 맥주 마시면서 걸어가기 : https://www.acmicpc.net/problem/9205
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

/*
T: 테스트 케이스 개수
N: 편의점 개수
*/
int T, N;
//집, 편의점, 페스티벌 위치 좌표(x, y)
vector<pair<int, int>> pos;

int abs(int a) { return (a > 0) ? a : -a; }

bool bfs() {
	queue<int> q;
	vector<int> visit(N+2, 0);
	int from = 0;
	q.push(from);
	visit[from] = 1;
	while(!q.empty()) {
		from = q.front();
		q.pop();
		for(int to = pos.size()-1; to >= 1; to--) {
			if(visit[to]) continue;
			//거리 = x좌표 차이 + y좌표 차이(문제에서 맨해튼 거리로 정의함)
			int distance = abs(pos[from].first-pos[to].first) + abs(pos[from].second-pos[to].second);
			//50미터마다 맥주 1병씩 마신다.
			//목적지까지 가는 동안 20병 이하로 마실 수 있는 경우만 큐에 넣어 계속 진행
			if(distance <= 20*50) {
				visit[to] = 1;
				q.push(to);
			}
		}
	}
	//목적지에 방문했으면 happy, 아니면 sad
	return (visit[N+1]) ? true : false;
}
int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &N);
		//pos 비우고 좌표 입력
		pos.clear();
		for(int i = 0; i < N+2; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			pos.push_back({x, y});
		}
		if(bfs()) printf("happy\n");
		else printf("sad\n");
	}
	return 0;
}
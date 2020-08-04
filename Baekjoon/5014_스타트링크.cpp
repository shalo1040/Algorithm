// [5014] 스타트링크 : https://www.acmicpc.net/problem/5014
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

/*
F: 가장 높은 층
S: 강호의 위치
G: 목적지
U: 올라가는 층의 수
D: 내려가는 층의 수
ans: 버튼 누른 횟수
*/
int F, S, G, U, D, ans;

//층 이동할 때마다 실행
void putNum(vector<int> &v, queue<int> &qu, int next) {
    v[next] = 1;
    qu.push(next);
    ans++;
}
void bfs() {
	vector<int> visit(F+1, 0);
	queue<int> q;
	q.push(S);
	visit[S] = 1;
	while(!q.empty()) {
		S = q.front();
		q.pop();
		int up = S+U;
		int down = S-D;
		//목적지에 도착하면 빠져 나온다.
		if(S==G) return;
		//목적지보다 아래층에 있으면 위로 올라간다.
		if(S < G) {
			if(up <= F && !visit[up])
			    putNum(visit, q, up);
			//위로 올라갈 수 없으면 내려간다.
			else if(down > 0 && !visit[down])
				putNum(visit, q, down);
		} else {
			//목적지보다 위층에 있으면 아래로 내려간다.
			if(down > 0 && !visit[down])
				putNum(visit, q, down);
			//아래로 내려갈 수 없으면 올라간다.
			else if(up <= F && !visit[up]) 
			    putNum(visit, q, up);
		}
	}
}
int main() {
	scanf("%d %d %d %d %d", &F, &S, &G, &U, &D);
	bfs();
	if(S==G) printf("%d", ans);
	else printf("use the stairs");
	return 0;
}
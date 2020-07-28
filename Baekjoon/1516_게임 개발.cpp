// [1516] 게임 개발 : https://www.acmicpc.net/problem/1516
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

//N: 건물의 수
int N;
//degree: 진입차수
//time: 건물을 짓는데 걸리는 시간
//wait: 건물을 짓기까지 기다리는 시간
int degree[501], time[501], wait[501];
queue<int> q;
vector<int> v[501];

void solve() {
	for(int i = 1; i <= N; i++) {
		if(degree[i] == 0) q.push(i);
	}
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		for(int i = 0; i < v[node].size(); i++) {
			int next = v[node][i];
			wait[next] = max(wait[next], wait[node] + time[node]);
			if(--degree[next] == 0)
				q.push(next);
		}
	}
	for(int i = 1; i <= N; i++)
		printf("%d\n", wait[i] + time[i]);
}
int main() {
	scanf("%d", &N);
	for(int i = 1; i <= N; i++) {
		scanf("%d", &time[i]);
		while(1) {
			int work;
			scanf("%d", &work);
			if(work==-1) break;
			v[work].push_back(i);
			degree[i]++;
		}
	}
	solve();
	return 0;
}
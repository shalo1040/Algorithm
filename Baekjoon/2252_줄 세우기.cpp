// [2252] 줄 세우기 : https://www.acmicpc.net/problem/2252
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

const int MAX = 32001;

//N: 학생 수, M: 키 비교 횟수
int N, M;
int student[MAX], count[MAX];
vector<int> v[MAX];
queue<int> q;

void solve() {
	//진입차수가 0인 학생을 큐에 넣음
	for(int i = 1; i <= N; i++) { if(!count[i]) q.push(i); }
	//큐가 비어있지 않을 동안 넣었던 학생 번호를 꺼내고
	//뒤에 올 수 있는 학생들의 진입차수를 1만큼 감소
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		printf("%d ", x);
		for(int i = 0; i < v[x].size(); i++) {
			int next = v[x][i];
			if(!--count[next]) q.push(next);
		}
	}
}

int main() {
	scanf("%d %d", &N, &M);
	while(M--) {
		int first, second;
		scanf("%d %d", &first, &second);
		count[second]++;
		v[first].push_back(second);
	}
	solve();
	return 0;
}
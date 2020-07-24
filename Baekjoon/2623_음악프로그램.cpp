// [2623] 음악프로그램 : https://www.acmicpc.net/problem/2623
#include <cstdio>
#include <queue>
using namespace std;

const int MAX = 1001;

//N: 가수, M: PD
int N, M;
int count[MAX];
vector<int> v[MAX];
queue<int> q;
queue<int> ans;

//선행되어야할 가수가 없으면 큐에 push
void putSinger() {
	for(int i = 1; i <= N; i++) {
		if(count[i]==0){
			q.push(i);
			count[i]--;
		}
	}
}

void solve() {
	for(int i = 0; i < N; i++) {
		putSinger();
		//N개를 모두 정렬하기 전에 큐가 빈다면 위상정렬 불가
		if(q.empty()) {
			printf("0");
			return;
		}
		//큐의 첫 번째 원소를 제거하고 연결된 노드의 진입차수 -1
		int x = q.front();
		q.pop();
		ans.push(x);
		for(int i = 0; i < v[x].size(); i++) 
			count[v[x][i]]--;
	}
	//정답 출력
	int y = ans.size();
	for(int i = 0; i < y; i++) {
		printf("%d\n", ans.front());
		ans.pop();
	}
}

int main() {
	scanf("%d %d", &N, &M);
	for(int i = 0; i < M; i++) {
		int num = 0, prev = 0;
		scanf("%d", &num);
		for(int j = 0; j < num; j++) {
			int singer = 0;
			scanf("%d", &singer);
			//앞에 와야할 가수가 있음을 나타냄
			if(j!=0) {
				v[prev].push_back(singer);
				count[singer]++;
			}
			prev = singer;
		}
	}
	solve();
	return 0;
}
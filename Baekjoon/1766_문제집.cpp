// [1766] 문제집 : https://www.acmicpc.net/problem/1766
#include <cstdio>
#include <vector>
#include <queue>
#define MAX 32001
using namespace std;

//N: 문제의 수, M: 문제에 대한 정보의 개수
int N, M;
int count[MAX];
//선행되어야할 문제 관계 저장
vector<int> v[MAX];
//{문제 번호}를 오름차순으로 저장
priority_queue<int> pq;

void solve() {
    //진입차수가 0이면 큐에 저장
	for(int i = 1; i < N+1; i++) {
		if(count[i] == 0) pq.push(-i);
	}
	while(!pq.empty()) {
		int num = -pq.top();
		pq.pop();
		//풀어야할 문제 순서대로 출력
		printf("%d ", num);
		//다음에 풀어야할 문제들의 진입차수 -1
		//진입차수가 0이면 큐에 저장
		for(int i = 0; i < v[num].size(); i++) {
		    if(--count[v[num][i]] == 0)
		        pq.push(-v[num][i]);
		}
	}
}

int main() {
	scanf("%d %d", &N, &M);
	while(M--) {
		int first, second;
		scanf("%d %d", &first, &second);
		v[first].push_back(second);
		count[second]++;
	}
	solve();
	return 0;
}
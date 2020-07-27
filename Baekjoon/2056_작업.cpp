// [2056] 작업 : https://www.acmicpc.net/problem/2056
#include <cstdio>
#include <vector>
#define MAX 10001
using namespace std;

//N: 수행해야 할 작업
int N;
int t[MAX];		//작업 수행 시간
vector<int> v[MAX];		//완료되어야할 작업 저장

void solve() {
	//처음부터 각 작업을 완료하기 위한 시간
	vector<int> time(N+1, MAX);
	int ans = 0;
	for(int i = 1; i <= N; i++) {
		int maxTime = 0;
		for(int j = 0; j < v[i].size(); j++) {
			if(maxTime < time[v[i][j]])
				maxTime = time[v[i][j]];
		}
		//선행되어야할 작업 중 가장 오래 걸리는 작업의 시간 + i번째 작업 수행 시간
		time[i] = maxTime + t[i];
		//가장 긴 작업 시간 저장
		if(ans < time[i]) ans = time[i];
	}
	printf("%d", ans);
}
int main() {
	scanf("%d", &N);
	for(int i = 1; i <= N; i++) {
		int works;
		scanf("%d %d", &t[i], &works);
		while(works--) {
			int work;
			scanf("%d", &work);
			v[i].push_back(work);
		}
	}
	solve();
	return 0;
}
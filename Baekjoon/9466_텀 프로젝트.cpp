// [9466] 텀 프로젝트 : https://www.acmicpc.net/problem/9466
#include <cstdio>
#include <set>
#include <vector>
using namespace std;

int T, n;
int student[100001];

int solve() {
	int cnt = 0;
	vector<int> arr;
	bool visit[n+1];
	for(bool &v : visit) v = false;
	for(int i = 1; i <= n; i++) {
		if(visit[i]) continue;
		set<int> s;
		arr.push_back(i);
		visit[i] = true;
		int start = i;
		int pointer = 0;
		bool flag = false;
		while(1) {
			int cur = arr[pointer];
			//student[cur]이 시작점과 같거나 이동경로(set) 중에 존재하면 flag = true
			if(student[cur] == start || (s.find(student[cur]) != s.end())) { start = student[cur]; flag = true; break; }
			if(visit[student[cur]]) break;
			s.insert(student[cur]);
			visit[student[cur]] = true;
			arr.push_back(student[cur]);
			pointer++;
		}
		if(flag) {
		    for(int i = pointer; i >= 0; i--) {
		        cnt++;
		        if(arr[i] == start) break;
		    }
		}
		arr.clear();
	}
	return n - cnt;
}
int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		//인덱스 1부터 n까지 학생 번호 저장
		for(int i = 1; i <= n; i++)
			scanf("%d", &student[i]);
		printf("%d\n", solve());
	}
	return 0;
}
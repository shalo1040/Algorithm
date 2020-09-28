// [17140] 이차원 배열과 연산 : https://www.acmicpc.net/problem/17140
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;

int r, c, k, row = 3, col = 3, ans;
vector<vector<int>> map(101, vector<int>(101));

int max(int a, int b) { return (a<b) ? b : a; }
void R() {
	for(int i = 1; i <= row; i++) {
		priority_queue<pair<int, int>> pq;
		unordered_map<int, int> hash;
		for(int j = 1; j <= col; j++) {
			if(!map[i][j]) continue;
			hash[map[i][j]]++;	//각 숫자의 개수를 센다
		}
		for(auto val : hash)
			pq.push({-val.second, -val.first});     //{등장 횟수, 수}
		int idx = 1;
		while(!pq.empty()) {
			if(idx > 100) break;	//100개 넘어가면 버린다.
			int cnt = -pq.top().first;
			int num = -pq.top().second;
			pq.pop();
			map[i][idx] = num;		//수 오름차순
			map[i][idx+1] = cnt;	//등장 횟수 오름차순
			idx += 2;
		}
		col = max(col, idx-1);	//최대 열의 길이 갱신
		if(idx <= 100) fill(map[i].begin()+idx, map[i].end(), 0);	//이후 공간은 0으로 초기화
	}
}
void C() {
	for(int i = 1; i <= col; i++) {
	    priority_queue<pair<int, int>> pq;
	    unordered_map<int, int> hash;
	    for(int j = 1; j <= row; j++) {
	        if(!map[j][i]) continue;
	        hash[map[j][i]]++;
	    }
	    for(auto val : hash)
	        pq.push({-val.second, -val.first});
	    int idx = 1;
	    while(!pq.empty()) {
	        if(idx > 100) break;
	        int cnt = -pq.top().first;
	        int num = -pq.top().second;
	        pq.pop();
	        map[idx][i] = num;
	        map[idx+1][i] = cnt;
	        idx += 2;
	    }
	    row = max(row, idx-1);
	    if(idx <= 100) {
	        for(int j = idx; j <= 100; j++)
	            map[j][i] = 0;
	    }
	}
}
void solve() {
	while(map[r][c] != k) {
		if(ans > 100) { ans = -1; break; }
		(row >= col) ? R() : C();
		ans++;
	}
}
int main() {
	scanf("%d %d %d", &r, &c, &k);
	for(int i = 1; i <= row; i++) {
		for(int j = 1; j <= col; j++)
			scanf("%d", &map[i][j]);
	}
	solve();
	printf("%d", ans);
	return 0;
}
//[5658] 보물상자 비밀번호 : https://swexpertacademy.com/main/code/problem/problemDetail.do
#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

int T, N, K;

int solve(vector<int> v) {
	priority_queue<int> pq;
	for(int l = 0; l < N/4; l++) {
    	for(int i = l; i < l + N; i += N/4) {
    		int result = 0;
    		//j 범위가 벡터 범위를 넘어가면 다시 0번 인덱스부터
    		for(int j = i; j < i + N/4; j++)
    		    result += (j>=N) ? v[j-N] * pow(16, (i+N/4)-j-1) : v[j] * pow(16, (i+N/4)-j-1);
    		pq.push(result);
    	}	   
	}
	int cnt = 0, num, prev = -1;
	while(!pq.empty()) {
		num = pq.top();
		pq.pop();
		if(num != prev) {
			cnt++;
			prev = num;
		}
		//K번째로 큰 수 찾으면 리턴
		if(cnt == K) break;
	}
	return num;
}
int main() {
	scanf("%d", &T);
	for(int t = 1; t <= T; t++) {
		scanf("%d %d", &N, &K);
		vector<int> v(0, N);
		for(int i = 0; i < N; i++) {
		    int num;
		    //1자리씩 16진수로 입력 받는다.
		    scanf("%1x", &num);
		    v.push_back(num);
		}
		int ans = solve(v);
		printf("#%d %d\n", t, ans);
	}
	return 0;
}
// [1655] 가운데를 말해요 : https://www.acmicpc.net/problem/1655
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

int n;
priority_queue<int> pq_small, pq_big;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int next;
		scanf("%d", &next);
		//pq_small.top()보다 작은 수는 pq_small, 큰 수는 pq_big에 push
		if(i == 1 || next < pq_small.top())
		    pq_small.push(next);
		else
		    pq_big.push(-next);
		//pq_small 또는 pq_big의 크기가 더 크다면 push, pop으로 조절
		if(pq_small.size() > pq_big.size() + 1) {
		    pq_big.push(-pq_small.top());
		    pq_small.pop();
		} else if(pq_big.size() > pq_small.size()) {
		    pq_small.push(-pq_big.top());
		    pq_big.pop();
		}
		//두 큐의 크기가 같으면 각 큐의 top()에서 작은 수 출력, 크기가 다르면 작은 큐의 top() 출력
		if(pq_small.size() == pq_big.size())
		    printf("%d\n", min(pq_small.top(), -pq_big.top()));
		else 
		    printf("%d\n", pq_small.top());
	}
	return 0;
}
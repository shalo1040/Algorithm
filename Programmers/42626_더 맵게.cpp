// [42626] 더 맵게 : https://programmers.co.kr/learn/courses/30/lessons/42626
#include <string>
#include <vector>
#include <queue>
using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    priority_queue<int> pq;
    for(int i = 0; i < scoville.size(); i++)
        pq.push(-scoville[i]);
    while(1) {
        //큐가 빌 때까지 K이상으로 만들지 못했으면 -1 리턴
        if(pq.size() == 0) return -1;
        int first = -pq.top(); pq.pop();
        if(first >= K) break;
        if(pq.size() != 0) {
            int second = -pq.top(); pq.pop();
            int newVal = first + second*2;
            pq.push(-newVal);
            answer++;
        }
    }
    return answer;
}
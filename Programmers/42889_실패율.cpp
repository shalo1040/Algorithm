// [42889] 실패율 : https://programmers.co.kr/learn/courses/30/lessons/42889/
#include <string>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    priority_queue<pair<double, int>> pq;
    int dp[N+1];
    memset(dp, 0, sizeof(dp));
    for(int i = 0; i < stages.size(); i++) {
        dp[stages[i]]++;    //각 스테이지에 몇 명이 있는지 저장
    }
    int total = stages.size();
    for(int i = 1; i <= N; i++) {
        if(dp[i] == 0) pq.push({0, -i});
        else pq.push({(double)dp[i]/total, -i});
        total -= dp[i];     //dp[i]명 만큼 다음 스테이지에 가지 못함
    }
    while(!pq.empty()) {
        int next = -pq.top().second;
        pq.pop();
        answer.push_back(next);
    }
    return answer;
}
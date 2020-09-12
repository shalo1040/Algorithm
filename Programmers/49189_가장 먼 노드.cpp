// [49189] 가장 먼 노드 : https://programmers.co.kr/learn/courses/30/lessons/49189
#include <string>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    //그래프를 그린다
    bool map[n+1][n+1];
    memset(map, false, sizeof(map));
    for(int i = 0; i < edge.size(); i++) {
        map[edge[i][0]][edge[i][1]] = true;
        map[edge[i][1]][edge[i][0]] = true;
    }
    priority_queue<int> pq;
    queue<pair<int, int>> q;
    bool visit[n+1];
    memset(visit, false, sizeof(visit));
    q.push({1, 0});
    visit[1] = true;
    while(!q.empty()) {
        int node = q.front().first;
        int cnt = q.front().second;
        q.pop();
        bool flag = true;
        for(int i = 1; i <= n; i++) {
            if(map[node][i] && !visit[i]) {
                q.push({i, cnt+1});
                visit[i] = true;
                flag = false;
            }
        }
        //연결되는 노드가 없다면 cnt 정보를 우선순위 큐에 넣는다
        if(flag) pq.push(cnt);
    }
    //pq는 cnt가 큰 순서대로 정렬되어 있고 cnt가 top인 것의 개수를 센다
    int max = pq.top();
    pq.pop();
    answer++;
    while(!pq.empty()) {
        if(pq.top() == max) {
            pq.pop();
            answer++;
        } else break;
    }
    return answer;
}
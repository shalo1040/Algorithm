// [49191] 순위 : https://programmers.co.kr/learn/courses/30/lessons/49191
#include <string>
#include <vector>
using namespace std;

bool map[101][101];

//플로이드 와샬
void solve(int n) {
    //k: 거쳐가는 지점, i: 출발 지점, j: 도착 지점
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(map[i][k] && map[k][j])
                    map[i][j] = true;
            }
        }
    }
}
int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    for(int i = 0; i < results.size(); i++) {
        int a = results[i][0];
        int b = results[i][1];
        map[a][b] = true;
    }
    solve(n);
    for(int i = 1; i <= n; i++) {
        int cnt = 0;
        for(int j = 1; j <= n; j++) {
            if(map[i][j] || map[j][i]) cnt++;
        }
        if(cnt == n-1) answer++;
    }
    return answer;
}
// [4014] 활주로 건설 : https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeW7FakkUDFAVH
#include <cstdio>
#include <vector>
using namespace std;

int T, N, X;

int abs(int x) { return (x<0) ? -x : x; }
int solve(vector<vector<int>> &map) {
    int prev, cnt, ans = 0;
    //가로로 놓을 수 있는 활주로 있는지 검사
    for(int i = 0; i < N; i++) {
        prev = map[i][0]; cnt = 1;
        for(int j = 1; j < N; j++) {
            //이전 높이와 현재 높이 차이가 1보다 크면 경사로를 놓을 수 없으므로 break
            if(abs(map[i][j] - prev) > 1) break;
            //이전 높이와 같으면 cnt+1
            if(map[i][j] == prev) cnt++; 
            //이전 높이와 현재 높이 차이가 1이고
            //현재 높이가 이전 높이보다 클 때
            else if(map[i][j] > prev) {
                //cnt가 X 이상이면 경사로를 놓고 아니라면 break
                if(cnt >= X) { cnt = 1; prev = map[i][j]; }
                else break;
            } else {	//현재 높이가 이전 높이보다 낮을 때
                cnt = 1; prev = map[i][j];
                //j번째부터 시작해 X만큼 경사로를 놓을 때 map의 범위를 넘어가면 break
                if(j+X-1 >= N) break;
                //X만큼 경사로를 놓을 수 있으면 isPossible == true
                bool isPossible = true;
                for(int k = 1; k <= X-1; k++) {
                    if(map[i][j+k] != prev) { isPossible = false; break; }
                }
                if(!isPossible) break;
                j = j+X-1;
                cnt = 0;
            }
            //N-1번째 인덱스까지 break 없이 진행했으면 ans+1
            if(j == N-1) ans++;
        }
    }
    //세로로 놓을 수 있는 활주로 있는지 검사
    for(int i = 0; i < N; i++) {
        prev = map[0][i]; cnt = 1;
        for(int j = 1; j < N; j++) {
            //이전 높이와 현재 높이 차이가 1보다 크면 경사로를 놓을 수 없으므로 break
            if(abs(map[j][i] - prev) > 1) break;
            //이전 높이와 같으면 cnt+1
            if(map[j][i] == prev) cnt++; 
            //이전 높이와 현재 높이 차이가 1이고
            //현재 높이가 이전 높이보다 클 때
            else if(map[j][i] > prev) {
                //cnt가 X 이상이면 경사로를 놓고 아니라면 break
                if(cnt >= X) { cnt = 1; prev = map[j][i]; }
                else break;
            } else {	//현재 높이가 이전 높이보다 낮을 때
                cnt = 1; prev = map[j][i];
                //j번째부터 시작해 X만큼 경사로를 놓을 때 map의 범위를 넘어가면 break
                if(j+X-1 >= N) break;
                //X만큼 경사로를 놓을 수 있으면 isPossible == true
                bool isPossible = true;
                for(int k = 1; k <= X-1; k++) {
                    if(map[j+k][i] != prev) { isPossible = false; break; }
                }
                if(!isPossible) break;
                j = j+X-1;
                cnt = 0;
            }
            //N-1번째 인덱스까지 break 없이 진행했으면 ans+1
            if(j == N-1) ans++;
        }
    }
    return ans;		//활주로 개수
}
int main() {
    scanf("%d", &T);
    for(int testcase = 1; testcase <= T; testcase++) {
        scanf("%d %d", &N, &X);
        vector<vector<int>> map;
        for(int i = 0; i < N; i++) {
            vector<int> v;
            for(int j = 0; j < N; j++) {
                int height;
                scanf("%d", &height);
                v.push_back(height);
            }
            map.push_back(v);
        }
        printf("#%d %d\n", testcase, solve(map));
    }
    return 0;
}
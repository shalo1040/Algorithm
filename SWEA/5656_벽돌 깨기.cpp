// [5656] 벽돌 깨기 : https://swexpertacademy.com/main/solvingProblem/solvingProblem.do
#include <cstdio>
#include <vector>
using namespace std;

int T, n, w, h;
vector<vector<int>> map;
int dir[][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

int max(int a, int b) { return (a < b) ? b : a; }
//연쇄적으로 벽돌을 깬다
int explode(int y, int x, vector<vector<int>> &tmp) {
    int count = 1;
    if(tmp[y][x] == 1) {  tmp[y][x] = 0; return count; }
    int size = tmp[y][x] - 1;
     tmp[y][x] = 0;
    for(int d = 0; d < 4; d++) {
    	for(int i = 1; i <= size; i++) {
			int ny = y+(dir[d][0] * i);
            int nx = x+(dir[d][1] * i);
            if(ny<0 || ny>=h || nx<0 || nx>=w || !tmp[ny][nx]) continue;
            count += explode(ny, nx, tmp);
        }
    }
    return count;
}
//중력에 의해 내려오는 벽돌
void reset(vector<vector<int>> &tmp) {
    for(int i = 0; i < w; i++) {
        for(int j = h-1, top = h-1; j >= 0; j--) {
            if(tmp[j][i]) {
                if(j != top) {
                    tmp[top][i] = tmp[j][i];
                    tmp[j][i] = 0;
                }
                top--;
            }
        }
    }
}
//모든 경우의 수 탐색
int solve(int start, int depth, const vector<vector<int>> &graph) {
    if(depth > n) return 0;
    vector<vector<int>> tmp;
    for(int i = 0; i < h; i++)
        tmp.push_back(graph[i]);
    int maximum = 0;
    for(int i = 0; i < h; i++) {
        if(tmp[i][start]) {
           	int cnt = explode(i, start, tmp);
            reset(tmp);
            for(int newStart = 0; newStart < w; newStart++)
            	maximum = max(maximum, solve(newStart, depth+1, tmp) + cnt);
            return maximum;
        }
    }
    return 0;
}
int main() {
    scanf("%d", &T);
    for(int testcase = 1; testcase <= T; ++testcase) {
        int sum = 0;
        map.clear();
        scanf("%d %d %d", &n, &w, &h);
        for(int i = 0; i < h; i++) {
            vector<int> v;
            for(int j = 0; j < w; j++) {
                int num;
                scanf("%d", &num);
                v.push_back(num);
                if(num) sum++;
            }
            map.push_back(v);
        }
        //전체 벽돌(sum)에서 최대로 깬 수(ans)를 뺀다
        int ans = 0;
        for(int i = 0; i < w; i++)
       		ans = max(ans, solve(i, 1, map));
        printf("#%d %d\n", testcase, sum - ans);
    }
    return 0;
}
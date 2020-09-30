// [17822] 원판 돌리기 : https://www.acmicpc.net/problem/17822
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, m, t, total, cnt;
vector<vector<int>> map;

int dir[][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

void clock(int x, int k) {
    vector<int> tmp(m+1, 0);
    int start = m-k+1;
    for(int i = 1; i <= m; i++) {
        int k = (start%m == 0) ? m : start%m;
        tmp[i] = map[x][k];
        start++;
    }
    for(int i = 1; i <= m; i++)
        map[x][i] = tmp[i];
}
void nonClock(int x, int k) {
    vector<int> tmp(m+1, 0);
    int start = k;
    for(int i = 1; i <= m; i++) {
        tmp[i] = map[x][start%m + 1];
        start++;
    }
    for(int i = 1; i <= m; i++)
        map[x][i] = tmp[i];
}
/*
처음 벡터 회전을 아래와 같이 구현했는데,
코드 가독성 및 시간 복잡도 면에서 위의 방법이 더 효율적임을 알았다.

//x번 원반을 시계 방향으로 k칸 회전
void clock(int x, int k) {
	vector<int> &cur = map[x];
	vector<int> first, tmp;
	for(auto it = cur.end()-k-1; it != cur.end()-1; ++it)
	    tmp.push_back(*it);
	for(auto it = cur.begin()+1; it < cur.end()-k-1; ++it)
	    tmp.push_back(*it);
	for(int i = 1; i <= m; i++)
	    cur[i] = tmp[i-1];
}
//x번 원반을 반시계 방향으로 k칸 회전
void nonClock(int x, int k) {
	vector<int> &cur = map[x];
	vector<int> tmp;
	for(auto it = cur.begin()+k+1; it != cur.end()-1; ++it)
		tmp.push_back(*it);
	for(auto it = cur.begin()+1; it < cur.begin()+k+1; ++it)
		tmp.push_back(*it);
	for(int i = 1; i <= m; i++)
	    cur[i] = tmp[i-1];
}
*/
//bfs
bool solve() {
    bool flag = false;
    vector<vector<bool>> visit(n+1, vector<bool>(m+2, false));
    queue<pair<int, int>> q;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(visit[i][j] || !map[i][j]) continue;
            int num = map[i][j];
            q.push({i, j});
            while(!q.empty()) {
                int y = q.front().first;
                int x = q.front().second;
                q.pop();
                for(int k = 0; k < 4; k++) {
                    int ny = y + dir[k][0];
                    int nx = x + dir[k][1];
                    if(k==1 && nx == 0) nx = m;
                    else if(k==0 && nx == m+1) nx = 1;
                    if(ny<1 || ny>n || nx<1 || nx>m || !map[ny][nx] || visit[ny][nx]) continue;
                    if(map[ny][nx] == num) {
                        visit[ny][nx] = true;
                        q.push({ny, nx});
                        total -= map[ny][nx];
                        cnt--;
                        map[ny][nx] = 0;
                        flag = true;
                    }
                }
            }
        }
    }
    return flag;
}
int main() {
	scanf("%d %d %d", &n, &m, &t);
	map = vector<vector<int>>(n+1, vector<int>(m+1, 0));
	cnt = n*m;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			scanf("%d", &map[i][j]);
			total += map[i][j];
		}
	}
	while(t--) {
		int x, d, k;
		scanf("%d %d %d", &x, &d, &k);
		//1. x의 배수인 원판을 d방향으로 k칸 회전
		for(int i = x; i <= n; i += x)
			(d) ? nonClock(i, k) : clock(i, k);
		//2. 인접하면서 수가 같은 것을 모두 찾는다.
		//2-1. 2를 만족하는 수가 있으면 지운다(0)
		bool flag = solve();
		//2-2. 2를 만족하는 수가 없으면 평균을 구해 그 수보다 크면 +1, 작으면 -1을 한다
		if(!flag) {
		    if(!cnt) break;
			float avg = (float)total / cnt;	//평균
			for(int i = 1; i <= n; i++) {
				for(int j = 1; j <= m; j++) {
					if(!map[i][j] || map[i][j] == avg) continue;
					if(map[i][j] > avg) {
					    map[i][j]--;
					    total--;
					} else {
					    map[i][j]++;
					    total++;
					}
				}
			}
		}
	}
	printf("%d", total);
	return 0;
}
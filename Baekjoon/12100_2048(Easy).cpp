// [12100] 2048(Easy) : https://www.acmicpc.net/problem/12100
#include <cstdio>
#include <vector>
using namespace std;

//n: 게임 보드 크기
int n, ans;
vector<vector<int>> graph;

//{y, x} 이 행렬을 사용하지 않지만 방향을 나타냄
int dir[][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

//가장 큰 블록 갱신
void findMaxValue(vector<vector<int>> &map) {
	int max = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(map[i][j] > max) max = map[i][j];
		}
	}
	ans = (ans > max) ? ans : max;
}
//이동하는 방향(dir[4][2] 참고)에 따른 보드 블록 값의 변화
void moveBlock(vector<vector<int>> &map, int d) {
	switch(d) {
		//{0,1}
		case 0:
			//각 행마다 숫자를 오른쪽으로 이동시킨다.
			for(int i = 0; i < n; i++) {
				//n번째 자리에서 수를 합한 적이 있는지 여부를 체크
				int visit[n] = {0,};
				//i행 j열 원소와 합치거나 원소가 위치할 수 있는 자리 번호
				//오른쪽부터 체크
				int idx = n-1;
				for(int j = idx-1; j >= 0; j--) {
				    if(map[i][j] == 0) continue;
				    //다음에 올 블록과 idx가 가리키고 있는 블록의 값이 같고
				    //idx 위치의 블록은 아직 다른 블록과 합한 적이 없다면 숫자를 합하고 visit 체크
				    if(map[i][j] == map[i][idx] && !visit[idx]) {
				        map[i][idx] += map[i][j];
				        map[i][j] = 0;	//기존의 위치는 빈 공간으로 바꿈
				        visit[idx] = 1;
				        idx--;		//다음 블록이 올 수 있는 위치
				    } else if(map[i][idx] == 0) {	//idx 자리가 0이면 다음 번에 같은 값의 블록이 올 수 있으니 idx 갱신하지 않음
				        map[i][idx] = map[i][j];
				        map[i][j] = 0;
				    } else {	//idx 자리에 블록을 위치시킬 수 없다면 idx-1
				        idx--;
				        if(j != idx) {	//idx와 j가 다르면 값 갱신
				            map[i][idx] = map[i][j];
				            map[i][j] = 0;
				        }
				    }
				}
			}
			break;
		//{0,-1}
		case 1:
			for(int i = 0; i < n; i++) {
				int visit[n] = {0,};
				int idx = 0;
				for(int j = idx+1; j < n; j++) {
				    if(map[i][j] == 0) continue;
				    if(map[i][j] == map[i][idx] && !visit[idx]) {
				        map[i][idx] += map[i][j];
				        map[i][j] = 0;
				        visit[idx] = 1;
				        idx++;
				    } else if(map[i][idx] == 0) {
				        map[i][idx] = map[i][j];
				        map[i][j] = 0;
				    } else {
				        idx++;
				        if(j != idx) {
				            map[i][idx] = map[i][j];
				            map[i][j] = 0;
				        }
				    }
				}
			}
			break;
		//{1,0}
		case 2:
			for(int i = 0; i < n; i++) {
				int visit[n] = {0,};
				int idx = n-1;
				for(int j = idx-1; j >= 0; j--) {
				    if(map[j][i] == 0) continue;
					if(map[j][i] == map[idx][i] && !visit[idx]) {
						map[idx][i] += map[j][i];
						map[j][i] = 0;
						visit[idx] = 1;
						idx--;
					} else if(map[idx][i] == 0) {
					    map[idx][i] = map[j][i];
					    map[j][i] = 0;
					} else {
					    idx--;
					    if(j != idx) {
    					    map[idx][i] = map[j][i];
    					    map[j][i] = 0;
					    }
					}
				}
			}
			break;
		//{-1,0}
		case 3:
		    for(int i = 0; i < n; i++) {
				int visit[n] = {0,};
				int idx = 0;
				for(int j = idx+1; j < n; j++) {
					if(map[j][i] == 0) continue;
					if(map[j][i] == map[idx][i] && !visit[idx]) {
						map[idx][i] += map[j][i];
						map[j][i] = 0;
						visit[idx] = 1;
						idx++;
					} else if(map[idx][i] == 0) {
					    map[idx][i] = map[j][i];
					    map[j][i] = 0;
					} else {
					    idx++;
					    if(j != idx) {
    					    map[idx][i] = map[j][i];
    					    map[j][i] = 0;
					    }
					}
				}
			}
			break;
	}
}
//dfs
void solve(vector<vector<int>> &map, int cnt) {
	if(cnt == 5) { findMaxValue(map); return; }
	for(int i = 0; i < 4; i++) {
		vector<vector<int>> tmp;
		tmp = map;
		moveBlock(tmp, i);
		solve(tmp, cnt+1);
	}
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
	    vector<int> arr;
		for(int j = 0; j < n; j++) {
		    int input;
		    scanf("%d", &input);
		    arr.push_back(input);
		}
	    graph.push_back(arr);
	}
	solve(graph, 0);
	printf("%d", ans);
	return 0;
}

/*
위 코드의 moveBlock()에서 중복되는 코드가 많아 별도의 함수 move()를 만들었다.
위의 코드는 코드를 작성하면서 더 직관적이었지만 불필요하게 코드가 길었고,
아래 코드는 코드가 더 짧고 간결해보이지만 시간 복잡도 면에서 효율성이 2배 떨어진다.

void move(vector<vector<int>> &map, int visit[], int i, int j, int &idx, int d) {
    if(map[i][j] == 0) return;
	if(map[i][j] == ((d<2) ? map[i][idx] : map[idx][j]) && !visit[idx]) {
		(d<2) ? map[i][idx] += map[i][j] : map[idx][j] += map[i][j];
		map[i][j] = 0;
		visit[idx] = 1;
		(d%2==0) ? idx-- : idx++;
	} else if((d<2) ? map[i][idx] == 0 : map[idx][j] == 0) {
		(d<2) ? map[i][idx] = map[i][j] : map[idx][j] = map[i][j];
		map[i][j] = 0;
	} else {
		(d%2==0) ? idx-- : idx++;
		if((d<2) ? j != idx : i != idx) {
		    (d<2) ? map[i][idx] = map[i][j] : map[idx][j] = map[i][j];
			map[i][j] = 0;
		}
	}
}
void moveBlock(vector<vector<int>> &map, int d) {
	switch(d) {
		case 0:
			for(int i = 0; i < n; i++) {
				int visit[n] = {0,};
				int idx = n-1;
				for(int j = idx-1; j >= 0; j--)
				    move(map, visit, i, j, idx, d);
			}
			break;
		case 1:
			for(int i = 0; i < n; i++) {
				int visit[n] = {0,};
				int idx = 0;
				for(int j = idx+1; j < n; j++)
				    move(map, visit, i, j, idx, d);
			}
			break;
		case 2:
			for(int i = 0; i < n; i++) {
				int visit[n] = {0,};
				int idx = n-1;
				for(int j = idx-1; j >= 0; j--)
				    move(map, visit, j, i, idx, d);
			}
			break;
		case 3:
		    for(int i = 0; i < n; i++) {
				int visit[n] = {0,};
				int idx = 0;
				for(int j = idx+1; j < n; j++)
				    move(map, visit, j, i, idx, d);
			}
			break;
	}
}
*/
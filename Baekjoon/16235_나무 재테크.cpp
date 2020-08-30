// [16235] 나무 재테크 : https://www.acmicpc.net/problem/16235
#include <cstdio>
#include <deque>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 11;

int n, m, k, ans;
//{나이} 오름차순
deque<int> trees[MAX][MAX];
int nutrition[MAX][MAX], addNutrition[MAX][MAX];
//{{y,x} 나이}
queue<pair<pair<int, int>, int>> deadTrees;

void spring() {
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
		    if(k==0) sort(trees[i][j].begin(), trees[i][j].end());
			int size = trees[i][j].size();
			for(int h = 0; h < size; h++) {
				int age = trees[i][j][h];
				//양분이 나무의 나이보다 많거나 같으면 양분을 먹고 나이 1 증가
				if(nutrition[i][j] >= age) {
					nutrition[i][j] -= age;
					trees[i][j][h] = ++age;
				} 
				//양분이 부족하면 나무는 죽는다.
				else {
					while(trees[i][j].size() > h) {
					    age = trees[i][j].back();
					    trees[i][j].pop_back();
					    deadTrees.push({{i, j}, age});
					    ans--;
					}
					break;
				}
			}
		}
	}
}
void summer() {
	while(!deadTrees.empty()) {
		int y = deadTrees.front().first.first;
		int x = deadTrees.front().first.second;
		int age = deadTrees.front().second;
		deadTrees.pop();
		nutrition[y][x] += age/2;
	}
}
void fall() {
	int dir[][2] = { {0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {1,-1}, {-1,1}, {-1,-1} };
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			int size = trees[i][j].size();
			for(int h = 0; h < size; h++) {
				int age = trees[i][j][h];
				//나무의 나이가 5의 배수일 때 인접한 칸에 나이가 1인 나무가 생긴다.
				if(age % 5 == 0) {
					for(int l = 0; l < 8; l++) {
						int y = i + dir[l][0];
						int x = j + dir[l][1];
						if(y<=0 || y>n || x<=0 || x>n) continue;
						trees[y][x].push_front(1);
						ans++;
					}
				}
			}
		}
	}
}
void winter() {
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++)
			nutrition[i][j] += addNutrition[i][j];
	}
}
void solve() {
	for(int i = 0; i < k; i++) {
		spring();
		summer();
		fall();
		winter();
	}
}
int main() {
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			//S2D2가 추가할 양분 정보
			scanf("%d", &addNutrition[i][j]);
			nutrition[i][j] = 5;	//현재 양분 초기화
		}
	}
	for(int i = 0; i < m; i++) {
		int y, x, age;
		scanf("%d %d %d", &y, &x, &age);
		trees[y][x].push_back(age);
		ans++;
	}
	solve();
	printf("%d", ans);
	return 0;
}
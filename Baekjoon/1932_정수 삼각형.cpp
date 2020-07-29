// [1932] 정수 삼각형 : https://www.acmicpc.net/problem/1932
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> tri[501];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < i; j++) {
			int num;
			scanf("%d", &num);
			tri[i].push_back(num);
			if(i!=1) {
				if(j==0) tri[i][j] += tri[i-1][j];
				else if(j==i-1) tri[i][j] += tri[i-1][j-1];
				else tri[i][j] += max(tri[i-1][j-1], tri[i-1][j]);
			}
		}
	}
	sort(tri[n].begin(), tri[n].end());
	printf("%d", tri[n].back());
	return 0;
}
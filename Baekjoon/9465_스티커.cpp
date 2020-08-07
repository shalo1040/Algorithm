// [9465] 스티커 : https://www.acmicpc.net/problem/9465
#include <cstdio>
#include <algorithm>
#define MAX 100003
using namespace std;

//T: 테스트 케이스 개수, n: 열 크기
int T, n;
int map[2][MAX];	//스티커 점수 저장 + 메모이제이션

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 0; i < 2; i++) {
			for(int j = 2; j < n+2; j++)
				scanf("%d", &map[i][j]);
		}
		//j-1, j-2열의 값 비교하며 합 구하기
		for(int j = 2; j < n+2; j++) {
		    map[0][j] += max(map[1][j-1], map[1][j-2]);
		    map[1][j] += max(map[0][j-1], map[0][j-2]);
	    }
	    //n+1 열의 두 값 중 큰 값 출력
		printf("%d\n", max(map[0][n+1], map[1][n+1]));
	}
	return 0;
}
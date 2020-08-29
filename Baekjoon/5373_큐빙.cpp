// [5373] 큐빙 : https://www.acmicpc.net/problem/5373
#include <cstdio>

//T: 테스트 케이스 수
//N: 큐브를 돌린 횟수
int T, N;
char command[3], newCube[6][3][3];
char cube[6][3][3] = {
	{
		{'w', 'w', 'w'},
		{'w', 'w', 'w'},
		{'w', 'w', 'w'}
	},
	{
		{'y', 'y', 'y'},
		{'y', 'y', 'y'},
		{'y', 'y', 'y'}
	},
	{
		{'r', 'r', 'r'},
		{'r', 'r', 'r'},
		{'r', 'r', 'r'}
	},
	{
		{'o', 'o', 'o'},
		{'o', 'o', 'o'},
		{'o', 'o', 'o'}
	},
	{
		{'g', 'g', 'g'},
		{'g', 'g', 'g'},
		{'g', 'g', 'g'}
	},
	{
		{'b', 'b', 'b'},
		{'b', 'b', 'b'},
		{'b', 'b', 'b'}
	}
};
//면을 중심으로 큐브 회전
void rotate(int side, int dir) {
	char tmp[3];
	for(int i = 1; i < 3; i++)
		tmp[i] = newCube[side][0][i];
	if(dir > 0) {
		for(int i = 1; i < 3; i++)
			newCube[side][0][i] = newCube[side][2-i][0];
		for(int i = 1; i < 3; i++)
			newCube[side][2-i][0] = newCube[side][2][2-i];
		for(int i = 1; i < 3; i++)
			newCube[side][2][2-i] = newCube[side][i][2];
		for(int i = 1; i < 3; i++)
			newCube[side][i][2] = tmp[i];
	} else {
		for(int i = 1; i < 3; i++)
			newCube[side][0][i] = newCube[side][i][2];
		for(int i = 1; i < 3; i++)
			newCube[side][i][2] = newCube[side][2][2-i];
		for(int i = 1; i < 3; i++)
			newCube[side][2][2-i] = newCube[side][2-i][0];
		for(int i = 1; i < 3; i++)
			newCube[side][2-i][0] = tmp[i];
	}
}
//면의 상하좌우 네 면 회전
void rotation(char side, char dir) {
	char tmp[4];
	//오른쪽 회전
	if(dir == '+') {
		switch(side) {
			case 'U':
				for(int i = 0; i < 3; i++)
					tmp[i] = newCube[3][0][i];
				for(int i = 0; i < 3; i++)
					newCube[3][0][i] = newCube[4][0][i];
				for(int i = 0; i < 3; i++)
					newCube[4][0][i] = newCube[2][0][i];
				for(int i = 0; i < 3; i++)
					newCube[2][0][i] = newCube[5][0][i];
				for(int i = 0; i < 3; i++)
					newCube[5][0][i] = tmp[i];
				rotate(0, 1);
				break;
			case 'D':
				for(int i = 0; i < 3; i++)
					tmp[i] = newCube[2][2][i];
				for(int i = 0; i < 3; i++)
					newCube[2][2][i] = newCube[4][2][i];
				for(int i = 0; i < 3; i++)
					newCube[4][2][i] = newCube[3][2][i];
				for(int i = 0; i < 3; i++)
					newCube[3][2][i] = newCube[5][2][i];
				for(int i = 0; i < 3; i++)
					newCube[5][2][i] = tmp[i];
				rotate(1, 1);
				break;
			case 'F':
				for(int i = 0; i < 3; i++)
					tmp[i] = newCube[0][2][i];
				for(int i = 0; i < 3; i++)
					newCube[0][2][i] = newCube[4][2-i][2];
				for(int i = 0; i < 3; i++)
					newCube[4][2-i][2] = newCube[1][0][2-i];
				for(int i = 0; i < 3; i++)
					newCube[1][0][2-i] = newCube[5][i][0];
				for(int i = 0; i < 3; i++)
					newCube[5][i][0] = tmp[i];
				rotate(2, 1);
				break;
			case 'B':
				for(int i = 0; i < 3; i++)
					tmp[i] = newCube[0][0][i];
				for(int i = 0; i < 3; i++)
					newCube[0][0][i] = newCube[5][i][2];
				for(int i = 0; i < 3; i++)
					newCube[5][i][2] = newCube[1][2][2-i];
				for(int i = 0; i < 3; i++)
					newCube[1][2][2-i] = newCube[4][2-i][0];
				for(int i = 0; i < 3; i++)
					newCube[4][2-i][0] = tmp[i];
				rotate(3, 1);
				break;
			case 'L':
				for(int i = 0; i < 3; i++)
					tmp[i] = newCube[0][i][0];
				for(int i = 0; i < 3; i++)
					newCube[0][i][0] = newCube[3][2-i][2];
				for(int i = 0; i < 3; i++)
					newCube[3][2-i][2] = newCube[1][i][0];
				for(int i = 0; i < 3; i++)
					newCube[1][i][0] = newCube[2][i][0];
				for(int i = 0; i < 3; i++)
					newCube[2][i][0] = tmp[i];
				rotate(4, 1);
				break;
			case 'R':
				for(int i = 0; i < 3; i++)
					tmp[i] = newCube[0][2-i][2];
				for(int i = 0; i < 3; i++)
					newCube[0][2-i][2] = newCube[2][2-i][2];
				for(int i = 0; i < 3; i++)
					newCube[2][2-i][2] = newCube[1][2-i][2];
				for(int i = 0; i < 3; i++)
					newCube[1][2-i][2] = newCube[3][i][0];
				for(int i = 0; i < 3; i++)
					newCube[3][i][0] = tmp[i];
				rotate(5, 1);
				break;
		}
	}
	//왼쪽 회전
	else {
		switch(side) {
			case 'U':
				for(int i = 0; i < 3; i++)
					tmp[i] = newCube[3][0][i];
				for(int i = 0; i < 3; i++)
					newCube[3][0][i] = newCube[5][0][i];
				for(int i = 0; i < 3; i++)
					newCube[5][0][i] = newCube[2][0][i];
				for(int i = 0; i < 3; i++)
					newCube[2][0][i] = newCube[4][0][i];
				for(int i = 0; i < 3; i++)
					newCube[4][0][i] = tmp[i];
				rotate(0, -1);
				break;
			case 'D':
				for(int i = 0; i < 3; i++)
					tmp[i] = newCube[2][2][i];
				for(int i = 0; i < 3; i++)
					newCube[2][2][i] = newCube[5][2][i];
				for(int i = 0; i < 3; i++)
					newCube[5][2][i] = newCube[3][2][i];
				for(int i = 0; i < 3; i++)
					newCube[3][2][i] = newCube[4][2][i];
				for(int i = 0; i < 3; i++)
					newCube[4][2][i] = tmp[i];
				rotate(1, -1);
				break;
			case 'F':
				for(int i = 0; i < 3; i++)
					tmp[i] = newCube[0][2][i];
				for(int i = 0; i < 3; i++)
					newCube[0][2][i] = newCube[5][i][0];
				for(int i = 0; i < 3; i++)
					newCube[5][i][0] = newCube[1][0][2-i];
				for(int i = 0; i < 3; i++)
					newCube[1][0][2-i] = newCube[4][2-i][2];
				for(int i = 0; i < 3; i++)
					newCube[4][2-i][2] = tmp[i];
				rotate(2, -1);
				break;
			case 'B':
				for(int i = 0; i < 3; i++)
					tmp[i] = newCube[0][0][i];
				for(int i = 0; i < 3; i++)
					newCube[0][0][i] = newCube[4][2-i][0];
				for(int i = 0; i < 3; i++)
					newCube[4][2-i][0] = newCube[1][2][2-i];
				for(int i = 0; i < 3; i++)
					newCube[1][2][2-i] = newCube[5][i][2];
				for(int i = 0; i < 3; i++)
					newCube[5][i][2] = tmp[i];
				rotate(3, -1);
				break;
			case 'L':
				for(int i = 0; i < 3; i++)
					tmp[i] = newCube[0][i][0];
				for(int i = 0; i < 3; i++)
					newCube[0][i][0] = newCube[2][i][0];
				for(int i = 0; i < 3; i++)
					newCube[2][i][0] = newCube[1][i][0];
				for(int i = 0; i < 3; i++)
					newCube[1][i][0] = newCube[3][2-i][2];
				for(int i = 0; i < 3; i++)
					newCube[3][2-i][2] = tmp[i];
				rotate(4, -1);
				break;
			case 'R':
				for(int i = 0; i < 3; i++)
					tmp[i] = newCube[0][2-i][2];
				for(int i = 0; i < 3; i++)
					newCube[0][2-i][2] = newCube[3][i][0];
				for(int i = 0; i < 3; i++)
					newCube[3][i][0] = newCube[1][2-i][2];
				for(int i = 0; i < 3; i++)
					newCube[1][2-i][2] = newCube[2][2-i][2];
				for(int i = 0; i < 3; i++)
					newCube[2][2-i][2] = tmp[i];
				rotate(5, -1);
				break;
		}
	}
}
int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &N);
		//큐브 초기화
		for(int i = 0; i < 6; i++) {
			for(int j = 0; j < 3; j++) {
				for(int k = 0; k < 3; k++)
					newCube[i][j][k] = cube[i][j][k];
			}
		}
		//회전 정보 입력
		for(int i = 0; i < N; i++) {
			scanf("%s", &command);
			rotation(command[0], command[1]);
		}
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++)
				printf("%c", newCube[0][i][j]);
			printf("\n");
		}
	}
	return 0;
}
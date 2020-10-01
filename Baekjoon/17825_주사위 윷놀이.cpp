// [17825] 주사위 윷놀이 : https://www.acmicpc.net/problem/17825
#include <cstdio>
#include <cstring>

typedef struct {
	int data;   //가리키는 위치의 점수
	int nextIdx[5];     //가리키는 위치에서 주사위 결과에 따라 갈 수 있는 좌표
} Info;

const int MAX = 2*10, SIZE = 33, FINISHED = 32;
int ans = -1;
int dice[10];

Info map[] = {
	{0, {1,2,3,4,5}},	//0(출발 지점)
	{2, {2,3,4,5,6}},	//1
	{4, {3,4,5,6,7}},	//2
	{6, {4,5,6,7,8}},	//3
	{8, {5,6,7,8,9}},	//4
	{10, {21,22,23,26,27}},	//5(첫 번째 파란 지점)
	{12, {7,8,9,10,11}},	//6
	{14, {8,9,10,11,12}},	//7
	{16, {9,10,11,12,13}},	//8
	{18, {10,11,12,13,14}},	//9
	{20, {24,25,26,27,28}},	//10(두 번째 파란 지점)
	{22, {12,13,14,15,16}},	//11
	{24, {13,14,15,16,17}},	//12
	{26, {14,15,16,17,18}},	//13
	{28, {15,16,17,18,19}},	//14
	{30, {29,30,31,26,27}},	//15(세 번째 파란 지점)
	{32, {17,18,19,20,FINISHED}},	//16
	{34, {18,19,20,FINISHED,FINISHED}},	//17
	{36, {19,20,FINISHED,FINISHED,FINISHED}},	//18
	{38, {20,FINISHED,FINISHED,FINISHED, FINISHED}},	//19
	{40, {FINISHED,FINISHED,FINISHED,FINISHED,FINISHED}},	//20
	{13, {22,23,26,27,28}},	//21
	{16, {23,26,27,28,20}},	//22
	{19, {26,27,28,20,FINISHED}},	//23
	{22, {25,26,27,28,20}},	//24
	{24, {26,27,28,20,FINISHED}},	//25
	{25, {27,28,20,FINISHED,FINISHED}},	//26
	{30, {28,20,FINISHED,FINISHED,FINISHED}},	//27
	{35, {20,FINISHED,FINISHED,FINISHED,FINISHED}},	//28
	{28, {30,31,26,27,28}},	//29
	{27, {31,26,27,28,20}},	//30
	{26, {26,27,28,20,FINISHED}},	//31
	{0, {FINISHED,FINISHED,FINISHED,FINISHED,FINISHED}}     //32(도착 지점)
};

int max(int a, int b) { return (a>b) ? a : b; }
void solve(int num) {
	//score: 각 말의 점수
	//pos: 각 말의 위치
	//state: map에서 존재하는 말의 개수(시작점에 4개의 말 존재)
	int score[4] = {0,}, pos[4] = {0,}, state[SIZE] = {4,};
	for(int i = 0; i < 10; i++) {
		int user = num&3;       //뒤에서 두자리가 움직일 말의 번호
		num >>= 2;      // num /= 4; 와 같은 명령. user부분을 지운다.
		if(pos[user] == FINISHED) continue;     //이미 도착지점에 도착했으면 continue
		int next = map[pos[user]].nextIdx[dice[i]-1];   //다음에 도착할 지점
		if(next != FINISHED && state[next]) return;     //next에 다른 말이 놓여져 있으면 갈 수 없으므로 return
		state[pos[user]]--;
		state[next]++;
		pos[user] = next;
		score[user] += map[next].data;
	}
	int sum = 0;
	for(auto n : score)
		sum += n;
	ans = max(ans, sum);
}
int main() {
	for(int i = 0; i < 10; i++)
		scanf("%d", &dice[i]);
	//중복 순열
	//이진수 00, 01, 10, 11이 말의 번호를 의미
	for(int i = 0; i < (1<<MAX); i++)
		solve(i);
	printf("%d", ans);
	return 0;
}
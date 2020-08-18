// [14888] 연산자 끼워넣기 : https://www.acmicpc.net/problem/14888
#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

int n, maxi = INT_MIN, mini = INT_MAX;
int num[101], operators[100];

enum Operator { plus, minus, multiply, divide };

void solve() {
	do {
		int result = num[0];
		for(int i = 0; i < n-1; i++) {
			switch(operators[i]) {
				case plus:
					result += num[i+1]; break;
				case minus:
					result -= num[i+1]; break;
				case multiply:
					result *= num[i+1]; break;
				case divide:
					//음수를 양수로 나눌 때는 음수를 양수로 취해 나눠준 뒤 다시 음수 취함
					if(result < 0) {
						result = (-result) / num[i+1];
						result *= -1;
					} else result /= num[i+1];
					break;
			}
		}
		if(maxi < result) maxi = result;
		if(mini > result) mini = result;
	} while(next_permutation(operators, operators + n-1));	//다음 순열로 위 코드 반복
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", num + i);
	//operators 배열에 값을 넣을 수 있는 위치의 인덱스 가리키는 point
	int point = 0;
	//연산자 4개에 대한 개수(count)를 입력받고
	//그 개수만큼 반복문으로 operators 배열에 0,1,2,3(+,-,*,/)를 넣는다.
	for(int i = 0; i < 4; i++) {
		int count;
		scanf("%d", &count);
		for(int j = point; j < point+count; j++)
			operators[j] = i;
		point += count;
	}
	solve();
	printf("%d\n", maxi);
	printf("%d\n", mini);
	return 0;
}
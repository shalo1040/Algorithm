// [11727] 2xn 타일링 2 : https://www.acmicpc.net/problem/11727
#include <cstdio>

int n;
int arr[1001];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		if(i == 1) { arr[i] = 1; continue; }
		if(i == 2) { arr[i] = 3; continue; }
		// i-1번째에 타일 1개 추가 + i-2번째에 타일 2개 추가
		arr[i] = (arr[i-1] + arr[i-2]*2)%10007;
	}
	printf("%d", arr[n]);
	return 0;
}
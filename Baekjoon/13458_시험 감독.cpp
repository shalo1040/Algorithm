//[13458] 시험 감독 : https://www.acmicpc.net/problem/13458
#include <cstdio>

//n: 시험장 수
//b: 총감독관이 감시할 수 있는 인원
//c: 부감독관이 감시할 수 있는 인원
int n, b, c;
long long ans;
int ppl[1000001];	//시험장 별 응시자 수

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", ppl+i);
	scanf("%d %d", &b, &c);
	for(int i = 0; i < n; i++)
		ans += (ppl[i]>b) ? (long long)(ppl[i]-b-1)/c+2 : 1;
	printf("%lld", ans);
	return 0;
}
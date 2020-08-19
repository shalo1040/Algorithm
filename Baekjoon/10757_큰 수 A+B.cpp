// [10757] 큰 수 A+B : https://www.acmicpc.net/problem/10757
#include <iostream>
#include <algorithm>
using namespace std;

//a,b : 입력된 수
//c : 출력할 수
//pointA, pointB : 각각 a, b의 인덱스를 표현
string a, b, c;
int pointA, pointB;

void solve() {
	//tmp : 다음 자릿수에 더해줄 숫자(0 or 1)
    int tmp = 0;
	while(pointA >= 0 || pointB >= 0) {
	    int aa = (pointA >= 0) ? a[pointA] - '0' : 0;
	    int bb = (pointB >= 0) ? b[pointB] - '0' : 0;
	    //현재 c의 마지막에는 10으로 나눈 나머지를 넣고
	    c += (aa + bb + tmp)%10 + '0';
	    //다음 자리에는 10으로 나눈 몫을 더하기 위해 tmp를 설정한다.
		if((aa + bb + tmp)/10) tmp = 1;
		else tmp = 0;
		pointA--; pointB--;
	}
    if(tmp) c += tmp + '0';
    //0번째부터 c에 값을 넣었으므로 순서를 바꿔준다.
    reverse(c.begin(), c.end());
}
int main() {
    cin >> a >> b;
	pointA = a.size()-1;
	pointB = b.size()-1;
	solve();
	cout << c << endl;
	return 0;
}
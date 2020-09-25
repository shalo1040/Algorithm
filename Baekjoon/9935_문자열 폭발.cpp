// [9935] 문자열 폭발 : https://www.acmicpc.net/problem/9935
#include <iostream>
#include <string>
using namespace std;

const int MAX = 1000001;
string str, del;
char answer[MAX];
int strSize, delSize, pointer;

int main() {
	cin >> str >> del;
	strSize = str.length();
	delSize = del.length();
	for(int i = 0; i < strSize; i++) {
		answer[pointer++] = str[i];
		//문자열 del이 answer에 있다고 탐지되면 pointer 위치 조정
		if((answer[pointer-1] == del[delSize-1]) && (pointer >= delSize)) {
			bool isDel = true;
			for(int j = 1; j < delSize; j++) {
				if(answer[pointer-j-1] != del[delSize-j-1]) {
					isDel = false;
					break;
				}
			}
			if(isDel) 
				pointer -= delSize;
		}
	}
	if(pointer == 0) cout << "FRULA";
	else {
		for(int i = 0; i < pointer; i++)
			cout << answer[i];
	}
	return 0;
}
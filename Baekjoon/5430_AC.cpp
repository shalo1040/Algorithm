// [5430] AC : https://www.acmicpc.net/problem/5430
#include <iostream>
#include <string>
#include <deque>
using namespace std;

int T, N;
string p, str;
deque<int> d;
bool isFront = true;

bool solve() {
	isFront = true;
	int pointer = 0;
	int size = p.length();
	while(pointer < size) {
		switch(p[pointer]) {
			case 'R':
				isFront = !isFront;
				break;
			case 'D':
				if(d.empty()) return false;
				(isFront) ? d.pop_front() : d.pop_back();
				break;
		}
		pointer++;
	}
	return true;
}
int main() {
	cin >> T;
	while(T--) {
		cin >> p >> N >> str;
		int i = 1;
		int len = str.length();
		while(i < len) {
			int num = 0;
			while(str[i] >= '0' && str[i] <= '9') {
				num *= 10;
				num += (str[i] - '0');
				i++;
			}
			if(num > 0) d.push_back(num);
			i++;
		}
		if(!solve()) printf("error\n");
		else {
			cout << "[";
			while(!d.empty()) {
				if(isFront) {
					cout << d.front();
					d.pop_front();
				} else {
					cout << d.back();
					d.pop_back();
				}
				if(d.size()) cout << ",";
			}
			cout << "]" << endl;
		}
	}
	return 0;
}
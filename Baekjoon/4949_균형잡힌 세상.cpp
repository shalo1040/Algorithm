// [4949] 균형잡힌 세상 : https://www.acmicpc.net/problem/4949
#include <iostream>
#include <string>
#include <stack>
using namespace std;

string str;
stack<char> s;

bool solve(string str) {
	int size = str.length();
	for(int i = 0; i < size; i++) {
		if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) continue;
		if(str[i] == '(' || str[i] == '[')
			s.push(str[i]);
		else if(str[i] == ')' || str[i] == ']') {
		    if(s.empty()) return false;
			if((str[i] == ')' && s.top() == '(') || (str[i] == ']' && s.top() == '[')) s.pop();
			else return false;
		}
	}
	return (s.empty()) ? true : false;
}
int main() {
	while(1) {
		getline(cin, str);
		if(str == ".") break;
		(solve(str)) ? cout << "yes" << endl : cout << "no" << endl;
	    while(!s.empty()) s.pop();
	}
	return 0;
}
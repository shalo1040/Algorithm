// [60058] 괄호 변환 : https://programmers.co.kr/learn/courses/30/lessons/60058
#include <string>
using namespace std;

//올바른 괄호 문자열인지 여부 반환
bool checkString(string p) {
    //빈 문자열일 때
    if(p.length() == 0) return true;
    int total = 0, repeat = 0;
    for(int i = 0; i < p.length(); i++) {
        if(p[i] == '(') {
            if(total == 0) { total++; repeat = 1; }
            else { total++; repeat++; }
        } else {
            if(total == 0) return false;
            else { total--; repeat--; }
        }
    }
    return true;
}
//u와 v로 나눈다.
void divideStr(string w, string &u, string &v) {
    int total = 0;
    for(int i = 0; i < w.length(); i++) {
        (w[i] == '(') ? total++ : total--;
        if(total == 0) { u = w.substr(0, i+1); v = w.substr(i+1, w.length()-i); break; }
    }
}
//분할 정복
string solve(string w) {
    string u = "", v = "";
    if(checkString(w)) return w;
    divideStr(w, u, v);
    if(!checkString(u)) {
        string uu = "";
        for(int i = 1; i < u.length()-1; i++)
            uu += (u[i] == '(') ? ')' : '(';
        return '(' + solve(v) + ')' + uu;
    } else return u + solve(v);
}
string solution(string p) {
    return solve(p);
}
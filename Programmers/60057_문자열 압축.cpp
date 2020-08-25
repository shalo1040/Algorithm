// [60057] 문자열 압축 : https://programmers.co.kr/learn/courses/30/lessons/60057
#include <string>
using namespace std;

int solution(string s) {
    int answer = 1234;
    int size = s.length();
    //문자열 길이의 반까지 나눠서 비교할 수 있다.
    //문자열 길이/2보다 큰 길이로 나누면 최소 (전체 길이+1)이 되어 답이 아니다.
    for(int i = 1; i <= size/2+1; i++) {
        //첫 번째 영역의 문자열을 prev에 저장한다.
        string prev = s.substr(0, i);
        //result: 문자열을 i씩 나눴을 때 나올 수 있는 압축된 문자열의 길이
        //cnt: 문자열을 i씩 나눴을 때 해당 블록이 중복되는 횟수
        int result = 0, cnt = 1;
        for(int j = i; j < size; j+=i) {
            //j로부터 i만큼 문자열을 자를 수 없을 때
            if(j+i > size) { 
                result += size-j;
                //cnt가 1이면 문자열 i만큼 result에 더하고
                //중복되는 횟수(cnt)의 자릿수에 따라 i에 1,2,3을 더한다.
                result += (cnt==1) ? i : (cnt<10) ? i+1 : (cnt<100) ? i+2 : i+3;
                cnt = 0; 
                break; 
            }
            string cur = s.substr(j, i);
            //현재 문자열 cur가 prev와 같으면 중복되므로 cnt+1
            if(cur == prev) { cnt++; continue; }
            //prev와 다르면 result에 이전 블록의 압축된 길이를 저장하고 prev, cnt 갱신
            else {
                result += (cnt==1) ? i : (cnt<10) ? i+1 : (cnt<100) ? i+2 : i+3;
                prev = cur;
                cnt = 1;
            }
        }
        if(cnt == 1) result += i;
        else if(cnt > 1) result += (cnt<10) ? i+1 : (cnt<100) ? i+2 : i+3;
        if(answer > result) answer = result;
    }
    return answer;
}
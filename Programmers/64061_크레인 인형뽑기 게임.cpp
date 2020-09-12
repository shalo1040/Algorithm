// [64061] 크레인 인형뽑기 게임 : https://programmers.co.kr/learn/courses/30/lessons/64061
#include <string>
#include <vector>
#include <stack>
using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    stack<int> s;
    for(int i = 0; i < moves.size(); i++) {
        int col = moves[i]-1;
        //크레인이 내려오면서 0이 아닌 값을 만나면 스택에 넣는다.
        for(int j = 0; j < board.size(); j++) {
            if(board[j][col] != 0) {
                //스택의 top에 같은 인형이 존재하면 answer를 2만큼 증가시키고 pop
                if(!s.empty() && s.top() == board[j][col]) { answer += 2; s.pop(); }
                else s.push(board[j][col]);
                board[j][col] = 0;
                break;
            }
        }
    }
    return answer;
}
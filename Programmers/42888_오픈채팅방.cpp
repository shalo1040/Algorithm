// [4288] 오픈채팅방 : https://programmers.co.kr/learn/courses/30/lessons/42888
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

vector<string> solution(vector<string> record) {
    vector<string> answer;
    vector<vector<string>> cmd;     //record를 공백을 제거해 벡터로 저장
    unordered_map<string, string> map;  //해시 {아이디, 닉네임}
    for(int i = 0; i < record.size(); i++) {
        string word;
        vector<string> words;
        for(int j = 0; j < record[i].length(); j++) {
            if(record[i][j] == ' ' || j == record[i].length()-1) {
                if(j == record[i].length()-1) word += record[i][j];
                words.push_back(word);
                word = "";
            } else word += record[i][j];
        }
        cmd.push_back(words);
        //아이디 words[1]가 존재하면 닉네임을 words[2]로 변경, 그렇지 않으면 insert
        if(words[0] != "Leave") map[words[1]] = words[2];
    }
    for(int i = 0; i < cmd.size(); i++) {
        string ans;
        string nickname = map[cmd[i][1]];
        if(cmd[i][0] == "Enter")
            ans = nickname + "님이 들어왔습니다.";
        else if(cmd[i][0] == "Leave")
            ans = nickname + "님이 나갔습니다.";
        else continue;
        answer.push_back(ans);
    }
    return answer;
}
// [60059] 자물쇠와 열쇠 : https://programmers.co.kr/learn/courses/30/lessons/60059
#include <string>
#include <vector>
using namespace std;

//시계방향으로 90도 회전
vector<vector<int>> rotateKey(vector<vector<int>> key) {
    vector<vector<int>> newKey = key;
    for(int i = 0; i < key.size(); i++) {
        for(int j = 0; j < key.size(); j++)
            newKey[j][i] = key[key.size()-i-1][j];
    }
    return newKey;
}
bool solve(vector<vector<int>> lock, vector<vector<int>> key, int n, int m, int b) {
    for(int i = 1-m; i < n; i++) {
        for(int j = 1-m; j < n; j++) {
            bool flag = true;
            int cnt = 0;
            //열쇠 시작 위치(y,x)
            int y = (i < 0) ? -i : 0;
            int x = (j < 0) ? -j : 0;
            //자물쇠 시작 위치(yy,xx)
            int yy = (i < 0) ? 0 : i;
            int xx = (j < 0) ? 0 : j;
            for(int k = y; k < m && yy < n; k++, yy++) {
                for(int l = x, ii = xx; l < m && ii < n; l++, ii++) {
                    if(lock[yy][ii] == key[k][l]) { flag = false; break; }
                    if(!lock[yy][ii]) cnt++;
                }
                if(!flag) break;
            }
            if(flag && cnt == b) return true;
        }
    }
    return false;
}
bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    bool answer = false;
    //자물쇠의 홈 개수
    int blank = 0;
    for(int i = 0; i < lock.size(); i++) {
        for(int j = 0; j < lock.size(); j++)
            if(!lock[i][j]) blank++;
    }
    //4번 회전 시키면서 자물쇠의 모든 홈에 맞는 열쇠인지 여부 판단
    for(int i = 0; i < 4; i++) {
        answer = solve(lock, key, lock.size(), key.size(), blank);
        if(answer) break;
        key = rotateKey(key);
    }
    return answer;
}
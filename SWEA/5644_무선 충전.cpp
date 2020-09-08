// [5644] 무선 충전 : https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRDL1aeugDFAUo
#include <cstdio>
#include <vector>
using namespace std;

typedef struct {
    int y, x, c, p;
} BC;

const int n = 11;
int T, M, A, C, P;
int ay, ax, by, bx; //사람 a,b의 위치
vector<int> cmdA, cmdB; //사람 a,b의 이동 방향
vector<BC> bc;

int dir[][2] = { {0,0}, {-1,0}, {0,1}, {1,0}, {0,-1} };

//절대값 반환
int abs(int x) { return (x<0) ? -x : x; }
//최대값 반환
int max(int a, int b) { return (a<b) ? b : a; }
int getSum() {
    int sum = 0;
    vector<int> userA, userB;
    //현재 a,b의 위치에 충전할 수 있는 bc가 존재하면 벡터에 push
    for(int i = 0; i < A; i++) {
        BC b = bc[i];
        if(abs(ax-b.x) + abs(ay-b.y) <= b.c) userA.push_back(i);
        if(abs(bx-b.x) + abs(by-b.y) <= b.c) userB.push_back(i);
    }
    //a,b 모두 충전할 수 있을 때
    if(userA.size() && userB.size()) {
        for(int i = 0; i < userA.size(); i++) {
            int bcA = userA[i];
            for(int j = 0; j < userB.size(); j++) {
                int bcB = userB[j];
                //a와 b가 같은 영역의 bc를 공유할 때
                if(bcA == bcB) sum = max(sum, bc[bcA].p);
                //서로 다른 bc를 이용할 때
                else sum = max(sum, bc[bcA].p + bc[bcB].p);
            }
        }	
    } else { //a 또는 b가 충전할 수 없을 때
        if(!userA.size()) {
            for(int i = 0; i < userB.size(); i++)
                sum = max(sum, bc[userB[i]].p);
        } else {
            for(int i = 0; i < userA.size(); i++)
                sum = max(sum, bc[userA[i]].p);
        }
    }
    return sum; //최대값 반환
}
int solve() {
    int ans = 0;
    ay = ax = 1, by = bx = 10;
    ans += getSum();
    //a,b가 이동할 때마다 충전되는 값의 최대값을 구한다.
    for(int i = 0; i < M; i++) {
        ay += dir[cmdA[i]][0];
        ax += dir[cmdA[i]][1];
        by += dir[cmdB[i]][0];
        bx += dir[cmdB[i]][1];
        ans += getSum();
    }
    return ans;
}
int main() {
    scanf("%d", &T);
    for(int testcase = 1; testcase <= T; testcase++) {
        //초기화
        cmdA.clear(); cmdB.clear();
        bc.clear();
        //입력
        scanf("%d %d", &M, &A);
        for(int i = 0; i < M; i++) {
            int cmd;
            scanf("%d", &cmd);
            cmdA.push_back(cmd);
        }
        for(int i = 0; i < M; i++) {
            int cmd;
            scanf("%d", &cmd);
            cmdB.push_back(cmd);
        }
        for(int i = 0; i < A; i++) {
            int x, y, c, p;
            scanf("%d %d %d %d", &x, &y, &c, &p);
            bc.push_back({y, x, c, p});
        }
        //출력
        printf("#%d %d\n", testcase, solve());
    }
    return 0;
}
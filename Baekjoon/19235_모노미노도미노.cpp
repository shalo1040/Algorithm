// [19235] 모노미노도미노 : https://www.acmicpc.net/problem/19235
#include <cstdio>
#include <vector>
using namespace std;

int n, score;
vector<vector<int>> green, blue, green_block, blue_block;

//블록이 존재할 수 있는 칸 탐색
void searchBlank(int t, int y, int h, vector<vector<int>> &map, vector<vector<int>> &block) {
    for(int height = h; ; height++) {
        bool isPossible = true;
        if(height >= 6) isPossible = false;
        else if(t==1 && map[height][y]) isPossible = false;
        else if(t==2 && (map[height][y] || map[height][y+1])) isPossible = false;
        else if(t==3 && (height+1 >= 6 || map[height][y] || map[height+1][y])) isPossible = false;
        if(!isPossible) {
            switch(t) {
                case 1:
                    map[height-1][y] = t; break;
                case 2:
                    map[height-1][y] = map[height-1][y+1] = t; break;
                case 3:
                    map[height-1][y] = map[height][y] = t; break;
            }
            block[height-1][y] = t;     //블록 정보 담는다(시작점)
            break;
        }
    }
}
//지운 행이 있으면 true 반환
bool check(vector<vector<int>> &map, vector<vector<int>> &block) {
	bool flag = false;
	for(int x = 5; x >= 2; x--) {
		bool flag2 = true;
		for(int y = 0; y < 4; y++) {
			if(!map[x][y]) {
				flag2 = false;
				break;
			}
		}
		//행이 모두 블록으로 차있으면 지운다
		if(flag2) {
			for(int y = 0; y < 4; y++) {
			    //세로로 있던 블록은 1로 쪼개진다.
			    if(map[x][y] == 3) {
			        if(block[x][y] == 3)
			            map[x+1][y] = block[x+1][y] = 1;
			        else map[x-1][y] = block[x-1][y] = 1;
			    }
			    map[x][y] = block[x][y] = 0;
			}
			score++;
			flag = true;
		}
	}
	//flag가 true이면 map의 모든 블록이 경계나 다른 블록과 만날 때까지 내려간다
	if(flag) {
	    for(int x = 5; x >= 0; x--) {
	        for(int y = 0; y < 4; y++) {
	            if(!block[x][y]) continue;
	            int t = map[x][y];
	            switch(block[x][y]) {
	                case 1:
	                    map[x][y] = block[x][y] = 0; break;
	                case 2:
	                    map[x][y] = map[x][y+1] = block[x][y] = 0; break;
	                case 3:
	                    map[x][y] = map[x+1][y] = block[x][y] = 0; break;
	            }
	            searchBlank(t, y, x+1, map, block);
	        }
	    }
	}
	return flag;
}
void del(vector<vector<int>> &map, vector<vector<int>> &block, int cnt) {
    if(cnt == 1) {
	    for(int k = 0; k < 4; k++) {
	    if(map[5-cnt][k]==3 && block[5-cnt][k]==3)
		    map[5-cnt][k] = block[5-cnt][k] = 1;
	    }
	} else {
		for(int k = 0; k < 4; k++) {
    		if(map[5-cnt][k]==3 && block[5-cnt][k]==3)
    		    map[5-cnt][k] = block[5-cnt][k] = 1;
		}
	}
	for(int y = 0; y < 4; y++) {
		for(int x = 5; x >= cnt; x--) {
			map[x][y] = map[x-cnt][y];
			block[x][y] = block[x-cnt][y];
			map[x-cnt][y] = block[x-cnt][y] = 0;
		}
	}
}
void putBlock(int t, int y, vector<vector<int>> &map, vector<vector<int>> &block) {
    //블록이 존재할 수 있는 칸 탐색
    searchBlank(t, y, 0, map, block);
	//지울 수 있는 행이 있는지 탐색
	while(check(map, block)) continue;
	//0,1행에 블록이 존재하는지 탐색
	int cnt = 0;
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 4; j++) {
			if(map[i][j]) { cnt++; break; }
		}
	}
	if(cnt) del(map, block, cnt);
}
int main() {
	scanf("%d", &n);
	green = blue = green_block = blue_block = vector<vector<int>>(6, vector<int>(4,0));
	for(int i = 0; i < n; i++) {
		int t, x, y;
		scanf("%d %d %d", &t, &x, &y);
		//초록색 타일에 블록 놓는다
		putBlock(t, y, green, green_block);
		//파란색 타일에 블록 놓는다
		(t==1) ? putBlock(t, x, blue, blue_block) : (t==2) ? putBlock(3, x, blue, blue_block) : putBlock(2, x, blue, blue_block);
	}
	printf("%d\n", score);
	int cnt = 0;
	for(int i = 0; i < 6; i++) {
	    for(int j = 0; j < 4; j++) {
	        if(green[i][j]) cnt++;
	        if(blue[i][j]) cnt++;
	    }
	}
	printf("%d\n", cnt);
	return 0;
}
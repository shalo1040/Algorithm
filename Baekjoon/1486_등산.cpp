// [1486] 등산 : https://www.acmicpc.net/problem/1486
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

typedef long long int ll;
const ll INF = 2e9;
ll h, w, T, D;
vector<vector<ll>> map;	//각 지점에서의 높이 저장
vector<vector<ll>> climb;	//다른 지점으로 가는 시간
vector<vector<ll>> back;	//시작 지점으로 돌아오는 시간

ll dir[][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};

ll abs(ll a) { return (a<0) ? -a : a; }
ll max(ll a, ll b) { return (a>b) ? a : b; }
ll square(ll a) { return a*a; }

//다익스트라
void solve() {
	priority_queue<pair<ll, pair<ll, ll>>> pq; //{시간, 좌표}
	pq.push({0,{0,0}});	//시작점(0,0)
	while(!pq.empty()) {
		ll time = -pq.top().first;
		ll y = pq.top().second.first;
		ll x = pq.top().second.second;
		pq.pop();
		for(ll i = 0; i < 4; i++) {
			ll ny = y + dir[i][0];
			ll nx = x + dir[i][1];
			if(ny<0 || ny>=h || nx<0 || nx>=w) continue;
            if(abs(map[y][x] - map[ny][nx]) > T) continue;		//높이 차이가 T 이하일 때만 이동 가능
			ll diff = (map[y][x] >= map[ny][nx]) ? 1 : square(map[ny][nx] - map[y][x]);
			if(climb[ny][nx] > climb[y][x] + diff) {
				climb[ny][nx] = climb[y][x] + diff;
				pq.push({-(time+climb[ny][nx]), {ny, nx}});
			}
			diff = (map[y][x] <= map[ny][nx]) ? 1 : square(map[y][x] - map[ny][nx]);
			if(back[ny][nx] > back[y][x] + diff)
				back[ny][nx] = back[y][x] + diff;
		}
	}
}
int main() {
	scanf("%lld %lld %lld %lld", &h, &w, &T, &D);
	map = vector<vector<ll>>(h, vector<ll>(w,0));
	climb = back = vector<vector<ll>>(h, vector<ll>(w,INF));
	climb[0][0] = back[0][0] = 0;
	//높이 입력
	for(ll i = 0; i < h; i++) {
		char info[w+1];
		scanf("%s", &info);
		for(ll j = 0; j < w; j++) {
			//대문자(0~25)
			if(info[j]-'a' < 0)
				map[i][j] = info[j]-'A';
			//소문자(26~51)
			else map[i][j] = info[j]-'a'+26;
		}
	}
	solve();
	ll ans = 0;
	for(ll i = 0; i < h; i++) {
		for(ll j = 0; j < w; j++) {
			if(climb[i][j] + back[i][j] > D) continue;
			ans = max(ans, map[i][j]);
		}
	}
	printf("%lld", ans);
	return 0;
}

/*
아래는 플로이드 와샬로 구현한 코드이다.

#include <cstdio>
#include <vector>
using namespace std;

typedef long long int ll;
const ll INF = 2e9;
ll h, w, T, D;
//map: 입력받은 높이를 이차원 행렬로 저장
//dist: (y,x)->(ny,nx) 간의 비용 저장
//map2: 높이를 일차원 배열로 저장
//idx: map2의 모든 인덱스 저장
vector<vector<ll>> map, dist;
vector<ll> map2, idx;	//arr2, num

ll dir[][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

ll abs(ll a) { return (a<0) ? -a : a; }
ll max(ll a, ll b) { return (a>b) ? a : b; }
ll square(ll a) { return a*a; }
void solve() {
	//cur->next로 가는 비용 계산
	for(ll i = 0; i < h; i++) {
		for(ll j = 0; j < w; j++) {
			for(ll d = 0; d < 4; d++) {
				ll ny = i+dir[d][0];
				ll nx = j+dir[d][1];
				if(ny<0 || ny>=h || nx<0 || nx>=w) continue;
				ll cur = i*w+j;		//일차원 배열의 인덱스
				ll next = ny*w+nx;
				if(abs(map[ny][nx] - map[i][j]) > T) continue;		//높이 차이가 T 이하일 때만 이동 가능
				dist[cur][next] = (map2[cur] >= map2[next]) ? 1 : square(map2[next] - map2[cur]);
			}
		}
	}
	//i부터 j까지의 최단비용(플로이드 와샬)
	for(auto k : idx) {
		for(auto i : idx) {
			for(auto j : idx) {
				if(dist[i][j] > dist[i][k] + dist[k][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}
}
int main() {
	scanf("%lld %lld %lld %lld", &h, &w, &T, &D);
	map = vector<vector<ll>>(h, vector<ll>(w,0));
	dist = vector<vector<ll>>(h*w, vector<ll>(h*w,INF));
	map2 = vector<ll>(h*w, 0);
	dist[0][0] = 0;
	for(ll i = 0; i < h; i++) {
		char info[w+1];
		scanf("%s", &info);
		for(ll j = 0; j < w; j++) {
			map[i][j] = (info[j] >= 'a' && info[j] <= 'z') ? info[j]-'a'+26 : info[j]-'A';
			idx.push_back(i*w+j);
			map2[i*w+j] = map[i][j];	//2차원 지도를 1차원으로 만들기
		}
	}
	solve();
	ll ans = 0;
	for(auto k : idx) {
	    if(dist[0][k] + dist[k][0] <= D)
	        ans = max(ans, map2[k]);
	}
	printf("%lld", ans);
	return 0;
}
*/
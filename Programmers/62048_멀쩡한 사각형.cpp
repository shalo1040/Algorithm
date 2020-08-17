// [62048] 멀쩡한 사각형 : https://programmers.co.kr/learn/courses/30/lessons/62048/
//사각형의 왼쪽 아래 꼭짓점을 (0,0), 오른쪽 위 꼭짓점을 (w,h)라고 생각하고
//두 점을 지나는 직선을 y=(h/w)x 로 둠
//0~w-1까지 정수 높이를 구해 answer에 더하고 삼각형이 두 개이므로 2를 곱해 리턴했다.
using namespace std;

long long solution(int w,int h) {
    long long answer = 0;
    for(int i = 0; i < w; i++)
        answer += (long long)(h*i)/w;
    return answer*2;
}
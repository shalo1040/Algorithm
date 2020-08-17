// [42586] 기능개발 : https://programmers.co.kr/learn/courses/30/lessons/42586?language=cpp
#include <string>
#include <vector>
#define MAX 100
using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    int size = progresses.size();
    //progresses 배열에 일을 마치는 데 걸리는 시간을 저장
    //속도와 나누어 떨어지지 않으면 하루 더 걸리므로 +1
    for(int i = 0; i < size; i++)
        progresses[i] = ((100 - progresses[i])%speeds[i] != 0) ? (100 - progresses[i])/speeds[i] + 1 : (100 - progresses[i])/speeds[i];
    for(int i = 0; i < size; i++) {
    	//이미 배포한 기능은 MAX 값 가짐
        if(progresses[i] == MAX) continue;
        int cnt = 1;
        //i보다 뒤에 나열된 기능들 중 시간이 적거나 같게 걸리는 기능이 있으면 cnt+1
        //더 오래 걸리는 기능이 있으면 반복문 나옴
        for(int j = i+1; j < size; j++) {
            if(progresses[i] >= progresses[j]) {
                cnt++;
                progresses[j] = MAX;
            } else break;
        }
        //answer에 push
        answer.push_back(cnt);
    }
    return answer;
}

/*
//반복문을 한 번만 써서 간단하게 코드를 작성할 수도 있음을 배웠다.
#include <string>
#include <vector>
using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    int max = 0;
    for(int i = 0; i < progresses.size(); i++) {
    	//100이 아닌 99에서 이미 완료된 작업을 빼 speeds와 나누어 떨어지는지 여부를 판별하는 코드 불필요해짐
        int days = (99 - progresses[i])/speeds[i] + 1;
        //아직 배포한 기능이 없거나 이전 기능을 배포하는데 걸린 시간보다 더 오래 걸리는 기능이면 다른 날에 배포
        //이전 기능 배포하는데 걸린 시간보다 같거나 적게 걸리는 기능이면 같은 날에 배포
        if(answer.empty() || max < days)
            answer.push_back(1);
        else answer.back()++;
        //다른 날에 배포하면 max값 갱신
        if(max < days) max = days;
    }
    return answer;
}
*/
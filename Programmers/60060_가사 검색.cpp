// [60060] 가사 검색 : https://programmers.co.kr/learn/courses/30/lessons/60060
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

//알파벳 문자 총 26개
const int MAX = 26;

//트라이를 구성하는 노드
struct Node {
    bool isEnd;     //리프노드인지 여부
    Node *children[MAX];    //자식 노드가 있다면 알파벳 인덱스에 저장
    unordered_map<int, int> map;    //해시. {key, value}. key: 문자열 크기, value: key에 해당하는 문자열 개수
}; 

// 루트노드 생성
Node *newNode() {
    Node *root = new Node();
    root->isEnd = false;
    for(int i = 0; i < MAX; i++)
        root->children[i] = NULL;
    return root;
}

//문자열 삽입
void insert(Node *root, string s) {
    Node *node = root;
    int size = s.length();
    for(int i = 0; i < size; i++) {
        node->map[size]++;      //각 노드마다 문자열 크기를 key로 갖고 있는 해시에 1만큼 더한다.
        int idx = s[i] - 'a';
        if(!node->children[idx])
            node->children[idx] = new Node();
        node = node->children[idx];     //다음 노드 탐색
    }
    node->isEnd = true;     //마지막 노드 표시
}

//문자열 탐색
int search(Node *root, string s) {
    Node *node = root;
    int size = s.length();
    for(int i = 0; i < size; i++) {
        if(s[i] == '?') return node->map[size];
        int idx = s[i] - 'a';
        if(node->children[idx])
            node = node->children[idx];
        else return 0;
    }
    return 0;
}

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;
    Node *trie = newNode();
    Node *reversedTrie = newNode();
    for(int i = 0; i < words.size(); i++) {
        insert(trie, words[i]);
        reverse(words[i].begin(), words[i].end());
        insert(reversedTrie, words[i]);
    }
    for(int i = 0; i < queries.size(); i++) {
        if(queries[i][0] == '?') {
            reverse(queries[i].begin(), queries[i].end());
            answer.push_back(search(reversedTrie, queries[i]));
        } else answer.push_back(search(trie, queries[i]));
    }
    return answer;
}
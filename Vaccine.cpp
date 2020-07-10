/* C++
내용
	한 환자에게 접종하면 밀접하게 접촉하는 사람까지 전파되는 백신이 딱 한개 있다.

입력
	N : 환자들의 수 / M 환자 사이 관계의 수 (2 <= N,M <= 200,200)
	a b : 환자 a, b 가 밀접해 있음 (환자 사이 관계)

출력
	백신을 가장 많이 퍼뜨리기 위해 접종해야하는 환자 번호 
	접종했을 때 치료되는 환자의 수
	위 두 값을 공백으로 구분하여 출력
	만약 답이 여러 개 존재한다면 가장 앞 환자번호쌍만 출력
*/
#include <iostream>
#include <vector>
using namespace std;

vector<int> adj[200000]; //DFS) 노드와 그 노드와 이어진 노드 저장 공간
int count[200000]; // 접종했을 때 치료되는 환자의 수
bool chk[200000]; // DFS) 노드를 확인 했는지 여부
bool isFst = false; // count를 초기 노드에서만 증가시키기 위함
int tStart=0; // 초기 노드 값

// 깊이 우선 탐색 DFS
void dfs(int start){
	if(chk[start]) return; // DFS) 이미 확인했으면 끝냄
	
	// 초기 노드 값 저장
	if(isFst) { 
		tStart = start;
		isFst = false;
	}
	count[tStart]++; // count를 초기 노드에서만 증가
	chk[start] = 1; // DFS) 확인
	
	// DFS) 탐색
	for(int i = 0; i<adj[start].size(); ++i){
		int next = adj[start][i];
		dfs(next);
	}
}

int main(void){
	int N, M; cin >> N >> M;
	for(int i=0; i<M; ++i){
		int a, b; cin >> a >> b;
		adj[a-1].push_back(b-1);
		adj[b-1].push_back(a-1);
	}
	int Max = 0; // 접종했을 때 치료되는 환자의 최대값
	int wMax; // 접종했을 때 가장 많이 치료되는 환자 번호
	for(int i=0; i<N; ++i){
		isFst = true;
		dfs(i);
		if(Max<count[i]){
			Max = count[i];
			wMax = i;
		}
	}
	
	cout << wMax+1 << " " << Max;
}
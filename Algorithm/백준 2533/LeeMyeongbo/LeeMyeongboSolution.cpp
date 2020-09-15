#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#define MAX 1000001
using namespace std;

int N, v1, v2, ans;
bool is_early[MAX], visited[MAX];
vector<int> adj[MAX];

bool DFS(int cur_v) {
	bool early_adapter = false;
	for (int child_v : adj[cur_v]) {	// ���� ���(cur_v)�� ����� �ڽ� ���� �߿���
		if (!visited[child_v]) {
			visited[child_v] = true;
			if (!DFS(child_v))			// �� �ƴ��Ͱ� �ƴ� �ڽ� ��尡 �ִٸ� ���� ��带 �� �ƴ��ͷ� ����
				early_adapter = true;
		}
	}
	if (early_adapter)
		is_early[cur_v] = true;			// ���� ��带 �� �ƴ��ͷ� üũ
	return early_adapter;				// ���� ���(�ڽ� ��尡 ���� ���)���� �� �ƴ��ͷ� �������� ����!
}

int main() {
	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		scanf("%d %d", &v1, &v2);
		adj[v1].push_back(v2);
		adj[v2].push_back(v1);
	}
	visited[1] = true;
	DFS(1);								// 1�� ��带 root�� ���� ����
	for (int i = 1; i <= N; i++)
		if (is_early[i])				// �� �ƴ����� ��� ���� ��Ƹ�
			ans++;
	cout << ans;
	return 0;
}
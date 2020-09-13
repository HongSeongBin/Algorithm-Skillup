#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n, k, s, before, after, n1, n2;
vector<int> outdegree[401];				// �ش� ����(index)���κ��� ���� ������ ����� ������ ����
bool complete, visited[401];

void DFS(int n1, int n2) {
	if (n1 == n2) {						// ���� ������ Ÿ�� ��ǥ�� �ϴ� n2�� ������ �Ǿ��ٸ� n1�� n2���� ���� �Ͼ�ٴ� ���� ����
		complete = true;
		return;
	}
	
	for (int v : outdegree[n1]) {
		if (!visited[v] && !complete) {
			visited[v] = true;
			DFS(v, n2);					// ��� �������� �� �湮 üũ �� Ǯ�� ���;� �ߺ��湮�� ���� �� ����!
		}
	}
}

int main() {
	cin >> n >> k;
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &before, &after);
		outdegree[before].push_back(after);				// ���� ��� index�� ���� ��� �߰�
	}
	cin >> s;
	for (int i = 0; i < s; i++) {
		scanf("%d %d", &n1, &n2);
		DFS(n1, n2);									// n1�� n2���� ���� �Ͼ ������ ����
		if (complete) {
			printf("-1\n");
			memset(visited, false, sizeof(visited));	// �׻� Ž���� ������ �湮 üũ ������� ������
			complete = false;
			continue;
		}
		memset(visited, false, sizeof(visited));
		DFS(n2, n1);
		if (complete) {
			printf("1\n");
			memset(visited, false, sizeof(visited));
			complete = false;
			continue;
		}
		memset(visited, false, sizeof(visited));
		printf("0\n");
	}
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
#define MAX 500001
using namespace std;

int visited[MAX], edges[MAX], N, num, ans, cnt, cycle_start = -1, cycle_end = -1;
bool is_maphia[MAX], visited_sub[MAX];
queue<int> q;
vector<int> graph[MAX];

void DFS(int parent, int cur, vector<int>& sub_graph, vector<int>& cycle) {
	visited[cur] = ++cnt;
	sub_graph.push_back(cur);
	int freq = 0;

	for (int n : graph[cur]) {
		if (!visited[n])
			DFS(cur, n, sub_graph, cycle);
		else if (parent != n && visited[n] && visited[n] < visited[cur]) {		// ���̰� 3 �̻��� ����Ŭ�� �߰����� ���
			cycle_start = visited[n];
			cycle_end = visited[cur];					// ����Ŭ ���� ������ �湮 ��ȣ�� ������ ������ �湮 ��ȣ ����
		}
		else if (parent == n) {
			freq++;
			if (freq == 2) {							// ���̰� 2�� ����Ŭ�� �߰����� ���
				cycle_start = visited[n];
				cycle_end = visited[cur];
			}
		}
	}
	// ����Ŭ �����ϴ� ������ �湮 ��ȣ�� ����Ŭ�� ������ ������ �湮 ��ȣ ���̿� �ִ� ������ ��� cycle ���Ϳ� ����
	if (cycle_start != -1 && visited[cur] >= cycle_start && visited[cur] <= cycle_end) {
		cycle.push_back(cur);
		if (cycle_start == visited[cur])
			cycle_start = cycle_end = -1;
	}
}

int Solve() {
	for (int i = 1; i <= N; i++) {
		if (!visited[i]) {						// �湮���� ���� ������ ���� ��� DFS�� ����� ���� ��� Ž��
			vector<int> sub_graph, cycle;
			bool is_cycle = false;

			DFS(0, i, sub_graph, cycle);
			for(int n : sub_graph)
				if (graph[n].size() == 1) {		// ����� ���� ���� 1�� ���� ������ ���� ť�� ����
					q.push(n);
					is_maphia[n] = true;
				}
			while (!q.empty()) {				// BFS�� �̿��� �������� �̿��� ���Ǿ� �Ǻ� (����Ŭ ������ ������ Ž��)
				int v = q.front();
				visited_sub[v] = true;
				q.pop();

				for (int vertex : graph[v]) {
					edges[v]--;
					edges[vertex]--;			// ���� ������ ����� ���� ����
					if (edges[vertex] == 1) {	// ���� ���� �� ���ο� ���� ������ ����� �� ť�� ����
						q.push(vertex);
						bool found = true;
						for (int n : graph[vertex]) {
							if (is_maphia[n]) {
								found = false;
								break;
							}
						}
						if (found)
							is_maphia[vertex] = true;
					}
				}
			}
			for (int v : cycle) {					// ���� ����Ŭ�� ������ Ž��
				for(int n : graph[v])				// �� �������� ���켭 ������ ���Ǿ��� ������ �����Ѵٸ� ť�� ����
					if (is_maphia[n]) {
						q.push(v);
						visited_sub[v] = true;
						break;
					}
			}
			if (q.empty()) {						// ����Ŭ�� ������ ������ �� ���Ǿư� �ϳ��� ���ٸ� ����Ŭ �ƹ� �����̳� ť�� ����
				q.push(cycle[0]);
				visited_sub[cycle[0]] = true;
			}
			while (!q.empty()) {
				is_cycle = true;
				int v = q.front();
				q.pop();

				bool find = true;
				for (int vertex : graph[v]) {
					if (!visited_sub[vertex]) {
						q.push(vertex);
						visited_sub[vertex] = true;
					}
					if (is_maphia[vertex])
						find = false;
				}
				if (find)
					is_maphia[v] = true;
			}
		}
	}
	for (int i = 1; i <= N; i++)
		if (is_maphia[i])
			ans++;
	return ans;
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {				// ���� ���� = ���� ����
		scanf("%d", &num);
		graph[i].push_back(num);
		edges[i]++;
		graph[num].push_back(i);
		edges[num]++;
	}
	cout << Solve();
	return 0;
}
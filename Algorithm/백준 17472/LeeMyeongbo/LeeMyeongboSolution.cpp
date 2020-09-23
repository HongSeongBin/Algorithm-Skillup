#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

queue<pair<int, int>> q;
int N, M, map[100][100], visited[100][100], island_num, bridge[7][7], parent[7], ans;
const int dc[] = { 1, -1, 0, 0 }, dr[] = { 0, 0, 1, -1 };
vector<pair<int, pair<int, int>>> bridges;		// �� �� ���� �ٸ� ���̿� �� �� ���� ��ȣ ����

void count_island() {							// �� ���� + �� ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!map[i][j] || visited[i][j])	// �ٴٰų� �湮�� ���� skip
				continue;
			island_num++;
			q.push(make_pair(i, j));
			visited[i][j] = island_num;

			while (!q.empty()) {
				pair<int, int> p = q.front();
				q.pop();

				for (int d = 0; d < 4; d++) {	// �� �� �� �� ������ ����
					int R = p.first + dr[d];
					int C = p.second + dc[d];
					if (R >= 0 && R < N && C >= 0 && C < M && map[R][C] && !visited[R][C]) {
						q.push(make_pair(R, C));
						visited[R][C] = island_num;
					}
				}
			}
		}
	}
}

void count_bridge() {
	for (int i = 1; i < 7; i++)
		for (int j = 1; j < 7; j++)
			bridge[i][j] = 100;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!visited[i][j])					// �ٴ��� ������ skip
				continue;
			for (int d = 0; d < 4; d++) {		// �ش� �� �������� ��, ��, ��, �� �� �������� �� ���鼭 �ٸ� �������� �ּ� �ٸ� ���� ����	
				int R = i + dr[d];
				int C = j + dc[d];
				int length = 0;
				while (R >= 0 && R < N && C >= 0 && C < M) {
					if (visited[R][C] == visited[i][j])		// ���� ���� ������ ������ ��� �ٷ� break
						break;
					else if (visited[R][C]) {				// �ٸ� �� ������ ������ ��� �ٸ� ���� �ּڰ� ���� + break
						if (length >= 2)
							bridge[visited[i][j]][visited[R][C]] = min(bridge[visited[i][j]][visited[R][C]], length);
						break;
					}
					length++;
					R += dr[d];
					C += dc[d];
				}
			}
		}
	}
}

int Find(int n) {				// ���� �ֻ��� �θ� ���� Ž��
	if (parent[n] == n)
		return n;
	return parent[n] = Find(parent[n]);
}

void Union(int v1, int v2, int weight) {	// ũ�罺Į Ȱ��
	v1 = Find(v1);
	v2 = Find(v2);
	if (v1 == v2)
		return;
	if (v1 > v2)
		parent[v1] = v2;
	else
		parent[v2] = v1;
	ans += weight;
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];
	
	count_island();
	count_bridge();

	for (int i = 0; i < 7; i++)
		parent[i] = i;

	for (int i = 1; i <= island_num; i++)
		for (int j = i + 1; j <= island_num; j++)
			if (bridge[i][j] < 100)					// �� �� ���̿� �ٸ��� ���� �� �ִ� ��� (�ٸ� ����, (���� ��ȣ�� ��, ���� ��ȣ�� ��)) ���·� ����
				bridges.push_back(make_pair(bridge[i][j], make_pair(i, j)));
	sort(bridges.begin(), bridges.end());			// �ٸ� ���� ������������ ����

	for (auto v : bridges)
		Union(v.second.first, v.second.second, v.first);	// MST (���Ͽ� ���ε�)

	for (int i = 1; i <= island_num; i++)			// ���������� ����� ���� ����
		Find(i);

	for (int i = 1; i <= island_num; i++) {			// ���� �ٸ��� ������� ���� ���� �����Ѵٸ� �ٷ� -1
		if (parent[i] != 1) {
			cout << -1;
			return 0;
		}
	}
	cout << ans;
	return 0;
}
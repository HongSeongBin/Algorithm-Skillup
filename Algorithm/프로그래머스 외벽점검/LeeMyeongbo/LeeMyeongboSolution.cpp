#include <iostream>
#include <vector>
using namespace std;

int answer = -1;
char wall[205];                 // �ܺ��� ���� (0 �̸� ����, 1�̸� ���)
bool visited_dist[8];           // ģ�� �湮 üũ

// visited_weak : �湮�� ��� ���� ��, start_point : ��� ���� �߿��� Ž�� ���� ��ġ
void DFS(int n, int depth, vector<int>& weak, vector<int>& dist, int visited_weak, int start_point) {
    if (weak.size() <= visited_weak) {                      // �湮�� ��� ���� ���� ���� ��� ���� �� �̻��� �Ǹ� �ּڰ� ����
        if (answer == -1)
            answer = depth;
        answer = depth < answer ? depth : answer;           // ���� = ���� ģ���� ��
        return;
    }
    
    for (unsigned int i = 0; i < dist.size(); i++) {        // ���� ������� dist ���Ϳ� ����� �� ��ŭ �ܺ� Ž��
        if (!visited_dist[i]) {
            visited_dist[i] = true;                         // �湮 üũ

            int j = start_point, cover = 0;                 // cover : ��� ���� �߰� �� ������ ����
            for (int d = 0; d <= dist[i]; d++) {            // �ش� ģ���� �̵� ���� �Ÿ���ŭ �̵�
                if (wall[j] == 1)
                    cover++;
                j = (j + 1) % n;                            // �ܺ��� ���� (���� ���� �� �ٽ� ó������ ���ƿ;� ��)
            }
            while(!wall[j])                                 // ���� ��� ���� �߰��� �� ���� j �̵�
                j = (j + 1) % n;

            DFS(n, depth + 1, weak, dist, visited_weak + cover, j);
            visited_dist[i] = false;
        }
    }
}

int solution(int n, vector<int> weak, vector<int> dist) {
    for (auto w : weak) 
        wall[w] = 1;                                // ����� �������� 1�� ����
    
    for (unsigned int i = 0; i < weak.size(); i++)
        DFS(n, 0, weak, dist, 0, weak[i]);

    return answer;
}
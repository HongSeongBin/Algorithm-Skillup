#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    int r, c, cnt;              // ���� ������ �� ������, ���� ������ �� ������ ��ǥ
    bool garo;                  // ���θ� true, ���θ� false
};
queue<Node> q;
bool visited[2][100][100];      // ���� ������ ���� [0][r][c]��, ���� ������ �� [1][r][c]�� �湮 üũ

int solution(vector<vector<int>> board) {
    int N = board.size();
    int dir[2] = { 1, -1 };
    q.push({ 0, 0, 0, true });
    visited[0][0][0] = true;

    while (!q.empty()) {
        Node node = q.front();
        q.pop();
        if ((node.r + 1 == N - 1 && node.c == N - 1) || (node.r == N - 1 && node.c + 1 == N - 1))
            return node.cnt;
        if (node.garo) {                                                                                // ���� ����� ���
            if (node.c + 2 < N && !visited[0][node.r][node.c + 1] && !board[node.r][node.c + 2]) {      // �������� �̵� ��
                visited[0][node.r][node.c + 1] = true;
                q.push({ node.r, node.c + 1, node.cnt + 1, true });
            }
            if (node.c - 1 >= 0 && !visited[0][node.r][node.c - 1] && !board[node.r][node.c - 1]) {     // �������� �̵� ��
                visited[0][node.r][node.c - 1] = true;
                q.push({ node.r, node.c - 1, node.cnt + 1, true });
            }
            for (int d = 0; d < 2; d++) {
                int R = node.r + dir[d];
                if (R >= 0 && R < N && !visited[0][R][node.c] && !board[R][node.c] && !board[R][node.c + 1]) {    // ����, �������� �̵� ��
                    visited[0][R][node.c] = true;
                    q.push({ R, node.c, node.cnt + 1, true });
                }
            }
            if (node.r + 1 < N && !board[node.r + 1][node.c] && !board[node.r + 1][node.c + 1]) {       // �� ���� �ƴϸ鼭 �κ� �Ʒ� 2ĭ�� �� ĭ�� ���
                if (!visited[1][node.r][node.c]) {                                                      // ���� �� �������� �ð� ���� ȸ�� ��
                    visited[1][node.r][node.c] = true;
                    q.push({ node.r, node.c, node.cnt + 1, false });
                }
                if (!visited[1][node.r][node.c + 1]) {                                                  // ������ �� �������� �ݽð� ���� ȸ�� ��
                    visited[1][node.r][node.c + 1] = true;
                    q.push({ node.r, node.c + 1, node.cnt + 1, false });
                }
            }
            if (node.r - 1 >= 0 && !board[node.r - 1][node.c] && !board[node.r - 1][node.c + 1]) {      // �� ���� �ƴϸ鼭 �κ� �� 2ĭ�� �� ĭ�� ���
                if (!visited[1][node.r - 1][node.c]) {                                                  // ���� �� �������� �ݽð� ���� ȸ�� ��
                    visited[1][node.r - 1][node.c] = true;
                    q.push({ node.r - 1, node.c, node.cnt + 1, false });
                }
                if (!visited[1][node.r - 1][node.c + 1]) {                                              // ������ �� �������� �ð� ���� ȸ�� ��
                    visited[1][node.r - 1][node.c + 1] = true;
                    q.push({ node.r - 1, node.c + 1, node.cnt + 1, false });
                }
            }
        }
        else {                                                                                          // ���� ����� ���
            for (int d = 0; d < 2; d++) {
                int C = node.c + dir[d];
                if (C >= 0 && C < N && !board[node.r][C] && !board[node.r + 1][C] && !visited[1][node.r][C]) {      // ����, �������� �̵� ��
                    visited[1][node.r][C] = true;
                    q.push({ node.r, C, node.cnt + 1, false });
                }
            }
            if (node.r + 2 < N && !board[node.r + 2][node.c] && !visited[1][node.r + 1][node.c]) {      // �������� �̵��� ���
                visited[1][node.r + 1][node.c] = true;
                q.push({ node.r + 1, node.c, node.cnt + 1, false });
            }
            if (node.r - 1 >= 0 && !board[node.r - 1][node.c] && !visited[1][node.r - 1][node.c]) {     // �������� �̵��� ���
                visited[1][node.r - 1][node.c] = true;
                q.push({ node.r - 1, node.c, node.cnt + 1, false });
            }
            if (node.c - 1 >= 0 && !board[node.r][node.c - 1] && !board[node.r + 1][node.c - 1]) {      // �� ������ �ƴϸ鼭 �κ� ���� 2ĭ�� �� ĭ�� ���
                if (!visited[0][node.r][node.c - 1]) {                                                  // ���� �� �������� �ð� ���� ȸ�� ��
                    visited[0][node.r][node.c - 1] = true;
                    q.push({ node.r, node.c - 1, node.cnt + 1, true });
                }
                if (!visited[0][node.r + 1][node.c - 1]) {                                              // �Ʒ��� �� �������� �ݽð� ���� ȸ�� ��
                    visited[0][node.r + 1][node.c - 1] = true;
                    q.push({ node.r + 1, node.c - 1, node.cnt + 1, true });
                }
            }
            if (node.c + 1 < N && !board[node.r][node.c + 1] && !board[node.r + 1][node.c + 1]) {       // �� �������� �ƴϸ鼭 �κ� ������ 2ĭ�� �� ĭ�� ���
                if (!visited[0][node.r][node.c]) {                                                      // ���� �� �������� �ݽð� ���� ȸ�� ��
                    visited[0][node.r][node.c] = true;
                    q.push({ node.r, node.c, node.cnt + 1, true });
                }
                if (!visited[0][node.r + 1][node.c]) {                                                  // �Ʒ��� �� �������� �ð� ���� ȸ�� ��
                    visited[0][node.r + 1][node.c];
                    q.push({ node.r + 1, node.c, node.cnt + 1, true });
                }
            }
        }
    }
    return 0;
}
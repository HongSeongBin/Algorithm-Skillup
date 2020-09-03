#include <vector>
using namespace std;
                                                       // tmp[0][r][c] : ���������� (r,c)�� ������ ���� ��� ��
int MOD = 20170805, dp[500][500], tmp[2][500][500];    // tmp[1][r][c] : �Ʒ������� (r,c)�� ������ ���� ��� ��
                                                       // dp[r][c] : (r,c)�� �� ���� �� ��� �� ����
int solution(int m, int n, vector<vector<int>> city_map) {
    dp[0][0] = 1;
    tmp[0][0][0] = tmp[1][0][0] = 0;

    bool is_blocked = false;
    for (int i = 1; i < n; i++) {                           // city_map���� �� ���� ó��
        if (city_map[0][i] != 1 && !is_blocked) {
            dp[0][i] = tmp[0][0][i] = 1;
            tmp[1][0][i] = 0;
        }
        else {                                              // ������� ��ġ�� ������ �� �ڿ� ĭ ��� 0���� ó��
            is_blocked = true;
            dp[0][i] = tmp[0][0][i] = tmp[1][0][i] = 0;
        }
    }
    is_blocked = false;
    for (int i = 1; i < m; i++) {                           // city_map���� �� ���� �� ó��
        if (city_map[i][0] != 1 && !is_blocked) {
            dp[i][0] = tmp[1][i][0] = 1;
            tmp[0][i][0] = 0;
        }
        else {                                              // ������� ��ġ�� ������ �� �ؿ� ĭ ��� 0���� ó��
            is_blocked = true;
            dp[i][0] = tmp[0][i][0] = tmp[1][i][0] = 0;
        }
    }

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (city_map[i][j] == 1)                                        // ���� ��ġ�� ������� ��ġ�� dp�� tmp ��� 0���� ��
                dp[i][j] = tmp[0][i][j] = tmp[1][i][j] = 0;
            else if (city_map[i - 1][j] != 2 && city_map[i][j - 1] != 2) {  // ���� ��ġ�� �ٷ� ���� ��ġ�� ���� ��ġ�� ��� ������ ������ �ƴ� ��
                dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;             // ���� ĭ�� �̸������ ����� �հ� ���� ĭ�� �̸������ ����� �� ����
                tmp[0][i][j] = dp[i][j - 1];
                tmp[1][i][j] = dp[i - 1][j];
            }
            else if (city_map[i - 1][j] != 2 && city_map[i][j - 1] == 2) {  // ���� ��ġ�� ���� ��ġ���� ������ ������ ��
                dp[i][j] = (dp[i - 1][j] + tmp[0][i][j - 1]) % MOD;         // ���������� ���� ĭ�� ������ ���� ��� �� + ���� ĭ�� ��� ��
                tmp[0][i][j] = tmp[0][i][j - 1];
                tmp[1][i][j] = dp[i - 1][j];
            }
            else if (city_map[i - 1][j] == 2 && city_map[i][j - 1] != 2) {  // ���� ��ġ�� ���� ��ġ���� ������ ������ ��
                dp[i][j] = (tmp[1][i - 1][j] + dp[i][j - 1]) % MOD;         // �Ʒ������� ���� ĭ�� ������ ���� ��� �� + ���� ĭ�� ��� ��
                tmp[0][i][j] = dp[i][j - 1];
                tmp[1][i][j] = tmp[1][i - 1][j];
            }
            else {                                                          // ���� ��ġ���� ���ʰ� ���� ��� ������ ������ ���
                dp[i][j] = (tmp[1][i - 1][j] + tmp[0][i][j - 1]) % MOD;     // ���������� ���� ĭ�� ������ ���� ��� �� + �Ʒ������� ���� ĭ�� ������ ���� ��� ��
                tmp[0][i][j] = tmp[0][i][j - 1];
                tmp[1][i][j] = tmp[1][i - 1][j];
            }
        }
    }
    return dp[m - 1][n - 1];
}
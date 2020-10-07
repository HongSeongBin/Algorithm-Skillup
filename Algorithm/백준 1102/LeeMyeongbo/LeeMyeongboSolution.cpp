#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int N, P, W[17][17], dp[1 << 17], num, working;
char c;

int DFS(int num, int working)
{
	if (num >= P)
		return 0;

	int& res = dp[working];
	if (res != -1)
		return res;
	
	for (int i = 1; i <= N; i++)
		if (working & (1 << (i - 1)))						// i�� �����Ұ� ���� ���� ��
			for (int j = 1; j <= N; j++)
				if (!(working & (1 << (j - 1))))			// j�� �����Ҵ� ���峭 ��� (���峭 �����Ҹ� �ϳ��ϳ� ���Ǹ� ��ġ�� ������ �ּڰ� ����)
				{
					if(res == -1)
						res = W[i][j] + DFS(num + 1, working | (1 << (j - 1)));
					else
						res = min(res, W[i][j] + DFS(num + 1, working | (1 << (j - 1))));
				}
	return res;
}

int main() 
{
	cin >> N;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> W[i][j];
	for (int i = 1; i <= N; i++)
	{
		cin >> c;
		if (c == 'Y')
		{
			num++;
			working = working | (1 << (i - 1));
		}
	}
	cin >> P;
	memset(dp, -1, sizeof(dp));
	cout << DFS(num, working);
	return 0;
}
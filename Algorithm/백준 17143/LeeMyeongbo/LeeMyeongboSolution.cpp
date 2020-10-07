#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

struct Map
{
	int speed, cur_dir, size;
};
vector<Map> map[101][101];
vector<pair<int, pair<int, int>>> info;					// info�� (��� ũ��, (��, ��)) ���·� ����
int R, C, M, r, c, s, d, z, cur_place, ans;

void catch_shark(int cur_place)
{
	bool caught = false;								// ��� ������ true
	for (int r = 1; r <= R && !caught; r++)
	{
		if (map[r][cur_place].size())					// ���� ������ 1����� ������ ���Ǹ� �ش� ĭ�� �� ���� ���
		{
			int shark = map[r][cur_place][0].size;
			ans += shark;
			map[r][cur_place].clear();					// ũ�� ���ϰ� �ش� ĭ�� ��� ����
			for(int i = 0; i < (int)info.size(); i++)	// info���� ���ŵ� ��� ��������� ��!
				if (info[i].first == shark)
				{
					info.erase(info.begin() + i);
					caught = true;
					break;
				}
		}
	}
}

void move_shark()
{
	vector<Map> tmp;
	for (int i = 0; i < (int)info.size(); i++)									// ��� ��� �̵�
	{
		tmp.push_back(map[info[i].second.first][info[i].second.second][0]);
		map[info[i].second.first][info[i].second.second].clear();				// ���� ��� �ִ� �ڸ� ����
		int sero_move = tmp[i].speed % ((R - 1) * 2);
		int garo_move = tmp[i].speed % ((C - 1) * 2);
		if (tmp[i].cur_dir < 3)													// ���η� ������ ���
		{
			for (int m = 0; m < sero_move; )
			{
				if (tmp[i].cur_dir == 1)
				{
					if (info[i].second.first - 1 >= 1)
					{
						info[i].second.first--;
						m++;
					}
					else
						tmp[i].cur_dir = 2;
				}
				else
				{
					if (info[i].second.first + 1 <= R)
					{
						info[i].second.first++;
						m++;
					}
					else
						tmp[i].cur_dir = 1;
				}
			}
		}
		else											// ���η� ������ ���
		{
			for (int m = 0; m < garo_move; )
			{
				if (tmp[i].cur_dir == 4)
				{
					if (info[i].second.second - 1 >= 1)
					{
						info[i].second.second--;
						m++;
					}
					else
						tmp[i].cur_dir = 3;
				}
				else
				{
					if (info[i].second.second + 1 <= C)
					{
						info[i].second.second++;
						m++;
					}
					else
						tmp[i].cur_dir = 4;
				}
			}
		}
	}

	for (int i = 0; i < (int)tmp.size(); i++)			// �� �� ���ο� ��ġ�� �ٽ� ����
		map[info[i].second.first][info[i].second.second].push_back(tmp[i]);

	for (int r = 1; r <= R; r++)
		for (int c = 1; c <= C; c++)
			while (map[r][c].size() > 1)				// map ��� ���켭 �� 2���� �̻� �ִ� ���� �� ������ ����
			{
				if (map[r][c][0].size > map[r][c][1].size)
				{
					for (int i = 0; i < (int)info.size(); i++)
						if (info[i].first == map[r][c][1].size)		// info�� �����Ϸ��� ��� ����
						{
							info.erase(info.begin() + i);
							break;
						}
					map[r][c].erase(map[r][c].begin() + 1);			// map�� �ش� ��ġ�� ��� ����
				}
				else
				{
					for (int i = 0; i < (int)info.size(); i++)
						if (info[i].first == map[r][c][0].size)
						{
							info.erase(info.begin() + i);
							break;
						}
					map[r][c].erase(map[r][c].begin());
				}					
			}
}

int Solve()
{
	while (cur_place <= C)
	{
		cur_place++;
		catch_shark(cur_place);
		move_shark();
	}
	return ans;
}

int main()
{
	scanf("%d %d %d", &R, &C, &M);
	for (int i = 0; i < M; i++)
	{
		scanf("%d %d %d %d %d", &r, &c, &s, &d, &z);
		map[r][c].push_back({ s, d, z });
		info.push_back({ z, {r, c} });
	}
	printf("%d", Solve());
	return 0;
}
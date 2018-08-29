#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

void dfs(vector<vector<int>> &map, int n, int m, const pair<int, int> &xy);
int zero_count(vector<vector<int>> &map, int n, int m);

vector<pair<int, int>> d = { { -1,0 },{ 0,1 },{ 1,0 },{ 0,-1 } }; // 4 Way Direction

int main() {

	int n = 0, m = 0; // n : col, m : row
	scanf("%d %d\n", &n, &m);

	vector<vector<int>> map(n + 1, vector<int>(m + 1, -1));       // 원본
	vector<vector<int>> temp_map(n + 1, vector<int>(m + 1, -1));  // 계산본
	vector<pair<int, int>> zero; // '0' 위치 저장
	vector<pair<int, int>> two;  // '2' 위치 저장

	int temp;
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			scanf("%d", &temp);
			map[i][j] = temp;
		}
	}

	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			if (map[i][j] == 0) {
				zero.push_back({ i,j });
			}
			else if (map[i][j] == 2) {
				two.push_back({ i,j });
			}
		}
	}

	int count;
	int maximum = -10;

	// 완전탐색 : 1을 모든 위치에 두고 다 계산해본다.
	for (int i = 0; i < zero.size(); i++) {
		for (int j = i + 1; j < zero.size(); j++) {
			for (int k = j + 1; k < zero.size(); k++) {
				temp_map.assign(map.begin(), map.end()); // 원본 -> 계산본

				// 1 세팅
				temp_map[zero[i].first][zero[i].second] = 1;
				temp_map[zero[j].first][zero[j].second] = 1;
				temp_map[zero[k].first][zero[k].second] = 1;

				// 모든 2의 위치에서 DFS 실시
				for (int i = 0; i < two.size(); i++) {
					dfs(temp_map, n, m, two[i]);
				}

				count = zero_count(temp_map, n, m);

				if (maximum < count) {
					maximum = count;
				}
			}
		}
	}
	printf("%d\n", maximum);

	return 0;
}

void dfs(vector<vector<int>>& map, int n, int m, const pair<int, int>& xy)
{
	int col, row;
	for (int i = 0; i < 4; i++) {
		col = xy.first + d[i].first;
		row = xy.second + d[i].second;
		if (0 < col && col < n + 1 && 0 < row && row < m + 1) {
			if (map[col][row] == 0) {
				map[col][row] = 2;
				dfs(map, n, m, { col, row });
			}
		}
	}
}
int zero_count(vector<vector<int>>& map, int n, int m)
{
	int count = 0;
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			if (map[i][j] == 0) {
				count++;
			}
		}
	}

	return count;
}


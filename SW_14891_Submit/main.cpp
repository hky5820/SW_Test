#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> gear(5, vector<int>(8, -1));
vector<pair<int, int>> we(5);
vector<int> check(5, -1);
void rotate(int gear_no, int rot);

int main() {

	vector<pair<int, int>> s;

	for (int i = 1; i < 5; i++) {
		we[i].first = 6;
		we[i].second = 2;
	}

	int temp;
	for (int i = 1; i < 5; i++) {
		for (int j = 0; j < 8; j++) {
			scanf("%1d", &temp);
			gear[i][j] = temp;
		}
	}

	int k = 0, n, r;
	scanf("%d\n", &k);
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &n, &r);
		s.push_back({ n,r });
	}

	int No, R;
	for (int i = 0; i < k; i++) {
		No = s[i].first; R = s[i].second;

		rotate(No, R);

		for (int i = 1; i < 5; i++) {
			check[i] = -1;
		}
	}

	int sum = 0;
	for (int i = 1; i < 5; i++) {
		if (gear[i][(we[i].first + 2) % 8] == 1) {
			sum += pow(2, i - 1);
		}
	}

	printf("%d\n", sum);

	return 0;
}

void rotate(int gear_no, int rot)
{
	if (gear_no - 1 > 0) {
		if (check[gear_no - 1] == -1) {
			if (gear[gear_no][we[gear_no].first] != gear[gear_no - 1][we[gear_no - 1].second]) {
				check[gear_no] = 1;
				rotate(gear_no - 1, -rot);
			}
		}
	}
	if (gear_no + 1 < 5) {
		if (check[gear_no + 1] == -1) {
			if (gear[gear_no][we[gear_no].second] != gear[gear_no + 1][we[gear_no + 1].first]) {
				check[gear_no] = 1;
				rotate(gear_no + 1, -rot);
			}
		}
	}

	if (rot == -1) {
		we[gear_no].first = (we[gear_no].first - rot) % 8;
		we[gear_no].second = (we[gear_no].second - rot) % 8;
	}
	else {
		we[gear_no].first -= rot;
		we[gear_no].second -= rot;

		if (we[gear_no].first  < 0) we[gear_no].first += 8;
		if (we[gear_no].second  < 0)  we[gear_no].second += 8;
	}
	;
	return;
}

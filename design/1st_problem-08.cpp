#include<iostream>

using namespace std;

int main() {
	int origin_matrix[5][5];
	int kernel[2][2];
	int pos_x, pos_y;
	int conv = 0;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cin >> origin_matrix[i][j];
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cin >> kernel[i][j];
		}
	}
	cin >> pos_x >> pos_y;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (pos_x + j < 0 || pos_y + i < 0 || pos_x + j >4 || pos_y + i >4) {
				continue;
			}
			conv += kernel[i][j] * origin_matrix[pos_y + i][pos_x + j];
		}
	}
	cout << conv;
}

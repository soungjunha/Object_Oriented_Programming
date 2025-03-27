#include<iostream>

using namespace std;

int main() {
	int matric1[3][3];
	int matric2[3][3];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> matric1[i][j];
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> matric2[i][j];
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << matric1[i][j] + matric2[i][j];
			if (j != 2)
				cout << ' ';
		}
		cout << endl;
	}

}

#include <iostream>

using namespace std;

int main() {
	int n;
	int flower[1000];
	int flower_buffer[1000];

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> flower[i];
		flower_buffer[i] = flower[i];
	}

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (flower[j] > flower[j + 1]) {
				int tmp = flower[j];
				flower[j] = flower[j + 1];
				flower[j + 1] = tmp;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (flower_buffer[i] == flower[j]) {
				cout << j + 1 << ' ';
				flower[j] = 0;
				break;
			}
		}
	}

}
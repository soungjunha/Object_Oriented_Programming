#include<iostream>

using namespace std;

int main() {

	int n, m;
	char operater;
	char yn;

	do
	{
		cin >> n;
		cin >> m;
		cin >> operater;
		if (operater == '+')
		{
			cout << n + m << endl;
		}
		else if (operater == '-')
		{
			cout << n - m << endl;
		}
		else if (operater == '*')
		{
			cout << n * m << endl;
		}
		else if (operater == '/')
		{
			if (m == 0) {
				break;
			}
			cout << n / m << endl;
		}

		cin >> yn;
	} while (yn == 'y');

}

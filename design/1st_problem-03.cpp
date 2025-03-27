#include<iostream>

using namespace std;

int main() {

	int n, m, d = 0;
	char bin[21];
	char oct[10];
	char hex[10];

	cin >> n;

	m = n;
	while (m != 0)
	{
		bin[d] = (m % 2) + '0';
		m /= 2;
		d++;
	}
	for (int i = 0; i < d / 2; i++)
	{
		char tmp = bin[i];
		bin[i] = bin[d - 1 - i];
		bin[d - 1 - i] = tmp;
	}
	bin[d] = '\0';

	d = 0;
	m = n;
	while (m != 0)
	{
		oct[d] = (m % 8) + '0';
		m /= 8;
		d++;
	}
	for (int i = 0; i < d / 2; i++)
	{
		char tmp = oct[i];
		oct[i] = oct[d - 1 - i];
		oct[d - 1 - i] = tmp;
	}
	oct[d] = '\0';

	d = 0;
	m = n;
	while (m != 0)
	{
		int div = m % 16;
		if (div < 10)
		{
			hex[d] = div + '0';
		}
		else if (div >= 10)
		{
			hex[d] = (div - 10) + 'A';
		}
		m /= 16;
		d++;
	}
	for (int i = 0; i < d / 2; i++)
	{
		char tmp = hex[i];
		hex[i] = hex[d - 1 - i];
		hex[d - 1 - i] = tmp;
	}
	hex[d] = '\0';

	cout << bin << endl << oct << endl << hex;
}

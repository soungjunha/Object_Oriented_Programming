#include<iostream>

using namespace std;

int main() {

	int n;
	char title[100];

	cin >> n;

	for (int i = 0; i < n; i++)
	{

		cin >> title;

		for (int j = 0; title[j] != '\0'; j++)
		{
			title[j] += 32;
		}

		cout << title << endl;

	}

}

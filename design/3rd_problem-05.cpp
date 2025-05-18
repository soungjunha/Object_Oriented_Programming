#include <iostream>
#include<string>
using namespace std;

int main() {
	int n;
	int total = 0;
	string s;
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cin >> s;
		try {
			total += stoi(s);
		}
		catch (...) {
			cout << "Error occurred" << endl;
		}
	}
	cout << "Total sum: " << total;

	return 0;
}
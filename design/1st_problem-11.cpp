#include<iostream>

using namespace std;

int main() {

	int n;
	int seat;

	cin >> n;

	for (int i = 0; i < n; i++)
	{

		cin >> seat;

		if (seat % 2 == 0)
			cout << "Available";
		else
			cout << "Not Available";
		cout << endl;

	}

}

#include<iostream>

using namespace std;

int main() {

	int money = 30000;
	int distance = 0;
	int cost;

	cout << money << endl;
	while (1)
	{
		cin >> distance;
		if (distance == -1) {
			cout << "Program exit.";
			break;
		}
		if (distance > 200 || distance < 2) {
			cout << money << endl;
			break;
		}
		if (distance <= 10) {
			cost = 1000;
		}
		else
		{
			cost = 1000 + (((distance - 10) / 5) * 150);
		}
		if (money - cost < 0) {
			cout << money << endl;
			break;
		}
		else
		{
			money -= cost;
			cout << cost << ' ' << money << endl;
		}
	}

}

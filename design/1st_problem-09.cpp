#include<iostream>

using namespace std;

int main() {
	int n;
	int score;
	int scholarship_num = 0;
	int scholarship_money = 1;

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> score;
		if (score >= 60) {
			scholarship_num++;
			scholarship_money *= score;
		}
	}

	cout << scholarship_num << endl << scholarship_money;

}

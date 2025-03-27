#include<iostream>

using namespace std;

int main() {

	for (int i = 0; i < 5; i++)
	{
		char name[6];
		int score;
		char grade;

		cin >> name >> score;

		if (score >= 90) {
			grade = 'A';
		}
		else if (score >= 80) {
			grade = 'B';
		}
		else if (score >= 70) {
			grade = 'C';
		}
		else if (score >= 60) {
			grade = 'D';
		}
		else {
			grade = 'F';
		}
		cout << name << ' ' << score << ' ' << grade << endl;
	}

}

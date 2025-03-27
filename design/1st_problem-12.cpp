#include<iostream>
using namespace std;
int main() {
	cout << fixed;
	cout.precision(3);

	int n;
	char gpa[3];
	int credit;
	int total_credit = 0;
	double total_gpa = 0;

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> gpa >> credit;
		total_credit += credit;
		if (gpa[0] == 'A')
		{
			if (gpa[1] == '+') {
				total_gpa += credit * 4.5;
			}
			else {
				total_gpa += credit * 4.0;
			}
		}
		else if (gpa[0] == 'B')
		{
			if (gpa[1] == '+') {
				total_gpa += credit * 3.5;
			}
			else {
				total_gpa += credit * 3.0;
			}
		}
		else if (gpa[0] == 'C')
		{
			if (gpa[1] == '+') {
				total_gpa += credit * 2.5;
			}
			else {
				total_gpa += credit * 2.0;
			}
		}
	}

	cout << total_gpa / total_credit << endl;
	cout << total_credit;

	return 0;
}

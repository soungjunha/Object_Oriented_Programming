#include<iostream>

using namespace std;

int main() {
	int n;
	int num;
	int digit_sum = 0;

	cin >> num;

	for (int i = 0; i < num; i++)
	{
		digit_sum = 0;
		cin >> n;
		while (n != 0)
		{
			digit_sum += n % 10;
			n /= 10;
		}
		cout << digit_sum << endl;
	}

}

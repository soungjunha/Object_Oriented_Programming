#include<iostream>
using namespace std;

void strpa(char* str, int& j, int& num) {
	if (num < 10) {
		str[j] = num + '0';
		j++;
	}
	else
	{
		str[j] = (num / 10) + '0';
		str[j + 1] = (num % 10) + '0';
		j += 2;
	}
}

int main() {
	cout << fixed;
	cout.precision(3);

	int n;
	char input_str[41];
	char encoding_str[81];
	char buffer = '\0';
	int input_byte = 0, encoding_byte = 0;
	double Compression_ratio;

	cin >> n;
	cin >> input_str;

	input_byte = n * 2;

	int i = 0, j = 0;
	int cnt = 0;
	buffer = input_str[0];

	while (input_str[i] != '\0')
	{
		if (buffer == input_str[i]) {
			cnt++;
		}
		else
		{
			encoding_str[j] = buffer;
			j++;
			strpa(encoding_str, j, cnt);
			buffer = input_str[i];
			cnt = 1;
		}
		i++;
	}
	encoding_str[j] = buffer;
	j++;
	strpa(encoding_str, j, cnt);
	encoding_str[j] = '\0';
	j = 0;
	while (encoding_str[j] != '\0')
	{
		if (encoding_str[j] >= '0' && encoding_str[j] <= '9') {
			encoding_byte++;
		}
		else
		{
			encoding_byte += 2;
		}
		j++;
	}
	Compression_ratio = (double)input_byte / (double)encoding_byte;
	cout << encoding_str << endl << Compression_ratio;

	return 0;
}

#include<iostream>

using namespace std;

class MyString {
private:
	char* str;
	int len;

public:
	MyString(const char* s = "") {
		// Allocate memory and copy string
		for (len = 0; s[len] != '\0'; len++);
		str = new char[len + 1];
		int i;
		for (i = 0; i < len; i++)
		{
			str[i] = s[i];
		}
		str[i] = '\0';
	}

	MyString(const MyString& other) {
		len = other.len;
		str = new char[len + 1];
		for (int i = 0; i <= len; ++i) {
			str[i] = other.str[i];
		}
	}

	~MyString() {
		// Free dynamically allocated memory
		delete[] str;
	}

	MyString& operator=(const MyString& other) {
		if (this == &other)
			return *this;

		char* new_str = new char[other.len + 1];
		for (int i = 0; i <= other.len; ++i) {
			new_str[i] = other.str[i];
		}

		delete[] this->str;

		this->str = new_str;
		this->len = other.len;

		return *this;
	}


	MyString operator+(const MyString& other) const {
		// Concatenate two strings and return a new MyString object
		char* result = new char[this->len + other.len + 1];

		for (int i = 0; i < this->len; i++) {
			result[i] = this->str[i];
		}
		for (int i = 0; i < other.len; i++) {
			result[this->len + i] = other.str[i];
		}

		result[this->len + other.len] = '\0';

		MyString tmp(result);
		delete[] result;
		return tmp;

	}

	bool operator==(const MyString& other) const {
		// Compare the contents of two strings

		if (this->len != other.len) return false;
		for (int i = 0; i < this->len; i++) {
			if (this->str[i] != other.str[i]) return false;
		}
		return true;
	}

	friend ostream& operator<<(ostream& os, const MyString& s) {
		// Output string using ostream
		return os << s.str;
	}
};


int main() {

	char buffer[100];
	cin.getline(buffer, 100);
	MyString str1(buffer);
	cin.getline(buffer, 100);
	MyString str2(buffer);

	while (true) {
		cin.getline(buffer, 100);//cin,cin.getline 혼용시 버퍼에 개행문자잔재가능성 있음으로 혼용시 주의!!
		if (buffer[0] == '0') {
			cout << "Program exit!";
			break;
		}
		else if (buffer[0] == '+')
		{
			cout << str1 + str2 << endl;
		}
		else if (buffer[0] == '=')
		{
			if (str1 == str2)
				cout << "Equal" << endl;
			else
				cout << "Not equal" << endl;
		}
		else if (buffer[0] == 'f')
		{
			cin.getline(buffer, 100);
			MyString tmp(buffer);
			str1 = tmp;
		}
		else if (buffer[0] == 's')
		{
			cin.getline(buffer, 100);
			MyString tmp(buffer);
			str2 = tmp;
		}
	}

}

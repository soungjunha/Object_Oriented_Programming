#include<iostream>

using namespace std;

class MyStringStack {
private:
	char* stack[10];
	int top;

public:
	MyStringStack() {
		top = 0;
	}

	~MyStringStack() {

	}

	bool push(const char* str) {
		if (!isFull()) {
			int len;
			for (len = 0; str[len] != '\0'; len++);
			this->stack[top] = new char[len + 1];
			for (int i = 0; i < len; i++)
			{
				stack[top][i] = str[i];
			}
			stack[top][len] = '\0';
			top++;
			return true;
		}
		else
			return false;

	}

	bool pop(char* str) {
		if (!isEmpty())
		{
			int len;
			cout << this->stack[--top] << endl;
			for (len = 0; str[len] != '\0'; len++);
			delete[] stack[top];
			return true;
		}
		else
			return false;
	}

	bool isEmpty() {
		if (top == 0)
			return true;
		else
			return false;
	}

	bool isFull() {
		if (top == 10)
			return true;
		else
			return false;
	}
};

int main() {

	char buffer[100];
	MyStringStack stack;

	while (1)
	{
		cin >> buffer;
		if (buffer[0] == 'e' && buffer[1] == 'n' && buffer[2] == 'd') {
			break;
		}
		if (!stack.push(buffer))
			cout << "Stack is full!" << endl;
	}

	cout << "Output (in reverse order):" << endl;
	for (int i = 0; stack.pop(buffer); i++);

}

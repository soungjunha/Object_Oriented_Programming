#include <iostream>   // ������� ���� �������
#include <string>     // ���ڿ� ó���� ���� �������
using namespace std;

// ============================================
// Stack Ŭ����: ���� ���ð� ���� ������ ���� ����
// ============================================
class Stack {
public:
    Stack();  // ������ ����

    // ���� ���� ����
    void pushInt(int v);     // ������ ���ÿ� �߰� (push)
    int popInt();            // ���ÿ��� ������ �����ϰ� ��ȯ (pop)
    int topInt();            // ������ �ֻ�� ������ ��ȯ (��ȸ��)
    bool isEmptyInt();       // ���� ������ ����ִ��� Ȯ��

    // ���� ���� ���� (������ �� ��ȣ��)
    void pushChar(char c);   // ���ڸ� ���ÿ� �߰�
    char popChar();          // ���ÿ��� ���ڸ� �����ϰ� ��ȯ
    char topChar();          // ���� �ֻ�� ���� ��ȯ
    bool isEmptyChar();      // ���� ������ ����ִ��� Ȯ��

private:
    int stack_int[100];      // ���� ���� �迭 (�ִ� 100�� ����)
    char stack_char[100];    // ���� ���� �迭 (�ִ� 100�� ����)
    int top_int;             // ���� ������ �ֻ�� �ε���
    int top_char;            // ���� ������ �ֻ�� �ε���
};

// Stack Ŭ���� ������: ���� �ʱ�ȭ
Stack::Stack() : top_int(-1), top_char(-1) {}

// ���� ���ÿ� �� �߰�
void Stack::pushInt(int v) {
    if (top_int < 99) {           // ������ ���� ���� �ʾҴ��� Ȯ��
        stack_int[++top_int] = v; // top ��ġ�� ������Ű�� �� ����
    }
}

// ���� ���ÿ��� �� ���� �� ��ȯ
int Stack::popInt() {
    if (top_int >= 0) {           // ������ ������� ������
        return stack_int[top_int--]; // �ֻ�� �� ��ȯ �� top ����
    }
    return -1; // ���� ó��: ������ ��������� -1 ��ȯ
}

// ���� ���� �ֻ�� �� ��ȸ
int Stack::topInt() {
    if (top_int >= 0) {
        return stack_int[top_int];
    }
    return -1; // ���� ó��: ������ ��������� -1 ��ȯ
}

// ���� ������ ����ִ��� Ȯ��
bool Stack::isEmptyInt() {
    return top_int == -1;
}

// ���� ���ÿ� ���� �߰�
void Stack::pushChar(char c) {
    if (top_char < 99) {
        stack_char[++top_char] = c;
    }
}

// ���� ���ÿ��� ���� ���� �� ��ȯ
char Stack::popChar() {
    if (top_char >= 0) {
        return stack_char[top_char--];
    }
    return '\0';  // ���� ó��: ������ ��������� �� ���� ��ȯ
}

// ���� ���� �ֻ�� ���� ��ȸ
char Stack::topChar() {
    if (top_char >= 0) {
        return stack_char[top_char];
    }
    return '\0';  // ���� ó��
}

// ���� ������ ����ִ��� Ȯ��
bool Stack::isEmptyChar() {
    return top_char == -1;
}

// ===================================================
// VariableTable Ŭ����: ���� �̸��� ���� ���� �� ��ȸ
// ===================================================
class VariableTable {
public:
    VariableTable();                    // ������
    void set(string name, int value);   // ���� ����
    int get(string name);               // ���� ��ȸ

private:
    string name[100];   // ���� �̸� ���� �迭
    int value[100];     // ���� �� ���� �迭
    int cnt;            // ���� ����� ���� ����
};

// ������: ���� ���� �ʱ�ȭ
VariableTable::VariableTable() : cnt(0) {}

// ���� ���� �Լ�
void VariableTable::set(string name, int value) {
    for (int i = 0; i < cnt; ++i) {
        if (this->name[i] == name) {   // �̹� �����ϴ� ������ �� ������Ʈ
            this->value[i] = value;
            return;
        }
    }
    // ���ο� ������� �迭�� �߰�
    this->name[cnt] = name;
    this->value[cnt] = value;
    cnt++;
}

// ���� ��ȸ �Լ�
int VariableTable::get(string name) {
    for (int i = 0; i < cnt; ++i) {
        if (this->name[i] == name) {   // ���� �̸��� ��ġ�ϸ� �� ��ȯ
            return this->value[i];
        }
    }
    return 0;  // ������� ���� ������ 0���� ó��
}

// ============================================
// Calculator Ŭ����: ������ �ٽ� ��� ����
// ============================================
class Calculator {
public:
    void process(string line);   // �Է� ���� �Ľ� �� ��� ����

private:
    Stack stack;                 // ���� �ν��Ͻ�
    VariableTable varTable;      // ���� ���̺� �ν��Ͻ�

    string rmv_space(const string& str);              // ���� ���� �Լ�
    int operator_precedence(char op);                 // ������ �켱���� ��ȯ
    bool convert_postfix(const string& expr, string postfix[]); // ����ǥ��� ��ȯ
    int evaluate_postfix(string postfix[], int size); // ����ǥ��� ���
};

// ���ڿ����� ���� ���� �Լ�
string Calculator::rmv_space(const string& str) {
    string result = "";
    for (int i = 0; i < str.length(); i++) {
        if (!(str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
            result += str[i];
    }
    return result;
}

// �������� �켱������ ��ȯ
int Calculator::operator_precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;  // ��Ÿ ����
}

// ����ǥ����� ����ǥ������� ��ȯ
bool Calculator::convert_postfix(const string& expr, string postfix[]) {
    int idx = 0;  // postfix �迭 �ε���

    for (int i = 0; i < expr.length(); ) {
        char c = expr[i];

        // ������ ��� ó�� (���� �ڸ��� ����)
        if (c >= '0' && c <= '9') {
            string num = "";
            while (i < expr.length() && expr[i] >= '0' && expr[i] <= '9') {
                num += expr[i++];
            }
            postfix[idx++] = num;
        }
        // ������ (�ҹ���) ó��
        else if (c >= 'a' && c <= 'z') {
            postfix[idx++] = string(1, c);
            i++;
        }
        // ���� ��ȣ ó��
        else if (c == '(') {
            stack.pushChar(c);
            i++;
        }
        // �ݴ� ��ȣ ó��
        else if (c == ')') {
            bool found = false;
            while (!stack.isEmptyChar()) {
                char top = stack.popChar();
                if (top == '(') {
                    found = true;
                    break;
                }
                postfix[idx++] = string(1, top);
            }
            if (!found) return false;  // ��ȣ ����ġ ����
            i++;
        }
        // ������ ó��
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!stack.isEmptyChar() && operator_precedence(stack.topChar()) >= operator_precedence(c)) {
                postfix[idx++] = string(1, stack.popChar());
            }
            stack.pushChar(c);
            i++;
        }
        else {
            return false;  // ��ȿ���� ���� ����
        }
    }

    // ���ÿ� �����ִ� ������ �߰�
    while (!stack.isEmptyChar()) {
        char top = stack.popChar();
        if (top == '(') return false;  // ��ȣ ����
        postfix[idx++] = string(1, top);
    }

    postfix[idx] = "";  // ���� ǥ��
    return true;
}

// ���ڿ� ���ڸ� ������ ��ȯ�ϴ� �Լ�
int stringToInt(const string& s) {
    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        num = num * 10 + (s[i] - '0');
    }
    return num;
}

// ����ǥ��� ��� �Լ�
int Calculator::evaluate_postfix(string postfix[], int size) {
    for (int i = 0; i < size; i++) {
        string token = postfix[i];
        if (token == "") break;

        if (token[0] >= '0' && token[0] <= '9') {
            stack.pushInt(stringToInt(token));
        }
        else if (token[0] >= 'a' && token[0] <= 'z') {
            int val = varTable.get(token);
            stack.pushInt(val);
        }
        else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/') {
            int b = stack.popInt();
            int a = stack.popInt();
            int result = 0;

            if (token[0] == '+') result = a + b;
            else if (token[0] == '-') result = a - b;
            else if (token[0] == '*') result = a * b;
            else if (token[0] == '/') result = (b == 0) ? 0 : a / b;

            stack.pushInt(result);
        }
    }
    return stack.popInt();  // ���� ��� ��ȯ
}

// �� �� �Է��� ó���ϴ� �Լ�
void Calculator::process(string line) {
    line = rmv_space(line);  // ���� ����

    if (line == "") {
        cout << 0 << endl;
        return;
    }

    string varName = "";
    string expr = line;

    // '=' ��ȣ�� ���� �Ҵ����� Ȯ��
    int eqPos = -1;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '=') {
            eqPos = i;
            break;
        }
    }

    // ���� �Ҵ��� ���
    if (eqPos != -1) {
        varName = line.substr(0, eqPos);
        expr = line.substr(eqPos + 1);

        if (varName.length() != 1 || !(varName[0] >= 'a' && varName[0] <= 'z')) {
            cout << 0 << endl;
            return;
        }
    }

    // ����ǥ��� ��ȯ �� ���
    string postfix[200];
    bool valid = convert_postfix(expr, postfix);
    if (!valid) {
        cout << 0 << endl;
        return;
    }

    int result = evaluate_postfix(postfix, 200);

    // ���� ���� �Ǵ� ��� ���
    if (varName != "") {
        varTable.set(varName, result);
        cout << varName << " = " << result << endl;
    }
    else {
        cout << result << endl;
    }
}

// ========================
// main �Լ�: ���α׷� ����
// ========================
int main() {
    Calculator calculator;   // ���� ��ü ����
    string cmd;
    while (true) {
        getline(cin, cmd);   // ����� �Է� �ޱ�
        if (cmd == "exit") { // 'exit' �Է� �� ����
            break;
        }
        calculator.process(cmd);  // �Է� ó��
    }
    return 0;
}

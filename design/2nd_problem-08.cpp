#include <iostream>   // 입출력을 위한 헤더파일
#include <string>     // 문자열 처리를 위한 헤더파일
using namespace std;

// ============================================
// Stack 클래스: 정수 스택과 문자 스택을 각각 관리
// ============================================
class Stack {
public:
    Stack();  // 생성자 선언

    // 정수 스택 연산
    void pushInt(int v);     // 정수를 스택에 추가 (push)
    int popInt();            // 스택에서 정수를 제거하고 반환 (pop)
    int topInt();            // 스택의 최상단 정수를 반환 (조회만)
    bool isEmptyInt();       // 정수 스택이 비어있는지 확인

    // 문자 스택 연산 (연산자 및 괄호용)
    void pushChar(char c);   // 문자를 스택에 추가
    char popChar();          // 스택에서 문자를 제거하고 반환
    char topChar();          // 스택 최상단 문자 반환
    bool isEmptyChar();      // 문자 스택이 비어있는지 확인

private:
    int stack_int[100];      // 정수 스택 배열 (최대 100개 저장)
    char stack_char[100];    // 문자 스택 배열 (최대 100개 저장)
    int top_int;             // 정수 스택의 최상단 인덱스
    int top_char;            // 문자 스택의 최상단 인덱스
};

// Stack 클래스 생성자: 스택 초기화
Stack::Stack() : top_int(-1), top_char(-1) {}

// 정수 스택에 값 추가
void Stack::pushInt(int v) {
    if (top_int < 99) {           // 스택이 가득 차지 않았는지 확인
        stack_int[++top_int] = v; // top 위치를 증가시키고 값 저장
    }
}

// 정수 스택에서 값 제거 후 반환
int Stack::popInt() {
    if (top_int >= 0) {           // 스택이 비어있지 않으면
        return stack_int[top_int--]; // 최상단 값 반환 후 top 감소
    }
    return -1; // 에러 처리: 스택이 비어있으면 -1 반환
}

// 정수 스택 최상단 값 조회
int Stack::topInt() {
    if (top_int >= 0) {
        return stack_int[top_int];
    }
    return -1; // 에러 처리: 스택이 비어있으면 -1 반환
}

// 정수 스택이 비어있는지 확인
bool Stack::isEmptyInt() {
    return top_int == -1;
}

// 문자 스택에 문자 추가
void Stack::pushChar(char c) {
    if (top_char < 99) {
        stack_char[++top_char] = c;
    }
}

// 문자 스택에서 문자 제거 후 반환
char Stack::popChar() {
    if (top_char >= 0) {
        return stack_char[top_char--];
    }
    return '\0';  // 에러 처리: 스택이 비어있으면 널 문자 반환
}

// 문자 스택 최상단 문자 조회
char Stack::topChar() {
    if (top_char >= 0) {
        return stack_char[top_char];
    }
    return '\0';  // 에러 처리
}

// 문자 스택이 비어있는지 확인
bool Stack::isEmptyChar() {
    return top_char == -1;
}

// ===================================================
// VariableTable 클래스: 변수 이름과 값을 저장 및 조회
// ===================================================
class VariableTable {
public:
    VariableTable();                    // 생성자
    void set(string name, int value);   // 변수 저장
    int get(string name);               // 변수 조회

private:
    string name[100];   // 변수 이름 저장 배열
    int value[100];     // 변수 값 저장 배열
    int cnt;            // 현재 저장된 변수 개수
};

// 생성자: 변수 개수 초기화
VariableTable::VariableTable() : cnt(0) {}

// 변수 저장 함수
void VariableTable::set(string name, int value) {
    for (int i = 0; i < cnt; ++i) {
        if (this->name[i] == name) {   // 이미 존재하는 변수면 값 업데이트
            this->value[i] = value;
            return;
        }
    }
    // 새로운 변수라면 배열에 추가
    this->name[cnt] = name;
    this->value[cnt] = value;
    cnt++;
}

// 변수 조회 함수
int VariableTable::get(string name) {
    for (int i = 0; i < cnt; ++i) {
        if (this->name[i] == name) {   // 변수 이름이 일치하면 값 반환
            return this->value[i];
        }
    }
    return 0;  // 선언되지 않은 변수는 0으로 처리
}

// ============================================
// Calculator 클래스: 계산기의 핵심 기능 구현
// ============================================
class Calculator {
public:
    void process(string line);   // 입력 라인 파싱 및 계산 수행

private:
    Stack stack;                 // 스택 인스턴스
    VariableTable varTable;      // 변수 테이블 인스턴스

    string rmv_space(const string& str);              // 공백 제거 함수
    int operator_precedence(char op);                 // 연산자 우선순위 반환
    bool convert_postfix(const string& expr, string postfix[]); // 후위표기법 변환
    int evaluate_postfix(string postfix[], int size); // 후위표기법 계산
};

// 문자열에서 공백 제거 함수
string Calculator::rmv_space(const string& str) {
    string result = "";
    for (int i = 0; i < str.length(); i++) {
        if (!(str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
            result += str[i];
    }
    return result;
}

// 연산자의 우선순위를 반환
int Calculator::operator_precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;  // 기타 문자
}

// 중위표기식을 후위표기식으로 변환
bool Calculator::convert_postfix(const string& expr, string postfix[]) {
    int idx = 0;  // postfix 배열 인덱스

    for (int i = 0; i < expr.length(); ) {
        char c = expr[i];

        // 숫자인 경우 처리 (여러 자리수 지원)
        if (c >= '0' && c <= '9') {
            string num = "";
            while (i < expr.length() && expr[i] >= '0' && expr[i] <= '9') {
                num += expr[i++];
            }
            postfix[idx++] = num;
        }
        // 변수명 (소문자) 처리
        else if (c >= 'a' && c <= 'z') {
            postfix[idx++] = string(1, c);
            i++;
        }
        // 여는 괄호 처리
        else if (c == '(') {
            stack.pushChar(c);
            i++;
        }
        // 닫는 괄호 처리
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
            if (!found) return false;  // 괄호 불일치 오류
            i++;
        }
        // 연산자 처리
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!stack.isEmptyChar() && operator_precedence(stack.topChar()) >= operator_precedence(c)) {
                postfix[idx++] = string(1, stack.popChar());
            }
            stack.pushChar(c);
            i++;
        }
        else {
            return false;  // 유효하지 않은 문자
        }
    }

    // 스택에 남아있는 연산자 추가
    while (!stack.isEmptyChar()) {
        char top = stack.popChar();
        if (top == '(') return false;  // 괄호 오류
        postfix[idx++] = string(1, top);
    }

    postfix[idx] = "";  // 종료 표시
    return true;
}

// 문자열 숫자를 정수로 변환하는 함수
int stringToInt(const string& s) {
    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        num = num * 10 + (s[i] - '0');
    }
    return num;
}

// 후위표기식 계산 함수
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
    return stack.popInt();  // 최종 결과 반환
}

// 한 줄 입력을 처리하는 함수
void Calculator::process(string line) {
    line = rmv_space(line);  // 공백 제거

    if (line == "") {
        cout << 0 << endl;
        return;
    }

    string varName = "";
    string expr = line;

    // '=' 기호로 변수 할당인지 확인
    int eqPos = -1;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '=') {
            eqPos = i;
            break;
        }
    }

    // 변수 할당인 경우
    if (eqPos != -1) {
        varName = line.substr(0, eqPos);
        expr = line.substr(eqPos + 1);

        if (varName.length() != 1 || !(varName[0] >= 'a' && varName[0] <= 'z')) {
            cout << 0 << endl;
            return;
        }
    }

    // 후위표기법 변환 및 계산
    string postfix[200];
    bool valid = convert_postfix(expr, postfix);
    if (!valid) {
        cout << 0 << endl;
        return;
    }

    int result = evaluate_postfix(postfix, 200);

    // 변수 저장 또는 결과 출력
    if (varName != "") {
        varTable.set(varName, result);
        cout << varName << " = " << result << endl;
    }
    else {
        cout << result << endl;
    }
}

// ========================
// main 함수: 프로그램 실행
// ========================
int main() {
    Calculator calculator;   // 계산기 객체 생성
    string cmd;
    while (true) {
        getline(cin, cmd);   // 사용자 입력 받기
        if (cmd == "exit") { // 'exit' 입력 시 종료
            break;
        }
        calculator.process(cmd);  // 입력 처리
    }
    return 0;
}

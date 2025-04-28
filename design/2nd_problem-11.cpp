#include <iostream>   // 표준 입출력 사용
#include <string>     // 문자열 처리를 위한 string 클래스
using namespace std;

// 연결 리스트(Node) 구조체 정의: 문자(char)와 다음 노드(next)를 가짐
struct Node {
	char ch;        // 저장할 문자
	Node* next;     // 다음 노드를 가리키는 포인터
	// 생성자: 문자 초기화, next는 nullptr로 설정
	Node(char c) : ch(c), next(nullptr) {}
};

// 텍스트 에디터 클래스 정의
class TextEditor {
private:
	Node* head;        // Dummy head node (문자열의 시작을 표시)
	Node* cursorPrev;  // 커서 바로 이전 노드를 가리키는 포인터

public:
	TextEditor();      // 생성자: head와 커서 초기화
	~TextEditor();     // 소멸자: 모든 노드 메모리 해제

	void insert(char c);    // 커서 위치에 문자 삽입
	void deleteChar();      // 커서 왼쪽 문자 삭제
	void moveLeft();        // 커서를 왼쪽으로 한 칸 이동
	void moveRight();       // 커서를 오른쪽으로 한 칸 이동
	void print() const;     // 현재 텍스트 출력
};

// 생성자 구현: Dummy head 노드를 생성하고 커서를 head로 초기화
TextEditor::TextEditor() {
	head = new Node('\0');   // Dummy head node 생성 (실제 데이터 아님)
	cursorPrev = head;       // 커서를 head 이전으로 설정
}

// 소멸자 구현: 연결 리스트 전체 순회하며 메모리 해제
TextEditor::~TextEditor() {
	Node* current = head;
	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
}

// 커서 위치에 문자 삽입
void TextEditor::insert(char c) {
	Node* newNode = new Node(c);   // 새로운 노드 생성
	newNode->next = cursorPrev->next;  // 새 노드의 next를 기존 커서 다음 노드로 설정
	cursorPrev->next = newNode;        // 커서 이전 노드가 새 노드를 가리키게 설정
	cursorPrev = newNode;              // 커서를 새로 삽입한 노드로 이동
}

// 커서 왼쪽 문자 삭제
void TextEditor::deleteChar() {
	if (cursorPrev == head) return;  // 삭제할 문자가 없으면 종료

	// 커서 이전 노드를 찾기 위해 head부터 순회
	Node* prev = head;
	while (prev->next != cursorPrev) {
		prev = prev->next;
	}

	Node* toDelete = cursorPrev;         // 삭제할 노드 지정
	prev->next = cursorPrev->next;       // 이전 노드가 삭제할 노드의 다음 노드를 가리키도록 설정
	cursorPrev = prev;                   // 커서를 왼쪽으로 이동
	delete toDelete;                     // 노드 삭제
}

// 커서를 왼쪽으로 한 칸 이동
void TextEditor::moveLeft() {
	if (cursorPrev != head) {            // head보다 왼쪽으로 이동 불가
		Node* prev = head;
		while (prev->next != cursorPrev) {  // 커서 이전 노드를 찾음
			prev = prev->next;
		}
		cursorPrev = prev;                // 커서를 왼쪽으로 이동
	}
}

// 커서를 오른쪽으로 한 칸 이동
void TextEditor::moveRight() {
	if (cursorPrev->next != nullptr) {   // 커서 오른쪽에 노드가 있을 때만 이동
		cursorPrev = cursorPrev->next;
	}
}

// 현재 텍스트 전체 출력
void TextEditor::print() const {
	Node* current = head->next;   // Dummy head 다음 노드부터 출력
	while (current != nullptr) {
		cout << current->ch;
		current = current->next;
	}
	cout << endl;
}

int main() {
	TextEditor editor;   // 텍스트 에디터 객체 생성
	string command;      // 사용자 명령어 저장
	char ch;

	while (true) {
		getline(cin, command);   // 한 줄 입력받기

		if (command == "exit") {   // 프로그램 종료 명령
			cout << "Program terminated!" << endl;
			break;
		}
		else if (command.substr(0, 6) == "insert") {   // 삽입 명령: "insert x"
			editor.insert(command[7]);   // 7번째 문자 삽입
		}
		else if (command == "delete") {  // 삭제 명령
			editor.deleteChar();
		}
		else if (command == "move left") {  // 커서 왼쪽 이동
			editor.moveLeft();
		}
		else if (command == "move right") { // 커서 오른쪽 이동
			editor.moveRight();
		}
		else if (command == "print") {      // 현재 텍스트 출력
			editor.print();
		}
	}

	return 0;
}
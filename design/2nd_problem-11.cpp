#include <iostream>
#include <string>
using namespace std;

struct Node {
	char ch;
	Node* next;
	Node(char c) : ch(c), next(nullptr) {}
};

class TextEditor {
private:
	Node* head;       // Dummy head node
	Node* cursorPrev; // Pointer to node before the cursor

public:
	TextEditor();           // Constructor: Initialize head and cursor
	~TextEditor();          // Destructor: Delete all nodes

	void insert(char c);    // Insert character c at cursor position
	void deleteChar();      // Delete character before cursor
	void moveLeft();        // Move cursor one character to the left
	void moveRight();       // Move cursor one character to the right
	void print() const;     // Print current text
};
TextEditor::TextEditor() {
	head = new Node('\0');
	cursorPrev = head;
}
TextEditor::~TextEditor() {
	Node* current = head;
	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
}
void TextEditor::insert(char c) {
	Node* newNode = new Node(c);
	newNode->next = cursorPrev->next;
	cursorPrev->next = newNode;
	cursorPrev = newNode;
}
void TextEditor::deleteChar() {
	if (cursorPrev == head) return;

	Node* prev = head;
	while (prev->next != cursorPrev) {
		prev = prev->next;
	}

	Node* toDelete = cursorPrev;
	prev->next = cursorPrev->next;
	cursorPrev = prev;
	delete toDelete;
}

void TextEditor::moveLeft() {
	if (cursorPrev != head) {
		Node* prev = head;
		while (true) {
			if (prev->next == cursorPrev) {
				break;
			}
			prev = prev->next;
		}
		cursorPrev = prev;
	}
}
void TextEditor::moveRight() {
	if (cursorPrev->next != nullptr) {
		cursorPrev = cursorPrev->next;
	}
}
void TextEditor::print() const {
	Node* current = head->next;
	while (current != nullptr) {
		cout << current->ch;
		current = current->next;
	}
	cout << endl;
}

int main() {
	TextEditor editor;
	string command;
	char ch;
	while (true) {
		getline(cin, command);
		if (command == "exit") {
			cout << "Program terminated!" << endl;
			break;
		}
		else if (command.substr(0, 6) == "insert") {
			editor.insert(command[7]);
		}
		else if (command == "delete") {
			editor.deleteChar();
		}
		else if (command == "move left") {
			editor.moveLeft();
		}
		else if (command == "move right") {
			editor.moveRight();
		}
		else if (command == "print") {
			editor.print();
		}
	}

	return 0;
}

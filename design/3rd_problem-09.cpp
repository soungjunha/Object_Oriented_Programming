#include <iostream>   // ǥ�� ����� ��Ʈ�� ����� ���� ��� ���� ����
#include <string>     // std::string ����� ���� ��� ���� ����
using namespace std;  // std ���ӽ����̽��� �̸��� ���� ���

// �л�(Student) �߻� �⺻ Ŭ���� ����
class Student {
protected:
    string name;     // �л� �̸�
    int id;          // �л� �й�(ID)
    string major;    // ����

public:
    // ������: �̸�, �й�, ������ �޾� �ʱ�ȭ
    Student(const string& n, int i, const string& m)
        : name(n), id(i), major(m) {
    }

    virtual ~Student() {}  // ���� �Ҹ���

    int getID() const {   // �й� ��ȯ ������
        return id;
    }

    virtual void PrintInfo() const = 0;  // ���� ���� �Լ�: �л� ���� ���

    // ���� ������ �����ε�: �й��� ������ ���� �л����� �Ǵ�
    bool operator==(const Student& other) const {
        return id == other.id;
    }
};

// �кλ�(Undergraduate) Ŭ����: Student���� �Ļ�
class Undergraduate : public Student {
private:
    int year;  // �г�

public:
    // ������: �θ� ������ ȣ�� �� �г� �ʱ�ȭ
    Undergraduate(const string& n, int i, const string& m, int y)
        : Student(n, i, m), year(y) {
    }

    // �л� ���� ��� ����
    void PrintInfo() const override {
        cout << "[Undergraduate] Name: " << name
            << ", ID: " << id
            << ", Major: " << major
            << ", Year: " << year
            << endl;
    }
};

// ���п���(Graduate) Ŭ����: Student���� �Ļ�
class Graduate : public Student {
private:
    string advisor;  // ���� ����

public:
    // ������: �θ� ������ ȣ�� �� ���� ���� �ʱ�ȭ
    Graduate(const string& n, int i, const string& m, const string& a)
        : Student(n, i, m), advisor(a) {
    }

    // �л� ���� ��� ����
    void PrintInfo() const override {
        cout << "[Graduate] Name: " << name
            << ", ID: " << id
            << ", Major: " << major
            << ", Advisor: " << advisor
            << endl;
    }
};

// ���� ���� ����Ʈ�� ��� ����ü ����
struct Node {
    Student* student;  // �л� ��ü�� ���� ������
    Node* next;        // ���� ��带 ����Ű�� ������

    // ������: �л� ������ �ʱ�ȭ, next�� nullptr�� ����
    Node(Student* s) : student(s), next(nullptr) {}
};

// �л� ���� ����Ʈ Ŭ����
class StudentList {
private:
    Node* head;  // ����Ʈ�� ù ��° ��带 ����Ű�� ������

public:
    // ������: head�� nullptr�� �ʱ�ȭ
    StudentList() : head(nullptr) {}

    // �Ҹ���: ����Ʈ�� ��� ���� �л� ��ü ����
    ~StudentList() {
        Node* curr = head;
        while (curr) {
            Node* temp = curr;         // ���� ��� ����
            curr = curr->next;         // ���� ���� �̵�
            delete temp->student;      // �л� ��ü �޸� ����
            delete temp;               // ��� �޸� ����
        }
    }

    // �л� �߰�: �й� ������������ ����
    void AddStudent(Student* s) {
        Node* newNode = new Node(s);  // ������ �� ��� ����

        // ����Ʈ�� ����ų�, ���ο� �л��� �й��� head���� ������ �� �տ� ����
        if (!head || s->getID() < head->student->getID()) {
            newNode->next = head;
            head = newNode;
            return;
        }

        // �߰� �Ǵ� ���� ������ ��ġ Ž��
        Node* curr = head;
        while (curr->next && curr->next->student->getID() < s->getID()) {
            curr = curr->next;
        }
        // �� ��带 ���� ��� �ڿ� ����
        newNode->next = curr->next;
        curr->next = newNode;
    }

    // ��� �л� ���� ���
    void PrintAll() const {
        Node* curr = head;
        while (curr) {
            curr->student->PrintInfo();  // �� ����� �л� ���� ���
            curr = curr->next;           // ���� ���� �̵�
        }
    }

    // Ư�� �й� �л� �˻� �� ���
    void FindStudent(int targetID) const {
        Node* curr = head;
        while (curr) {
            if (curr->student->getID() == targetID) {
                curr->student->PrintInfo();  // ã���� ���� ��� �� ��ȯ
                return;
            }
            curr = curr->next;  // ���� ���� �̵�
        }
        // �˻� ���� �� �޽��� ���
        cout << "Student not found" << endl;
    }
};

int main() {
    string command;      // ����� ��� ���� ����
    StudentList list;    // �л� ���� ����Ʈ ��ü ����

    // ��� �Է� ����
    while (cin >> command) {
        if (command == "ADD") {  // ADD ��� ó��
            string type;         // �л� ����(UG/GR)
            cin >> type;
            string name, major;  // �̸�, ����
            int id;              // �й�

            cin >> name >> id >> major;

            if (type == "UG") {  // �кλ� �߰�
                int year;        // �г�
                cin >> year;
                Student* s = new Undergraduate(name, id, major, year);
                list.AddStudent(s);
            }
            else if (type == "GR") {  // ���п��� �߰�
                string advisor;  // ���� ����
                cin >> advisor;
                Student* s = new Graduate(name, id, major, advisor);
                list.AddStudent(s);
            }
        }
        else if (command == "PRINT") {  // PRINT ��� ó��: ��ü ���
            list.PrintAll();
        }
        else if (command == "FIND") {   // FIND ��� ó��: ���� �˻�
            int targetID;
            cin >> targetID;
            list.FindStudent(targetID);
        }
        else if (command == "EXIT") {   // EXIT ��� ó��: ���α׷� ����
            break;
        }
    }

    return 0;  // ���� �Լ� ����
}

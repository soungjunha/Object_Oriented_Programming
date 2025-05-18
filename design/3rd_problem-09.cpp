#include <iostream>   // 표준 입출력 스트림 사용을 위한 헤더 파일 포함
#include <string>     // std::string 사용을 위한 헤더 파일 포함
using namespace std;  // std 네임스페이스의 이름을 직접 사용

// 학생(Student) 추상 기본 클래스 선언
class Student {
protected:
    string name;     // 학생 이름
    int id;          // 학생 학번(ID)
    string major;    // 전공

public:
    // 생성자: 이름, 학번, 전공을 받아 초기화
    Student(const string& n, int i, const string& m)
        : name(n), id(i), major(m) {
    }

    virtual ~Student() {}  // 가상 소멸자

    int getID() const {   // 학번 반환 접근자
        return id;
    }

    virtual void PrintInfo() const = 0;  // 순수 가상 함수: 학생 정보 출력

    // 동등 연산자 오버로드: 학번이 같으면 같은 학생으로 판단
    bool operator==(const Student& other) const {
        return id == other.id;
    }
};

// 학부생(Undergraduate) 클래스: Student에서 파생
class Undergraduate : public Student {
private:
    int year;  // 학년

public:
    // 생성자: 부모 생성자 호출 및 학년 초기화
    Undergraduate(const string& n, int i, const string& m, int y)
        : Student(n, i, m), year(y) {
    }

    // 학생 정보 출력 구현
    void PrintInfo() const override {
        cout << "[Undergraduate] Name: " << name
            << ", ID: " << id
            << ", Major: " << major
            << ", Year: " << year
            << endl;
    }
};

// 대학원생(Graduate) 클래스: Student에서 파생
class Graduate : public Student {
private:
    string advisor;  // 지도 교수

public:
    // 생성자: 부모 생성자 호출 및 지도 교수 초기화
    Graduate(const string& n, int i, const string& m, const string& a)
        : Student(n, i, m), advisor(a) {
    }

    // 학생 정보 출력 구현
    void PrintInfo() const override {
        cout << "[Graduate] Name: " << name
            << ", ID: " << id
            << ", Major: " << major
            << ", Advisor: " << advisor
            << endl;
    }
};

// 단일 연결 리스트의 노드 구조체 정의
struct Node {
    Student* student;  // 학생 객체에 대한 포인터
    Node* next;        // 다음 노드를 가리키는 포인터

    // 생성자: 학생 포인터 초기화, next는 nullptr로 설정
    Node(Student* s) : student(s), next(nullptr) {}
};

// 학생 관리 리스트 클래스
class StudentList {
private:
    Node* head;  // 리스트의 첫 번째 노드를 가리키는 포인터

public:
    // 생성자: head를 nullptr로 초기화
    StudentList() : head(nullptr) {}

    // 소멸자: 리스트의 모든 노드와 학생 객체 해제
    ~StudentList() {
        Node* curr = head;
        while (curr) {
            Node* temp = curr;         // 현재 노드 보관
            curr = curr->next;         // 다음 노드로 이동
            delete temp->student;      // 학생 객체 메모리 해제
            delete temp;               // 노드 메모리 해제
        }
    }

    // 학생 추가: 학번 오름차순으로 삽입
    void AddStudent(Student* s) {
        Node* newNode = new Node(s);  // 삽입할 새 노드 생성

        // 리스트가 비었거나, 새로운 학생의 학번이 head보다 작으면 맨 앞에 삽입
        if (!head || s->getID() < head->student->getID()) {
            newNode->next = head;
            head = newNode;
            return;
        }

        // 중간 또는 끝에 삽입할 위치 탐색
        Node* curr = head;
        while (curr->next && curr->next->student->getID() < s->getID()) {
            curr = curr->next;
        }
        // 새 노드를 현재 노드 뒤에 연결
        newNode->next = curr->next;
        curr->next = newNode;
    }

    // 모든 학생 정보 출력
    void PrintAll() const {
        Node* curr = head;
        while (curr) {
            curr->student->PrintInfo();  // 각 노드의 학생 정보 출력
            curr = curr->next;           // 다음 노드로 이동
        }
    }

    // 특정 학번 학생 검색 및 출력
    void FindStudent(int targetID) const {
        Node* curr = head;
        while (curr) {
            if (curr->student->getID() == targetID) {
                curr->student->PrintInfo();  // 찾으면 정보 출력 후 반환
                return;
            }
            curr = curr->next;  // 다음 노드로 이동
        }
        // 검색 실패 시 메시지 출력
        cout << "Student not found" << endl;
    }
};

int main() {
    string command;      // 사용자 명령 저장 변수
    StudentList list;    // 학생 관리 리스트 객체 생성

    // 명령 입력 루프
    while (cin >> command) {
        if (command == "ADD") {  // ADD 명령 처리
            string type;         // 학생 유형(UG/GR)
            cin >> type;
            string name, major;  // 이름, 전공
            int id;              // 학번

            cin >> name >> id >> major;

            if (type == "UG") {  // 학부생 추가
                int year;        // 학년
                cin >> year;
                Student* s = new Undergraduate(name, id, major, year);
                list.AddStudent(s);
            }
            else if (type == "GR") {  // 대학원생 추가
                string advisor;  // 지도 교수
                cin >> advisor;
                Student* s = new Graduate(name, id, major, advisor);
                list.AddStudent(s);
            }
        }
        else if (command == "PRINT") {  // PRINT 명령 처리: 전체 출력
            list.PrintAll();
        }
        else if (command == "FIND") {   // FIND 명령 처리: 개별 검색
            int targetID;
            cin >> targetID;
            list.FindStudent(targetID);
        }
        else if (command == "EXIT") {   // EXIT 명령 처리: 프로그램 종료
            break;
        }
    }

    return 0;  // 메인 함수 종료
}

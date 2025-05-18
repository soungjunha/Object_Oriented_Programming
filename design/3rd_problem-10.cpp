#include <iostream>   // 표준 입출력 스트림 사용을 위한 헤더 파일
using namespace std;  // std 네임스페이스에 정의된 이름을 직접 사용

// 다항식의 각 항(term)을 나타내는 구조체
struct Term {
    int coef;      // 항의 계수(coefficient)
    int deg;       // 항의 차수(degree)
    Term* next;    // 다음 항을 가리키는 포인터

    // 생성자: 계수와 차수를 받아 초기화하고, next 포인터는 nullptr로 설정
    Term(int c, int d) : coef(c), deg(d), next(nullptr) {}
};

// 단일 변수 다항식을 연결 리스트로 구현하는 클래스
class Polynomial {
private:
    Term* head;  // 리스트의 첫 번째 항(head)을 가리키는 포인터

    // 항을 리스트에 삽입하거나, 같은 차수 항이 있으면 계수를 합산
    void insertTerm(int coef, int deg) {
        if (coef == 0)                // 계수가 0이면 리스트에 추가할 필요 없음
            return;
        if (!head || head->deg < deg) {  // 리스트가 비었거나 새 항의 차수가 더 크면
            Term* nt = new Term(coef, deg);  // 새 항 생성
            nt->next = head;                 // 기존 head를 뒤로 연결
            head = nt;                        // 새 항을 head로 설정
            return;
        }
        Term* cur = head;    // 현재 탐색 중인 노드
        Term* prev = nullptr;  // 이전 노드를 가리키는 포인터
        // 삽입 위치 또는 같은 차수 항 탐색 (차수 내림차순 유지)
        while (cur && cur->deg > deg) {
            prev = cur;
            cur = cur->next;
        }
        if (cur && cur->deg == deg) {   // 같은 차수의 항이 존재하면
            cur->coef += coef;          // 계수 합산
            if (cur->coef == 0) {       // 합산 후 0이 되면 노드 삭제
                if (prev) prev->next = cur->next;
                else      head = cur->next;
                delete cur;
            }
        }
        else {  // 같은 차수 항이 없으면 새 항을 중간에 삽입
            Term* nt = new Term(coef, deg);
            nt->next = cur;
            prev->next = nt;
        }
    }

public:
    // 기본 생성자: head를 nullptr로 초기화
    Polynomial() : head(nullptr) {}

    // 복사 생성자: 다른 다항식의 모든 항을 복사
    Polynomial(const Polynomial& other) : head(nullptr) {
        for (Term* cur = other.head; cur; cur = cur->next) {
            insertTerm(cur->coef, cur->deg);
        }
    }

    // 소멸자: 연결된 모든 Term 노드를 해제
    ~Polynomial() {
        Term* cur = head;
        while (cur) {
            Term* nxt = cur->next;
            delete cur;   // 현재 노드 메모리 해제
            cur = nxt;    // 다음 노드로 이동
        }
    }

    // 사용자 호출 함수: 새로운 항을 다항식에 추가
    void addTerm(int coef, int deg) {
        insertTerm(coef, deg);
    }

    // 덧셈 연산자 오버로드: 두 다항식을 더한 결과를 반환
    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;     // 결과를 저장할 다항식 객체
        Term* p1 = head;       // 첫 번째 다항식 탐색용 포인터
        Term* p2 = other.head; // 두 번째 다항식 탐색용 포인터

        // 두 리스트를 병합하면서 차수를 비교해 삽입
        while (p1 && p2) {
            if (p1->deg == p2->deg) {
                result.insertTerm(p1->coef + p2->coef, p1->deg);
                p1 = p1->next;
                p2 = p2->next;
            }
            else if (p1->deg > p2->deg) {
                result.insertTerm(p1->coef, p1->deg);
                p1 = p1->next;
            }
            else {
                result.insertTerm(p2->coef, p2->deg);
                p2 = p2->next;
            }
        }
        // 남은 항이 있으면 결과에 추가
        while (p1) {
            result.insertTerm(p1->coef, p1->deg);
            p1 = p1->next;
        }
        while (p2) {
            result.insertTerm(p2->coef, p2->deg);
            p2 = p2->next;
        }
        return result;  // 합산된 다항식 반환
    }

    // 다항식 출력 함수: 사람 읽기 좋은 형태로 출력
    void print() const {
        if (!head) {              // 항이 하나도 없으면 0 출력
            cout << "0\n";
            return;
        }
        Term* cur = head;         // 리스트 탐색용 포인터
        bool first = true;        // 첫 항 여부 판단 플래그
        while (cur) {
            if (!first) cout << ' ';         // 첫 항 이후에는 공백 추가
            cout << cur->coef << "x^" << cur->deg;
            first = false;                   // 첫 항 출력 후 플래그 해제
            cur = cur->next;                 // 다음 항으로 이동
        }
        cout << '\n';  // 줄 바꿈
    }
};

int main() {
    Polynomial p1, p2;  // 두 개의 다항식 객체 생성
    int n1, n2;         // 각 다항식의 항 개수

    cin >> n1;          // 첫 번째 다항식 항 개수 입력
    for (int i = 0; i < n1; i++) {
        int cof, deg;
        cin >> cof >> deg;    // 각 항의 계수와 차수 입력
        p1.addTerm(cof, deg); // 첫 번째 다항식에 항 추가
    }

    cin >> n2;          // 두 번째 다항식 항 개수 입력
    for (int i = 0; i < n2; i++) {
        int cof, deg;
        cin >> cof >> deg;    // 각 항의 계수와 차수 입력
        p2.addTerm(cof, deg); // 두 번째 다항식에 항 추가
    }

    Polynomial sum = p1 + p2;  // 두 다항식 더하기
    sum.print();               // 결과 출력

    return 0;  // 프로그램 종료
}

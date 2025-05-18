#include <iostream>   // 표준 입출력 스트림을 사용하기 위한 헤더
using namespace std;  // std 네임스페이스에 정의된 이름을 직접 사용

// 다항식의 항(term)을 표현하는 구조체
struct Term {
    int coef;        // 항의 계수(coefficient)
    int deg;         // 항의 차수(degree)
    Term* next;      // 다음 항을 가리키는 포인터

    // 생성자: 계수와 차수를 초기화하고 next 포인터를 nullptr로 설정
    Term(int c, int d) : coef(c), deg(d), next(nullptr) {}
};

// 단일 변수 다항식을 연결 리스트로 구현하는 클래스
class Polynomial {
private:
    Term* head;  // 연결 리스트의 첫 번째 항을 가리키는 포인터

    // 항을 리스트에 삽입하거나, 같은 차수의 항이 있으면 계수를 합산
    void insertTerm(int coef, int deg) {
        if (coef == 0)               // 계수가 0이면 의미가 없으므로 무시
            return;
        if (!head || head->deg < deg) {  // 리스트가 비었거나, 새로운 항의 차수가 더 크면
            Term* nt = new Term(coef, deg);  // 새 노드 생성
            nt->next = head;                 // 기존 head를 뒤로 연결
            head = nt;                        // 새 노드를 head로 설정
            return;
        }
        Term* cur = head;   // 현재 노드를 탐색하기 위한 포인터
        Term* prev = nullptr;  // 이전 노드를 가리키는 포인터
        // 삽입 위치(또는 같은 차수 노드) 탐색: 차수 내림차순 유지
        while (cur && cur->deg > deg) {
            prev = cur;
            cur = cur->next;
        }
        if (cur && cur->deg == deg) {      // 같은 차수의 항이 이미 존재하면
            cur->coef += coef;             // 계수 합산
            if (cur->coef == 0) {          // 합산 후 계수가 0이면 노드 삭제
                if (prev) prev->next = cur->next;
                else      head = cur->next;
                delete cur;
            }
        }
        else {  // 같은 차수 노드가 없으면 새로 삽입
            Term* nt = new Term(coef, deg);
            nt->next = cur;
            if (prev) prev->next = nt;
            else      head = nt;
        }
    }

public:
    // 기본 생성자: 빈 다항식을 초기화
    Polynomial() : head(nullptr) {}

    // 복사 생성자: 다른 다항식의 모든 항을 복사
    Polynomial(const Polynomial& other) : head(nullptr) {
        for (Term* cur = other.head; cur; cur = cur->next) {
            insertTerm(cur->coef, cur->deg);
        }
    }

    // 소멸자: 연결된 모든 Term 노드를 해제
    ~Polynomial() {
        Term* current = head;
        while (current != nullptr) {
            Term* next = current->next;
            delete current;
            current = next;
        }
    }

    // 사용자 함수: 새 항을 추가
    void addTerm(int coef, int deg) {
        insertTerm(coef, deg);
    }

    // 대입 연산자(=): 자기 자신이 아닌 다른 다항식을 복사
    Polynomial& operator=(const Polynomial& other) {
        if (this == &other)           // 자기 자신일 경우 아무 작업도 하지 않음
            return *this;
        // 기존 리스트 해제
        while (head) {
            Term* tmp = head->next;
            delete head;
            head = tmp;
        }
        // 다른 다항식 복사
        for (Term* cur = other.head; cur; cur = cur->next) {
            insertTerm(cur->coef, cur->deg);
        }
        return *this;
    }

    // 덧셈 연산자(+): 두 다항식을 더한 새 다항식 반환
    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;           // 결과 다항식
        Term* c1 = head;             // 첫 번째 다항식 탐색용 포인터
        Term* c2 = other.head;       // 두 번째 다항식 탐색용 포인터
        // 두 리스트를 병합하며 항의 차수를 비교
        while (c1 && c2) {
            if (c1->deg == c2->deg) {
                result.insertTerm(c1->coef + c2->coef, c1->deg);
                c1 = c1->next;
                c2 = c2->next;
            }
            else if (c1->deg > c2->deg) {
                result.insertTerm(c1->coef, c1->deg);
                c1 = c1->next;
            }
            else {
                result.insertTerm(c2->coef, c2->deg);
                c2 = c2->next;
            }
        }
        // 남은 항 처리
        while (c1) { result.insertTerm(c1->coef, c1->deg); c1 = c1->next; }
        while (c2) { result.insertTerm(c2->coef, c2->deg); c2 = c2->next; }
        return result;
    }

    // 뺄셈 연산자(-): 두 다항식의 차를 계산해 새 다항식 반환
    Polynomial operator-(const Polynomial& other) const {
        Polynomial result;
        Term* c1 = head;
        Term* c2 = other.head;
        while (c1 && c2) {
            if (c1->deg == c2->deg) {
                result.insertTerm(c1->coef - c2->coef, c1->deg);
                c1 = c1->next;
                c2 = c2->next;
            }
            else if (c1->deg > c2->deg) {
                result.insertTerm(c1->coef, c1->deg);
                c1 = c1->next;
            }
            else {
                result.insertTerm(-c2->coef, c2->deg);
                c2 = c2->next;
            }
        }
        while (c1) { result.insertTerm(c1->coef, c1->deg); c1 = c1->next; }
        while (c2) { result.insertTerm(-c2->coef, c2->deg); c2 = c2->next; }
        return result;
    }

    // 다항식 평가 함수: 주어진 x 값에서 다항식의 값을 계산
    double calculate(double x) const {
        double result = 0.0;         // 최종 합산 결과
        for (Term* cur = head; cur; cur = cur->next) {
            double t = 1.0;           // x^deg 계산용 변수
            for (int i = 0; i < cur->deg; ++i)
                t *= x;              // 지수만큼 x 곱셈
            result += cur->coef * t; // 계수와 곱해 더함
        }
        return result;
    }

    // 미분 함수: 현재 다항식의 1차 도함수를 새 다항식으로 반환
    Polynomial differentiation() const {
        Polynomial deriv;            // 도함수 다항식
        for (Term* cur = head; cur; cur = cur->next) {
            if (cur->deg > 0)
                deriv.insertTerm(cur->coef * cur->deg, cur->deg - 1);
        }
        return deriv;
    }

    // 다항식 출력 함수: 사람이 읽기 좋은 형태로 출력
    void print() const {
        if (!head) {                 // 항이 하나도 없으면 0 출력
            cout << "0\n";
            return;
        }
        Term* cur = head;
        bool first = true;           // 첫 항 여부 플래그
        while (cur) {
            int c = cur->coef, d = cur->deg;
            if (first) {
                if (c < 0) {         // 첫 항이 음수면 '-' 기호 먼저
                    cout << '-';
                    c = -c;
                }
                cout << c << "x^" << d;
                first = false;
            }
            else {
                cout << ' ' << (cur->coef < 0 ? '-' : '+')
                    << (c < 0 ? -c : c) << "x^" << d;
            }
            cur = cur->next;
        }
        cout << '\n';  // 줄 바꿈
    }
};

int main() {
    Polynomial p1, p2;    // 두 개의 다항식 객체 생성
    int cof, deg;         // 입력받을 계수와 차수 변수
    char buffer;          // 연산 명령을 저장할 변수

    // 첫 번째 다항식 입력: (-1, -1)이 들어오면 종료
    while (true) {
        cin >> cof >> deg;
        if (cof == -1 && deg == -1)
            break;
        p1.addTerm(cof, deg);
    }

    // 두 번째 다항식 입력: 동일하게 (-1, -1)이면 종료
    while (true) {
        cin >> cof >> deg;
        if (cof == -1 && deg == -1)
            break;
        p2.addTerm(cof, deg);
    }

    // 입력 완료된 다항식 출력
    cout << "P1: "; p1.print();
    cout << "P2: "; p2.print();

    // 연산 명령 루프: 'q' 입력 시 종료
    while (true) {
        cin >> buffer;
        if (buffer == 'q') {
            cout << "Program exit!";
            break;
        }
        if (buffer == '+') {
            cout << "P1 + P2: ";
            (p1 + p2).print();
        }
        else if (buffer == '-') {
            cout << "P1 - P2: ";
            (p1 - p2).print();
        }
        else if (buffer == 'd') {
            cout << "P1': ";
            p1.differentiation().print();
        }
        else if (buffer == 'v') {
            double x;
            cin >> x;
            cout << p1.calculate(x) << '\n';
        }
    }

    return 0;  // 프로그램 정상 종료
}

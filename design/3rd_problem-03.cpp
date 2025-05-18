#include <iostream>   // ǥ�� ����� ��Ʈ���� ����ϱ� ���� ���
using namespace std;  // std ���ӽ����̽��� ���ǵ� �̸��� ���� ���

// ���׽��� ��(term)�� ǥ���ϴ� ����ü
struct Term {
    int coef;        // ���� ���(coefficient)
    int deg;         // ���� ����(degree)
    Term* next;      // ���� ���� ����Ű�� ������

    // ������: ����� ������ �ʱ�ȭ�ϰ� next �����͸� nullptr�� ����
    Term(int c, int d) : coef(c), deg(d), next(nullptr) {}
};

// ���� ���� ���׽��� ���� ����Ʈ�� �����ϴ� Ŭ����
class Polynomial {
private:
    Term* head;  // ���� ����Ʈ�� ù ��° ���� ����Ű�� ������

    // ���� ����Ʈ�� �����ϰų�, ���� ������ ���� ������ ����� �ջ�
    void insertTerm(int coef, int deg) {
        if (coef == 0)               // ����� 0�̸� �ǹ̰� �����Ƿ� ����
            return;
        if (!head || head->deg < deg) {  // ����Ʈ�� ����ų�, ���ο� ���� ������ �� ũ��
            Term* nt = new Term(coef, deg);  // �� ��� ����
            nt->next = head;                 // ���� head�� �ڷ� ����
            head = nt;                        // �� ��带 head�� ����
            return;
        }
        Term* cur = head;   // ���� ��带 Ž���ϱ� ���� ������
        Term* prev = nullptr;  // ���� ��带 ����Ű�� ������
        // ���� ��ġ(�Ǵ� ���� ���� ���) Ž��: ���� �������� ����
        while (cur && cur->deg > deg) {
            prev = cur;
            cur = cur->next;
        }
        if (cur && cur->deg == deg) {      // ���� ������ ���� �̹� �����ϸ�
            cur->coef += coef;             // ��� �ջ�
            if (cur->coef == 0) {          // �ջ� �� ����� 0�̸� ��� ����
                if (prev) prev->next = cur->next;
                else      head = cur->next;
                delete cur;
            }
        }
        else {  // ���� ���� ��尡 ������ ���� ����
            Term* nt = new Term(coef, deg);
            nt->next = cur;
            if (prev) prev->next = nt;
            else      head = nt;
        }
    }

public:
    // �⺻ ������: �� ���׽��� �ʱ�ȭ
    Polynomial() : head(nullptr) {}

    // ���� ������: �ٸ� ���׽��� ��� ���� ����
    Polynomial(const Polynomial& other) : head(nullptr) {
        for (Term* cur = other.head; cur; cur = cur->next) {
            insertTerm(cur->coef, cur->deg);
        }
    }

    // �Ҹ���: ����� ��� Term ��带 ����
    ~Polynomial() {
        Term* current = head;
        while (current != nullptr) {
            Term* next = current->next;
            delete current;
            current = next;
        }
    }

    // ����� �Լ�: �� ���� �߰�
    void addTerm(int coef, int deg) {
        insertTerm(coef, deg);
    }

    // ���� ������(=): �ڱ� �ڽ��� �ƴ� �ٸ� ���׽��� ����
    Polynomial& operator=(const Polynomial& other) {
        if (this == &other)           // �ڱ� �ڽ��� ��� �ƹ� �۾��� ���� ����
            return *this;
        // ���� ����Ʈ ����
        while (head) {
            Term* tmp = head->next;
            delete head;
            head = tmp;
        }
        // �ٸ� ���׽� ����
        for (Term* cur = other.head; cur; cur = cur->next) {
            insertTerm(cur->coef, cur->deg);
        }
        return *this;
    }

    // ���� ������(+): �� ���׽��� ���� �� ���׽� ��ȯ
    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;           // ��� ���׽�
        Term* c1 = head;             // ù ��° ���׽� Ž���� ������
        Term* c2 = other.head;       // �� ��° ���׽� Ž���� ������
        // �� ����Ʈ�� �����ϸ� ���� ������ ��
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
        // ���� �� ó��
        while (c1) { result.insertTerm(c1->coef, c1->deg); c1 = c1->next; }
        while (c2) { result.insertTerm(c2->coef, c2->deg); c2 = c2->next; }
        return result;
    }

    // ���� ������(-): �� ���׽��� ���� ����� �� ���׽� ��ȯ
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

    // ���׽� �� �Լ�: �־��� x ������ ���׽��� ���� ���
    double calculate(double x) const {
        double result = 0.0;         // ���� �ջ� ���
        for (Term* cur = head; cur; cur = cur->next) {
            double t = 1.0;           // x^deg ���� ����
            for (int i = 0; i < cur->deg; ++i)
                t *= x;              // ������ŭ x ����
            result += cur->coef * t; // ����� ���� ����
        }
        return result;
    }

    // �̺� �Լ�: ���� ���׽��� 1�� ���Լ��� �� ���׽����� ��ȯ
    Polynomial differentiation() const {
        Polynomial deriv;            // ���Լ� ���׽�
        for (Term* cur = head; cur; cur = cur->next) {
            if (cur->deg > 0)
                deriv.insertTerm(cur->coef * cur->deg, cur->deg - 1);
        }
        return deriv;
    }

    // ���׽� ��� �Լ�: ����� �б� ���� ���·� ���
    void print() const {
        if (!head) {                 // ���� �ϳ��� ������ 0 ���
            cout << "0\n";
            return;
        }
        Term* cur = head;
        bool first = true;           // ù �� ���� �÷���
        while (cur) {
            int c = cur->coef, d = cur->deg;
            if (first) {
                if (c < 0) {         // ù ���� ������ '-' ��ȣ ����
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
        cout << '\n';  // �� �ٲ�
    }
};

int main() {
    Polynomial p1, p2;    // �� ���� ���׽� ��ü ����
    int cof, deg;         // �Է¹��� ����� ���� ����
    char buffer;          // ���� ����� ������ ����

    // ù ��° ���׽� �Է�: (-1, -1)�� ������ ����
    while (true) {
        cin >> cof >> deg;
        if (cof == -1 && deg == -1)
            break;
        p1.addTerm(cof, deg);
    }

    // �� ��° ���׽� �Է�: �����ϰ� (-1, -1)�̸� ����
    while (true) {
        cin >> cof >> deg;
        if (cof == -1 && deg == -1)
            break;
        p2.addTerm(cof, deg);
    }

    // �Է� �Ϸ�� ���׽� ���
    cout << "P1: "; p1.print();
    cout << "P2: "; p2.print();

    // ���� ��� ����: 'q' �Է� �� ����
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

    return 0;  // ���α׷� ���� ����
}

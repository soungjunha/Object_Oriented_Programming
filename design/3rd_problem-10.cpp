#include <iostream>   // ǥ�� ����� ��Ʈ�� ����� ���� ��� ����
using namespace std;  // std ���ӽ����̽��� ���ǵ� �̸��� ���� ���

// ���׽��� �� ��(term)�� ��Ÿ���� ����ü
struct Term {
    int coef;      // ���� ���(coefficient)
    int deg;       // ���� ����(degree)
    Term* next;    // ���� ���� ����Ű�� ������

    // ������: ����� ������ �޾� �ʱ�ȭ�ϰ�, next �����ʹ� nullptr�� ����
    Term(int c, int d) : coef(c), deg(d), next(nullptr) {}
};

// ���� ���� ���׽��� ���� ����Ʈ�� �����ϴ� Ŭ����
class Polynomial {
private:
    Term* head;  // ����Ʈ�� ù ��° ��(head)�� ����Ű�� ������

    // ���� ����Ʈ�� �����ϰų�, ���� ���� ���� ������ ����� �ջ�
    void insertTerm(int coef, int deg) {
        if (coef == 0)                // ����� 0�̸� ����Ʈ�� �߰��� �ʿ� ����
            return;
        if (!head || head->deg < deg) {  // ����Ʈ�� ����ų� �� ���� ������ �� ũ��
            Term* nt = new Term(coef, deg);  // �� �� ����
            nt->next = head;                 // ���� head�� �ڷ� ����
            head = nt;                        // �� ���� head�� ����
            return;
        }
        Term* cur = head;    // ���� Ž�� ���� ���
        Term* prev = nullptr;  // ���� ��带 ����Ű�� ������
        // ���� ��ġ �Ǵ� ���� ���� �� Ž�� (���� �������� ����)
        while (cur && cur->deg > deg) {
            prev = cur;
            cur = cur->next;
        }
        if (cur && cur->deg == deg) {   // ���� ������ ���� �����ϸ�
            cur->coef += coef;          // ��� �ջ�
            if (cur->coef == 0) {       // �ջ� �� 0�� �Ǹ� ��� ����
                if (prev) prev->next = cur->next;
                else      head = cur->next;
                delete cur;
            }
        }
        else {  // ���� ���� ���� ������ �� ���� �߰��� ����
            Term* nt = new Term(coef, deg);
            nt->next = cur;
            prev->next = nt;
        }
    }

public:
    // �⺻ ������: head�� nullptr�� �ʱ�ȭ
    Polynomial() : head(nullptr) {}

    // ���� ������: �ٸ� ���׽��� ��� ���� ����
    Polynomial(const Polynomial& other) : head(nullptr) {
        for (Term* cur = other.head; cur; cur = cur->next) {
            insertTerm(cur->coef, cur->deg);
        }
    }

    // �Ҹ���: ����� ��� Term ��带 ����
    ~Polynomial() {
        Term* cur = head;
        while (cur) {
            Term* nxt = cur->next;
            delete cur;   // ���� ��� �޸� ����
            cur = nxt;    // ���� ���� �̵�
        }
    }

    // ����� ȣ�� �Լ�: ���ο� ���� ���׽Ŀ� �߰�
    void addTerm(int coef, int deg) {
        insertTerm(coef, deg);
    }

    // ���� ������ �����ε�: �� ���׽��� ���� ����� ��ȯ
    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;     // ����� ������ ���׽� ��ü
        Term* p1 = head;       // ù ��° ���׽� Ž���� ������
        Term* p2 = other.head; // �� ��° ���׽� Ž���� ������

        // �� ����Ʈ�� �����ϸ鼭 ������ ���� ����
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
        // ���� ���� ������ ����� �߰�
        while (p1) {
            result.insertTerm(p1->coef, p1->deg);
            p1 = p1->next;
        }
        while (p2) {
            result.insertTerm(p2->coef, p2->deg);
            p2 = p2->next;
        }
        return result;  // �ջ�� ���׽� ��ȯ
    }

    // ���׽� ��� �Լ�: ��� �б� ���� ���·� ���
    void print() const {
        if (!head) {              // ���� �ϳ��� ������ 0 ���
            cout << "0\n";
            return;
        }
        Term* cur = head;         // ����Ʈ Ž���� ������
        bool first = true;        // ù �� ���� �Ǵ� �÷���
        while (cur) {
            if (!first) cout << ' ';         // ù �� ���Ŀ��� ���� �߰�
            cout << cur->coef << "x^" << cur->deg;
            first = false;                   // ù �� ��� �� �÷��� ����
            cur = cur->next;                 // ���� ������ �̵�
        }
        cout << '\n';  // �� �ٲ�
    }
};

int main() {
    Polynomial p1, p2;  // �� ���� ���׽� ��ü ����
    int n1, n2;         // �� ���׽��� �� ����

    cin >> n1;          // ù ��° ���׽� �� ���� �Է�
    for (int i = 0; i < n1; i++) {
        int cof, deg;
        cin >> cof >> deg;    // �� ���� ����� ���� �Է�
        p1.addTerm(cof, deg); // ù ��° ���׽Ŀ� �� �߰�
    }

    cin >> n2;          // �� ��° ���׽� �� ���� �Է�
    for (int i = 0; i < n2; i++) {
        int cof, deg;
        cin >> cof >> deg;    // �� ���� ����� ���� �Է�
        p2.addTerm(cof, deg); // �� ��° ���׽Ŀ� �� �߰�
    }

    Polynomial sum = p1 + p2;  // �� ���׽� ���ϱ�
    sum.print();               // ��� ���

    return 0;  // ���α׷� ����
}

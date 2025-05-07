#include<iostream>

using namespace std;

struct Term {
	int coef;   // Coefficient
	int deg;    // Degree
	Term* next;

	Term(int c, int d) : coef(c), deg(d), next(nullptr) {}
};

class Polynomial {
private:
	Term* head;

	void insertTerm(int coef, int deg) {
		// Insert a term in sorted order by degree (descending)
		// Combine terms with the same degree and remove zero-coefficient terms
		Term* new_term = new Term(coef, deg);
		if (head == nullptr)
		{
			head = new_term;
		}
		else
		{
			if (head->deg < deg)
			{
				new_term->next = head;
				head = new_term;
			}
			else
			{
				Term* current = head;
				while (current->next != nullptr && current->next->deg > deg)
				{
					current = current->next;
				}
				new_term->next = current->next;
				current->next = new_term;
			}
		}
	}

public:
	Polynomial() : head(nullptr) {}

	~Polynomial() {
		// Free all allocated memory for the linked list
		Term* current = head;
		while (current != nullptr) {
			Term* next = current->next;
			delete current;
			current = next;
		}
	}

	void addTerm(int coef, int deg) {
		insertTerm(coef, deg);
	}

	Polynomial operator+(const Polynomial& other) const {
		// Return a new polynomial that is the sum of this and other
		Polynomial result;
		Term* current1 = this->head;
		Term* current2 = other.head;

		while (current1 != nullptr && current2 != nullptr) {
			if (current1->deg == current2->deg)
			{
				result.insertTerm(current1->coef + current2->coef, current1->deg);
				current1 = current1->next;
				current2 = current2->next;
			}
			else if (current1->deg > current2->deg)
			{
				result.insertTerm(current1->coef, current1->deg);
				current1 = current1->next;
			}
			else if (current1->deg < current2->deg)
			{
				result.insertTerm(current2->coef, current2->deg);
				current2 = current2->next;
			}
		}

		while (current2 != nullptr) {
			result.insertTerm(current2->coef, current2->deg);
			current2 = current2->next;
		}

		while (current1 != nullptr) {
			result.insertTerm(current1->coef, current1->deg);
			current1 = current1->next;
		}

		return result;
	}

	Polynomial operator-(const Polynomial& other) const {
		// Return a new polynomial that is the difference of this and other
		Polynomial result;
		Term* current1 = this->head;
		Term* current2 = other.head;

		while (current1 != nullptr && current2 != nullptr) {
			if (current1->deg == current2->deg)
			{
				result.insertTerm(current1->coef - current2->coef, current1->deg);
				current1 = current1->next;
				current2 = current2->next;
			}
			else if (current1->deg > current2->deg)
			{
				result.insertTerm(current1->coef, current1->deg);
				current1 = current1->next;
			}
			else if (current1->deg < current2->deg)
			{
				result.insertTerm(-current2->coef, current2->deg);
				current2 = current2->next;
			}
		}

		while (current2 != nullptr) {
			result.insertTerm(-current2->coef, current2->deg);
			current2 = current2->next;
		}

		while (current1 != nullptr) {
			result.insertTerm(current1->coef, current1->deg);
			current1 = current1->next;
		}

		return result;
	}

	double calculate(double x) const {
		// Evaluate the polynomial at the given x value
		double result = 0;
		Term* current = head;

		while (current != nullptr) {
			double pow = 1;
			for (int i = 0; i < current->deg; i++)
			{
				pow *= x;
			}
			result += pow * current->coef;
			current = current->next;
		}

		return result;
	}

	Polynomial differentiation() const {
		// Return the derivative of the current polynomial
		Polynomial result;
		Term* current = head;

		while (current != nullptr) {
			if (current->deg > 0) {
				int new_coef = current->coef * current->deg;
				int new_deg = current->deg - 1;
				result.addTerm(new_coef, new_deg);
			}
			current = current->next;
		}

		return result;
	}

	void print() const {
		Term* current = head;
		while (current != nullptr) {
			if (current->coef != 0)
			{
				if (current != head && current->coef >= 0) cout << "+";
				cout << current->coef << "x^" << current->deg << " ";
			}
			current = current->next;
		}
		if (head == nullptr) {
			cout << 0;
		}
		cout << endl;
	}
};

int main() {

	Polynomial p1, p2;

	int deg, cof;
	char buffer;
	cin >> cof >> deg;

	while (deg != -1 && cof != -1)
	{
		p1.addTerm(cof, deg);
		cin >> cof >> deg;
	}

	cin >> cof >> deg;

	while (deg != -1 && cof != -1)
	{
		p2.addTerm(cof, deg);
		cin >> cof >> deg;
	}

	cout << "P1:";
	p1.print();

	cout << "P2:";
	p2.print();

	while (true) {
		cin >> buffer;
		if (buffer == 'q')
		{
			cout << "Program exit!";
			break;
		}
		if (buffer == '+')
		{
			cout << "P1 + P2: ";
			(p1 + p2).print();
		}
		else if (buffer == '-')
		{
			cout << "P1 - P2: ";
			(p1 - p2).print();
		}
		else if (buffer == 'd') {
			cout << "P1': ";
			p1.differentiation().print();
		}
		else if (buffer == 'v')
		{
			int x;
			cin >> x;
			cout << p1.calculate(x) << endl;
		}
	}

}

#include <iostream>   // 입출력을 위한 헤더파일 포함
#include <string>     // 문자열(string) 클래스를 사용하기 위한 헤더파일 포함
using namespace std;  // 표준 네임스페이스 사용

// 추상 기본 클래스(Animal) 정의: 모든 동물의 공통 속성과 인터페이스 제공
class Animal {
	string name;   // 동물 이름 (private 멤버 변수)
	int age;       // 동물 나이
	int prio;      // 치료 우선순위 (숫자가 작을수록 우선순위 높음)
public:
	// 생성자(Constructor): 이름, 나이, 우선순위를 초기화
	Animal(string name, int age, int prio) : name(name), age(age), prio(prio) {}

	// Getter 함수들: 멤버 변수 값을 외부에서 읽을 수 있도록 제공
	string getName() { return name; }
	int getAge() { return age; }
	int getPrio() { return prio; }

	// 순수가상함수(Pure Virtual Function): 자식 클래스에서 반드시 구현해야 함 (Polymorphism 구현)
	virtual void printInfo() = 0;

	// 가상 소멸자(Virtual Destructor): 다형성 사용 시 메모리 누수 방지
	virtual ~Animal() {}
};

// Dog 클래스 정의: Animal 클래스를 상속받음 (public 상속)
class Dog : public Animal {
public:
	// Dog 생성자: 부모 클래스 생성자 호출로 초기화
	Dog(string name, int age, int prio) : Animal(name, age, prio) {}

	// printInfo 함수 오버라이드: 개의 정보를 출력
	void printInfo() {
		cout << "Dog: " << getName() << ", " << getAge() << " years old (Priority " << getPrio() << ")" << endl;
	}
};

// Cat 클래스 정의: Animal 클래스 상속
class Cat : public Animal {
public:
	Cat(string name, int age, int prio) : Animal(name, age, prio) {}

	void printInfo() {
		cout << "Cat: " << getName() << ", " << getAge() << " years old (Priority " << getPrio() << ")" << endl;
	}
};

// Bird 클래스 정의: Animal 클래스 상속
class Bird : public Animal {
public:
	Bird(string name, int age, int prio) : Animal(name, age, prio) {}

	void printInfo() {
		cout << "Bird: " << getName() << ", " << getAge() << " years old (Priority " << getPrio() << ")" << endl;
	}
};

// 우선순위 기준으로 Animal 포인터 배열을 정렬하는 함수 (Bubble Sort 사용)
void sortByPriority(Animal* animals[], int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			// 우선순위가 높은(숫자가 작은) 동물이 앞으로 오도록 스왑
			if (animals[j]->getPrio() > animals[j + 1]->getPrio()) {
				Animal* temp = animals[j];
				animals[j] = animals[j + 1];
				animals[j + 1] = temp;
			}
		}
	}
}

int main() {
	int n;  // 등록할 동물의 수
	cin >> n;  // 사용자로부터 동물 수 입력

	// Animal 포인터 배열을 동적으로 생성 (크기 n)
	Animal** animal = new Animal * [n];

	string type;  // 동물 종류 (Dog, Cat, Bird)
	string name;  // 동물 이름
	int age;      // 동물 나이
	int prio;     // 동물 우선순위

	// n번 반복하여 동물 정보 입력 및 객체 생성
	for (int i = 0; i < n; i++) {
		cin >> type >> name >> age >> prio;  // 한 동물의 정보 입력
		// 입력받은 type에 따라 적절한 클래스의 객체 생성 후 배열에 저장
		if (!type.compare("Dog")) {
			animal[i] = new Dog(name, age, prio);
		}
		else if (!type.compare("Cat")) {
			animal[i] = new Cat(name, age, prio);
		}
		else if (!type.compare("Bird")) {
			animal[i] = new Bird(name, age, prio);
		}
	}

	// 등록된 동물 목록 출력
	cout << "List of registered animals:" << endl;
	for (int i = 0; i < n; i++) {
		animal[i]->printInfo();  // 다형성으로 각각의 printInfo 호출
	}

	// 우선순위 기준으로 정렬 수행
	sortByPriority(animal, n);

	cout << endl;
	// 정렬된 대기 목록 출력
	cout << "Sorted waiting list by priority (lower number = higher priority):" << endl;
	for (int i = 0; i < n; i++) {
		cout << i + 1 << ". ";  // 순번 출력
		animal[i]->printInfo(); // 정렬된 순서대로 정보 출력
	}

	// 동적으로 생성한 객체 메모리 해제
	for (int i = 0; i < n; i++) {
		delete animal[i];
	}
	delete[] animal;  // 포인터 배열 해제

	return 0;  // 프로그램 종료
}
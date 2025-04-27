#include <iostream>
#include <string>
using namespace std;

// Define abstract base class Animal
class Animal {
	string name;
	int age;
	int prio;
public:
	Animal(string name, int age, int prio) : name(name), age(age), prio(prio) {}
	string getName() { return name; }
	int getAge() { return age; }
	int getPrio() { return prio; }
	virtual void printInfo() = 0;
	virtual ~Animal() {}
};

// Define derived class Dog : public Animal
class Dog : public Animal {
public:
	Dog(string name, int age, int prio) : Animal(name, age, prio) {}
	void printInfo() {
		cout << "Dog: " << getName() << ", " << getAge() << " years old (Priority " << getPrio() << ")" << endl;
	}
};

// Define derived class Cat : public Animal
class Cat : public Animal {
public:
	Cat(string name, int age, int prio) : Animal(name, age, prio) {}
	void printInfo() {
		cout << "Cat: " << getName() << ", " << getAge() << " years old (Priority " << getPrio() << ")" << endl;
	}
};

// Define derived class Bird : public Animal
class Bird : public Animal {
public:
	Bird(string name, int age, int prio) : Animal(name, age, prio) {}
	void printInfo() {
		cout << "Bird: " << getName() << ", " << getAge() << " years old (Priority " << getPrio() << ")" << endl;
	}
};

// Implement sortByPriority function
void sortByPriority(Animal* animals[], int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (animals[j]->getPrio() > animals[j + 1]->getPrio()) {
				Animal* temp = animals[j];
				animals[j] = animals[j + 1];
				animals[j + 1] = temp;
			}
		}
	}
}

int main() {
	int n;
	cin >> n;

	// TODO: Create dynamic Animal* array
	Animal** animal = new Animal * [n];

	// Implement your main function
	string type;
	string name;
	int age;
	int prio;
	for (int i = 0; i < n; i++) {
		cin >> type >> name >> age >> prio;
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
	cout << "List of registered animals:" << endl;
	for (int i = 0; i < n; i++) {
		animal[i]->printInfo();
	}
	sortByPriority(animal, n);
	cout << endl;
	cout << "Sorted waiting list by priority (lower number = higher priority):" << endl;
	for (int i = 0; i < n; i++) {
		cout << i + 1 << ". ";
		animal[i]->printInfo();
	}
	for (int i = 0; i < n; i++) {
		delete animal[i];
	}
	delete[] animal;

	return 0;
}


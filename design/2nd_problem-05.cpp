#include <iostream>
#include <string>

using namespace std;

class Passenger {
protected:
	string name;
	int id;
	string destination;

public:
	Passenger(const string& n, int i, const string& d) : name(n), id(i), destination(d) {}
	virtual void Board() = 0;
};

class Commuter : public Passenger {
public:
	Commuter(const string& n, int i, const string& d) : Passenger(n, i, d) {}
	void Board()override;
};
void Commuter::Board() {
	cout << "[Commuter] " << name << " (ID: " << id << "), Destination: " << destination << " - Boarded with work pass" << endl;
}

class Student : public Passenger {
public:
	Student(const string& n, int i, const string& d) : Passenger(n, i, d) {}
	void Board()override;
};
void Student::Board() {
	cout << "[Student] " << name << " (ID: " << id << "), Destination: " << destination << " - Boarded using student card" << endl;
}

class PassengerQueue {
private:
	Passenger* queue[100];
	int front;
	int rear;

public:
	PassengerQueue() : front(0), rear(0) {}

	bool isEmpty() const {
		// TODO: Return true if front == rear
		if (front == rear) {
			return true;
		}
		return false;
	}

	bool isFull() const {
		// TODO: Return true if rear >= 100
		if (rear >= 100) {
			return true;
		}
		return false;
	}

	void enqueue(Passenger* p) {
		// TODO: Add passenger pointer to queue[rear++]
		if (!isFull()) queue[rear++] = p;
	}

	Passenger* dequeue() {
		// TODO: Return queue[front++] if not empty
		if (!isEmpty()) {
			return queue[front++];
		}
	}

	void clear() {
		// TODO: Delete all dynamically allocated passengers in the queue
		while (!isEmpty()) {
			delete dequeue();
		}
	}

	~PassengerQueue() {
		clear();
	}
};

int main() {

	// Implement your main function
	int N;
	cin >> N;
	cin.ignore();

	string commuterDest[] = { "Company", "Office", "Lab" };
	string studentDest[] = { "University", "HighSchool", "Library" };

	PassengerQueue queue;

	for (int i = 0; i < N; ++i) {
		string type, name, destination;
		int id;

		cin >> type >> name >> id >> destination;

		if (type == "Commuter" && (commuterDest[0] == destination || commuterDest[1] == destination || commuterDest[2] == destination)) {
			queue.enqueue(new Commuter(name, id, destination));
		}
		else if (type == "Student" && (studentDest[0] == destination || studentDest[1] == destination || studentDest[2] == destination)) {
			queue.enqueue(new Student(name, id, destination));
		}
	}

	string command;
	cin >> command;
	if (command == "START") {
		while (!queue.isEmpty()) {
			Passenger* p = queue.dequeue();
			p->Board();
			delete p;
		}
	}

	return 0;
}

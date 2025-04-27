#include <iostream>
#include <string>
using namespace std;

class C_Queue {
    int arr[11];
    int head;
    int tail;

public:
    C_Queue() : head(0), tail(0) {
        for (int i = 0; i < 11; ++i) {
            arr[i] = 0;
        }
    }

    bool is_empty() {
        return head == tail;
    }

    bool is_full() {
        return (tail + 1) % 11 == head;

    }

    void enqueue(int x) {
        if (is_full()) {
            cout << "queue is full" << endl;
        }
        else {
            arr[tail] = x;
            tail = (tail + 1) % 11;
        }
    }

    int dequeue() {
        if (is_empty()) {
            return -1;
        }
        else {
            int x = arr[head];
            head = (head + 1) % 11;
            return x;
        }
    }

    void print_dequeue_all() {
        if (is_empty()) {
            cout << "-1" << endl;
        }
        else {
            int i = head;
            while (i != tail) {
                cout << arr[i] << " ";
                i = (i + 1) % 11;
            }
            cout << endl;
            head = tail;
        }
    }

    void print_size() {
        cout << (tail - head + 11) % 11 << endl;
    }
};

int main() {
    int N;
    cin >> N;
    C_Queue cque;

    for (int i = 0; i < N; ++i) {
        string cmd;
        cin >> cmd;

        if (cmd == "enqueue") {
            int x;
            cin >> x;
            cque.enqueue(x);
        }
        else if (cmd == "dequeue") {
            cout << cque.dequeue() << endl;
        }
        else if (cmd == "dequeue_all") {
            cque.print_dequeue_all();
        }
        else if (cmd == "size") {
            cque.print_size();
        }
    }
    return 0;
}

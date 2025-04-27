#include <iostream>   // 입출력 사용을 위한 헤더파일
#include <string>     // 문자열(string) 클래스 사용을 위한 헤더파일
using namespace std;  // 표준 네임스페이스 사용

// 원형 큐 클래스 정의
class C_Queue {
    int arr[11];   // 큐 데이터를 저장할 배열 (크기 11, 실제 데이터 공간은 10개)
    int head;      // 큐의 첫 번째 요소 위치 (삭제 위치)
    int tail;      // 큐의 마지막 요소 다음 위치 (삽입 위치)

public:
    // 생성자: head와 tail 초기화 및 배열 요소 0으로 초기화
    C_Queue() : head(0), tail(0) {
        for (int i = 0; i < 11; ++i) {
            arr[i] = 0;
        }
    }

    // 큐가 비어있는지 확인 (head와 tail이 같으면 비어있음)
    bool is_empty() {
        return head == tail;
    }

    // 큐가 가득 찼는지 확인 (원형 구조를 고려하여 계산)
    bool is_full() {
        return (tail + 1) % 11 == head;
    }

    // 큐에 데이터 삽입 (enqueue)
    void enqueue(int x) {
        if (is_full()) {
            cout << "queue is full" << endl;  // 큐가 가득 찼을 때 메시지 출력
        }
        else {
            arr[tail] = x;                   // tail 위치에 데이터 삽입
            tail = (tail + 1) % 11;          // tail을 다음 위치로 이동 (원형 구조 반영)
        }
    }

    // 큐에서 데이터 삭제 (dequeue) 후 반환
    int dequeue() {
        if (is_empty()) {
            return -1;   // 비어있으면 -1 반환
        }
        else {
            int x = arr[head];               // head 위치의 데이터 저장
            head = (head + 1) % 11;          // head를 다음 위치로 이동
            return x;                        // 삭제한 데이터 반환
        }
    }

    // 큐에 있는 모든 데이터를 출력하고 비우기
    void print_dequeue_all() {
        if (is_empty()) {
            cout << "-1" << endl;  // 비어있으면 -1 출력
        }
        else {
            int i = head;
            // head부터 tail 전까지 순차적으로 출력
            while (i != tail) {
                cout << arr[i] << " ";
                i = (i + 1) % 11;  // 원형 구조 고려
            }
            cout << endl;
            head = tail;  // 모든 데이터를 출력했으므로 큐를 비움
        }
    }

    // 큐에 현재 저장된 데이터의 개수를 출력
    void print_size() {
        cout << (tail - head + 11) % 11 << endl;  // 원형 큐 크기 계산 공식
    }
};

int main() {
    int N;           // 명령어 개수
    cin >> N;        // 사용자로부터 명령어 개수 입력
    C_Queue cque;    // 원형 큐 객체 생성

    // N번 명령어 처리
    for (int i = 0; i < N; ++i) {
        string cmd;
        cin >> cmd;   // 명령어 입력

        if (cmd == "enqueue") {   // 데이터 삽입 명령
            int x;
            cin >> x;
            cque.enqueue(x);
        }
        else if (cmd == "dequeue") {   // 데이터 삭제 명령
            cout << cque.dequeue() << endl;
        }
        else if (cmd == "dequeue_all") {   // 전체 출력 후 비우기
            cque.print_dequeue_all();
        }
        else if (cmd == "size") {   // 큐 크기 출력
            cque.print_size();
        }
    }
    return 0;   // 프로그램 종료
}
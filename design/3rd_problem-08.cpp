#include <iostream>   // 표준 입출력 스트림을 사용하기 위한 헤더
#include <string>     // std::string 클래스를 사용하기 위한 헤더
using namespace std;  // std 네임스페이스에 정의된 이름들을 직접 사용

// 키 타입 K, 값 타입 V를 받아들이는 범용 해시 테이블 클래스 템플릿
template <typename K, typename V>
class TABLE {
private:
    K keys[100];      // 최대 100개의 키를 저장할 배열
    V vals[100];      // keys[i]에 대응하는 값을 저장할 배열
    int cnt;          // 현재 저장된 (키,값) 쌍의 개수

public:
    // 생성자: 객체가 생성될 때 cnt를 0으로 초기화
    TABLE() {
        cnt = 0;
    }

    // put 메서드: 키가 이미 존재하면 값을 갱신하고, 없으면 새로 삽입
    void put(K key, V val) {
        for (int i = 0; i < cnt; i++) {
            if (keys[i] == key) {   // 동일한 키를 검색
                vals[i] = val;      // 존재하면 값만 덮어씀
                return;             // 삽입/갱신 완료 후 즉시 반환
            }
        }
        if (cnt < 100) {            // 배열에 여유가 있으면
            keys[cnt] = key;        // 새로운 키 저장
            vals[cnt] = val;        // 새로운 값 저장
            cnt++;                  // 항목 개수 증가
        }
    }

    // get 메서드: 키에 대응하는 값을 출력하거나, 없으면 "None" 출력
    void get(K key) {
        for (int i = 0; i < cnt; i++) {
            if (keys[i] == key) {   // 키 검색
                cout << vals[i] << endl;  // 값 출력
                return;                  // 찾으면 바로 반환
            }
        }
        cout << "None" << endl;    // 키가 없으면 None 출력
    }

    // size 메서드: 현재 저장된 (키,값) 쌍의 개수를 출력
    void size() {
        cout << cnt << endl;
    }
};

int main() {
    string key_type, value_type;  // 입력으로 받을 키 타입, 값 타입 문자열
    int n;                        // 이후 처리할 명령의 개수

    cin >> key_type >> value_type;  // 예: "string" "int" 혹은 "int" "string"
    cin >> n;                       // 명령의 수 입력

    // 키 타입이 string, 값 타입이 int인 경우
    if (key_type == "string" && value_type == "int") {
        TABLE<string, int> table;   // TABLE<string, int> 인스턴스 생성
        for (int i = 0; i < n; i++) {
            string cmd;
            cin >> cmd;             // 명령어 입력: put, get, size
            if (cmd == "put") {
                string k;
                int v;
                cin >> k >> v;      // put일 경우 키와 값 입력
                table.put(k, v);    // 테이블에 삽입 또는 갱신
            }
            else if (cmd == "get") {
                string k;
                cin >> k;           // get일 경우 키 입력
                table.get(k);       // 테이블에서 값 검색 및 출력
            }
            else if (cmd == "size") {
                table.size();       // size일 경우 항목 개수 출력
            }
        }
    }
    // 키 타입이 int, 값 타입이 string인 경우
    else if (key_type == "int" && value_type == "string") {
        TABLE<int, string> table;   // TABLE<int, string> 인스턴스 생성
        for (int i = 0; i < n; i++) {
            string cmd;
            cin >> cmd;             // 명령어 입력
            if (cmd == "put") {
                int k;
                string v;
                cin >> k >> v;      // put일 경우 키(int)와 값(string) 입력
                table.put(k, v);    // 테이블에 삽입 또는 갱신
            }
            else if (cmd == "get") {
                int k;
                cin >> k;           // get일 경우 키(int) 입력
                table.get(k);       // 테이블에서 값 검색 및 출력
            }
            else if (cmd == "size") {
                table.size();       // size일 경우 항목 개수 출력
            }
        }
    }

    return 0;  // 프로그램 종료
}

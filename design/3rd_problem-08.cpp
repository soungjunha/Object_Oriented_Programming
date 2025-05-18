#include <iostream>   // ǥ�� ����� ��Ʈ���� ����ϱ� ���� ���
#include <string>     // std::string Ŭ������ ����ϱ� ���� ���
using namespace std;  // std ���ӽ����̽��� ���ǵ� �̸����� ���� ���

// Ű Ÿ�� K, �� Ÿ�� V�� �޾Ƶ��̴� ���� �ؽ� ���̺� Ŭ���� ���ø�
template <typename K, typename V>
class TABLE {
private:
    K keys[100];      // �ִ� 100���� Ű�� ������ �迭
    V vals[100];      // keys[i]�� �����ϴ� ���� ������ �迭
    int cnt;          // ���� ����� (Ű,��) ���� ����

public:
    // ������: ��ü�� ������ �� cnt�� 0���� �ʱ�ȭ
    TABLE() {
        cnt = 0;
    }

    // put �޼���: Ű�� �̹� �����ϸ� ���� �����ϰ�, ������ ���� ����
    void put(K key, V val) {
        for (int i = 0; i < cnt; i++) {
            if (keys[i] == key) {   // ������ Ű�� �˻�
                vals[i] = val;      // �����ϸ� ���� ���
                return;             // ����/���� �Ϸ� �� ��� ��ȯ
            }
        }
        if (cnt < 100) {            // �迭�� ������ ������
            keys[cnt] = key;        // ���ο� Ű ����
            vals[cnt] = val;        // ���ο� �� ����
            cnt++;                  // �׸� ���� ����
        }
    }

    // get �޼���: Ű�� �����ϴ� ���� ����ϰų�, ������ "None" ���
    void get(K key) {
        for (int i = 0; i < cnt; i++) {
            if (keys[i] == key) {   // Ű �˻�
                cout << vals[i] << endl;  // �� ���
                return;                  // ã���� �ٷ� ��ȯ
            }
        }
        cout << "None" << endl;    // Ű�� ������ None ���
    }

    // size �޼���: ���� ����� (Ű,��) ���� ������ ���
    void size() {
        cout << cnt << endl;
    }
};

int main() {
    string key_type, value_type;  // �Է����� ���� Ű Ÿ��, �� Ÿ�� ���ڿ�
    int n;                        // ���� ó���� ����� ����

    cin >> key_type >> value_type;  // ��: "string" "int" Ȥ�� "int" "string"
    cin >> n;                       // ����� �� �Է�

    // Ű Ÿ���� string, �� Ÿ���� int�� ���
    if (key_type == "string" && value_type == "int") {
        TABLE<string, int> table;   // TABLE<string, int> �ν��Ͻ� ����
        for (int i = 0; i < n; i++) {
            string cmd;
            cin >> cmd;             // ��ɾ� �Է�: put, get, size
            if (cmd == "put") {
                string k;
                int v;
                cin >> k >> v;      // put�� ��� Ű�� �� �Է�
                table.put(k, v);    // ���̺� ���� �Ǵ� ����
            }
            else if (cmd == "get") {
                string k;
                cin >> k;           // get�� ��� Ű �Է�
                table.get(k);       // ���̺��� �� �˻� �� ���
            }
            else if (cmd == "size") {
                table.size();       // size�� ��� �׸� ���� ���
            }
        }
    }
    // Ű Ÿ���� int, �� Ÿ���� string�� ���
    else if (key_type == "int" && value_type == "string") {
        TABLE<int, string> table;   // TABLE<int, string> �ν��Ͻ� ����
        for (int i = 0; i < n; i++) {
            string cmd;
            cin >> cmd;             // ��ɾ� �Է�
            if (cmd == "put") {
                int k;
                string v;
                cin >> k >> v;      // put�� ��� Ű(int)�� ��(string) �Է�
                table.put(k, v);    // ���̺� ���� �Ǵ� ����
            }
            else if (cmd == "get") {
                int k;
                cin >> k;           // get�� ��� Ű(int) �Է�
                table.get(k);       // ���̺��� �� �˻� �� ���
            }
            else if (cmd == "size") {
                table.size();       // size�� ��� �׸� ���� ���
            }
        }
    }

    return 0;  // ���α׷� ����
}

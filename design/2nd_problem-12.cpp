#include <iostream>   // 표준 입출력 사용
#include <string>     // 문자열(string) 클래스 사용
using namespace std;

// Matrix 클래스 정의 (동적 2차원 배열 기반)
class Matrix {
private:
    int** data;    // 2차원 배열을 가리키는 포인터
    int rows;      // 행(row) 개수
    int cols;      // 열(column) 개수

public:
    // 생성자: 행과 열을 입력받아 초기화, 기본값은 0
    Matrix(int r = 0, int c = 0) : rows(r), cols(c), data(nullptr) {
        if (r > 0 && c > 0) allocate(r, c);  // 크기가 유효하면 메모리 할당
    }

    // 소멸자: 동적 메모리 해제
    ~Matrix() {
        clear();
    }

    // 행렬 크기만큼 메모리 동적 할당
    void allocate(int r, int c) {
        clear();  // 기존 메모리 해제 후 재할당
        data = new int*[r];
        for (int i = 0; i < r; i++) {
            data[i] = new int[c];
        }
        this->rows = r;
        this->cols = c;
    }

    // 동적 메모리 해제
    void clear() {
        if (data) {
            for (int i = 0; i < rows; i++)
                delete[] data[i];
            delete[] data;
            data = nullptr;
        }
    }

    // 행렬 값 입력 받기
    void inputValues() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> data[i][j];
            }
        }
    }

    // 행렬 출력 (각 행 끝에 공백 포함)
    void print() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    // 두 행렬의 크기가 같은지 확인
    bool isSameSize(const Matrix& other) const {
        return (this->rows == other.rows && this->cols == other.cols);
    }

    // 행렬 곱셈 가능 여부 확인 (this.cols == other.rows)
    bool isMultipliableWith(const Matrix& other) const {
        return (this->cols == other.rows);
    }

    // 행렬 덧셈 수행
    Matrix add(const Matrix& other) const {
        Matrix result(rows, cols);   // 결과 행렬 생성
        if (isSameSize(other)) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    result.setValue(i, j, this->data[i][j] + other.data[i][j]);
                }
            }
            result.print();
        } else {
            cout << "Error" << endl;  // 크기가 다르면 에러 출력
        }
        return result;   // 결과 반환
    }

    // 행렬 곱셈 수행
    Matrix multiply(const Matrix& other) const {
        Matrix result(this->rows, other.cols);
        if (isMultipliableWith(other)) {
            for (int i = 0; i < this->rows; ++i) {
                for (int j = 0; j < other.cols; ++j) {
                    int sum = 0;
                    for (int k = 0; k < this->cols; ++k) {
                        sum += this->data[i][k] * other.data[k][j];
                    }
                    result.setValue(i, j, sum);
                }
            }
            result.print();
        } else {
            cout << "Error" << endl;  // 곱셈 불가 시 에러 출력
        }
        return result;
    }

    // 행렬을 제자리에서 전치(transpose)
    void transposeInPlace() {
        int** new_data = new int*[cols];   // 전치된 크기만큼 새 메모리 할당
        for (int i = 0; i < cols; ++i) {
            new_data[i] = new int[rows];
        }

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                new_data[j][i] = data[i][j];  // 행과 열 교환
            }
        }

        clear();           // 기존 메모리 해제
        data = new_data;   // 새 데이터로 교체

        int tmp = rows;    // 행과 열 값 교환
        rows = cols;
        cols = tmp;
    }

    // 특정 위치 값 설정
    void setValue(int r, int c, int val) {
        if (r < rows && c < cols) {
            data[r][c] = val;
        }
    }

    // 행렬이 초기화되었는지 확인
    bool isInitialized() const {
        return data != nullptr;
    }
};

// 메인 함수: 명령어 기반 행렬 연산 수행
int main() {
    Matrix A, B;     // 두 개의 행렬 객체 선언
    string cmd;      // 명령어 저장 변수
    int r, c;        // 행, 열
    char m_name;     // 행렬 이름 ('A' 또는 'B')

    while (true) {
        cin >> cmd;   // 명령어 입력

        if (cmd == "exit") {
            cout << "Program terminated!" << endl;
            break;
        }
        else if (cmd == "setsize") {
            cin >> m_name >> r >> c;
            if (m_name == 'A') {
                A.allocate(r, c);
            } else if (m_name == 'B') {
                B.allocate(r, c);
            }
        }
        else if (cmd == "setmatrix") {
            cin >> m_name;
            if (m_name == 'A') {
                A.inputValues();
            } else if (m_name == 'B') {
                B.inputValues();
            }
        }
        else if (cmd == "add") {
            A.add(B);
        }
        else if (cmd == "mul") {
            A.multiply(B);
        }
        else if (cmd == "transpose") {
            cin >> m_name;
            if (m_name == 'A') {
                A.transposeInPlace();
            } else if (m_name == 'B') {
                B.transposeInPlace();
            }
        }
        else if (cmd == "print") {
            cin >> m_name;
            if (m_name == 'A') {
                A.print();
            } else if (m_name == 'B') {
                B.print();
            }
        }
        else if (cmd == "set") {
            cin >> m_name >> r >> c;
            int val;
            cin >> val;
            if (m_name == 'A') {
                A.setValue(r, c, val);
            } else if (m_name == 'B') {
                B.setValue(r, c, val);
            }
        }
    }
}
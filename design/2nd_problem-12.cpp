#include <iostream>
#include <string>

using namespace std;

class Matrix {
private:
    int** data;    // Pointer to 2D array for matrix data
    int rows;      // Number of rows
    int cols;      // Number of columns

public:
    Matrix(int r = 0, int c = 0) : rows(r), cols(c), data(nullptr) {
        if (r > 0 && c > 0) allocate(r, c);
    }

    ~Matrix() {
        clear();
    }

    // Allocate memory for the matrix with new size (r x c)
    void allocate(int r, int c) {
        data = new int* [r];
        for (int i = 0; i < r; i++)
        {
            data[i] = new int[c];
        }
        this->rows = r;
        this->cols = c;
    }

    // Free any allocated memory
    void clear() {
        if (data) {
            for (int i = 0; i < rows; i++)
                delete[] data[i];
            delete[] data;
            data = nullptr;
        }
    }

    // Read matrix values from standard input
    void inputValues() {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cin >> data[i][j];
            }
        }
    }

    // Print matrix values to standard output (each line ends with a space)
    void print() const {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }

    }

    // Return true if dimensions match this and another matrix
    bool isSameSize(const Matrix& other) const {
        return (this->rows == other.rows && this->cols == other.cols);
    }

    // Return true if current matrix is multipliable with another (this.cols == other.rows)
    bool isMultipliableWith(const Matrix& other) const {
        return (this->cols == other.rows);
    }

    // Return a new matrix which is the result of this + other
    Matrix add(const Matrix& other) const {
        Matrix result(rows, cols);
        if (isSameSize(other)) {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    result.setValue(i, j, this->data[i][j] + other.data[i][j]);
                }
            }
            result.print();
        }
        else
        {
            cout << "Error" << endl;
        }
        return result;
    }

    // Return a new matrix which is the result of this * other
    Matrix multiply(const Matrix& other) const {
        Matrix result(this->rows, other.cols);
        if (isMultipliableWith(other)) {
            for (int i = 0; i < this->rows; ++i) {
                for (int j = 0; j < other.cols; ++j) {
                    int to = 0;
                    for (int k = 0; k < this->cols; ++k) {
                        to += this->data[i][k] * other.data[k][j];
                    }
                    result.setValue(i, j, to);
                }
            }
            result.print();
        }
        else
        {
            cout << "Error" << endl;
        }
        return result;
    }

    // Replace current matrix data with its transpose
    void transposeInPlace() {
        int** new_data = new int* [cols];
        for (int i = 0; i < cols; ++i) {
            new_data[i] = new int[rows];
        }

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                new_data[j][i] = data[i][j];
            }
        }

        clear();

        data = new_data;

        int tmp = rows;
        rows = cols;
        cols = tmp;

    }

    // Set specific value at (r, c)
    void setValue(int r, int c, int val) {
        if (r < rows && c < cols) {
            data[r][c] = val;
        }
    }

    // Check if matrix has been initialized (data is not null)
    bool isInitialized() const {
        return data != nullptr;
    }
};

int main() {
    Matrix A, B;
    string cmd;
    int r, c;
    char m_name;

    while (true)
    {
        cin >> cmd;
        if (cmd == "exit") {
            cout << "Program terminated!" << endl;
            break;
        }
        else if (cmd == "setsize") {
            cin >> m_name >> r >> c;
            if (m_name == 'A')
            {
                A.allocate(r, c);
            }
            else if (m_name == 'B')
            {
                B.allocate(r, c);
            }
        }
        else if (cmd == "setmatrix") {
            cin >> m_name;
            if (m_name == 'A')
            {
                A.inputValues();
            }
            else if (m_name == 'B')
            {
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
            if (m_name == 'A')
            {
                A.transposeInPlace();
            }
            else if (m_name == 'B')
            {
                B.transposeInPlace();
            }
        }
        else if (cmd == "print") {
            cin >> m_name;
            if (m_name == 'A')
            {
                A.print();
            }
            else if (m_name == 'B')
            {
                B.print();
            }
        }
        else if (cmd == "set") {
            cin >> m_name >> r >> c;
            int val;
            cin >> val;
            if (m_name == 'A')
            {
                A.setValue(r, c, val);
            }
            else if (m_name == 'B')
            {
                B.setValue(r, c, val);
            }
        }
    }

}

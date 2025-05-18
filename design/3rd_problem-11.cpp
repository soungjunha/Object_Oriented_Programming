#include <iostream>
#include <string>
using namespace std;

struct Node {
    int value;
    Node* up;
    Node* down;
    Node* left;
    Node* right;
    Node(int v) : value(v), up(nullptr), down(nullptr), left(nullptr), right(nullptr) {}
};

class Board {
public:
    int N;
    Node* nodes[100][100];

    Board(int n) : N(n) {
        //todo : Initialize the board with input values and properly link all nodes (up, down, left, right with wrap-around).
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                int val;
                cin >> val;
                nodes[i][j] = new Node(val);
            }
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                nodes[i][j]->up = nodes[(i - 1 + N) % N][j];
                nodes[i][j]->down = nodes[(i + 1) % N][j];
                nodes[i][j]->left = nodes[i][(j - 1 + N) % N];
                nodes[i][j]->right = nodes[i][(j + 1) % N];
            }
        }
    }
    ~Board() {
        //todo : Deallocate all dynamically allocated nodes to avoid memory leaks.
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                delete nodes[i][j];
            }
        }
    }

    void shift_row(int row_idx, char direction) {
        //todo : Shift the specified row to the left (L) or right (R) by one position (circular shift).
        if (direction == 'L') {
            int tmp = nodes[row_idx][0]->value;
            for (int j = 0; j < N - 1; ++j)
                nodes[row_idx][j]->value = nodes[row_idx][j + 1]->value;
            nodes[row_idx][N - 1]->value = tmp;
        }
        else if (direction == 'R') {
            int tmp = nodes[row_idx][N - 1]->value;
            for (int j = N - 1; j > 0; --j)
                nodes[row_idx][j]->value = nodes[row_idx][j - 1]->value;
            nodes[row_idx][0]->value = tmp;
        }
    }

    void shift_col(int col_idx, char direction) {
        //todo : Shift the specified column up (U) or down (D) by one position (circular shift).
        if (direction == 'U') {
            int tmp = nodes[0][col_idx]->value;
            for (int i = 0; i < N - 1; ++i)
                nodes[i][col_idx]->value = nodes[i + 1][col_idx]->value;
            nodes[N - 1][col_idx]->value = tmp;
        }
        else if (direction == 'D') {
            int tmp = nodes[N - 1][col_idx]->value;
            for (int i = N - 1; i > 0; --i)
                nodes[i][col_idx]->value = nodes[i - 1][col_idx]->value;
            nodes[0][col_idx]->value = tmp;
        }
    }

    void print_board() {
        //todo : Print the current state of the board, with each row on a new line and values separated by spaces.
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << nodes[i][j]->value
                    << " ";
            }
            cout << "\n";
        }
    }

    // DO NOT MODIFY print_node FUNCTION
    void print_node(int r, int c) {
        Node* target = nodes[r][c];
        cout << target->value << " "
            << target->up->value << " "
            << target->down->value << " "
            << target->left->value << " "
            << target->right->value << " " << endl;
    }
};

// DO NOT MODIFY MAIN FUNCTION
int main() {
    int N;
    cin >> N;
    Board board(N);

    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        string cmd;
        cin >> cmd;
        if (cmd == "R") {
            int r;
            char dir;
            cin >> r >> dir;
            board.shift_row(r, dir);
        }
        else if (cmd == "C") {
            int c;
            char dir;
            cin >> c >> dir;
            board.shift_col(c, dir);
        }
        else if (cmd == "print_board") {
            board.print_board();
        }
        else if (cmd == "print_node") {
            int r, c;
            cin >> r >> c;
            board.print_node(r, c);
        }
    }

    return 0;
}
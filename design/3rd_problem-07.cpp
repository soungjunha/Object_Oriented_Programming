#include <iostream>
#include <string>

using namespace std;

const int MAX_CHILD = 10;

class Folder {
private:
    // Declare member variables
    string name;
    Folder* children[MAX_CHILD];
    int child_cnt;
public:
    // Implement member functions of Folder class
    Folder(string name) {
        this->name = name;
        child_cnt = 0;
        for (int i = 0; i < MAX_CHILD; i++) {
            children[i] = nullptr;
        }
    }

    string getName() {
        return name;
    }

    bool add_child(Folder* child) {
        if (child_cnt >= MAX_CHILD) return false;
        children[child_cnt++] = child;
        return true;
    }

    void print(int depth = 0) {
        for (int i = 0; i < depth * 2; i++) cout << " ";
        cout << name << endl;
        for (int i = 0; i < child_cnt; i++) {
            children[i]->print(depth + 1);
        }
    }

    Folder* get_child(string childName) {
        for (int i = 0; i < child_cnt; i++) {
            if (children[i]->getName() == childName) {
                return children[i];
            }
        }
        return nullptr;
    }

    int get_child_count() {
        return child_cnt;
    }

    Folder* get_child_at(int index) {
        if (index < 0 || index >= child_cnt) return nullptr;
        return children[index];
    }

    void clear_all() {
        for (int i = 0; i < child_cnt; i++) {
            if (children[i]) {
                children[i]->clear_all();  // 자식부터 삭제
                delete children[i];        // 자식 메모리 해제
                children[i] = nullptr;
            }
        }
    }
};

Folder* find_folder(Folder* current, const string& name) {
    if (current->getName() == name) return current;

    for (int i = 0; i < current->get_child_count(); i++) {
        Folder* found = find_folder(current->get_child_at(i), name);
        if (found) return found;
    }

    return nullptr;
}

int main() {
    string command;
    // Root folder is always created automatically with name "root"
    Folder* root = new Folder("root"); // 

    // Implemet your main function  
    while (cin >> command) {
        if (command == "ADD") {
            string parentName, childName;
            cin >> parentName >> childName;
            Folder* parent = find_folder(root, parentName);
            if (parent) {
                Folder* child = new Folder(childName);
                if (!parent->add_child(child)) {
                    delete child; // 자식 10개 초과 시 무시 및 메모리 반환
                }
            }
        }
        else if (command == "PATH") {
            string folderName;
            cin >> folderName;
            Folder* start = find_folder(root, folderName);
            if (start) {
                start->print();
            }
        }
        else if (command == "EXIT") {
            break;
        }
    }

    root->clear_all();
    delete root;

    return 0;
}

#include<iostream>
using namespace std;

class dot {
public:
    float x, y;

};

class triangle {
private:
    float area = 0;
public:
    triangle(dot a, dot b, dot c) {
        this->area = (1.0 / 2.0) * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
        if (this->area < 0)
            this->area *= -1;
    }
    double get_area() {
        return this->area;
    }
    bool is_valid() {
        if (this->area <= 0)
            return false;
        else
            return true;
    }
};

int main() {
    cout << fixed;
    cout.precision(3);
    dot a, b, c;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    triangle t(a, b, c);
    if (t.is_valid())
        cout << t.get_area() << endl;
    else
        cout << "Not triangle" << endl;
    return 0;
}

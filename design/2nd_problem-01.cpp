#include <iostream>
#include <string>
using namespace std;

class Boom
{
public:
    Boom(int seconds, char wire_color, string unlock_code);

    int seconds;
    char wire_color;
    string unlock_code;

private:

};

Boom::Boom(int seconds, char wire_color, string unlock_code)
{
    this->seconds = seconds;
    this->unlock_code = unlock_code;
    this->wire_color = wire_color;
}

int main() {
    string unlock_code;
    char wire_color;
    int seconds;

    cin >> unlock_code >> wire_color >> seconds;

    Boom b = Boom(seconds, wire_color, unlock_code);

    cout << "code : " << b.unlock_code << endl;
    cout << "color : " << b.wire_color << endl;
    cout << "second : " << b.seconds << endl;
    return 0;
}
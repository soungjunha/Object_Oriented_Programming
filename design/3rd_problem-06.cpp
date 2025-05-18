#include<iostream>
using namespace std;

class Time {
public:
    int H, M, S;
    Time(int h, int m, int s) :H(h), M(m), S(s) {
        //todo : Implement constructor
    }
    Time operator+(const Time& input) {
        //todo : Implement addition
        int sec = S + input.S;
        int min = M + input.M + sec / 60;
        int hour = H + input.H + min / 60;
        sec %= 60;
        min %= 60;
        hour %= 24;
        return Time(hour, min, sec);
    }
    Time operator-(const Time& input) {
        //todo : Implement subtraction
        int t1_total = H * 3600 + M * 60 + S;
        int t2_total = input.H * 3600 + input.M * 60 + input.S;

        if (t1_total < t2_total)
            return Time(0, 0, 0);

        int diff = t1_total - t2_total;

        int hour = (diff / 3600) % 24;
        int min = (diff % 3600) / 60;
        int sec = diff % 60;

        return Time(hour, min, sec);
    }
    Time operator*(int num) const {
        int total = (H * 3600 + M * 60 + S) * num;
        int hour = (total / 3600) % 24;
        int min = (total % 3600) / 60;
        int sec = total % 60;
        return Time(hour, min, sec);
    }
    friend Time operator*(int num, const Time& t) {
        return t * num;
    }
    void print_time() {
        cout << H << ":" << M << ":" << S << endl;
    }
};

//todo : Implement time multiplication



int main() {
    int a, b, c;
    int d, e, f;
    int num1, num2;

    cin >> a >> b >> c;
    cin >> d >> e >> f;
    cin >> num1 >> num2;

    Time t1(a, b, c);
    Time t2(d, e, f);

    Time sum = t1 + t2;
    Time diff = t1 - t2;
    Time mul1 = t1 * num1;
    Time mul2 = num2 * t2;

    sum.print_time();
    diff.print_time();
    mul1.print_time();
    mul2.print_time();

    return 0;
}

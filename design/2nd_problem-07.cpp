#include <iostream>
using namespace std;

class Zone {
private:
    double temp;
public:
    void setTemperature(double t) {
        this->temp = t;
    }

    double getTemperature() {

        return temp;
    }
};


int main() {

    int N;
    cin >> N;

    Zone** zone = new Zone * [N];

    for (int i = 0; i < N; ++i) {
        double temp;
        cin >> temp;
        zone[i] = new Zone;
        zone[i]->setTemperature(temp);
    }

    double avg = 0;
    double max = -101;

    for (int i = 0; i < N; i++)
    {
        avg += zone[i]->getTemperature();
        if (max < zone[i]->getTemperature())max = zone[i]->getTemperature();
    }
    cout << fixed;
    cout.precision(2);

    cout << avg / N << endl;
    cout << max;

    return 0;
}

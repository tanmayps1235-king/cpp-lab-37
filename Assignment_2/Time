#include <iostream>
using namespace std;

class Time {
private:
    int hours, minutes;

public:
    Time(int h = 0, int m = 0) : hours(h), minutes(m) {}

    Time add(const Time &t) {
        int h = hours + t.hours;
        int m = minutes + t.minutes;

        if (m >= 60) {
            h = h + m / 60;
            m = m % 60;
        }

        return Time(h, m);
    }

    Time subtract(const Time &t) {
        int h = hours - t.hours;
        int m = minutes - t.minutes;

        if (m < 0) {
            h = h - 1;
            m = m + 60;
        }

        return Time(h, m);
    }

    void display() const {
        cout << hours << " hours " << minutes << " minutes" << endl;
    }
};

int main() {
    Time t1(2, 45), t2(1, 30);

    Time sum = t1.add(t2);
    Time diff = t1.subtract(t2);

    cout << "First Time: ";
    t1.display();

    cout << "Second Time: ";
    t2.display();

    cout << "Addition: ";
    sum.display();

    cout << "Subtraction: ";
    diff.display();

    return 0;
}

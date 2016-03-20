#include <iostream>

using namespace std;

struct DivideByZero {
    double divisor;
    DivideByZero(double x) : divisor(x) {}
    void what () {cout << "Can't divide " << divisor << " by 0." << endl;}
};

double divide(double x, double y)
{
    if (y == 0)
        throw DivideByZero(x);
    else
        return x / y;
}

int main()
{
    try {
       cout << divide(101.5, 12.2) << endl;
       cout << divide(10.1, 0.0) << endl;
    }

    catch (DivideByZero &e) {
        e.what();
        return 1;
    }

    catch (...) {
        cerr << "Some other exception was caught." << endl;
        return 1;
    }

    return 0;
}

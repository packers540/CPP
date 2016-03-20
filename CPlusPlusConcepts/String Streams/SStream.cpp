#include <iostream>
#include <sstream>

using namespace std;

struct DivideByZero {
    double divisor;
    DivideByZero(double x) : divisor(x) {}
    const char* what () {
        //Allows me to define custom exceptions while maintaining the convention and data type used in std exceptions
        //I could also inherit the exception class and overwrite the virtual function what()
        stringstream stm;
        stm << "Can't divide " << divisor << " by 0." << endl;
        string temp = stm.str();
        return temp.c_str();
    }
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
        cerr << e.what();
        return 1;
    }

    catch (...) {
        cerr << "Some other exception was caught." << endl;
        return 1;
    }

    return 0;
}

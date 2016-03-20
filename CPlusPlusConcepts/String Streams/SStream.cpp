#include <iostream>
#include <sstream>
#include <exception>
#include <typeinfo>

using namespace std;

class DivideByZero : public exception{
    public:
        double divisor;
        DivideByZero(double x) : divisor(x) {}
        virtual const char* what () const throw() {
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
       DivideByZero * test = 0;
       typeid(*test);
       cout << divide(10.1, 0.0) << endl;
    }

    //Since my DivideByZero exception class inherits from the standard exceptions class and overwrite the what() function
    //The exceptions is thrown as reference so we can use polymorphism to look for both standard exceptions
    //and our custom defined ones
    catch (exception &e) {
        cerr << e.what();
        return 1;
    }

    catch (...) {
        cerr << "Some other exception was caught." << endl;
        return 1;
    }

    return 0;
}

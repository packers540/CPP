#include <iostream>

using namespace std;

int main()
{
    int x = 7;
    x &= ~(1u << 1);
    cout << x;
    return 0;
}

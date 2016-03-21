#include <iostream>
#include <deque>
#include <string>
#include <iterator>

using namespace std;

int main()
{
    deque <string> test;
    test.push_front("John");
    test.push_back("Bob");
    deque<string>::iterator it = test.begin();
    advance(it, 1);
    test.insert(it, "Nick");

    for (int i =0; i < test.size(); ++i){
        cout << test[i] << endl;
    }

    return 0;
}

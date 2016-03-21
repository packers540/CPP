#include <iostream>
#include <utility>

using namespace std;

int main()
{
    pair<string, string> phoneBook("Nick", "123-372-4403");
    cout << "Name: " << phoneBook.first << " Number: " << phoneBook.second <<endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    vector <char> test;
    ifstream file;
    file.open("C:\\Users\\Nick\\Desktop\\test.txt");
    char cinput;
    while (!file.eof()){
        cinput = file.get();
        test.push_back(cinput);
    }

    for (int i = 0; i < test.size(); ++i){
        cout << test[i] << endl;
    }

    return 0;
}

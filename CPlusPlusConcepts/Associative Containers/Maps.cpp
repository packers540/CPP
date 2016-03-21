#include <iostream>
#include <map>
#include <utility>

using namespace std;

template <typename T>
int hashFunc(T data)
{
    int key = (int)data % 11;
    return key;
}

int main()
{
    map <string, double> grades;
    grades["Nick"] = 90.0;
    grades["Susy"] = 95.1;
    grades["John"] = 60.5;

    cout<<grades["John"] << endl << endl << "Multiset HashTable." << endl;

    //MultiMap
    multimap <int, string> hashTable;
    hashTable.insert(pair<int, string> (hashFunc("Bob"), "Bob"));
    hashTable.insert(pair<int, string> (hashFunc("Nick"), "Nick"));
    hashTable.insert(pair<int, string> (hashFunc("Bill"), "Bill"));
    hashTable.insert(pair<int, string> (hashFunc("Susy"), "Susy"));
    hashTable.insert(pair<int, string> (hashFunc("Susan"), "Susan"));
    hashTable.insert(pair<int, string> (hashFunc("Alex"), "Alex"));
    hashTable.insert(pair<int, string> (hashFunc("Cindy"), "Cindy"));
    hashTable.insert(pair<int, string> (hashFunc("George"), "George"));
    hashTable.insert(pair<int, string> (hashFunc("Frodo"), "Frodo"));
    hashTable.insert(pair<int, string> (hashFunc("Sam"), "Sam"));
    hashTable.insert(pair<int, string> (hashFunc("Gamdalf"), "Gandalf"));

    multimap<int, string>::iterator it = hashTable.begin();

    for (it; it != hashTable.end(); ++it)
        cout << "Key: " << it->first << " Name: " << it->second<<endl;


    //Search for specific key values
    multimap<int, string>::iterator it_begin = hashTable.find(hashFunc("Nick"));
    multimap<int, string>::iterator it_end = hashTable.upper_bound(hashFunc("Nick"));

    for (it_begin; it_begin != it_end; ++it_begin){
        if (it_begin->second == "Nick") {
            cout << "Found Data!" <<endl;
            break;
        }
    }

    if (it_begin == it_end)
        cout<< "Data Not Found!" <<endl;




    return 0;
}

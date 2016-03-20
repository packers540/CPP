#include <iostream>
#include <list>

using namespace std;

template <class T>
void displayList(const T &myList)
{
    typename T::const_iterator it = myList.begin();
    while (it != myList.end()){
        cout << *it << endl;
        ++it;
    }
}

int main()
{
    list<string> myList;
    list<string> myList2;
    myList.push_back("Eggs");
    myList.push_back("Bread");
    myList.push_back("Milk");
    myList.push_back("Butter");
    myList.push_back("Ice Cream");
    myList.push_back("Chocolate");
    myList.push_back("Steak");

    displayList(myList);

    //sort list
    myList.sort();
    cout<<endl<<"--Sorted List--"<<endl;
    displayList(myList);

    //reverse list
    myList.reverse();
    cout<<endl<<"--Reversed List--"<<endl;
    displayList(myList);

    //copy list
    myList2.merge(myList);
    cout<<endl<<"--List 2"<<endl;
    displayList(myList2);

   //Remove specific data value
   myList2.remove("Eggs");
   cout<<endl<<"Eggs removed from list 2"<<endl;
   displayList(myList2);

   //Insert Element
   list<string>::iterator it = myList2.begin();
   ++it;

   myList2.insert(it, "Fish");
   cout<<endl<<"Fish inserted into 2nd pos in list"<<endl;
   displayList(myList2);

   //Splicing
   myList.splice(myList.begin(), myList2, myList2.begin(), myList2.end());
   cout<<endl<<"--List 1--"<<endl;
   displayList(myList);
   cout<<endl<<"--List 2--"<<endl;
   displayList(myList2);

    return 0;
}

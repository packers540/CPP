#include <iostream>
#include<vector>
#include<string>


using namespace std;

template<typename T>
class CList{
    private:
        vector<T> data;
    public:
        void add (T d){
            data.push_back(d);
        }

        void display(){
            for (int i = 0; i < data.size(); ++i)
                cout<< data[i] << endl;
        }


};

int main()
{
    CList<int> numbers;
    CList<string> names;

    numbers.add(10);
    numbers.add(20);
    numbers.add(40);
    numbers.add(50);

    names.add("Bob");
    names.add("Nick");
    names.add("John");

    numbers.display();
    cout<<endl;
    names.display();

    return 0;
}

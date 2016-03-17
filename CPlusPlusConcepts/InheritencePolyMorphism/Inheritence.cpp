#include <iostream>

using namespace std;

//base class
class Programmer{
    //An Attribute every programmer has and doesn't need to be directly accessed or changed by the derived class
    private:
        string Knowledge = " knows how to code in ";
    //An attribute every programmer has, but has the ability to be changed and accessed in the derived class
    protected:
        string name;
        int salary;
        string language;
    public:
        //Default Constructor
        Programmer (){
            name = "";
            language = "";
        }
        //Constructor
        Programmer (string n, string lang, int sal){
            language = lang;
            name = n;
            salary = sal;
        }
        //Print info about the programmer
        void printInfo(){
            cout << name << Knowledge << language << " and gets paid: "<< salary << endl;
        }

};

//derived class
class ComputerEng : public Programmer {
    private:
        string degree = "Computer Engineering";
        double gpa;
    public:
        //Constructor using inherited constructor
        ComputerEng (string n, string lang, int sal, double g)
            : Programmer(n, lang, sal)
            {
                gpa = g;
            }

        void printDegree()
        {
            cout<< name << " has a degree in " << degree << " and a "<< gpa << " GPA." << endl;
        }

};

int main()
{
    ComputerEng Nick("Nick", "C++", 60000, 2.88);
    Nick.printDegree();
    Nick.printInfo();
    return 0;
}

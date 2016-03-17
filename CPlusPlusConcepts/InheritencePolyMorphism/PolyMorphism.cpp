#include <iostream>
#include <vector>

using namespace std;

//base class
class GamingPlatforms{
    protected:
        int cost;
        int players;
        int games;
    public:
        GamingPlatforms(int c, int p, int g)
        {
            cost = c;
            players = p;
            games = g;
        }
        //PURE Virtual Function to print details about each console
        virtual void print() = 0;

};

//derived class
class PC : public GamingPlatforms{
    public:
        PC (int c, int p, int g) : GamingPlatforms(c, p, g) {}

        virtual void print()
        {
            cout << "The PC platform costs: " << cost << ", has " << players << " players, and has " << games << " games." << endl;
        }

};

//derived class
class Xbox: public GamingPlatforms{
    public:
        Xbox (int c, int p, int g) : GamingPlatforms(c, p, g) {}

        virtual void print()
        {
            cout << "The Xbox platform costs: " << cost << ", has " << players << " players, and has " << games << " games." << endl;
        }
};


int main()
{
    Xbox xbx(300, 10000, 500);
    PC p(1000, 5000, 1000);

    /*This is where polymorphism comes into play.
    I can create a vector of the type pointer of the base class
    I can then call the virtual function print, and the compiler is able
    to decide which function to use based on the object stored in the vector.*/
    vector <GamingPlatforms*> GamingPlats;
    GamingPlats.push_back(&xbx);
    GamingPlats.push_back(&p);
    //Uses xbox print function
    GamingPlats[0]->print();
    //Uses PC print function
    GamingPlats[1]->print();
    return 0;
}

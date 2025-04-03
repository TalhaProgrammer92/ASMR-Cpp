#include <iostream>

////////////////////
// Constants
////////////////////
#define RED "\033[91m"
#define BLUE "\033[94m"
#define YELLOW "\033[93m"
#define BOLD "\033[1m"
#define RESET "\033[0m"

using namespace std;

////////////////////
// Player
////////////////////
class Player
{
private:
    string name;
    int wins;
public:
    Player(string name) : name(name), wins(0) {}

    //* Getters
    string getName() {return name;}
    int getWins() {return wins;}

    //* Method to increase wins
    void increaseWins() {wins++;}

    //* Method to show details
    void showInfo(){
        cout << "Name:\t" << name << endl
             << "Wins:\t" << wins << endl;
    }
};


int main() {
    // cout << RED << "Hello " << RESET << BLUE << "World!" << RESET << endl;
    Player p("Talha Ahmad");
    p.increaseWins();
    p.increaseWins();
    p.increaseWins();

    p.showInfo();

    return 0;
}
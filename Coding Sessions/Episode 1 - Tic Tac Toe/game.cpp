#include <iostream>

using namespace std;

/////////////////////////
// Color Constants
/////////////////////////
#define RED "\033[91m"
#define BLUE "\033[94m"
#define YELLOW "\033[93m"
#define BOLD "\033[1m"
#define RESET "\033[0m"

/////////////////////
// Functions
/////////////////////
//* function to get color code with given text
string getColorCode(string text, string color, bool bold = false);

/////////////////////
// Player class
/////////////////////
class Player
{
private:
    string name, symbol;
    int wins;

public:
    //* Constructor
    Player(string name, string symbol);

    //* Getters
    string getName();
    int getWins();

    //* Display Info
    void showInfo();
};

////////////////////
// Board
////////////////////
class Board
{
private:
    string grid[3][3], line_separator = getColorCode("---+---+---", YELLOW, true), pipe = getColorCode("|", YELLOW, true);

public:
    //* Constructor
    Board();

    //* Board clear/reset
    void reset();

    //* Display Board
    void display();
};

int main()
{
    
    return 0;
}
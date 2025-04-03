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
string getColorCode(string text, string color, bool bold = false)
{
    return (bold) ? color + BOLD + text + RESET : color + text + RESET;
}

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
    Player(string name, string symbol) : name{name}, symbol(symbol), wins(0) {}

    //* Getters
    string getName() { return name; }
    int getWins() { return wins; }

    //* Display Info
    void showInfo()
    {
        cout << "Name:\t" << name << endl
             << "Wins:\t" << wins << endl;
    }
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
    Board() { reset(); }

    //* Board clear/reset
    void reset()
    {
        char count = '1';
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                string cell = " ";
                cell[0] = count++;
                grid[i][j] = cell;
            }
        }
    }

    //* Display Board
    void display()
    {
        //* Rows
        for (int i = 0; i < 3; i++)
        {
            //* Columns
            for (int j = 0; j < 3; j++)
            {
                cout << " " + grid[i][j] + " ";
                if (j < 2)
                    cout << pipe;
            }
            cout << endl
                 << line_separator << endl;
        }
    }
};

int main()
{
    Board b;
    b.display();
    return 0;
}
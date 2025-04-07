#include <iostream>
#include <limits>

using namespace std;

/////////////////////////
// Color Constants
/////////////////////////
#define RED "\033[91m"
#define BLUE "\033[94m"
#define YELLOW "\033[93m"
#define GREEN "\033[92m"
#define MAGENTA "\033[95m"
#define CYAN "\033[96m"
#define BOLD "\033[1m"
#define RESET "\033[0m"

/////////////////////
// Functions
/////////////////////

//* function to get color code with given text
string getColorCode(string text, string color, bool bold = false);

//* function to clear the console/terminal screen
void clrscr();

//* function to hold the screen
void holdScreen();

/////////////////////
// Symbol class
/////////////////////
class Symbol
{
private:
    //* Attributes
    char symbol;
    string code;
    bool bold;

public:
    //* Constructors
    //! Default constructor
    Symbol() {};
    //! Constructor with parameters
    Symbol(char symbol, string code);

    //* Getters
    char getSymbol();
    string getColor();

    //* Property
    void makeBold();

    //* Display symbol (overload <<)
    friend ostream &operator<<(ostream &os, const Symbol &symbol);

    //* Overload == operator
    bool operator==(const Symbol &other) const;

    //* Overload != operator
    bool operator!=(const Symbol &other) const;
};

/////////////////////
// Board class
/////////////////////
class Board
{
private:
    //* Attributes
    Symbol *board;
    int size;
    int moves;

public:
    //* Constructor
    Board(int size);

    //* Clear board
    void clear();

    //* display board
    void display();

    //* Get a symbol/cell
    Symbol get(int index);

    //* Insert a symbol/cell
    void insert(Symbol symbol, int index);
};

/////////////////////
// Entry Point
/////////////////////
int main()
{
    Board board(7);
    board.display();

    return 0;
}

////////////////////////////
// Function Definitions
////////////////////////////

//* function to get color code with given text
string getColorCode(string text, string color, bool bold)
{
    return (bold) ? BOLD + color + text + RESET : color + text + RESET;
}

//* function to clear the console/terminal screen
void clrscr()
{
//? Clear the console/terminal screen
#ifdef _WIN32
    //! For Windows
    system("cls");
#else
    //! For Linux and MacOS
    system("clear");
#endif
}

//* function to hold the screen
void holdScreen()
{
    cout << getColorCode("\nPress Enter to continue...", YELLOW, true);
    //! ignore the invalid input
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //! wait for user to press enter
    cin.get();
}

//* Symbol class constructor
Symbol::Symbol(char symbol, string code)
{
    this->symbol = symbol;
    this->code = code;
    this->bold = false;
}

//* Symbol class getters
char Symbol::getSymbol()
{
    return this->symbol;
}

string Symbol::getColor()
{
    return this->code;
}

//* Symbol class makeBold
void Symbol::makeBold()
{
    //? Make the symbol bold
    this->bold = true;
    this->code = BOLD + this->code;
}

//* Symbol class overload << operator
ostream &operator<<(ostream &os, const Symbol &symbol)
{
    //? Display the symbol with color code
    os << symbol.code << symbol.symbol << RESET;
    return os;
}

//* Symbol class overload == operator
bool Symbol::operator==(const Symbol &other) const
{
    //? Check if the symbols are equal
    return this->symbol == other.symbol;
}

//* Symbol class overload != operator
bool Symbol::operator!=(const Symbol &other) const
{
    //? Check if the symbols are not equal
    return this->symbol != other.symbol;
}

/////////////////////
// Board class
/////////////////////

//* Constructor
Board::Board(int size /* Limit: 3 to 9 */)
{
    this->size = size;

    //! Clear board
    clear();
}

//* Clear the board
void Board::clear()
{
    //! Declare an array to pointer
    board = new Symbol[size * size];

    //! Iteration to set '-' symbols to all cells
    for (int i = 0; i < size * size; i++)
        board[i] = Symbol('-', CYAN);
}

//* Display the board
void Board::display()
{
    //! Number strip (columns)
    cout << "  ";
    for (int i = 1; i <= size; i++)
        cout << ' ' << getColorCode(to_string(i), YELLOW, true) << ' ';

    //! Board
    int n = 1;
    for (int i = 0; i < size * size; i++)
    {
        //! New line & Number strip (rows)
        if (i % size == 0)
        {
            cout << endl;
            cout << getColorCode(to_string(n++), YELLOW, true) << ' ';
        }

        //! Cell
        cout << ' ' << board[i] << ' ';
    }
}

#include <iostream>

using namespace std;

/////////////////////////
// Color Constants
/////////////////////////
#define RED "\033[91m"
#define BLUE "\033[94m"
#define YELLOW "\033[93m"
#define GREEN "\033[92m"
#define BOLD "\033[1m"
#define RESET "\033[0m"

/////////////////////
// Functions
/////////////////////

//* function to get color code with given text
string getColorCode(string text, string color, bool bold = false);

//* function to clear the console/terminal screen
void clrscr();

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
    //* 3x3 grid & line separator
    string grid[3][3],                                              //! The grid is a 2D array of strings to represent the board
        line_separator = getColorCode("---+---+---", YELLOW, true), //! Line separator
        pipe = getColorCode("|", YELLOW, true);                     //! Pipe separator

public:
    //* Constructor
    Board();

    //* Getters
    string getCell(int row, int col);

    //* Board clear/reset
    void reset();

    //* Display Board
    void display();

    //* Check if the board is full
    bool isFull();
};

////////////////////
// Game
////////////////////
class Game
{
private:
    //* Game variables
    Player *player;         //! Array of players
    Board board;            //! Board object
    int turn;               //! Current turn
    bool game_over, winner; //! Status flags

public:
    //* Constructor
    Game();

    //* Start Game
    void start();

    //* Check for winner
    bool checkWinner();

    //* List players
    void listPlayers();
};

////////////////////
// Main
////////////////////
int main()
{
    //* Create game object
    Game game;

    //* Start the game
    game.start();

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
    system("cls"); //! For Windows
#else
    system("clear"); //! For Linux and MacOS
#endif
}

//* Player class constructor
Player::Player(string name, string symbol)
{
    this->name = name;
    this->symbol = symbol;
    this->wins = 0;
}

//* Player class getters
string Player::getName()
{
    return this->name;
}

int Player::getWins()
{
    return this->wins;
}

//* Player class showInfo
void Player::showInfo()
{
    //? Display player name
    cout << getColorCode("Name:\t", GREEN, true) << getColorCode(this->name, BLUE) << endl;

    //? Display player wins
    cout << getColorCode("Wins:\t", GREEN, true) << getColorCode(to_string(this->wins), YELLOW) << endl;
}

//* Board class constructor
Board::Board()
{
    this->reset(); //! Reset the board to empty strings
}

//* Board class getters
string Board::getCell(int row, int col)
{
    return this->grid[row][col];
}

//* Board class reset
void Board::reset()
{
    char number = '1';

    //? Reset the grid to empty strings
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->grid[i][j] = getColorCode(string(1, number), GREEN);
            number++;
        }
    }
}

//* Board class display
void Board::display()
{
    //? Display the grid
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            //? Display the cell
            cout << ' ' << this->grid[i][j] << ' ';

            //? Display the pipe separator
            if (j != 2)
                cout << this->pipe;
        }
        //? Display the line separator
        cout << endl;

        //? Display the line separator
        if (i != 2)
            cout << this->line_separator << endl;
    }
}

//* Board class isFull
bool Board::isFull()
{
    char number = '1';

    //? Check if the board is full
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            //? Check if the cell is empty
            if (this->grid[i][j] == getColorCode(string(1, number), GREEN))
                return false;

            //? Increment the number
            number++;
        }
    }

    return true;
}

//* Game class constructor
Game::Game()
{
    this->turn = 0;             //! Initialize turn to 0
    this->game_over = false;    //! Initialize game_over to false
    this->winner = 0;           //! Initialize winner to false

    //? Create players
    string name1, name2, symbol1, symbol2;

    //? Get player 1 name and symbol
    cout << getColorCode("Enter Player 1 Name: ", GREEN, true);
    getline(cin, name1);
    symbol1 = getColorCode("X", BLUE);

    //? Get player 2 name and symbol
    cout << getColorCode("Enter Player 2 Name: ", GREEN, true);
    getline(cin, name2);
    symbol2 = getColorCode("O", RED);

    //? Create player objects
    this->player = new Player[2]{
        Player(name1, symbol1),
        Player(name2, symbol2)};
    
    //? Clear the console/terminal screen
    clrscr();
}

//* Game class start
void Game::start()
{
    
}
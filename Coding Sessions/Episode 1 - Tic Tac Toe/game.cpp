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
    Symbol() {}; //! Default constructor
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
// Player class
/////////////////////
class Player
{
private:
    //* Attributes
    string name;
    Symbol symbol;
    int wins;

public:
    //* Constructor
    Player(string name, Symbol symbol);

    //* Getters
    string getName();
    Symbol getSymbol();
    int getWins();

    //* Increment wins
    void incrementWins();

    //* Display Info
    void showInfo();
};

////////////////////
// Board
////////////////////
class Board
{
private:
    //* 3x3 Grid
    //! The grid is a 2D array of strings to represent the board
    Symbol grid[3][3];

    //* Separators
    string line_separator = getColorCode("---+---+---", YELLOW, true), //! Line separator
        pipe = getColorCode("|", YELLOW, true);                        //! Pipe separator

public:
    //* Constructor
    Board();

    //* Getters
    Symbol getCell(int row, int col);

    //* Make symbol bold
    void makeSymbolBold(int row, int col);

    //* Board clear/reset
    void reset();

    //* Display Board
    void display();

    //* Check if the board is full
    bool isFull();

    //* Place symbol in the board
    bool placeSymbol(int index, Symbol symbol);
};

////////////////////
// Game
////////////////////
class Game
{
private:
    //* Game variables
    Player *player; //! Array of players
    Board board;    //! Board object
    int turn;       //! Current turn
    bool game_over; //! Status flags

    //* Check for winner
    bool checkWinner();

    //* Update turn
    void updateTurn();

    //* List players
    void listPlayers();

    //* Play a round
    void playRound();

public:
    //* Constructor
    Game();

    //* Start Game
    void start();
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

//* function to hold the screen
void holdScreen()
{
    cout << getColorCode("Press Enter to continue...", YELLOW, true);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //! ignore the invalid input
    cin.get();                                           //! wait for user to press enter
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
    this->bold = true;
    this->code = BOLD + this->code; //! Make the symbol bold
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

//* Player class constructor
Player::Player(string name, Symbol symbol)
{
    //? Initialize player name and symbol
    this->name = name;
    //! Create a new symbol object
    this->symbol = symbol;

    //? Initialize player wins
    this->wins = 0;
}

//* Player class getters
string Player::getName()
{
    return this->name;
}

Symbol Player::getSymbol()
{
    return this->symbol;
}

int Player::getWins()
{
    return this->wins;
}

//* Player class increment wins
void Player::incrementWins()
{
    this->wins++;
}

//* Player class showInfo
void Player::showInfo()
{
    //? Display player name
    cout << getColorCode("Name:\t", MAGENTA, true) << getColorCode(this->name, CYAN) << endl;

    //? Display player symbol
    cout << getColorCode("Symbol:\t", MAGENTA, true) << getColorCode(string(1, this->symbol.getSymbol()), CYAN) << endl;

    //? Display player wins
    cout << getColorCode("Wins:\t", MAGENTA, true) << getColorCode(to_string(this->wins), CYAN) << endl;
}

//* Board class constructor
Board::Board()
{
    this->reset(); //! Reset the board to empty strings
}

//* Board class getters
Symbol Board::getCell(int row, int col)
{
    return this->grid[row][col];
}

//* Board class makeSymbolBold
void Board::makeSymbolBold(int row, int col)
{
    //? Make the symbol bold
    this->grid[row][col].makeBold();
}

//* Board class reset
void Board::reset()
{
    char number = '1';

    //? Reset the grid to numbered strings
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            //? Set the cell to the number with color code
            Symbol symbol(number++, GREEN);
            this->grid[i][j] = symbol;
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
            Symbol symbol(number++, GREEN);
            //? Check if the cell is empty
            if (this->grid[i][j] == symbol)
                return false;

            //? Increment the number
            number++;
        }
    }

    return true;
}

//* Board class placeSymbol
bool Board::placeSymbol(int index, Symbol symbol)
{
    //? Convert index to row and column
    int row = (index - 1) / 3;
    int col = (index - 1) % 3;

    //? Check if the cell is empty
    if (this->grid[row][col] != Symbol('1' + index - 1, GREEN))
        return false;

    //? Place the symbol in the cell
    this->grid[row][col] = symbol;

    return true;
}

//* Game class constructor
Game::Game()
{
    //? Initialize game variables
    //! Initialize turn to 0
    this->turn = 0;
    //! Initialize game_over to false
    this->game_over = false;

    //? Create players
    string name1, name2;
    Symbol symbol1, symbol2;

    //? Get player 1 name and symbol
    cout << getColorCode("Enter Player 1 (X) Name: ", MAGENTA, true);
    getline(cin, name1);
    symbol1 = Symbol('X', BLUE);

    //? Get player 2 name and symbol
    cout << getColorCode("Enter Player 2 (O) Name: ", MAGENTA, true);
    getline(cin, name2);
    symbol2 = Symbol('O', BLUE);

    //? Create player objects
    this->player = new Player[2]{
        Player(name1, symbol1),
        Player(name2, symbol2)};

    //? Clear the console/terminal screen
    clrscr();
}

//* Game class updateTurn
void Game::updateTurn()
{
    turn ^= 1; //! Toggle the turn between 0 and 1
}

//* Game class listPlayers
void Game::listPlayers()
{
    //? Display players info
    player[0].showInfo();
    cout << endl;

    player[1].showInfo();
    cout << endl;

    //? Prompt user to continue / hold the screen
    holdScreen();
}

//* Game class checkWinner
bool Game::checkWinner()
{
    //? Check for winner
    Symbol symbol = player[turn].getSymbol();

    //? Check rows & columns
    for (int i = 0; i < 3; i++)
        //? Check rows
        if (board.getCell(i, 0) == symbol && board.getCell(i, 1) == symbol && board.getCell(i, 2) == symbol)
        {
            //! Make the symbols bold
            board.makeSymbolBold(i, 0);
            board.makeSymbolBold(i, 1);
            board.makeSymbolBold(i, 2);
            
            return true;
        }

        //? Check columns
        else if (board.getCell(0, i) == symbol && board.getCell(1, i) == symbol && board.getCell(2, i) == symbol)
        {
            return true;
        }

    //? Check diagonals
    if (board.getCell(0, 0) == symbol && board.getCell(1, 1) == symbol && board.getCell(2, 2) == symbol)
    {
        return true;
    }

    if (board.getCell(0, 2) == symbol && board.getCell(1, 1) == symbol && board.getCell(2, 0) == symbol)
    {
        return true;
    }

    return false;
}

//* Game class playRound
void Game::playRound()
{
    //? Variables
    int index;
    bool valid = false;

    //? Reset the board
    board.reset(); //! Reset the board

    //? Start the game
    while (true)
    {
        //? Clear the console/terminal screen
        clrscr();

        //? Display the board
        board.display();

        //? Display the current player
        cout << getColorCode("\nCurrent Player: ", GREEN, true) << player[turn].getName() << endl;

        //? Take input from the user & place symbol
        do
        {
            try
            {
                //? Prompt user to enter cell number
                cout << getColorCode("\nEnter cell number (1-9): ", GREEN);
                cin >> index;

                //? Check if input failed (e.g., non-integer input)
                if (cin.fail())
                {
                    cin.clear();                                         //! Clear error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //! Discard bad input
                    throw runtime_error("Invalid input");
                }

                //? Check if the cell is valid
                if (index < 1 || index > 9)
                {
                    cout << getColorCode("Invalid cell number! Try again.\n", RED);
                    valid = false;
                    continue;
                }

                //? Check if the cell is already occupied
                if (!board.placeSymbol(index, player[turn].getSymbol()))
                {
                    cout << getColorCode("Cell already occupied! Try again.\n", RED);
                    valid = false;
                    continue;
                }

                valid = true;
            }
            //? Catch invalid input exceptions
            catch (const exception &e)
            {
                cout << getColorCode("Invalid input! Try again.\n", RED);
                valid = false;
                cin.clear();                                         //! Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //! Discard bad input
            }
        } while (!valid);

        //? Check for winner
        if (checkWinner())
        {
            //? Display the board
            clrscr();
            board.display();

            //? Display message
            cout << getColorCode("Game Over! " + player[turn].getName() + " won!\n", YELLOW, true);

            //? Increment the winner's wins
            player[turn].incrementWins();
            break;
        }

        //? Check if game is draw
        if (board.isFull())
        {
            //? Display the board
            clrscr();
            board.display();

            //? Display message
            cout << getColorCode("Game Over! It's a draw.\n", YELLOW, true);
            break;
        }

        //? Update the turn
        updateTurn();
    }

    //? Display result
    holdScreen(); //! Hold the screen
}

//* Game class start
void Game::start()
{
    int choice; //! User choice

    //? Game loop
    while (!game_over)
    {
        //? Clear the console/terminal screen
        clrscr();

        //? Display welcome message
        cout << getColorCode("Welcome to Tic Tac Toe!\n\n", GREEN, true);

        //? Prompt user to play the game
        cout << getColorCode("1: Play Game, 2: View players info, 3: Quit? ", YELLOW, true);
        cin >> choice;

        //? Decide what to do based on user choice
        switch (choice)
        {
        case 1:
            //? Play the game
            playRound();
            break;

        case 2:
            //? Display players info
            clrscr();      //! Clear the console/terminal screen
            listPlayers(); //! List players
            break;

        case 3:
            //? Quit the game
            clrscr(); //! Clear the console/terminal screen
            cout << getColorCode("Thanks for playing!\n", GREEN, true);
            game_over = true; //! Set game_over to true
            break;

        default:
            break;
        }
    }
}
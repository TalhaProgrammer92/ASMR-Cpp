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
    string getSymbol();
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

    //* Place symbol in the board
    bool placeSymbol(int index, string symbol);
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

    //* Check for winner
    bool checkWinner();

    //* Update turn
    void updateTurn();

    //* List players
    void listPlayers();

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

string Player::getSymbol()
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

    //? Reset the grid to numbered strings
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

//* Board class placeSymbol
bool Board::placeSymbol(int index, string symbol)
{
    //? Convert index to row and column
    int row = (index - 1) / 3;
    int col = (index - 1) % 3;

    //? Check if the cell is empty
    if (this->grid[row][col] == getColorCode("X", BLUE) || this->grid[row][col] == getColorCode("O", RED))
        return false;

    //? Place the symbol in the cell
    this->grid[row][col] = symbol;

    return true;
}

//* Game class constructor
Game::Game()
{
    this->turn = 0;          //! Initialize turn to 0
    this->game_over = false; //! Initialize game_over to false
    this->winner = 0;        //! Initialize winner to false

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

    //? Prompt user to continue
    cout << getColorCode("Press any key to continue...", GREEN, true);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //! Wait for user input
    cin.get();                                           //! Wait for user input
}

//* Game class checkWinner
bool Game::checkWinner()
{
    //? Check for winner
    string symbol = player[turn].getSymbol();

    //? Check rows
    for (int i = 0; i < 3; i++)
        if (board.getCell(i, 0) == symbol && board.getCell(i, 1) == symbol && board.getCell(i, 2) == symbol)
        {
            winner = turn; //! Set winner to current player
            return true;
        }

    //? Check columns
    for (int i = 0; i < 3; i++)
        if (board.getCell(0, i) == symbol && board.getCell(1, i) == symbol && board.getCell(2, i) == symbol)
        {
            winner = turn; //! Set winner to current player
            return true;
        }

    //? Check diagonals
    if (board.getCell(0, 0) == symbol && board.getCell(1, 1) == symbol && board.getCell(2, 2) == symbol)
    {
        winner = turn; //! Set winner to current player
        return true;
    }
    if (board.getCell(0, 2) == symbol && board.getCell(1, 1) == symbol && board.getCell(2, 0) == symbol)
    {
        winner = turn; //! Set winner to current player
        return true;
    }

    return false;
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
            //! cell number
            int index;

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
                while (true)
                {
                    //? Prompt user to enter cell number
                    cout << getColorCode("Enter cell number (1-9): ", GREEN);
                    cin >> index;

                    //? Check if the input is valid
                    if (cin.fail())
                    {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');      //! ignore the invalid input
                        cout << getColorCode("Invalid input! Try again.\n", RED); //! display error message
                        continue;
                    }

                    //? Check if the cell is valid
                    if (index < 1 || index > 9)
                    {
                        cout << getColorCode("Invalid cell number! Try again.\n", RED);
                        continue;
                    }

                    //? Check if the cell is already occupied
                    if (!board.placeSymbol(index, player[turn].getSymbol()))
                    {
                        cout << getColorCode("Cell already occupied! Try again.\n", RED);
                        continue;
                    }
                }

                //? Check for winner
                if (checkWinner())
                {
                    //? Display the board
                    clrscr();
                    board.display();

                    //? Display message
                    cout << getColorCode("Game Over! " + player[winner].getName() + " won!\n", YELLOW, true);

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
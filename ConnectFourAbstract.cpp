/*
 * File:   ConnectFourAbstract.cpp
 * Author: Emre OZGUN
 *
 *Implemantation of ConnectFourAbstract class
 */

#include <iostream>
#include <fstream>

#include "ConnectFourAbstract.h"
#include "Cell.h"

//One funtion is not directly related with the game
namespace Str
{
using std::endl;
using std::cin;
using std::cerr;
using std::string;
//this function is not directly related to the game, only to read the inputs
string readLine()
{
    string line;
    getline(cin, line);
    if (cin.eof())
    {
        cerr << endl << "ERROR: cin EOF" << endl;
        exit(1);
    }
    return line;
}

}

namespace ConnectFourGame
{

using namespace Str; //I use the readLine function for these namespace
int ConnectFourAbstract::LivCell = 0;

using std::ostream;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::cout;
using std::cin;
using std::cerr;
using std::max;
using std::streamsize;

//Default assignment of data members
ConnectFourAbstract::ConnectFourAbstract() : gameBoard(NULL),width(0),height(0),turn(0),filename("board.txt"),
    command(""),gameMode(U_vs_U),gameType(),winner(0),error(0)
{
    //Empty implementation
}

//Constructor of take two parameter
ConnectFourAbstract::ConnectFourAbstract(int width,int height) : ConnectFourAbstract()
//same assignment with default constructor except width,height and dynamic gameboard
{
    int i,j;
    this->width = width;
    this->height = height;

    gameBoard = new Cell*[height];

    for(int i = 0; i < height; i++)
        gameBoard[i] = new Cell[width];

    for( i = 0; i < height; i++)
    {
        for(j = 0; j <width; j++)
        {
            gameBoard[i][j].setType(Empty);
        }

    }
}
//ı used that function in assignmet operator because
//only pointers or dynamic allocation will be change
//this function copy gameboard another one
Cell** ConnectFourAbstract::copyGameBoard() const
{
    int i, j;
    Cell ** board = new Cell*[height];
    for(int i = 0; i < height; i++)
        board[i] = new Cell[width];
    for( i = 0; i < height; i++)
    {
        for(j = 0; j <width; j++)
        {
            // gameBoard[i][j].setType(game.gameBoard[i][j].getType());
            this->gameBoard[i][j] = board[i][j];
        }
    }
    return board;
}

//Copy constructor
ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract &game)
{
    int i,j;
    this->width = game.width;
    this->height = game.height;
    this->turn = game.turn;
    this->filename = game.filename;
    this->command = game.command;
    this->gameMode = game.gameMode;
    this->gameType = game.gameType;
    this->winner = game.winner;
    this->error = game.error;

    this->gameBoard = new Cell*[height];

    for(int i = 0; i < height; i++)
        this->gameBoard[i] = new Cell[width];

    for( i = 0; i < height; i++)
    {
        for(j = 0; j <width; j++)
        {
            this->gameBoard[i][j] = game.gameBoard[i][j];
        }

    }

}
//I assign same data members and then copy the gameboard
ConnectFourAbstract & ConnectFourAbstract::operator = (const ConnectFourAbstract &rightSideObje)
{

    this->~ConnectFourAbstract();
    this->width = rightSideObje.width;
    this->height = rightSideObje.height;
    this->turn = rightSideObje.turn;
    this->filename = rightSideObje.filename;
    this->command = rightSideObje.command;
    this->gameMode = rightSideObje.gameMode;
    this->gameType = rightSideObje.gameType;
    this->winner = rightSideObje.winner;
    this->error = rightSideObje.error;

    this->gameBoard = rightSideObje.copyGameBoard();
    return *this;
}


//Destructor delete dynamic games array automaticly
ConnectFourAbstract::~ConnectFourAbstract()
{


    if (gameBoard == NULL)
        return;

    //Deleting dynamic array with constructor
    for(int i = 0; i < getHeight(); i++)
        delete [] gameBoard[i];
    delete [] gameBoard;

    gameBoard = NULL;
}
/*GETTERS*/
GameType ConnectFourAbstract::getGameType() const
{
    return gameType;
}
int ConnectFourAbstract::getWidth()const //will take Width
{
    return width;
}

int ConnectFourAbstract::getHeight()const //will take Height
{
    return height;
}

GameMode ConnectFourAbstract::getMode()const //will take game Mode
{
    return gameMode;
}

string ConnectFourAbstract::getCommand()const //will take Which command
{
    return command;
}

bool ConnectFourAbstract::getError() //will take errr
{
    return error;
}

int ConnectFourAbstract::getWinner() // will take winnner or not (0 == not winner || 1 == winner)
{
    return winner;
}

Celltype ConnectFourAbstract::getUserCelltype()
{
    if (getUserNo() == 1)
        return user1;
    else
        return user2;
}

string ConnectFourAbstract::getFilename()const //will take filename
{
    return filename;
}

/*SETTERS*/
void ConnectFourAbstract::setGameType(const GameType gameType)
{
    this->gameType = gameType;
}

void ConnectFourAbstract::setHeight(const int height)
{
    this->height = height;
}

void ConnectFourAbstract::setWidth(const int width)
{
    this->width = width;
}

void ConnectFourAbstract::setGameMode(GameMode gameMode)
{
    this->gameMode = gameMode;
}

int ConnectFourAbstract::increaseLivingCells()
{
    return LivCell++;
}

void ConnectFourAbstract::setCommand(string command)
{
    this->command = command;
}

void ConnectFourAbstract::setFilename(string filename)
{
    this->filename = filename;
}

int ConnectFourAbstract::getUserNo()
{
    return (turn % 2) + 1;
}

//That play function play as computer
bool ConnectFourAbstract::play()
{
    int input = getComputerInput();


    // bool moveReturn = moveUser(input, getUserNo());
    bool moveReturn = play(input);

    return moveReturn;
}

//That play function play as user--Operator overloading
bool ConnectFourAbstract::play(int pos)
{
    //cout << "Pos: " << pos << endl;
    /*Controls about my attempts */
    //cout << "UserNo: " << getUserNo()<< endl;
    return moveUser(pos, getUserNo());
}

//One turn for objects
bool ConnectFourAbstract::playOneTurn(bool * moveCompleted)
{
    bool isComputer;

    int input;
    //if not equal NULL assign that false
    if (moveCompleted != NULL)
        *moveCompleted = false;

    // cout << "turn: " << turn <<  " userNo: " << getUserNo() << " started" << endl;

    //check for user2 and is it computer or player
    if (getUserNo() == 2)
    {
        if (getMode() == U_vs_U)
        {
            isComputer = false; //user2 is player
        }
        else if (getMode() == U_vs_C)
        {
            isComputer = true; //user2 is computer
        }
    }

    if(isComputer == true && getUserNo() == 2)
    {
        if (winner != 0)
        {
            cout << "Winner" << endl;
            return true;
        }

        //play as computer function with no arguments
        bool playReturn = play();
        //check to play
        if (playReturn == false)
        {
            return false;
        }
    }
    //if it is not computer take players inputs
    else
    {

        input = getUserInput();


        if (input < 0)
        {
            runCommand(getCommand(),input);
            return false;
        }

        if (winner != 0)
        {
            // cout << " Winner" << endl;
            return true;
        }

        // cout << "play" << endl;
        //if play function return value isnt true,one turn didnt completed
        bool playReturn = play(input);
        if (playReturn == false)
            return false;

    }

    // cout << "move completed" << endl;

    if (moveCompleted != NULL)
        *moveCompleted = true;

    //increase livingcell with every move
    increaseLivingCells();
    winner = checkWinner(getUserCelltype(), true);
    turn++;

    // cout << "checkWinner : " << winner << endl;
    if(winner > 0)
        return true;

    return false;
}
//play as single mod while game is finished
void ConnectFourAbstract::playSingleGame()
{
    while (true)
    {
        //Game will continue in single Mode depending playOneTurn function
        bool gameEnd = playOneTurn();
        printGame();
        //if return true from playOneTurn game will finish
        if (gameEnd)
        {
            break;
        }
    }
}

bool ConnectFourAbstract::moveUser(int res, int user)
{
    int i;
    //to put in the empty place
    for (i = getHeight() - 1; i >= 0; i--)
    {
        if (gameBoard[i][res].getType() == Empty)
        {
            //Moving cells set and assign there
            if(user == 1)
            {
                gameBoard[i][res].setType(user1);
                gameBoard[i][res] = Cell(i,res,user1);
                break;
            }
            else
            {
                gameBoard[i][res].setType(user2);
                gameBoard[i][res] = Cell(i,res,user2);
                break;
            }


        }
    }
    //İt is forbbiden to move
    if (i < 0)
    {
        return false;
    }
    //Move completed
    return true;
}

int ConnectFourAbstract::checkUserInput(string command)
{
    //İt means not command only move
    if (command.length() == 1)
    {
        //if user enter input upper it will be lower
        int pos = toupper(command[0]) - 'A';
        //control of board limits
        if (pos <= getWidth() && pos >= 0 &&  gameBoard[0][pos].getType() == Empty)
        {
            return pos;
        }
    }
    //it means command SAVE or LOAD
    else if (command.length() > 1)
    {
        //For save the game substr take 4 letter in input
        if (command.substr(0, 4) == "SAVE")
        {
            return -2;

        }
        //For taking 4 letter for it is LOAD command or not
        else if (command.substr(0, 4) == "LOAD")
            return -3;

    }

    // error
    return -1;
}

int ConnectFourAbstract::getUserInput()
{

    while (1)
    {
        cout << "User" << getUserNo() << " your turn enter your letter: ";
        command = readLine();
        cout << endl;
        //will check that input command or move if it is illegal command ask again
        int ret = checkUserInput(command);

        if (ret != -1)
            return ret; //error

    }

}
//Computer finding the best cell to play with playing like player
int ConnectFourAbstract::getComputerInput()
{

    int rivalUserNo;
    Celltype rivalCelltype; //player Celltype
    cout << "UserNo Computer: " << getUserNo() << endl;
    //assign Players userNo and Celltype
    if (getUserNo() == 1)
    {
        rivalUserNo = 2;
        rivalCelltype = user2;
    }
    else
    {
        rivalUserNo = 1;
        rivalCelltype = user1;
    }

    int i;

    //İt the first precedence(oncelik)
    // to look for himself can be winner
    for (i = 0; i < getHeight(); i++)
    {
        //will search move while top and play like user
        if (moveUser(i, getUserNo()) == false)
        {
            continue;
        }
        //and then check game will be finish if game will be finish with that move delete that move and that play
        if (checkWinner(getUserCelltype(), false) != 0)
        {
            removeTop(i);
            return i;
        }
        removeTop(i);
    }

    //İt the second precedence(
    // to look for rival can be winner
    //finding which move will make the user winner and play that Cell
    for (i = 0; i < getWidth(); i++)
    {
        if (moveUser( i, rivalUserNo) == false)
            continue;

        if (checkWinner(rivalCelltype, false) != 0)
        {
            removeTop(i);
            return i;
        }

        removeTop(i);
    }

    //And all precedence are not avaliable,playing to randomly
    return rand() % getWidth();
}
//We play like user should delete that move that function about that topic
int ConnectFourAbstract::removeTop(int position)
{
    int i;
    for (i = 0; i < getHeight(); i++)
    {
        //Which position are not empty or point loop will break and then that cell will be point again
        if (gameBoard[i][position].getType() != Empty)
            break;
    }
    if (i >= height)
        return -1;

    //Move being point again that assignement
    gameBoard[i][position] = Cell(i,position,Empty);

    return 0;
}
//setTop and getTop function is about with Undo command
//But it is the comman function about game it is not special for ConnectFourPlusUndo
//Maybe that function can use another problem cause of that ı used functions in base class
Celltype ConnectFourAbstract::getTop(int position)
{
    int i;
    for (i = 0; i < getHeight(); i++)
    {
        //Which position are not empty or point loop will break and then that cell will be point again
        if (gameBoard[i][position].getType() != Empty)
            break;
    }

    if (i >= getHeight())
        return Empty;

    //will return celltype of top
    return gameBoard[i][position].getType();
}

int ConnectFourAbstract::setTop(int position,Celltype celltype)
{
    int i;
    for (i = 0; i < getHeight(); i++)
    {
        //Which position are not empty or point loop will break and then that cell will be point again
        if (gameBoard[i][position].getType() != Empty)
            break;
    }
    if (i >= height)
        return -1;
    //will set top of cell
    gameBoard[i][position].setType(celltype);

    return 0;
}

//starting input about GameMode
int ConnectFourAbstract::startingInput()
{
    char choose;

    do
    {
        cout << " Do you wanna play with user or computer(Press 'P' for user, Press 'C' for computer) ? " << endl;
        string line = readLine();
        choose = line[0];

        switch (choose)
        {
        case 'P':
            setGameMode(U_vs_U);
            break;
        case 'C':
            setGameMode(U_vs_C);
            break;
        }
    }
    while (!(choose == 'P' || choose == 'C'));

    return 0;
}

//Function about to display game
void ConnectFourAbstract::printGame()
{
    int i, j,k = 0;
    //firstly print letters(a b c d e f... like that etc.)
    for (char letter = 'A'; k < getWidth(); letter++)
    {
        cout <<"  "<< letter;
        k++;
    }

    cout << endl;

    for (i = 0; i < getHeight(); i++)
    {
        for (j = 0; j < getWidth(); j++)
        {
            switch (gameBoard[i][j].getType()) //print the board as type
            {
            case Empty:
                cout <<" * ";
                break;
            case user1:
                cout <<" X ";
                break;
            case user1_x:
                cout <<" x ";
                break;
            case user2_o:
                cout <<" o ";
                break;
            case user2:
                cout <<" O ";
                break;
            }
        }
        cout << endl;
    }
    //If game is end print that winner message
    switch (winner)
    {
    case 1:
        cout << " X(User1) is winner !!!" << endl;
        break;
    case 2:
        cout << " O(User2) is winner !!!" << endl;
        break;
    case 3:
        cout << "Every cell is full. It is draw" << endl;
        break;
    }
    //print LivingCell to every move
    //cout << "LivingCell: " << LivCell << endl;  //IT IS ABOUT PREVIOUS GAME IT CAN BE ACTIVABLE

}



int ConnectFourAbstract::SaveGame(string filename)
{
    ofstream myfile(filename);
    //width--height--GameMode--Turn--winner writing to file
    int gameMode = 0;
    if (getMode() == U_vs_C)
        gameMode = 1;
    //Save all information with sequencely
    myfile << " " << getWidth()  << " " << getHeight()
           << " " << gameMode << " " << turn << " " << winner << " " << (char)getGameType() << endl;

    //Then save the board in next line
    if (myfile.is_open())
    {
        for (int i = 0; i < getHeight(); i++)
        {
            for (int j = 0; j < getWidth(); j++)
            {
                //For saving txt with current game status
                myfile << (char) gameBoard[ i ][ j ].getType();

            }
            myfile << endl;
        }
        myfile.close();
    }
    else
    {
        return -1;
    }
    return 0;

}
//runing the commands(LOAD;SAVE) to correctly
int ConnectFourAbstract::runCommand(string command,int CommandNo)
{
    // int length = command.length();
    // filename = command.substr(5,length); //will take everything after LOAD or SAVE(these are same length)
    if (CommandNo == -2) //means SAVE
    {

        int length = command.length();
        filename = command.substr(5,length); //will take everything after LOAD

        int error = this->SaveGame(filename); //check SAVE is successfull or not
        //if SaveGame function return value equal 0 save is completed
        if (error == 0)
        {
            cout << "Save to file '" << filename << "' successfull." << endl;
            return 0;
        }
        else
        {
            cerr << "Save to file '" << filename << "' failed." << endl;
            return -2;
        }
    }
    else if (CommandNo == -3) //means LOAD
    {

        int length = command.length();
        filename = command.substr(5,length); //will take everything after SAVE

        int error = this->LoadGame(filename); //check LOAD is successfull or not
        //if LoadGame function return value equal 0 load is completed
        if (error >= 0)
        {
            cout << "Loading is" << filename << " successful." << endl;
            printGame(); //and then print the game
            return 0;
        }
        else
        {
            cerr << "Loading is" << filename << " failed. (" << error << ")" << endl;
            return -2;
        }

    }

    return -1;

}

int ConnectFourAbstract::LoadGame(string filename)
{
    ifstream myfile;
    myfile.open(filename);
    int i, j;
    //Loading Open error

    if (!myfile.is_open())
    {
        cerr << "Error opening file !" << endl;
        myfile.close();
        return -1;
    }

    //about change the living cells with loading.I didnt lose previous turn. ->>>>LİNE 1479
    int oldTurn = turn;


    int gameMode;
    char gameType;
    //Loading error about width heigth gameMode etc.
    if (!(myfile >> width >> height >> gameMode >> turn >> winner >> gameType))
    {
        myfile.close();
        return -2;
    }
    //check gameMode is true or not
    if ((gameMode != 0 && gameMode != 1) || getGameType() != gameType)
    {
        cout <<"ERROR GAMEMODE: " <<gameMode <<" GAMETYPE: " <<gameType << endl;
        myfile.close();
        return -3;
    }

    //then set game Mode
    if (gameMode == 0)
        setGameMode(U_vs_U);
    else
        setGameMode(U_vs_C);


    if (gameBoard != NULL)
    {
        //delete previous gameboard
        for(i = 0; i < getHeight(); i++)
            delete [] gameBoard[i];
        delete [] gameBoard;
    }

    setWidth(width);
    setHeight(height);
    //And then create new game board
    gameBoard = new Cell*[getHeight()];

    for(i = 0; i < height; i++)
        gameBoard[i] = new Cell[getWidth()];

    string data;
    getline(myfile,data);
    // cout << "line: '" << data << "'" << endl;


    for (i = 0; i < getHeight(); i++)
    {
        getline(myfile,data);
        // cout << "line: '" << data << "'" << endl;
        for (j = 0; j < getWidth(); j++)
        {
            //Placed board for every data from file
            switch (data[j])
            {
            case 'X':
                gameBoard[i][j] = Cell(i,j,user1);
                break;
            case 'x':
                gameBoard[i][j] = Cell(i,j,user1_x);
                break;
            case 'O':
                gameBoard[i][j] = Cell(i,j,user2);
                break;
            case 'o':
                gameBoard[i][j] = Cell(i,j,user2_o);
                break;
            case '*':
                gameBoard[i][j] = Cell(i,j,Empty);
                break;
            //Error with data
            default:
                cerr << "Error data: '" << data << "'" << endl;
                myfile.close();
                return -4;
            }

        }
    }
    //if the user load game living cell change cause of that assignment
    LivCell = LivCell - oldTurn + turn; //substract previous turn(before loading) then add new turn
    int fPos = myfile.tellg();
    myfile.close();
    //Correct loading
    return fPos;
}

//control horizonal for 4 connect

int ConnectFourAbstract::checkHorizonal(Celltype user, Celltype userTemp)
{
    int i, j;

    auto & grid = gameBoard;

    for (i = 0; i < getHeight(); i++)
    {
        for (j = 3; j < getWidth(); j++)
        {
            //if 4 cell is equal user ,game will finish with return 1
            if (grid[i][j].getType() == user && grid[i][j - 1].getType() == user &&
                    grid[i][j - 2].getType() == user && grid[i][j - 3].getType() == user)
            {
                //  cout << "horizontal win " << (char)userTemp << endl;
                //to write the connected cells with small case
                grid[i][j].setType(userTemp);
                grid[i][j - 1].setType(userTemp);
                grid[i][j - 2].setType(userTemp);
                grid[i][j - 3].setType(userTemp);

                return 1;
            }

        }
    }

    return 0;

}
//control vertical for 4 connect

int ConnectFourAbstract::checkVertical(Celltype user, Celltype userTemp)
{
    int i, j;

    for (i = 3; i < getHeight(); i++)
    {
        for (j = 0; j < getWidth(); j++)
        {
            //check vertical 4 cells to equal
            //if 4 cell is equal user ,game will finish with return 1
            if (gameBoard[i][j].getType() == user && gameBoard[i - 1][j].getType() == user &&
                    gameBoard[i - 2][j].getType() == user && gameBoard[i - 3][j].getType() == user)
            {
                //to write the connected cells with small case
                gameBoard[i][j].setType(userTemp);
                gameBoard[i - 1][j].setType(userTemp);
                gameBoard[i - 2][j].setType(userTemp);
                gameBoard[i - 3][j].setType(userTemp);
                printGame();
                return 1;
            }

        }
    }

    return 0;
}
//control diognal right for 4 connect

int ConnectFourAbstract::checkDiognalRight(Celltype user, Celltype userTemp)
{

    int i, j;

    auto & grid = gameBoard;

    for (i = 0; i < getHeight() - 3; i++)
    {
        for (j = 3; j < getWidth(); j++)
        {
            //check right diognal 4 cells to equal
            //if 4 cell is equal user ,game will finish with return 1
            if (grid[i][j].getType() == user && grid[i + 1][j - 1].getType() == user &&
                    grid[i + 2][j - 2].getType() == user && grid[i + 3][j - 3].getType() == user)
            {
                //to write the connected cells with small case

                grid[i][j].setType(userTemp);
                grid[i + 1][j - 1].setType(userTemp);
                grid[i + 2][j - 2].setType(userTemp);
                grid[i + 3][j - 3].setType(userTemp);

                return 1;
            }

        }
    }

    return 0;
}
//control diognal left for 4 connect

int ConnectFourAbstract::checkDiognalLeft(Celltype user, Celltype userTemp)
{
    int i, j;
    //for writing shortly gameData.grid long variable name cause of that ı used grid with auto
    auto & grid = gameBoard;

    for (i = 0; i < getHeight() - 3; i++)
    {
        for (j = 0; j < getWidth() - 3; j++)
        {
            //check left diognal 4 cells to equal
            //if 4 cell is equal user ,game will finish with return 1
            if (grid[i][j].getType() == user && grid[i + 1][j + 1].getType() == user &&
                    grid[i + 2][j + 2].getType() == user && grid[i + 3][j + 3].getType() == user)
            {
                //to write the connected cells with small case
                grid[i][j].setType(userTemp);
                grid[i + 1][j + 1].setType(userTemp);
                grid[i + 2][j + 2].setType(userTemp);
                grid[i + 3][j + 3].setType(userTemp);
                return 1;
            }

        }
    }

    return 0;
}

// user : checkWinner test user
// user is not equal to getUserCelltype() in getComputerInput function
int ConnectFourAbstract::checkWinner(Celltype user, bool showConnect)
{

    decltype(user) userTemp;

    //if There are 4 'X' connect,user2 will be win
    if (user == user1)
    {
        if (showConnect)
            userTemp = user1_x;
        else
            userTemp = user1;

        //control horizonal,vertical and diognal
        if (checkHorizonal(user, userTemp) || checkVertical(user, userTemp) ||
                checkDiognalRight(user, userTemp) || checkDiognalLeft(user, userTemp))
        {
            return 1;
        }
    }

    //if There are 4 'O' connect,user2 will be win
    if (user == user2)
    {
        if (showConnect)
            userTemp = user2_o;
        else
            userTemp = user2;

        if (checkHorizonal(user, userTemp) || checkVertical(user, userTemp) ||
                checkDiognalRight(user, userTemp) || checkDiognalLeft(user, userTemp))
        {
            return 2;
        }

    }

    //if every cell is full,it will be draw
    if (turn == getWidth() * getHeight() - 1)
    {
        return 3;
    }

    return 0;

}


}

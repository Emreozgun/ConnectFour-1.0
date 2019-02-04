/*
 * File:   ConnectFourAbstract.h
 * Author: Emre OZGUN
 *
 * Prototype(Header file) of ConnectFourAbstract class
 */

#include "Cell.h"

#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H


//two different game mode to play(USER VS USER <-----> USER VS COMPUTER)
typedef enum
{
    U_vs_U = 0,
    U_vs_C = 1
} GameMode;

//two different game type to play(Plus <------> PlusUndo <-----> Diag)
typedef enum
{
    PlusUndo = 'U',
    Plus = 'P',
    Diag = 'D'
}   GameType;

//to read all inputs with that functions
namespace Str
{
using std::string;
string readLine();
}

namespace ConnectFourGame
{
using std::ostream;
using std::string;
using std::istream;
//Base Class
class ConnectFourAbstract
{
public:
    ConnectFourAbstract();// default constructor
    ConnectFourAbstract(int width,int height);//Constructor takes number of width and height as parameter
    ConnectFourAbstract(const ConnectFourAbstract &game); //copy constructor
    virtual ConnectFourAbstract & operator = (const ConnectFourAbstract &rightSideObje);
    virtual ~ConnectFourAbstract(); //Destructor
    void playSingleGame(); //Single mod to play
    bool playOneTurn(bool * moveCompleted = NULL); //One turn for games
    virtual int SaveGame(string filename);
    virtual int LoadGame(string filename);
    void printGame(); //Display the game
    virtual int runCommand(string command,int CommandNo); //running commands (Load and Save).It must be virtual ı will change it in ConnectFourPlusUndo class
    bool play();
    virtual bool play(int pos); //
    int startingInput();  //will take gameMode input
    int getWidth()const ;
    int getHeight()const ;
    GameMode getMode()const;
    string getCommand()const;			/* GETS OF MEMBERS */
    bool getError();
    int getWinner();
    GameType getGameType() const;
    void setWidth(const int width);
    void setHeight(const int height); 		/* SETS OF MEMBERS */
    void setGameMode(const GameMode gameMode);
    void setCommand(string command);
    void setFilename(string filename);
    void setGameType(const GameType gameType);
    int checkHorizonal(Celltype user, Celltype userTemp); // will check only Horizonal connect four
    int checkVertical(Celltype user, Celltype userTemp);  // will check only Vertical connect four
    int checkDiognalRight(Celltype user, Celltype userTemp); // will check only Right Diognal connect four
    int checkDiognalLeft(Celltype user, Celltype userTemp);  // will check only Left Diognal connect four
//I will use that members and function in another class
protected :
    Cell ** gameBoard;
    int width;
    int height;
    int turn = 0;
    string filename = "";
    string command = "";
    static int LivCell; //
    virtual int checkWinner(Celltype user, bool showConnect); //common function about checking winner
    virtual int getUserInput(); //
    virtual int checkUserInput(string command);
    int getUserNo();
    int removeTop( int position); //computer will make moves like user and then remove that move
    Celltype getTop(int position);
    int setTop(int position,Celltype celltype);
    Cell** copyGameBoard() const;
private:
    int getComputerInput(); //
    bool moveUser(int res, int user); //it used play and getComputerInput functions
    GameMode gameMode;
    GameType gameType;
    int winner;
    bool error = false;
    Celltype getUserCelltype(); //
    string getFilename()const; //
    static int increaseLivingCells( );//static function about finding Living cell number

};

}

#endif // CONNECTFOURABSTRACT_H

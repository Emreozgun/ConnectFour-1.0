/*
 * File:   ConnectFourPlusUndo.h
 * Author: Emre OZGUN
 *
 * Prototype(Header file) of ConnectFourPlusUndo class
 */


#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H

#include "ConnectFourPlus.h"
#include <vector>

namespace ConnectFourGame
{
using std::ostream;
using std::string;
using std::istream;
using std::vector;

class ConnectFourPlusUndo : public ConnectFourPlus
{
public:

    ConnectFourPlusUndo();// default constructor
    ConnectFourPlusUndo(int width,int height);//Constructor takes number of width and height as parameter
    ConnectFourPlusUndo(const ConnectFourPlusUndo &game); //copy constructor
    virtual ConnectFourPlusUndo & operator = (const ConnectFourPlusUndo &rightSideObje);//assignment operator
    virtual ~ConnectFourPlusUndo(); //Destructor
    virtual int SaveGame(string filename);
    virtual int LoadGame(string filename);
    virtual int checkUserInput(string command);

private:
    // int checkWinner(Celltype user, bool showConnect); // will be override
    struct UndoData
    {
        int userNo;
        int position;
    };
    int runCommand(string command,int CommandNo);
    int removeLastMove();
    vector < UndoData > undoList;
    virtual bool play(int res);
};

}


#endif // ONNECTFOURPLUSUNDO_H


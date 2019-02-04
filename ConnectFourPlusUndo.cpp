/*
 * File:   ConnectFourPlusUndo.cpp
 * Author: Emre OZGUN
 *
 *Implemantation of ConnectFourPlusUndo class
 */

#include <iostream>
#include <fstream>

#include "ConnectFourPlusUndo.h"
#include "ConnectFourPlus.h"
#include <iostream>

namespace ConnectFourGame
{
using std::ostream;
using std::string;
using std::istream;
using std::cout;
using std::cerr;
using std::endl;
using Str::readLine;
using std::ofstream;
using std::ifstream;

ConnectFourPlusUndo::ConnectFourPlusUndo() : ConnectFourPlus()
{
    //Empty implementation
}

ConnectFourPlusUndo::ConnectFourPlusUndo(int width,int height) : ConnectFourPlus(width, height)
{
    //Empty implementation
}

//Destructor delete dynamic games array automaticly
ConnectFourPlusUndo::~ConnectFourPlusUndo()
{
    //Empty implementation
}

ConnectFourPlusUndo::ConnectFourPlusUndo(const ConnectFourPlusUndo &game) : ConnectFourPlus(game)
{
    //Empty implementation
}

ConnectFourPlusUndo & ConnectFourPlusUndo::operator = (const ConnectFourPlusUndo &rightSideObje)
{
    this->~ConnectFourPlusUndo();
    ConnectFourPlus::operator=(rightSideObje);

    this->undoList = vector<UndoData>(rightSideObje.undoList);
    return *this;
}

//runing the commands(LOAD;SAVE) to correctly
int ConnectFourPlusUndo::runCommand(string command,int CommandNo)
{

    int error = ConnectFourPlus::runCommand(command, CommandNo);

    if (error == 0)
        return 0;

    if (error < -1)
        return error;

    if (error == -1)
    {
        if (CommandNo == - 4)
        {
            int undoCount = 1;
            /* if(getMode() == U_vs_C)
                 undoCount = 2;*/  //undo twice for p vs c game.IT CAN BE ACTİVABLE

            for(int i = 0; i < undoCount; i++)
            {
                int error = removeLastMove(); //check SAVE is successfull or not
                //if SaveGame function return value equal 0 save is completed
                if (error >= 0)
                {
                    cout << "Undo of move is successful" << endl;
                    return 0;
                }
                else
                {
                    cerr << "Undo of move is failed" << endl;
                    return -2;
                }
            }
        }

    }

    // command not found
    return -1;
}

int ConnectFourPlusUndo::checkUserInput(string command)
{
    int ret = ConnectFourPlus::checkUserInput(command);
    if (ret != -1)
    {
        return ret;
    }
    else
    {
        // if command not found in parent class
        if (command.substr(0, 4) == "UNDO")
            return -4;
    }

    return -1; // command not found
}

int ConnectFourPlusUndo::removeLastMove()
{
    if (undoList.size() == 0)
        return -1;
    UndoData x = undoList.back();
    Celltype cell = getTop(x.position);

    if ((x.userNo == 1 && cell == user1) || (x.userNo == 2 && cell == user2))
    {
        undoList.pop_back();
        setTop(x.position,Empty);
        turn--;
        ConnectFourAbstract::LivCell--;
    }
    else
    {
        cerr << "Error undo move"  << endl;
        cerr << " " << (char)cell << " " << x.position  << endl;
        return -1;
    }

//   cout << " " << x.position << " " << x.userNo << endl;

    return 0;
}

bool ConnectFourPlusUndo::play(int res) //it used play and getComputerInput functions **
{
    UndoData undodat;
    undodat.position = res;
    undodat.userNo = getUserNo();
    undoList.push_back(undodat);

    //  cout << "play " << res << " " << getUserNo() << endl;

    return ConnectFourPlus::play(res);
}

int ConnectFourPlusUndo::SaveGame(string filename)
{

    int error = ConnectFourPlus::SaveGame(filename);
    if(error != 0)
        return error;
    ofstream outfile;

    outfile.open(filename, std::ios_base::app);
    outfile << undoList.size() << endl;  //number of undo move in vector
    for(UndoData u:undoList)
    {
        outfile << u.position << " " << u.userNo <<endl; // will write vector positions and which user play that move 
    }

    outfile.close();
    return 0;

}

int ConnectFourPlusUndo::LoadGame(string filename)
{
    //similar procesing with the load function
    int fp = ConnectFourPlus::LoadGame(filename);
    //Different parts of base Load function
    ifstream myfile(filename);
    string line;
    myfile.seekg(fp,myfile.beg); //Sets the position of the next character to be extracted from the input stream.
    getline(myfile, line);
    int length = atoi(line.c_str()); //convert string to integer
    undoList.clear();  //clear of the vector
    for(int i = 0; i < length; i++)
    {
        UndoData undoData;
        if(!(myfile >> undoData.position >> undoData.userNo))
        {
            return -1;
        }
        getline(myfile, line);
        undoList.push_back(undoData);  //push_back fill the vector
    }

    return myfile.tellg();
}

}

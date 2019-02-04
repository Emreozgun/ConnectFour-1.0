/*
 * File:   ConnectFourDiag.cpp
 * Author: Emre OZGUN
 *
 *Implemantation of ConnectFourDiag class
 */

#include <iostream>
#include <fstream>

#include "ConnectFourAbstract.h"
#include "ConnectFourDiag.h"
#include <iostream>

namespace ConnectFourGame
{
using std::ostream;
using std::string;
using std::istream;

ConnectFourDiag::ConnectFourDiag() : ConnectFourAbstract()
{
    //Empty implementation
}
//same assignment with default constructor except width,height and dynamic gameboard
ConnectFourDiag::ConnectFourDiag(int width,int height) : ConnectFourAbstract(width,height)
{
    int i,j;
    this->setHeight(height);
    this->setWidth(width);
    this->gameBoard = new Cell*[height];

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

//Base class destructor run all destructors automaticly
ConnectFourDiag::~ConnectFourDiag()
{

}

ConnectFourDiag::ConnectFourDiag(const ConnectFourAbstract &game) : ConnectFourAbstract(game)
{
    //Empty implementation
}

//I assign same data members and then copy the gameboard
ConnectFourDiag & ConnectFourDiag::operator = (const ConnectFourDiag &rightSideObje)
{
    this->~ConnectFourDiag();
    ConnectFourAbstract::operator=(rightSideObje);

    return *this;
}

//Overrided function
int ConnectFourDiag::checkWinner(Celltype user, bool showConnect)
{
    decltype(user) userTemp;

    //if There are 4 'X' connect,user2 will be win
    if (user == user1)
    {
        if (showConnect)
            userTemp = user1_x;
        else
            userTemp = user1;

        //control only diognal
        if (checkDiognalRight(user, userTemp) || checkDiognalLeft(user, userTemp))
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

        if (checkDiognalRight(user, userTemp) || checkDiognalLeft(user, userTemp))
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


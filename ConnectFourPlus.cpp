/*
 * File:   ConnectFourPlus.cpp
 * Author: Emre OZGUN
 *
 *Implemantation of ConnectFourPlus class
 */


#include <iostream>
#include <fstream>

#include "ConnectFourPlus.h"
#include "ConnectFourAbstract.h"
#include <iostream>

namespace ConnectFourGame
{
using std::ostream;
using std::string;
using std::istream;

ConnectFourPlus::ConnectFourPlus() : ConnectFourAbstract()
{
    //Empty implementation
}
//same assignment with default constructor except width,height and dynamic gameboard
ConnectFourPlus::ConnectFourPlus(int width,int height) : ConnectFourAbstract(width,height)
{
    int i,j;
    this->setHeight(height);
    this->setWidth(width);
    this->gameBoard = new Cell*[height];

    for( i = 0; i < height; i++)
        this->gameBoard[i] = new Cell[width];

    for( i = 0; i < height; i++)
    {
        for(j = 0; j <width; j++)
        {
            gameBoard[i][j].setType(Empty);
        }

    }

}

//Base class destructor run all destructors automaticly
ConnectFourPlus::~ConnectFourPlus()
{

}

ConnectFourPlus::ConnectFourPlus(const ConnectFourAbstract &game) : ConnectFourAbstract(game)
{
    //Empty implementation
}

//I assign same data members and then copy the gameboard
ConnectFourPlus & ConnectFourPlus::operator = (const ConnectFourPlus &rightSideObje)
{
    this->~ConnectFourPlus();
    ConnectFourAbstract::operator=(rightSideObje);

    return *this;
}

int ConnectFourPlus::checkWinner(Celltype user, bool showConnect)// will be override
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
        if (checkHorizonal(user, userTemp) || checkVertical(user, userTemp))
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

        if (checkHorizonal(user, userTemp) || checkVertical(user, userTemp))
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


/*
 * File:   Cell.cpp
 * Author: Emre OZGUN
 *
 *Implemantation of Cell class
 */

#include <iostream>
#include "Cell.h"
//Namespace of the game
namespace ConnectFourGame
{

using std::ostream;
using std::istream;

Cell::Cell() : position(0),rowNum(0),type(Empty)
{
    //Empty implemantation
}

Cell::Cell(char position, int rowNum,Celltype type) : position(position),rowNum(rowNum),type(type)
{
    //Constructor take three parameter(Cell position,Cell row number and Cell type)
}
//Assignment operator of class with all members
Cell & Cell::operator = (const Cell &rightSideObje)
{
    this->position = rightSideObje.position;
    this->rowNum = rightSideObje.rowNum;
    this->type = rightSideObje.type;
    return *this;
}


/*get and sets of data members  */
int Cell::getPosition() const
{
    return position;
}

Celltype Cell::getType() const
{
    return type;
}

void Cell::setPosition(char position)
{
    this->position = 'a' + position;
}

void Cell::setType(Celltype type)
{
    this->type = type;
}

}

/*
 * File:   ConnectFourPlus.h
 * Author: Emre OZGUN
 *
 * Prototype(Header file) of ConnectFourPlus class
 */

#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H

#include "ConnectFourAbstract.h"

namespace ConnectFourGame
{
using std::ostream;
using std::string;
using std::istream;

class ConnectFourPlus : public ConnectFourAbstract
{
public:

    ConnectFourPlus();// default constructor
    ConnectFourPlus(int width,int height);//Constructor takes number of width and height as parameter
    ConnectFourPlus(const ConnectFourAbstract &game); //copy constructor
    virtual ConnectFourPlus & operator = (const ConnectFourPlus &rightSideObje); //assignment operator
    ~ConnectFourPlus(); //Destructor
private:
    int checkWinner(Celltype user, bool showConnect); // will be override
};

}


#endif // CONNECTFOURPLUS_H


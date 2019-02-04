/*
 * File:   ConnectFourDiag.h
 * Author: Emre OZGUN
 *
 * Prototype(Header file) of ConnectFourDiag class
 */


#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H

#include "ConnectFourAbstract.h"

namespace ConnectFourGame
{
using std::ostream;
using std::string;
using std::istream;

class ConnectFourDiag : public ConnectFourAbstract
{
public:

    ConnectFourDiag();// default constructor
    ConnectFourDiag(int width,int height);//Constructor takes number of width and height as parameter
    ConnectFourDiag(const ConnectFourAbstract &game); //copy constructor
    virtual ConnectFourDiag & operator = (const ConnectFourDiag &rightSideObje);////assignment operator
    virtual ~ConnectFourDiag(); //Destructor

private:
    int checkWinner(Celltype user, bool showConnect); // will be override
};

}


#endif // CONNECTFOURDIAG_H

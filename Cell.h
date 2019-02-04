/*
 * File:   Cell.h
 * Author: Emre OZGUN
 *
 * Prototype(Header file) of Cell class
 */

#ifndef CELL_H
#define CELL_H

namespace ConnectFourGame
{
using std::istream;
using std::ostream;
//All cell type for user1,user2 and empty cells
typedef enum
{
    Empty= '*',
    user1 = 'X',
    user1_x = 'x',
    user2_o = 'o',
    user2 = 'O',
}   Celltype ;

class Cell
{
public:
    //Constructors
    Cell();
    Cell(char position, int rowNum,Celltype type);
    //Getters
    int getPosition() const;
    Celltype getType() const;
    //Setters
    void setPosition(char position );
    void setType(Celltype type);
    virtual Cell & operator = (const Cell &rightSideObje);
//Private data members
private:
    char position;
    int rowNum;
    Celltype type;
};
}

#endif // CELL_H


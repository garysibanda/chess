//
//  position.hpp
//  chess
//
//  Created by Isaac Radford on 5/4/23.
//

#ifndef position_hpp
#define position_hpp

#include <stdio.h>

class Position
{
private:
    char location;
    static double squareWidth();
    static double squareHeight();
    
public:
    Position();
    int getLocation();
    int getRow();
    int getColumn();
    int getX();
    int getY();
    
    bool isValid();
    
    void setRow(row);
    void setColumn(column);
    void set(row, column);
    void adjustRow(dRow);
    void adjustCol(dCol);
    
//    Operator ==
//    Operator =
//    Operator +
//    Operator <<
//    Operator >>
    
};

#endif /* position_hpp */

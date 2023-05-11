//
//  move.hpp
//  chess
//
//  Created by Isaac Radford on 5/4/23.
//

#ifndef move_hpp
#define move_hpp

#include <stdio.h>
#include <string>
using namespace std;

class Move
{
private:
    Position source;
    bool destination;
    char piece;
    char capture;
    
    bool enpassant;
    bool castleK;
    bool castleQ;
    bool isWhite;
    
    string error;
    
public:
    Move();
    string getText();
    Position getSrc();
    Position getDestination();
    char getPromotion();
    char getCapture();
    
    bool getEnPassant();
    bool getCastleK();
    bool getCastleQ();
    bool getWhiteMove();
    
    void setEnPassant();
    void setCastle(isKing);
    void setCastleQ();
    void setWhiteMove();
    void assign(move);
    void assign(string);
    
//    << operator
//    >> operator
    
};

#endif /* move_hpp */

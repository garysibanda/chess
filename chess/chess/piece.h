//
//  piece.hpp
//  chess
//
//  Created by Isaac Radford on 5/4/23.
//

#ifndef piece_hpp
#define piece_hpp

#include <stdio.h>
#include "position.h"
#include "piece.h"

class Piece
{
protected:
    Position position;
    bool fwhite;
    int nMoves;
    int lastMove;

public:
    void piece(row, col, isWhite);
    
    void assign(position);
    void assign(Piece);
    
    bool isWhite();
    bool isMove();
    int getNMoves();
    Position getPostion();
    bool justMoved();
    virtual char getLetter() = 0;
    virtual void display(gout) = 0;
    virtual void getMoves(board) = 0;
    
};

#endif /* piece_hpp */

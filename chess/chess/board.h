//
//  board.hpp
//  chess
//
//  Created by Isaac Radford on 5/4/23.
//

#ifndef board_hpp
#define board_hpp

#include <stdio.h>

class Board
{
private:
#define NOPAWNS
   char board[64] =
    {
      'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
      'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',

#ifdef NOPAWNS
       ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
#else
      'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
#endif
      'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'
   };
    int currentMove;
    ogstream gout;
    
    void swap(pos1, pos2);
    void assertBoard();

public:
    Board();
    Board(gout, reset);
    
    int getCurrentMove();
    bool whiteTurn();
    void display(posHover, posSel);
    piece get(Pos position);
    void free();
    void reset();
    void move(Move move);
    void assign(Piece);
};

#endif /* board_hpp */

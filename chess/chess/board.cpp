//
//  board.cpp
//  chess
//
//  Created by Gary Sibanda on 5/10/23.
//

#include "board.h"
#include "piece.h"

/********************************************
 * BOARD RESET
 * Setup board with all pieces in the right place
***********************************************************************/

void Board:: reset()
{
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
   for (int i = 0; i < 64; i++)
      {
         int row = i / 8;
         int col = i % 8;
         bool isWhite;
         switch (board[i])
      {
           case 'p':
               board[i] = make_unique<Pawn>(Pawn(col, row, false));
               break;
           case 'P':
               board[i] = make_unique<Pawn>(Pawn(col, row, true));
               break;
           case 'r':
               board[i] = make_unique<Rook>(Rook(col, row, false));
               break;
           case 'R':
               board[i] = make_unique<Rook>(Rook(col, row, true));
               break;
           case 'n':
               board[i] = make_unique<Knight>(Knight(col, row, false));
               break;
           case 'N':
               board[i] = make_unique<Knight>(Knight(col, row, true));
               break;
           case 'b':
               board[i] = make_unique<Bishop>(Bishop(col, row, false));
               break;
           case 'B':
               board[i] = make_unique<Bishop>(Bishop(col, row, true));
               break;
           case 'q':
               board[i] = make_unique<Queen>(Queen(col, row, false));
               break;
           case 'Q':
               board[i] = make_unique<Queen>(Queen(col, row, true));
               break;
           case 'k':
               board[i] = make_unique<King>(King(col, row, false));
               break;
           case 'K':
               board[i] = make_unique<King>(King(col, row, true));
               break;
           default:
               board[i] = make_unique<Space>(Space(col, row, false));
               break;
              }
   }

/***********************************************************************
 * Source File:
 *    King
 * Author:
 *    Gary Sibanda
 * Summary:
 *    The King class
 ************************************************************************/

#include "pieceKing.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

/***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void King::display(ogstream* pgout) const
{
   pgout->drawKing(position, !isWhite());
}


/**********************************************
 * King : GET POSITIONS
 *********************************************/
void King::getMoves(set <Move>& moves, const Board& board) const
{
   Move m;
   // Directions: up, down, left, right, and 4 diagonals
   static const int dCol[] = { 0,  0, -1, 1,  1,  1, -1, -1 };
   static const int dRow[] = { 1, -1,  0, 0,  1, -1,  1, -1 };
   
   int col = position.getCol();
   int row = position.getRow();
   
   for (int dir = 0; dir < 8; ++dir)
   {
      int c = col + dCol[dir];
      int r = row + dRow[dir];
      
      // Check boundaries: king moves only one step
      if (c >= 0 && c < 8 && r >= 0 && r < 8)
      {
         Piece* pDest = board.getPiece(Position(c, r));
         
         if (pDest == nullptr || pDest->getType() == SPACE)
         {
            m.setSource(position);
            m.setDest(Position(c, r));
            m.setMoveType(Move::MOVE);
            m.setWhiteTurn(this->fWhite);
            moves.insert(m);
         }
         else if (pDest->isWhite() != this->fWhite)
         {
            m.setSource(position);
            m.setDest(Position(c, r));
            m.setMoveType(Move::MOVE);
            m.setWhiteTurn(this->fWhite);
            m.setCapture(pDest->getType());
            moves.insert(m);
         }
         // No further movement, king only moves one square
      }
   }
   
   if (nMoves == 0 && col == 4)
   {
      Piece* qSideRook = board.getPiece(Position(0, row));
      Piece* kSideRook = board.getPiece(Position(7, row));
      
      // King has not moved yet, check for King castling
      if (qSideRook && qSideRook->getNMoves() == 0)
      {
         if ((board.getPiece(Position(1, row)) == nullptr &&
              board.getPiece(Position(2, row)) == nullptr &&
              board.getPiece(Position(3, row)) == nullptr) ||
             (board.getPiece(Position(1, row))->getType() == SPACE &&
              board.getPiece(Position(2, row))->getType() == SPACE &&
              board.getPiece(Position(3, row))->getType() == SPACE))
         {
            m.setSource(position);
            m.setDest(Position(2, row));
            m.setMoveType(Move::CASTLE_QUEEN);
            m.setWhiteTurn(this->fWhite);
            moves.insert(m);
         }
      }
      
      if (kSideRook && kSideRook->getNMoves() == 0)
      {
         if ((board.getPiece(Position(5, row)) == nullptr &&
              board.getPiece(Position(6, row)) == nullptr) ||
             (board.getPiece(Position(5, row))->getType() == SPACE &&
              board.getPiece(Position(6, row))->getType() == SPACE))
         {
            m.setSource(position);
            m.setDest(Position(6, row));
            m.setMoveType(Move::CASTLE_KING);
            m.setWhiteTurn(this->fWhite);
            moves.insert(m);
         }
      }
   }
}

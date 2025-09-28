/***********************************************************************
 * Source File:
 *    Rook
 * Author:
 *    Gary Sibanda
 * Summary:
 *    The Rook class
 ************************************************************************/

#include "pieceRook.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

/***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Rook::display(ogstream* pgout) const
{
   pgout->drawRook(position, !isWhite());
}


/**********************************************
 * Rook : GET POSITIONS
 *********************************************/
void Rook::getMoves(set <Move>& moves, const Board& board) const
{
   static const int dCol[] = { 0,  0, -1, 1 };
   static const int dRow[] = { 1, -1,  0, 0 };
   
   int col = position.getCol();
   int row = position.getRow();
   
   // For each diagonal direction
   for (int dir = 0; dir < 4; ++dir)
   {
      int c = col + dCol[dir];
      int r = row + dRow[dir];
      
      // Slide in this direction until blocked
      while (c > -1 && c < 8 && r > -1 && r < 8)
      {
         Piece* pDest = board.getPiece(Position(c, r));
         
         if (pDest == nullptr || pDest->getType() == SPACE)
         {
            Move m;
            m.setSource(position);
            m.setDest(Position(c, r));
            m.setMoveType(Move::MOVE);
            m.setWhiteTurn(this->fWhite);
            moves.insert(m);
         }
         else
         {
            if (pDest->isWhite() != this->fWhite)
            {
               Move m;
               m.setSource(position);
               m.setDest(Position(c, r));
               m.setMoveType(Move::MOVE);
               m.setWhiteTurn(this->fWhite);
               m.setCapture(pDest->getType());
               moves.insert(m);
            }
            // Stop sliding after hitting any piece
            break;
         }
         c += dCol[dir];
         r += dRow[dir];
      }
   }
}

/***********************************************************************
 * Source File:
 *    Pawn
 * Author:
 *    Gary Sibanda
 * Summary:
 *    The Pawn class
 ************************************************************************/

#include "piecePawn.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()

/***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Pawn::display(ogstream* pgout) const
{
   pgout->drawPawn(position, !isWhite());
}


/**********************************************
 * Pawn : GET POSITIONS
 *********************************************/
void Pawn::getMoves(set <Move>& moves, const Board& board) const
{
   int col = position.getCol();
   int row = position.getRow();
   
   // Determine direction: white moves up (+1), black moves down (-1)
   int dir = (fWhite ? 1 : -1);
   int nextRow = row + dir;
   
   // Forward move (one square)
   if (nextRow >= 0 && nextRow < 8)
   {
      Piece* pDest = board.getPiece(Position(col, nextRow));
      bool isPromotion = (fWhite && nextRow == 7) || (!fWhite && nextRow == 0);
      if (pDest == nullptr || pDest->getType() == SPACE)
      {
         Move m;
         m.setSource(position);
         m.setDest(Position(col, nextRow));
         m.setMoveType(Move::MOVE);
         m.setWhiteTurn(this->fWhite);
         if (isPromotion)
            m.setPromote(QUEEN);
         moves.insert(m);
         
         // Initial two-square advance
         int startRow = fWhite ? 1 : 6;
         int nextNextRow = row + 2 * dir;
         if (row == startRow && nextNextRow >= 0 && nextNextRow < 8)
         {
            Piece* pDest2 = board.getPiece(Position(col, nextNextRow));
            if (pDest2 == nullptr || pDest2->getType() == SPACE)
            {
               Move m2;
               m2.setSource(position);
               m2.setDest(Position(col, nextNextRow));
               m2.setMoveType(Move::MOVE);
               m2.setWhiteTurn(this->fWhite);
               moves.insert(m2);
            }
         }
      }
      // Diagonal captures
      for (int dCol = -1; dCol <= 1; dCol += 2) // -1 (left), +1 (right)
      {
         int diagCol = col + dCol;
         if (diagCol >= 0 && diagCol < 8)
         {
            Piece* pDiag = board.getPiece(Position(diagCol, nextRow));
            bool isPromotionCapture = (fWhite && nextRow == 7) || (!fWhite && nextRow == 0);
            if (pDiag && pDiag->getType() != SPACE && pDiag->isWhite() != this->isWhite())
            {
               Move m;
               m.setSource(position);
               m.setDest(Position(diagCol, nextRow));
               m.setMoveType(Move::MOVE);
               m.setWhiteTurn(this->fWhite);
               if (isPromotionCapture)
                  m.setPromote(QUEEN);
               moves.insert(m);
            }
            // En passant (non-standard: no move history, just check adjacent pawn in correct position)
            Piece* pSide = board.getPiece(Position(diagCol, row));
            int enPassantRow = fWhite ? 4 : 3; // 5th rank for white, 4th for black (0-based)
            if (pSide && pSide->getType() == PAWN
                && pSide->isWhite() != this->isWhite()
                && row == enPassantRow)
            {
               Move m;
               m.setSource(position);
               m.setDest(Position(diagCol, nextRow));
               m.setMoveType(Move::ENPASSANT);
               m.setWhiteTurn(this->fWhite);
               moves.insert(m);
            }
         }
      }
   }
}

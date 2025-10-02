/***********************************************************************
 * Source File:
 *    BOARD
 * Author:
 *    Gary Sibanda
 * Summary:
 *    A collection of pieces and a small amount of game state
 ************************************************************************/

#include "board.h"
#include "uiDraw.h"
#include "position.h"
#include "piece.h"
#include "pieceSpace.h"
#include "pieceKnight.h"
#include "pieceRook.h"
#include "pieceBishop.h"
#include "pieceQueen.h"
#include "pieceKing.h"
#include "piecePawn.h"
#include <cassert>
using namespace std;


/***********************************************
 * BOARD : RESET
 *         Just fill the board with the known pieces
 *   +---a-b-c-d-e-f-g-h---+
 *   |                     |
 *   8     N         N     8
 *   7                     7
 *   6                     6
 *   5                     5
 *   4                     4
 *   3                     3
 *   2                     2
 *   1     n         n     1
 *   |                     |
 *   +---a-b-c-d-e-f-g-h---+
 ***********************************************/
void Board::reset(bool fFree)
{
   // Free all pieces if requested
   if (fFree)
      free();
   
   // Set all board pointers to nullptr
   for (int c = 0; c < 8; ++c)
      for (int r = 0; r < 8; ++r)
         board[c][r] = nullptr;
   
   // Place the Rooks on the board
   board[0][0] = new Rook(0, 0, true);
   board[7][0] = new Rook(7, 0, true);
   board[0][7] = new Rook(0, 7, false);
   board[7][7] = new Rook(7, 7, false);
   
   // Place the knights on the board
   board[1][0] = new Knight(1, 0, true);
   board[6][0] = new Knight(6, 0, true);
   board[1][7] = new Knight(1, 7, false);
   board[6][7] = new Knight(6, 7, false);
   
   // Place the bishops on the board
   board[2][0] = new Bishop(2, 0, true);
   board[5][0] = new Bishop(5, 0, true);
   board[2][7] = new Bishop(2, 7, false);
   board[5][7] = new Bishop(5, 7, false);
   
   // Place the queens on the board
   board[3][0] = new Queen(3, 0, true);
   board[3][7] = new Queen(3, 7, false);
   
   // Place the kings on the board
   board[4][0] = new King(4, 0, true);
   board[4][7] = new King(4, 7, false);
   
   // Place the pawns on the board
   for (int c = 0; c < 8; ++c)
   {
      board[c][1] = new Pawn(c, 1, true);
      board[c][6] = new Pawn(c, 6, false);
   }
   
   for (int c = 0; c < 8; ++c)
      for (int r = 0; r < 8; ++r)
         if (board[c][r] == nullptr)
            board[c][r] = new Space(c, r);
   
   numMoves = 0;
   assertBoard();
}

/***********************************************
 * BOARD : GET
 *         Get a piece from a given position.
 ***********************************************/
const Piece& Board::operator[](const Position& pos) const
{
   assert(pos.getRow() >= 0 && pos.getRow() < 8);
   assert(pos.getCol() >= 0 && pos.getCol() < 8);
   return *board[pos.getCol()][pos.getRow()];
}

Piece& Board::operator[](const Position& pos)
{
   assert(pos.getRow() >= 0 && pos.getRow() < 8);
   assert(pos.getCol() >= 0 && pos.getCol() < 8);
   return *board[pos.getCol()][pos.getRow()];
}

/***********************************************
 * BOARD : DISPLAY
 *         Display the board
 ***********************************************/
void Board::display(const Position& posHover, const Position& posSelect) const
{
   // Draw the board
   pgout->drawBoard();

   // Check game status and display message
   bool currentPlayerIsWhite = whiteTurn();
   if (isInCheckmate(currentPlayerIsWhite))
   {
      pgout->drawGameStatus("CHECKMATE!");
   }
   else if (isInStalemate(currentPlayerIsWhite))
   {
      pgout->drawGameStatus("STALEMATE!");
   }
   else if (isInCheck(currentPlayerIsWhite))
   {
      pgout->drawGameStatus("CHECK!");
   }
  
   if (posHover.isValid() && (*this)[posHover].getType() != SPACE)
      pgout->drawHover(posHover);

   if (posSelect.isValid())
   {
      Piece* selectedPiece = getPiece(posSelect);

      if (selectedPiece && (*this)[posSelect].getType() != SPACE)
      {
         pgout->drawSelected(posSelect);
         set<Move> possibleMoves;
         selectedPiece->getMoves(possibleMoves, *this);
         for (const Move& m : possibleMoves)
            pgout->drawPossible(m.getDest());
      }
   }
   
   // Draw all pieces
   for (int c = 0; c < 8; ++c)
   {
      for (int r = 0; r < 8; ++r)
      {
         if (board[c][r])
            board[c][r]->display(pgout);
      }
   }
}


/************************************************
 * BOARD : CONSTRUCT
 *         Free up all the allocated memory
 ************************************************/
Board::Board(ogstream* pgout, bool noreset) : pgout(pgout), numMoves(0)
{
   // Initialize all board pointers to nullptr
   for (int c = 0; c < 8; ++c)
      for (int r = 0; r < 8; ++r)
         board[c][r] = nullptr;
   
   // Place the Rooks on the board
   board[0][0] = new Rook(0, 0, true);
   board[7][0] = new Rook(7, 0, true);
   board[0][7] = new Rook(0, 7, false);
   board[7][7] = new Rook(7, 7, false);
   
   // Place the knights on the board
   board[1][0] = new Knight(1, 0, true);
   board[6][0] = new Knight(6, 0, true);
   board[1][7] = new Knight(1, 7, false);
   board[6][7] = new Knight(6, 7, false);
   
   // Place the bishops on the board
   board[2][0] = new Bishop(2, 0, true);
   board[5][0] = new Bishop(5, 0, true);
   board[2][7] = new Bishop(2, 7, false);
   board[5][7] = new Bishop(5, 7, false);
   
   // Place the queens on the board
   board[3][0] = new Queen(3, 0, true);
   board[3][7] = new Queen(3, 7, false);
   
   // Place the kings on the board
   board[4][0] = new King(4, 0, true);
   board[4][7] = new King(4, 7, false);
   
   // Place the pawns on the board
   for (int c = 0; c < 8; ++c)
   {
      board[c][1] = new Pawn(c, 1, true);
      board[c][6] = new Pawn(c, 6, false);
   }
   
   for (int c = 0; c < 8; ++c)
      for (int r = 0; r < 8; ++r)
         if (board[c][r] == nullptr)
            board[c][r] = new Space(c, r);
   
   if (noreset) reset();
}

/************************************************
 * BOARD : FREE
 *         Free up all the allocated memory
 ************************************************/
void Board::free()
{
   // Delete all pieces and set pointers to nullptr
   for (int c = 0; c < 8; ++c)
      for (int r = 0; r < 8; ++r)
         if (board[c][r] == nullptr)
            delete board[c][r];
}


/**********************************************
 * BOARD : ASSERT BOARD
 *         Verify the board is well-formed
 *********************************************/
void Board::assertBoard()
{
   for (int c = 0; c < 8; ++c)
      for (int r = 0; r < 8; ++r)
         if (board[c][r] != nullptr)
         {
            Position pos = board[c][r]->getPosition();
            assert(pos.getRow() == r);
            assert(pos.getCol() == c);
            assert(board[c][r]->getType() == SPACE  ||
                   board[c][r]->getType() == KING   ||
                   board[c][r]->getType() == QUEEN  ||
                   board[c][r]->getType() == ROOK   ||
                   board[c][r]->getType() == BISHOP ||
                   board[c][r]->getType() == KNIGHT ||
                   board[c][r]->getType() == PAWN);
         }
}




/**********************************************
 * BOARD : MOVE
 *         Execute a move according to the contained instructions
 *   INPUT move The instructions of the move
 *********************************************/
void Board::move(const Move& move)
{
   int srcCol = move.getSource().getCol();
   int srcRow = move.getSource().getRow();
   Piece* pMoving = board[srcCol][srcRow];
   
   if (!pMoving || pMoving->isWhite() != whiteTurn())
      return;
   
   set<Move> legalMoves;
   pMoving->getMoves(legalMoves, *this);
   
   if (legalMoves.find(move) == legalMoves.end())
      return;
   
   ++numMoves;
   
   int dstCol = move.getDest().getCol();
   int dstRow = move.getDest().getRow();
   
   // Handle en passant
   if (move.getMoveType() == Move::ENPASSANT)
   {
      // Move the pawn
      board[dstCol][dstRow] = pMoving;
      pMoving->setPosition(dstCol, dstRow);
      board[srcCol][srcRow] = new Space(srcCol, srcRow);
      
      // Remove the captured pawn
      int capturedRow = pMoving->isWhite() ? dstRow - 1 : dstRow + 1;
      delete board[dstCol][capturedRow];
      board[dstCol][capturedRow] = new Space(dstCol, capturedRow);
      return;
   }
   
   // Handle castling (already implemented)
   if (move.getMoveType() == Move::CASTLE_KING)
   {
      int rookSrcCol = 7;
      int rookDstCol = 5;
      int row = srcRow;
      board[rookDstCol][row] = board[rookSrcCol][row];
      board[rookDstCol][row]->setPosition(rookDstCol, row);
      board[rookSrcCol][row] = new Space(rookSrcCol, row);
      // Move the king
      board[dstCol][dstRow] = pMoving;
      pMoving->setPosition(dstCol, dstRow);
      board[srcCol][srcRow] = new Space(srcCol, srcRow);
      return;
   }
   else if (move.getMoveType() == Move::CASTLE_QUEEN)
   {
      int rookSrcCol = 0;
      int rookDstCol = 3;
      int row = srcRow;
      board[rookDstCol][row] = board[rookSrcCol][row];
      board[rookDstCol][row]->setPosition(rookDstCol, row);
      board[rookSrcCol][row] = new Space(rookSrcCol, row);
      // Move the king
      board[dstCol][dstRow] = pMoving;
      pMoving->setPosition(dstCol, dstRow);
      board[srcCol][srcRow] = new Space(srcCol, srcRow);
      return;
   }
   
   // Handle promotion (with or without capture)
   if (pMoving->getType() == PAWN && move.getPromote() != SPACE)
   {
      if (board[dstCol][dstRow] && board[dstCol][dstRow]->getType() != SPACE)
         delete board[dstCol][dstRow];
      board[dstCol][dstRow] = pMoving;
      pMoving->setPosition(dstCol, dstRow);
      board[srcCol][srcRow] = new Space(srcCol, srcRow);
      
      bool isWhite = pMoving->isWhite();
      delete board[dstCol][dstRow];
      Piece* pPromoted = nullptr;
      switch (move.getPromote())
      {
         case QUEEN:  pPromoted = new Queen(dstCol, dstRow, isWhite); break;
         case ROOK:   pPromoted = new Rook(dstCol, dstRow, isWhite); break;
         case BISHOP: pPromoted = new Bishop(dstCol, dstRow, isWhite); break;
         case KNIGHT: pPromoted = new Knight(dstCol, dstRow, isWhite); break;
         default:     pPromoted = new Queen(dstCol, dstRow, isWhite); break;
      }
      board[dstCol][dstRow] = pPromoted;
      return;
   }
   
   // Default: normal move (including standard pawn capture)
   if (board[dstCol][dstRow] && board[dstCol][dstRow]->getType() != SPACE)
      delete board[dstCol][dstRow];
   board[dstCol][dstRow] = pMoving;
   pMoving->setPosition(dstCol, dstRow);
   board[srcCol][srcRow] = new Space(srcCol, srcRow);
}

/**********************************************
 * BOARD : FIND KING
 * Find the position of the king for a given color
 *********************************************/
Position Board::findKing(bool isWhite) const
{
   for (int c = 0; c < 8; ++c)
   {
      for (int r = 0; r < 8; ++r)
      {
         Piece* piece = board[c][r];
         if (piece && piece->getType() == KING && piece->isWhite() == isWhite)
         {
            return Position(c, r);
         }
      }
   }
   return Position(); // Return invalid position if not found
}

/**********************************************
 * BOARD : IS SQUARE UNDER ATTACK
 * Check if a square is under attack by the opponent
 *********************************************/
bool Board::isSquareUnderAttack(const Position& pos, bool byWhite) const
{
   if (!pos.isValid())
      return false;
   
   // Check all opponent pieces
   for (int c = 0; c < 8; ++c)
   {
      for (int r = 0; r < 8; ++r)
      {
         Piece* piece = board[c][r];
         if (piece && piece->getType() != SPACE && piece->isWhite() == byWhite)
         {
            set<Move> moves;
            piece->getMoves(moves, *this);
            
            // Check if any move targets this position
            for (const Move& move : moves)
            {
               if (move.getDest() == pos)
               {
                  return true;
               }
            }
         }
      }
   }
   return false;
}

/**********************************************
 * BOARD : IS IN CHECK
 * Determine if the king of the given color is in check
 *********************************************/
bool Board::isInCheck(bool isWhite) const
{
   Position kingPos = findKing(isWhite);
   
   if (kingPos.isInvalid())
      return false;
   
   // Check if the king's position is under attack by the opponent
   return isSquareUnderAttack(kingPos, !isWhite);
}

/**********************************************
 * BOARD : WOULD MOVE LEAVE KING IN CHECK
 * Test if making a move would leave your own king in check
 *********************************************/
bool Board::wouldMoveLeaveKingInCheck(const Move& move, bool isWhite) const
{
   // Make a temporary copy of the board state
   Piece* tempBoard[8][8];
   for (int c = 0; c < 8; ++c)
      for (int r = 0; r < 8; ++r)
         tempBoard[c][r] = board[c][r];
   
   int srcCol = move.getSource().getCol();
   int srcRow = move.getSource().getRow();
   int dstCol = move.getDest().getCol();
   int dstRow = move.getDest().getRow();
   
   // Simulate the move
   Piece* movingPiece = board[srcCol][srcRow];
   Piece* capturedPiece = board[dstCol][dstRow];
   
   // Temporarily modify the board array
   const_cast<Board*>(this)->board[dstCol][dstRow] = movingPiece;
   const_cast<Board*>(this)->board[srcCol][srcRow] = nullptr;
   
   // Update piece position temporarily
   Position originalPos = movingPiece->getPosition();
   const_cast<Piece*>(movingPiece)->setPosition(dstCol, dstRow);
   
   // Check if king is in check after this move
   bool kingInCheck = isInCheck(isWhite);
   
   // Restore the board
   const_cast<Board*>(this)->board[srcCol][srcRow] = movingPiece;
   const_cast<Board*>(this)->board[dstCol][dstRow] = capturedPiece;
   const_cast<Piece*>(movingPiece)->setPosition(originalPos.getCol(), originalPos.getRow());
   
   return kingInCheck;
}

/**********************************************
 * BOARD : HAS LEGAL MOVES
 * Check if a player has any legal moves (moves that don't leave king in check)
 *********************************************/
bool Board::hasLegalMoves(bool isWhite) const
{
   for (int c = 0; c < 8; ++c)
   {
      for (int r = 0; r < 8; ++r)
      {
         Piece* piece = board[c][r];
         if (piece && piece->getType() != SPACE && piece->isWhite() == isWhite)
         {
            set<Move> moves;
            piece->getMoves(moves, *this);
            
            // Check if any move would get the king out of check
            for (const Move& move : moves)
            {
               if (!wouldMoveLeaveKingInCheck(move, isWhite))
               {
                  return true;
               }
            }
         }
      }
   }
   return false;
}

/**********************************************
 * BOARD : IS IN CHECKMATE
 * Determine if the player is in checkmate
 *********************************************/
bool Board::isInCheckmate(bool isWhite) const
{
   return isInCheck(isWhite) && !hasLegalMoves(isWhite);
}

/**********************************************
 * BOARD : IS IN STALEMATE
 * Determine if the player is in stalemate (no legal moves but not in check)
 *********************************************/
bool Board::isInStalemate(bool isWhite) const
{
   return !isInCheck(isWhite) && !hasLegalMoves(isWhite);
}

/**********************************************
 * BOARD EMPTY
 * The game board that is completely empty.
 * It does not even have spaces though each non-filled
 * spot will report it has a space. This is for unit testing
 *********************************************/
BoardEmpty::BoardEmpty() : BoardDummy(), pSpace(nullptr), moveNumber(0)
{
   for (int c = 0; c < 8; ++c)
      for (int r = 0; r < 8; ++r)
         board[c][r] = nullptr;
   pSpace = new Space(0, 0);
}
BoardEmpty::~BoardEmpty()
{
   delete pSpace;
}

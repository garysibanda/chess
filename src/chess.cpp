/**********************************************************************
 * Source File:
 *    Lab 06: Chess
 * Author:
 *    Gary Sibanda
 * Summary:
 *    Play the game of chess
 ************************************************************************/


#include "uiInteract.h"   // for Interface
#include "uiDraw.h"       // for OGSTREAM
#include "position.h"     // for POSITION
#include "piece.h"        // for PIECE and company
#include "board.h"        // for BOARD
#include "test.h"
#include <set>            // for STD::SET
#include <cassert>        // for ASSERT
#include <fstream>        // for IFSTREAM
#include <string>         // for STRING
#include <iostream>       // for COUT
using namespace std;


/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(Interface* pUI, void* p)
{
   Board* pBoard = (Board*)p;
   
   Move move;
   set <Move> possible;
   
   Position src = pUI->getPreviousPosition();
   Position dest = pUI->getSelectPosition();
   
   // Get possible moves for selected piece
   if (src.isValid())
   {
      (*pBoard)[src].getMoves(possible, *pBoard);
      
      // Filter out moves that would leave king in check
      set<Move> legalMoves;
      bool currentPlayerIsWhite = pBoard->whiteTurn();
      
      for (const Move& m : possible)
      {
         // Check if this move would leave the king in check
         if (!pBoard->wouldMoveLeaveKingInCheck(m, currentPlayerIsWhite))
         {
            legalMoves.insert(m);
         }
      }
      possible = legalMoves;
   }
   
   // If the source and destination are valid, and the move is possible
   if (dest.isValid() && src.isValid())
      move = Move(src, dest, possible);
   
   // Attempt to make the move
   if (possible.find(move) != possible.end())
   {
      // Perform the move
      pBoard->move(move);
      pUI->clearSelectPosition();
      
      // Check game state after the move
      bool nextPlayerIsWhite = pBoard->whiteTurn();
      
      if (pBoard->isInCheckmate(nextPlayerIsWhite))
      {
         // Game over - checkmate
         string winner = nextPlayerIsWhite ? "Black" : "White";
         cout << "\n*** CHECKMATE! " << winner << " wins! ***\n" << endl;
      }
      else if (pBoard->isInStalemate(nextPlayerIsWhite))
      {
         // Game over - stalemate
         cout << "\n*** STALEMATE! Game is a draw! ***\n" << endl;
      }
      else if (pBoard->isInCheck(nextPlayerIsWhite))
      {
         // Player is in check but not checkmate
         string player = nextPlayerIsWhite ? "White" : "Black";
         cout << "\n*** CHECK! " << player << " king is in check! ***\n" << endl;
      }
   }
   
   // If no possible move was found, draw current selection possible moves
   else if (dest.isValid())
   {
      possible.clear();
      (*pBoard)[dest].getMoves(possible, *pBoard);
      
      // Filter out illegal moves for display
      set<Move> legalMoves;
      bool currentPlayerIsWhite = pBoard->whiteTurn();
      
      for (const Move& m : possible)
      {
         if (!pBoard->wouldMoveLeaveKingInCheck(m, currentPlayerIsWhite))
         {
            legalMoves.insert(m);
         }
      }
      possible = legalMoves;
   }
   
   // if blank spot clicked, clear selection
   if (dest.isValid() && (*pBoard)[dest].getType() == SPACE)
      pUI->clearSelectPosition();
   
   // Draw the board
   pBoard->display(pUI->getHoverPosition(), pUI->getSelectPosition());
}


/*********************************
 * MAIN - Where it all begins...
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
                   _In_ HINSTANCE hInstance,
                   _In_opt_ HINSTANCE hPrevInstance,
                   _In_ PSTR pCmdLine,
                   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   
   // run all the unit tests
   testRunner();
   
   // Instantiate the graphics window
   Interface ui("Chess");
   
   // Initialize the game class
   ogstream* pgout = new ogstream;
   Board board(pgout);
   
   // set everything into action
   ui.run(callBack, (void*)(&board));
   
   // All done.
   delete pgout;
   return 0;
}

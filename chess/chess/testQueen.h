//
//  testQueen.h
//  Chess_Test
//
//  Created by Gary Sibanda on 5/5/23.
//

#pragma once

#include <iostream>
#include "board.h"
#include "move"

using namespace std;

class TestQueen
{
public:
   void run()
   {
      test_queenVerticalMoves();
      test_queenHorizontalMoves();
      test_queenDiagonalMoves();
      test_queenCaptureHorizontal();
      test_queenCaptureVertical();
      test_queenCaptureDiagonal();
      test_queenNoMoves();
   }
   // test queen vertical Moves
   /**************************************************
    *
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *  |                                                        |
    *  8                                                      8
    *  7                                                      7
    *  6                                                      6
    *  5         p                                           5
    *  4                                                      4
    *  3                                                      3
    *  2              p                                      2
    *  1         (q) r                                       1
    *  |                                                        |
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *
    *****************************************************************************/
   void test_queenVerticalMoves()
   {
      // setup
      BoardStub board;
      Queen * queen = new Queen("a1", true) // White Queen
      board.placePiece(new Rook("b2", true)) // White Rook
      board.placePiece(new Pawn("b2", true)) // White Pawn
      board.placePiece(new Pawn("a5", true)) // White Pawn
                                             // exercise
      set <Move> moves;
      queen.getPossibleMoves(moves, board)
      // verify
      set <Move> ::iterator it;
      assert(moves.size() == 3);
      Move move;
      
      // First move
      move = "a1a2";
      it = moves.find(move)
      assert(it != moves.end())
      
      // Second move
      move = "a1a3";
      it = moves.find(move)
      assert(it != moves.end())
      
      // Third move
      move = "a1a4";
      it = moves.find(move)
      assert(it != moves.end())
      
      // Impossible move where the white pawn at a5 is.
      move = "a1a5";
      it = moves.find(move)
      assert(it == moves.end())
      
      // Impossible move behind the white pawn at a5.
      move = "a1a6";
      it = moves.find(move)
      assert(it == moves.end())
      
      // teardown
   }
   
   // test queen Horizontal Moves
   /**************************************************
    *
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *  |                                                        |
    *  8                                                      8
    *  7                                                      7
    *  6                                                      6
    *  5                                                      5
    *  4                                                      4
    *  3                                                      3
    *  2         p   p                                      2
    *  1        (q)                 k                       1
    *  |                                                        |
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *
    *****************************************************************************/
   void test_queenHorizontalMoves()
   {
      // setup
      BoardStub board;
      Queen * queen = new Queen("a1", true) // White queen
      board.placePiece(new King("e1", true)) // White King
      board.placePiece(new Pawn("a2", true)) // White Pawn
      board.placePiece(new Pawn("b2", true)) // White Pawn
                                             // exercise
      set <Move> moves;
      queen.getPossibleMoves(moves, board)
      // verify
      set <Move> ::iterator it;
      assert(moves.size() == 3); // only horizontal slides possible
      Move move;
      
      // First move
      move = "a1b1";
      it = moves.find(move)
      assert(it != moves.end())
      
      // Second move
      move = "a1c1";
      it = moves.find(move)
      assert(it != moves.end())
      
      // Third move
      move = "a1d1";
      it = moves.find(move)
      assert(it != moves.end())
      
      // Impossible move where the white king at e1 is.
      move = "a1e1";
      it = moves.find(move)
      assert(it == moves.end())
      
      // Impossible move behind the white king at e1.
      move = "a1f1";
      it = moves.find(move)
      assert(it == moves.end())
      
      // teardown
   }
   
   // test queen Diagonal Moves
   /**************************************************
    *
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *  |                                                        |
    *  8                                                      8
    *  7                                                      7
    *  6                                                      6
    *  5                             p                       5
    *  4                                                      4
    *  3                                                      3
    *  2          p                                          2
    *  1        (q)  r                                      1
    *  |                                                        |
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *
    *****************************************************************************/
   
   void test_queenDiagonalMoves()
   {
      // setup
      BoardStub board;
      Queen * queen = new Queen("a1", true) // White queen
      board.placePiece(new Rook("b1", true)) // White rook
      board.placePiece(new Pawn("a2", true)) // White Pawn
      board.placePiece(new Pawn("e5", false)) // Black Pawn
                                              // exercise
      set <Move> moves;
      queen.getPossibleMoves(moves, board)
      // verify
      set <Move> ::iterator it;
      assert(moves.size() == 3); // Only diagonal slides possible
      Move move;
      
      // First move
      move = "a1b2";
      it = moves.find(move)
      assert(it != moves.end())
      
      // Second move
      move = "a1c3";
      it = moves.find(move)
      assert(it != moves.end())
      
      // Third move
      move = "a1d4";
      it = moves.find(move)
      assert(it != moves.end())
      
      // Impossible move where the white pawn at e5 is.
      move = "a1e5";
      it = moves.find(move)
      assert(it == moves.end())
      
      // Impossible move behind the white pawn at e5.
      move = "a1f6";
      it = moves.find(move)
      assert(it == moves.end())
      // teardown
   }
   
   // Queen vertical capture
   /**************************************************
    *
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *  |                                                        |
    *  8        Q                                           8
    *  7                                                      7
    *  6                                                      6
    *  5                                                      5
    *  4                                                      4
    *  3                                                      3
    *  2              p                                      2
    *  1        (q)  r                                       1
    *  |                                                        |
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *
    *****************************************************************************/
   
   void test_queenCaptureVertical()
   {
      // setup
      BoardStub board; // Blank
      Pawn * pawn = new Queen("a1", true) // White pawn
      board.placePiece(new Rook("b1", true)) // White rook
      board.placePiece(new Pawn("b2", true)) // White pawn
      board.placePiece(new Queen("a8", false)) // Black queen
      
      // exercise
      set <Move> moves;
      pawn.getPossibleMoves(moves, board)
      // verify
      set <Move> ::iterator it;
      assert(moves.size() == 7);
      Move move;
      
      // Capture Queen
      move = "a1a8q";
      it = moves.find(move)
      assert(it != moves.end())
      // teardown
   }
   
   // Queen diagonal capture
   /**************************************************
    *
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *  |                                                        |
    *  8                                            Q       8
    *  7                                                      7
    *  6                                                      6
    *  5                                                      5
    *  4                                                      4
    *  3                                                      3
    *  2         p                                           2
    *  1        (q)  r                                       1
    *  |                                                        |
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *
    **************************************************/
   
   void test_queenCaptureDiagonal()
   {
      // setup
      BoardStub board; // Blank
      Pawn * pawn = new Queen("a1", true) // White pawn
      board.placePiece(new Rook("b1", true)) // White rook
      board.placePiece(new Pawn("a2", true)) // White pawn
      board.placePiece(new Queen("h8", false)) // Black King
      
      // exercise
      set <Move> moves;
      pawn.getPossibleMoves(moves, board)
      // verify
      set <Move> ::iterator it;
      assert(moves.size() == 7);
      Move move;
      
      // Capture Queen
      move = "a1h8q";
      it = moves.find(move)
      assert(it != moves.end())
      // teardown
   }
   
   // Queen Horizontal capture
   /**************************************************
    *
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *  |                                                        |
    *  8                                                      8
    *  7                                                      7
    *  6                                                      6
    *  5                                                      5
    *  4                                                      4
    *  3                                                      3
    *  2         p   p                                      2
    *  1        (q)                 Q                      1
    *  |                                                        |
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *
    *****************************************************************************/
   
   void test_queenCaptureHorizontal()
   {
      // setup
      BoardStub board; // Blank
      Pawn * pawn = new Queen("a1", true) // White pawn
      board.placePiece(new Pawn("a2", true)) // White pawn
      board.placePiece(new Pawn("b2", true)) // White pawn
      board.placePiece(new Queen("e1", false)) // Black queen
      
      // exercise
      set <Move> moves;
      pawn.getPossibleMoves(moves, board)
      // verify
      set <Move> ::iterator it;
      assert(moves.size() == 4);
      Move move;
      
      // Capture Queen
      move = "a1e1q";
      it = moves.find(move)
      assert(it != moves.end())
      // teardown
   }
   
};

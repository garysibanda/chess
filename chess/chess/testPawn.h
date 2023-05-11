//
//  testPawn.h
//  Chess_Test
//
//  Created by Gary Sibanda on 5/5/23.
//

#pragma once

#include <cassert>
#include <iostream>

using namespace std;

class TestPawn
{
public:
   void run()
   {
      test_pawnRegularMove();
      test_pawnCapture();
      test_pawnInitialMove();
      test_pawnPromotion();
      test_pawnEnPassant();
      test_pawnNoPossibleMoves();

      // add test for when white pawn cannot go to white piece
   }
   
   // pawn regular move
   /**************************************************
    *
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *  |                                                        |
    *  8                                                      8
    *  7                                                      7
    *  6                                                      6
    *  5                                                      5
    *  4                         p                           4
    *  3                  (p)                                3
    *  2                                                      2
    *  1                                                      1
    *  |                                                        |
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *
    *****************************************************************************/
   void test_pawnRegularMove()
   {
      // setup
      BoardStub board; // Blank board
      Pawn * pawn = new Pawn("c3", true) // White pawn
      board.placePiece(new Pawn("d4", true)) // White pawn to ensure no possible capture
      
      // exercise
      set <Move> moves;
      pawn.getPossibleMoves(moves, board)
      
      // verify
      set <Move> ::iterator it;
      assert(moves.size() == 1);
      Move move;
      
      // Only valid move
      move = "c3c4";
      it = moves.find(move)
      assert(it != moves.end())
      
      // Impossible capture of same color piece
      move = "c3d4p";
      it = moves.find(move)
      assert(it == moves.end())
      // teardown
   }
   
   // pawn initial move
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
    *  2                        (p)                          2
    *  1                                                      1
    *  |                                                        |
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *
    *****************************************************************************/
   void test_pawnInitialMove()
   {
      // setup
      BoardStub board; // Blank board
      Pawn * pawn = new Pawn("d2", true) // White pawn
      
      // exercise
      set <Move> moves;
      pawn.getPossibleMoves(moves, board)
      
      // verify
      set <Move> ::iterator it;
      assert(moves.size() == 2);
      Move move;
      
      // Single Square move
      move = "d2d3";
      it = moves.find(move)
      assert(it != moves.end())
      
      // Double Square move
      move = "d2d4";
      it = moves.find(move)
      assert(it != moves.end())
      
      // Impossible move - 3 spaces
      move = "d2d5";
      it = moves.find(move)
      assert(it == moves.end())
      // teardown
   }
   
   
   // pawn capture
   /**************************************************
    *
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *  |                                                        |
    *  8                                                      8
    *  7        P   P   P                                 7
    *  6            (p)                                      6
    *  5                                                      5
    *  4                                                      4
    *  3                                                      3
    *  2                                                      2
    *  1                                                      1
    *  |                                                        |
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *
    *****************************************************************************/
   
   void test_pawnCapture()
   {
      // setup
      BoardStub board; // Blank
      Pawn * pawn = new Pawn("b6", true) // White pawn
      board.placePiece(new Pawn("a7", false)) // Black pawn
      board.placePiece(new Pawn("b7", false)) // Black pawn
      board.placePiece(new Pawn("c7", false)) // Black pawn
      // exercise
      set <Move> moves;
      pawn.getPossibleMoves(moves, board)
      // verify
      set <Move> ::iterator it;
      assert(moves.size() == 2);
      Move move;
      
      // First move
      move = "b6a7p";
      it = moves.find(move)
      assert(it != moves.end())
      
      // Second move
      move = "b6c7p";
      it = moves.find(move)
      assert(it != moves.end())
      // teardown
   }
   
   // pawn promotion
   /**************************************************
    *
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *  |                                                        |
    *  8                                                      8
    *  7                       (p)                          7
    *  6                                                      6
    *  5                                                      5
    *  4                                                      4
    *  3                                                      3
    *  2                                                      2
    *  1                                                      1
    *  |                                                        |
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *
    *****************************************************************************/
   void test_pawnPromotion()
   {
      // setup
      BoardStub board; // Blank
      Pawn * pawn = new Pawn("d7", true) // White pawn
      
      // exercise
      set <Move> moves;
      pawn.getPossibleMoves(moves, board)
      
      // verify
      set <Move> ::iterator it;
      assert(moves.size() == 1);
      Move move;
      
      // Promotion move to Queen
      move = "d7d8Q";
      it = moves.find(move)
      assert(it != moves.end())
      
      // teardown
   }
   
   // pawn enPassant
   /**************************************************
    *
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *  |                                                        |
    *  8                                                      8
    *  7                                                      7
    *  6         .   P   .                                   6
    *  5         P (p) P                                  5
    *  4                                                      4
    *  3                                                      3
    *  2                                                      2
    *  1                                                      1
    *  |                                                        |
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *
    *****************************************************************************/
   void test_pawnEnPassant()
   {
      // setup
      BoardStub board; // Blank
      Pawn * pawn = new Pawn("b5", true) // White pawn
      board.placePiece(new Pawn("b6", false)) // Black pawn
      Pawn * pawn1 = (new Pawn("a5", false)) // Black pawn
      Pawn * pawn2 = (new Pawn("c5", false)) // Black pawn
      pawn1.lastMove = 1; // set these as the "last move made"
      pawn2.lastMove = 1; // set these as the "last move made"
      
      // exercise
      set <Move> moves;
      pawn.getPossibleMoves(moves, board)
      
      // verify
      set <Move> ::iterator it;
      assert(moves.size() == 2);
      Move move;
      
      // En Passant to the left
      move = "b5a6E"
      it = moves.find(move)
      assert(it != moves.())
      
      // En Passant to the right
      move = "b5c6E"
      it = moves.find(move)
      assert(it != moves.())
      
      // teardown
   }
   
   // pawn no possible moves
   /**************************************************
    *
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *  |                                                        |
    *  8                                                      8
    *  7                                                      7
    *  6                                                      6
    *  5             p                                       5
    *  4            (p)                                      4
    *  3                                                      3
    *  2                                                      2
    *  1                                                      1
    *  |                                                        |
    *  + - - - a - b - c - d - e - f - g - h - - - +
    *
    *****************************************************************************/
   void test_pawnNoPossibleMoves()
   {
      // setup
      BoardStub board; // Blank
      Pawn * pawn = new Pawn("b4", true) // White pawn
      board.placePiece(new Pawn("b5", true)) // White pawn

      // exercise
      set <Move> moves;
      pawn.getPossibleMoves(moves, board)
      
      // verify
      set <Move> ::iterator it;
      assert(moves.size() == 0);
      Move move;
      
      // Impossible move to space occupied by another white pawn
      move = "b4b5"
      it = moves.find(move)
      assert(it == moves.())
      
      // teardown
   }
   
};


// populated board template
/**************************************************
 *
 *  + - - - a - b - c - d - e - f - g - h - - - +
 *  |                                                        |
 *  8        R   N   B   Q  K   B  N  R        8
 *  7        P   P   P   P   P   P  P  P         7
 *  6            (p)                                      6
 *  5                                                      5
 *  4                                                      4
 *  3                                                      3
 *  2        p         p   p   p   p   p   p        2
 *  1        r     n   b   q   k   b   n   r         1
 *  |                                                        |
 *  + - - - a - b - c - d - e - f - g - h - - - +
 *
 *****************************************************************************/

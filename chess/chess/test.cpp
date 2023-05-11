//
//  test.cpp
//  chess
//
//  Created by Gary Sibanda on 5/6/23.
//

#include "test.hpp"
#include "testQueen.h"
#include "testPawn.h"

/************************************
 * TEST RUNNER
 * Runs all the unit tests
 ******************************************************/

void testRunner()
{
   TestQueen().run();
   TestPawn().run();
}

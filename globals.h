#ifndef GLOBALS_H
#define GLOBALS_H

/* Includes */
#include <cassert>
#include <cstdlib>
#include <vector>
#include <iostream>

/* Using Statements */
using std::cout;
using std::endl;
using std::atoi;
using std::swap;
using std::move;
using std::vector;

/* Forward Declarations */
struct Pair;

/* Typedefs */
typedef Pair* PairPtr;
typedef int Tile;
typedef Tile** Board;
typedef vector<PairPtr> Locations;

#endif

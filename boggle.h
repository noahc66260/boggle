// boggle.h
// Prototypes for functions to read in and solve boggle games

#ifndef BOGGLE_H
#define BOGGLE_H

//#include "dic.h"
#include "dictionary.h"
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <utility>

using std::istream;
using std::vector;
using std::set;
using std::string;
using std::pair;


// reads the first 16 non-whitespace characters in a file opened
// by the filestream and returns a 4 x 4 vector of chars that are
// placed into the array in row-major order, so 
// 1 2 3 4 ... 16 is read in as
//  1  2  3  4
//  5  ....  8
//  9  .... 12
// 13  .... 16
// ifs must correspond to an opened file
vector< vector<char> > readBoard(istream & ifs);

// tells us if a given index (i,j) is a valid index in a rows x cols matrix
// where i is the row and j is the column
bool valid_index(int rows, int cols, int i, int j);

// Finds solution to boggle game stored in game by using DFS, a pair 
// to hold the indices (i,j) of the space to process next, 
// a record of visited spaces, and
// a prefix string from previously visited spaces on the board.
// solutions stores our solutions to the Boggle game
// game must be initialized
// visited must be initialized
void dfs_boggle(set<string>& solutions,
                vector< vector<char> >& game, 
                pair<int,int> indices,
                string prefix,
                vector< vector<bool> >& visited, 
                //Dictionary& dictionary);
                DictionaryInterface& dictionary);

#endif

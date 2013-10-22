// boggle.cpp
// Implementation of boggle functions from boggle.h

#include "boggle.h"
#include <iostream>
#include <string>
#include "dic.h"
#include <vector>
#include <set>
#include <cctype>
#include <exception>
#include <stdexcept>
#include <utility>

#define ROWS 4
#define COLS 4

using namespace std;

vector< vector<char> > readBoard(istream & ifs)
{
  if (!ifs.good())
    throw ios_base::failure("ifs.good() is false");

  vector< vector<char> > board = vector< vector<char> >(ROWS);
  for (int i = 0; i < ROWS; i++)
    board[i] = vector<char>(COLS);

  // read each letter and store it in our matrix in row-major order
  char c;
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
    {
      ifs >> c;
      if (ifs.eof())
        throw ios_base::failure("EOF reached prematurely");
      else if (!isalpha(c))
        throw invalid_argument("Non-alphabetic character detected");
      board[i][j] = c;
    }
  return board;
}

bool valid_index(int rows, int cols, int i, int j)
{
  return 0 <= i && i < rows && 0 <= j && j < cols;
}

// for each boggle board game, we perform DFS starting at index (i,j)
// held in the pair<int,int> struct called indices,
// with the prefix string. This is a recursive function, and we preserve
// the property of the DFS with the visited variable to tell us
// which spaces we have and haven't visited. For each string, we
// check if it is a prefix using the dictionary. If a given string
// is a word, we add it to the set solutions. Recursion stops when
// a string is no longer a prefix in a dictionary or there are no
// unvisited and adjacent spaces to recurse. The maximum depth of 
// recursion is therefore bounded by the number of grid spaces, which
// is 16.
void dfs_boggle(set<string>& solutions,
                vector< vector<char> >& game, 
                pair<int,int> indices,
                string prefix,
                vector< vector<bool> >& visited, 
                Dictionary& dictionary)
{
  if (!dictionary.isPrefix(prefix))
    return;

  int i = indices.first;
  int j = indices.second;

  prefix += tolower(game[i][j]);
  visited[i][j] = true;
  if (dictionary.isWord(prefix))
    solutions.insert(prefix);

  // recurse on all extant unvisited neighbors
  for (int k = i-1; k <= i+1; k++)
    for (int l = j-1; l <= j+1; l++)
      if (valid_index(ROWS, COLS, k, l) && visited[k][l] == false)
      {
        indices = pair<int,int>(k, l);
        dfs_boggle(solutions, game, indices, prefix, visited, dictionary);
      }
  visited[i][j] = false;
}

#undef ROWS
#undef COLS

// main.cpp
// Reads an ASCII boggle board in row-major order from stdin or
// from a file, finds all solutions and prints each solution to
// standard output, with one solution per line.

#include "boggle.h"
#include <string>
//#include "dic.h"
#include "hash_dictionary.h"
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <cstdlib>
#include <utility>

#define ROWS 4
#define COLS 4 

using namespace std;

int main(int argc, char **argv)
{
  vector< vector<char> > game; 
  if (argc == 1)
    game = readBoard(cin);
  else if (argc == 2)
  {
    ifstream ifs(argv[1]);
    game = readBoard(ifs);
    ifs.close();
  }
  else 
  {
    cout << "usage: " << argv[0] << " [filename.txt]" << endl;
    exit(EXIT_FAILURE);
  }

  // creates 4 x 4 vector of bools, all initialized to false
  vector< vector<bool> > visited = 
    vector< vector<bool> >(ROWS, vector<bool>(COLS, false));
  set<string> solutions = set<string>();
  //Dictionary dictionary = Dictionary();
  HashDictionary dictionary = HashDictionary();

  string s = "";
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
    {
      pair<int, int> indices = pair<int, int>(i, j);
      dfs_boggle(solutions, game, indices, s, visited, dictionary);
    }

  set<string>::iterator i;
  for (i = solutions.begin(); i != solutions.end(); i++)
    cout << *i << endl;

  return 0;
}

#undef ROWS
#undef COLS

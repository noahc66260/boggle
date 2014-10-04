// main3.cpp
// Reads an ASCII boggle board in row-major order from stdin or
// from a file, finds all solutions and prints each solution to
// standard output, with one solution per line.

#include "boggle.h"
#include <string>
#include "hash_dictionary.h"
#include "trie_dictionary.h"
#include "boggle_solver.h"
#include "boggle_board.h"
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <cstdlib>
#include <utility>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>

// to do list:
// 1. I need to decide if i want to pass in the boggle board through
//    standard input only.
// 4. Also, I need to learn how to embed a dictionary into a file
//    for testing.
// 5. and i need to get that dictionary discussed in Think Python.
// 6. check that everything is OK with google coding standards

using namespace std;

int main(int argc, char **argv)
{
  int rows = 0, cols = 0;
  string file = "/usr/share/dict/words";
  processOptions(argc, argv, &rows, &cols, file);
  BoggleBoard board; 
  if (rows > 0 && cols > 0) {
    board = BoggleBoard(rows, cols);
  } else {
    board = BoggleBoard();
  }

  /*
  if (optind < argc)
  {
    ifstream ifs(argv[optind]);
    board.readFromStream(ifs);
    ifs.close();
  }
  else {
    board.readFromStream(cin);
  }
  */

  if (!board.readFromStream(cin)) {
    printf("Too few characters for a %d by %d board\n", rows, cols);
    exit(1);
  }

  BoggleSolver solver = BoggleSolver();
  //TrieDictionary dictionary = TrieDictionary(file);
  HashDictionary dictionary(file);
  solver.setDictionary(dictionary);
  set<string> solutions = solver.solve(board);

  set<string>::iterator i;
  for (i = solutions.begin(); i != solutions.end(); i++)
    cout << *i << endl;

  return 0;
}

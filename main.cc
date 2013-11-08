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
// 2. Change readFromFile() to readFromStream()
// 3. Apparently my code doesn't break when I designate a board larger
//    than characters available and it's possible that it's putting in
//    empty characters such that it would add erroneous solutions 
//    (boggle board entries must be in alphabet)
// 4. Also, I need to learn how to embed a dictionary into a file
//    for testing.
// 5. and i need to get that dictionary discussed in Think Python.
// 6. check that everything is OK with google coding standards

using namespace std;

static const int buffer_len = 500;

// rvalue[buffer_len - 1] must be '\0', same with cvalue, dvalue
void parseOptions(int argc, char **argv, char cvalue[buffer_len], 
                  char rvalue[buffer_len], char dvalue[buffer_len])
{
  int c;
  while ((c = getopt (argc, argv, "r:c:d:")) != -1) {
    switch (c) {
      case 'r':
        strncpy(rvalue, optarg, buffer_len - 1);
        break;
      case 'c':
        strncpy(cvalue, optarg, buffer_len - 1);
        break;
      case 'd':
        strncpy(dvalue, optarg, buffer_len - 1);
        break;
      case '?':
        if (optopt == 'c' || optopt == 'r') {
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        } else if (isprint (optopt)) {
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        } else {
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        }
        exit(1);
      default:
        abort();
    }
  }

  if (optind < argc) {
    for (int index = optind; index < argc; index++) {
      printf ("Non-option argument %s\n", argv[index]);
    }
    exit(1);
  }
}

void setValues(char cvalue[buffer_len], char rvalue[buffer_len],
               char dvalue[buffer_len], int* prows, int* pcols, 
               char pfile[buffer_len])
{
  if ( (rvalue && !cvalue) || (!rvalue && cvalue)) {
    printf("You must set both rows and columns, or neither\n");
    exit(1);
  }

  if (rvalue && cvalue) {
    *prows = strtol(rvalue, NULL, 10);
    *pcols = strtol(cvalue, NULL, 10);
  } else if (!rvalue && !cvalue) {
    *prows = 4;
    *pcols = 4;
  }

  if (strlen(dvalue) > 0) {
    strncpy(pfile, dvalue, buffer_len-1);
  }
}

void processOptions(int argc, char **argv, int* prows, int* pcols, 
                    char pfile[buffer_len])
{
  char cvalue[buffer_len] = {}; 
  char rvalue[buffer_len] = {}; 
  char dvalue[buffer_len] = {};
  opterr = 0;
  parseOptions(argc, argv, cvalue, rvalue, dvalue);
  setValues(cvalue, rvalue, dvalue, prows, pcols, pfile);
}

int main(int argc, char **argv)
{
  int rows, cols;
  char file[buffer_len] = "/usr/share/dict/words";
  processOptions(argc, argv, &rows, &cols, file);
  BoggleBoard board = BoggleBoard(rows, cols);

  /*
  if (optind < argc)
  {
    ifstream ifs(argv[optind]);
    board.readFromFile(ifs);
    ifs.close();
  }
  else {
    board.readFromFile(cin);
  }
  */

  board.readFromFile(cin);

  BoggleSolver solver = BoggleSolver();
  TrieDictionary dictionary = TrieDictionary(file);
  solver.setDictionary(dictionary);
  set<string> solutions = solver.solve(board);

  set<string>::iterator i;
  for (i = solutions.begin(); i != solutions.end(); i++)
    cout << *i << endl;

  return 0;
}

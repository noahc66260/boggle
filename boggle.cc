// boggle.cc

#include <unistd.h>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include "boggle.h"

using std::string;

// parseOptions() will use the GNU getopt() function to read in the options
//  but will not check the valididity of the input. In the event that
//  an option is not specified, the corresponding buffer will not be
//  modified. 
//
//  cvalue corresponds to the mandatory argument for the -c option
//  rvalue corresponds to the mandatory argument for the -r option
//  dvalue corresponds to the mandatory argument for the -d option
//
// cvalue, rvalue, and dvalue will only be changed if the user specified
//  the relevant options. 
void parseOptions(int argc, char **argv, string& cvalue,
                  string& rvalue, string& dvalue);

// setValues() will use the output of parseOptions() to set rows, cols, 
//  and file. This function will check the validity of the options
//  corresponding to cvalue, rvalue, and dvalue and call exit() if 
//  something is wrong. An empty string corresponds to an option that
//  was never set. It is an error if rvalue is set but not cvalue and
//  vice versa. If neither is set, default values will be used.
//  file will only be changed if dvalue is not empty. 
//
// The default number of rows is 4.
// The default number of columns is 4.
void setValues(string& cvalue, string& rvalue, string& dvalue, int* rows, 
               int* cols, string& file);

void processOptions(int argc, char **argv, int* rows, int* cols, string& file)
{
  string cvalue, rvalue, dvalue;
  opterr = 0;
  parseOptions(argc, argv, cvalue, rvalue, dvalue);
  setValues(cvalue, rvalue, dvalue, rows, cols, file);
}

void parseOptions(int argc, char **argv, string& cvalue, string& rvalue, 
                  string& dvalue)
{
  int c;
  while ((c = getopt (argc, argv, "r:c:d:")) != -1) {
    switch (c) {
      case 'r':
        rvalue = optarg;
        break;
      case 'c':
        cvalue = optarg;
        break;
      case 'd':
        dvalue = optarg;
        break;
      case '?':
        if (optopt == 'c' || optopt == 'r') {
          fprintf(stderr, "Option -%c requires an argument.\n", optopt);
        } else if (isprint(optopt)) {
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        } else { fprintf(stderr,
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

void setValues(string& cvalue, string& rvalue, string& dvalue, int* rows, 
               int* cols, string& file)
{
  if (rvalue.empty() != cvalue.empty()) {
    printf("You must set both rows and columns, or neither\n");
    exit(1);
  }

  if (!rvalue.empty() && !cvalue.empty()) {
    std::stringstream ss;
    ss.str(rvalue);
    ss >> *rows;
    ss.clear();
    ss.str(cvalue);
    ss >> *cols;
  } else if (rvalue.empty() && cvalue.empty()) {
    *rows = 4;
    *cols = 4;
  }

  if (!dvalue.empty()) {
    file = dvalue;
  }
}

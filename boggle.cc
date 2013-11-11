// boggle.cc
// Implementation of boggle functions from boggle.h

//extern const int buffer_len; // do i need this?

#include "boggle.h"
#include <cctype>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>

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

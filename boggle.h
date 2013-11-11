// boggle.h
// Prototypes for functions to read in and solve boggle games

#ifndef HOME_NOAH_DOCUMENTS_FOO_BOGGLE_H
#define HOME_NOAH_DOCUMENTS_FOO_BOGGLE_H

const int buffer_len = 500; // how do i deal with this?

void parseOptions(int argc, char **argv, char cvalue[buffer_len], 
                  char rvalue[buffer_len], char dvalue[buffer_len]);

void setValues(char cvalue[buffer_len], char rvalue[buffer_len],
               char dvalue[buffer_len], int* prows, int* pcols, 
               char pfile[buffer_len]);

void processOptions(int argc, char **argv, int* prows, int* pcols, 
                    char pfile[buffer_len]);

#endif // HOME_NOAH_DOCUMENTS_FOO_BOGGLE_H

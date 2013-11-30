// boggle.h
//
// Functions to parse command-line input for specifying boggle board
//  dimensions and which file to use as a dictionary.

#ifndef HOME_NOAH_DOCUMENTS_FOO_BOGGLE_H
#define HOME_NOAH_DOCUMENTS_FOO_BOGGLE_H

#include <string>

using std::string;

// When called, rows, cols, and file will be modified to reflect
//  the specifications as dictated by the argv string. Uses getops()
//  function to process the options. The options are as follows:
//
//  -r num  Specifies the number of rows. Must be used with -c option.
//  -c num  Specifies the number of columns. Must be used with -r option.
//  -d pathname   Specifies the pathname of the dictionary to be used.
//
//  The -r and -c options must be used together, or not at all. The default
//    values (if neither -r nor -c is used) are 4 and 4.
//  The -d option is optional
void processOptions(int argc, char **argv, int* rows, int* cols, 
                    string& file);

#endif // HOME_NOAH_DOCUMENTS_FOO_BOGGLE_H

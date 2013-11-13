// boggle_board.h
// Interface for BoggleBoard class
//
// A boggle board is a 2D array of characters of dimensions rows() x cols().
// The game of boggle is generally played with alphabetical characters but
// any ASCII character may be used.

#ifndef HOME_NOAH_DOCUMENTS_FOO_BOGGLE_BOARD_H 
#define HOME_NOAH_DOCUMENTS_FOO_BOGGLE_BOARD_H

#include <iostream>
#include <vector>

using std::vector;
using std::istream;

class BoggleBoard
{
  public:
    BoggleBoard();
    BoggleBoard(int rows, int cols);
    ~BoggleBoard() {};
    int rows() const {return rows_;}
    int cols() const {return cols_;}

    // Uses std::cin object to read in rows() x cols() characters into
    //  the board which can be retrieved with the at() function. 
    // The characters are stored in row major order. 
    // Returns true if rows() x cols() characters were read in successfully.
    bool readFromStream(istream& is); 

    // Returns true if we have rows() x cols() characters stored in the 
    //  board and each character is alphabetical. 
    bool isValid(); 

    // Returns the character stored at index (i, j) in the board.
    char& at(int i, int j);
    const char& at(int i, int j) const; 
  private:
    int rows_, cols_;
    vector< vector<char> > board_;
};


#endif // HOME_NOAH_DOCUMENTS_FOO_BOGGLE_BOARD_H

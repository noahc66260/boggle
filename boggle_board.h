// boggle_board.h
// interface for BoggleBoard class

#ifndef HOME_DOCUMENTS_FOO_BOGGLE_BOARD_H 
#define HOME_DOCUMENTS_FOO_BOGGLE_BOARD_H

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
    bool readFromFile(istream& is); // does not close file
    // should i bother overloading [][]?
    char& at(int i, int j);
    const char& at(int i, int j) const; // the need for this confuses me
  private:
    int rows_, cols_;
    vector< vector<char> > board_;
};


#endif //HOME_DOCUMENTS_FOO_BOGGLE_BOARD_H

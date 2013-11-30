// boggle_board.cc
// Implementation for the BoggleBoard class
// 
// The underlying board is implemented as a vector of vector of chars.
//  The game of boggle is played on a 4 x 4 board, but we allow the client
//  to choose their own dimensions so that boggle variants may be played.
//  The board is initialized by reading a stream. To promote modularity,
//  data input is kept separate from verification.
//
// A valid boggle board has an alphabetic character in each entry.

#include "boggle_board.h"

// Boggle is usually played on a 4 x 4 grid, which is a reasonable default
BoggleBoard::BoggleBoard()
{
  rows_ = 4;
  cols_ = 4;
  board_ = vector< vector<char> >(rows_, vector<char>(cols_, '\0'));
}

// Underlying implementation uses the STL vector object, so inappropriate
//  input will be dealt with indirectly through the std::vector class. 
//  This arrangement does not preclude making a boggle board with one
//  dimension equal to 0 (or both). This is an unchecked runtime error.
BoggleBoard::BoggleBoard(int rows, int cols)
{
  rows_ = rows;
  cols_ = cols;
  board_ = vector< vector<char> >(rows_, vector<char>(cols_, '\0'));
}

// Returns true if we read rows_ x cols_ characters from the file.
// This function does not close the stream.
// Characters are read in row major order.
// There is no validation of the characters read in.
bool BoggleBoard::readFromStream(istream& is)
{
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (!(is >> board_[i][j])) {
        return false;  
      }
    }
  }
  return true;
}

// Returns true if board_ is of dimensions rows_ x cols_ and if
//  each entry is an alphabetic character (case insensitive).
bool BoggleBoard::isValid()
{
  if (board_.size() != (unsigned) rows_) {
    return false;
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (board_[j].size() != (unsigned) cols_) {
        return false;
      } else if (!std::isalpha(board_[i][j])) {
        return false;
      }
    }
  }
  return true;
}

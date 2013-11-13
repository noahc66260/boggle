// boggle_board.cc
// 
// The underlying board is implemented as a vector of vector of chars.
// The game of boggle is played on a 4 x 4 board, but we allow the client
// to choose their own dimensions so that boggle variants may be played.
// The board is initialized by reading a stream. To promote modularity,
// reading in data is kept separate from verifying that the data read in
// represents a valid boggle board of alphabetic characters.

#include "boggle_board.h"

// Boggle is usually played on a 4 x 4 grid, which is a reasonable default
BoggleBoard::BoggleBoard()
{
  rows_ = 4;
  cols_ = 4;
  board_ = vector< vector<char> >(rows_, vector<char>(cols_, '\0'));
}

// Underlying implementation uses the STL vector object, so inappropriate
// input will be dealt with indirectly through the std::vector class. 
// This arrangement does not preclude making a boggle board with one
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
//  each entry is an alphabetic character.
bool BoggleBoard::isValid()
{
  using std::isalpha;

  if (board_.size() != rows_) {
    return false;
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (board_[j].size() != cols_) {
        return false;
      } else if (!isalpha(board_[i][j])) {
        return false;
      }
    }
  }
  return true;
}

char& BoggleBoard::at(int i, int j)
{
  //return  board_[i][j]; 
  return  board_.at(i).at(j); 
}

const char& BoggleBoard::at(int i, int j) const
{
  //return  board_[i][j]; 
  return  board_.at(i).at(j); 
}



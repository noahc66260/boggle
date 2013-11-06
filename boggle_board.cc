// boggle_board.cc

#include "boggle_board.h"

BoggleBoard::BoggleBoard()
{
  rows_ = 4;
  cols_ = 4;
  board_ = vector< vector<char> >(rows_, vector<char>(cols_, '\0'));
}

BoggleBoard::BoggleBoard(int rows, int cols)
{
  // how should i deal with invalid input (neg values)?
  rows_ = rows;
  cols_ = cols;
  board_ = vector< vector<char> >(rows_, vector<char>(cols_, '\0'));
}

// returns True if we read rows_ x cols_ characters from the file
// does not close the stream
// stores data in row major order
// does not validate the board
bool BoggleBoard::readFromFile(istream& is)
{
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (!is.good()) {
        return false;
      }
      is >> board_[i][j]; // or board_.at(i).at(j);
    }
  }
  return true;
}

// i should inline these?
char& BoggleBoard::at(int i, int j)
{
  return  board_[i][j]; // or board_.at(i).at(j);
}

const char& BoggleBoard::at(int i, int j) const
{
  return  board_[i][j]; // or board_.at(i).at(j);
}



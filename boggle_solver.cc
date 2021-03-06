// boggle_solver.cc

#include "boggle_solver.h"
#include <utility>
#include <vector>

void BoggleSolver::setDictionary(DictionaryInterface& dictionary)
{
  pdictionary_ = &dictionary;
}

set<string> BoggleSolver::solve(BoggleBoard& board)
{
  using std::vector;
  using std::pair;

  int rows = board.rows();
  int cols = board.cols();
  // creates 4 x 4 vector of bools, all initialized to false
  vector< vector<bool> > visited = 
    vector< vector<bool> >(rows, vector<bool>(cols, false));
  set<string> solutions = set<string>();

  string prefix = "";
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      pair<int, int> indices = pair<int, int>(i, j);
      dfs_boggle(board, indices, prefix, visited, &solutions);
    }
  }
  return solutions; 
}

bool BoggleSolver::valid_index(int rows, int cols, int i, int j)
{
  return i >= 0 && i < rows && j >= 0 && j < cols;
}

void BoggleSolver::dfs_boggle(BoggleBoard& board, 
                              pair<int,int> indices,
                              string& prefix,
                              vector< vector<bool> >& visited,
                              set<string>* psolutions)
{
  if (!pdictionary_->isPrefix(prefix))
    return;

  int i = indices.first;
  int j = indices.second;

  prefix += tolower(board.at(i, j));
  visited[i][j] = true;
  if (pdictionary_->isWord(prefix))
    psolutions->insert(prefix);

  // recurse on all extant unvisited neighbors
  int rows = board.rows();
  int cols = board.cols();
  for (int k = i-1; k <= i+1; ++k) {
    for (int l = j-1; l <= j+1; ++l) {
      if (valid_index(rows, cols, k, l) && !visited[k][l]) {
        indices = pair<int,int>(k, l);
        dfs_boggle(board, indices, prefix, visited, psolutions);
      }
    }
  }
  prefix = prefix.substr(0, prefix.length()-1);
  visited[i][j] = false;
}


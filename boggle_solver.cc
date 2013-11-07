// boggle_solver.cc
//
// Ok... so the next step is making boggle_solver such that it can deal with
//  either a hash dictionary or a trie dictionary.
// Then implement GNU getops
// Then do robust testing

#include "boggle_solver.h"
#include <vector>
#include "trie_dictionary.h"
#include <utility>

void BoggleSolver::setDictionary(DictionaryInterface& dictionary)
{
  dictionary_ = &dictionary;
}

// no need for using directives since .h file has it
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

  //HashDictionary dictionary = HashDictionary();
  //TrieDictionary dictionary = TrieDictionary();

  string s = "";
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
    {
      pair<int, int> indices = pair<int, int>(i, j);
      dfs_boggle(solutions, board, indices, s, visited, *dictionary_);
    }
  return solutions; 
}

bool BoggleSolver::valid_index(int rows, int cols, int i, int j)
{
  return 0 <= i && i < rows && 0 <= j && j < cols;
}

void BoggleSolver::dfs_boggle(set<string>& solutions,
                BoggleBoard& board, 
                pair<int,int> indices,
                string& prefix,
                vector< vector<bool> >& visited, 
                DictionaryInterface& dictionary)
{
  if (!dictionary.isPrefix(prefix))
    return;

  int i = indices.first;
  int j = indices.second;

  prefix += tolower(board.at(i, j));
  visited[i][j] = true;
  if (dictionary.isWord(prefix))
    solutions.insert(prefix);

  // recurse on all extant unvisited neighbors
  int rows = board.rows();
  int cols = board.cols();
  for (int k = i-1; k <= i+1; k++)
    for (int l = j-1; l <= j+1; l++)
      if (valid_index(rows, cols, k, l) && visited[k][l] == false)
      {
        indices = pair<int,int>(k, l);
        dfs_boggle(solutions, board, indices, prefix, visited, dictionary);
      }
  //prefix.pop_back(); // might be C++11 feature
  prefix = prefix.substr(0, prefix.length()-1);
  visited[i][j] = false;
}


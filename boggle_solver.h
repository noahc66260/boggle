// boggle_solver.h
// interacts with BoggleBoard object

#ifndef HOME_DOCUMENTS_FOO_BOGGLE_SOLVER_H
#define HOME_DOCUMENTS_FOO_BOGGLE_SOLVER_H

#include <set>
#include <string>
#include "boggle_board.h"
#include <utility>
#include <vector>
#include "dictionary.h"

using std::set;
using std::vector;
using std::string;
using std::pair;

class BoggleSolver
{
  public:
    BoggleSolver() {};
    ~BoggleSolver() {};
    void setDictionary(DictionaryInterface& dictionary);
    set<string> solve(BoggleBoard& board);
  private:
    DictionaryInterface* pdictionary_;
    bool valid_index(int rows, int cols, int i, int j);

    void dfs_boggle(BoggleBoard& board, 
                pair<int,int> indices,
                string& prefix,
                vector< vector<bool> >& visited,
                set<string>* psolutions);
};




#endif // HOME_DOCUMENTS_FOO_BOGGLE_SOLVER_H


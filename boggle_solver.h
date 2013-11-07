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

using namespace std;
using std::set;
using std::string;

class BoggleSolver
{
  public:
    BoggleSolver() {};
    ~BoggleSolver() {};
    void setDictionary(DictionaryInterface& dictionary);
    set<string> solve(BoggleBoard& board);
  private:
    DictionaryInterface* dictionary_;
    bool valid_index(int rows, int cols, int i, int j);

    void dfs_boggle(set<string>& solutions,
                BoggleBoard& board, 
                pair<int,int> indices,
                string& prefix,
                vector< vector<bool> >& visited, 
                DictionaryInterface& dictionary);
};




#endif // HOME_DOCUMENTS_FOO_BOGGLE_SOLVER_H


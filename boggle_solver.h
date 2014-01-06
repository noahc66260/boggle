// boggle_solver.h
// Class for an object that uses a DictionaryInterface object and 
//  a BoggleBoard object to generate solutions as per the game of boggle. 
//

#ifndef HOME_NOAH_DOCUMENTS_FOO_BOGGLE_SOLVER_H
#define HOME_NOAH_DOCUMENTS_FOO_BOGGLE_SOLVER_H

#include <set>
#include <string>
#include <utility>
#include <vector>
#include "boggle_board.h"
#include "dictionary_interface.h"

using std::set;
using std::vector;
using std::string;
using std::pair;

class BoggleSolver
{
  public:
    BoggleSolver() {};
    ~BoggleSolver() {};

    // It is the user's responsibility to ensure the instance 
    //  passed as an argument persists (i.e. is not destroyed).
    // The user may "switch" dictionaries by providing another
    //  dictionary as an argument to this function, which will
    //  erase any association between the BoggleSolver object and
    //  the prior dictionary.
    void setDictionary(DictionaryInterface& dictionary);
    set<string> solve(BoggleBoard& board);
  private:
    DictionaryInterface* pdictionary_;

    // Returns true if row i, column j is a valid index in an array
    //  of dimensions rows x cols.
    bool valid_index(int rows, int cols, int i, int j);

    // Finds solutions to the game of boggle through a depth first search
    //  graph traversal algorithm implemented recursively. To keep track
    //  of the path we need the current index, the sequence of characters
    //  traversed (also important for checking solutions), and a record
    //  of which indices we've visited.
    // After this function is called, *psolutions will be modified.
    void dfs_boggle(BoggleBoard& board, 
                    pair<int,int> indices,
                    string& prefix,
                    vector< vector<bool> >& visited,
                    set<string>* psolutions);
};

#endif // HOME_NOAH_DOCUMENTS_FOO_BOGGLE_SOLVER_H

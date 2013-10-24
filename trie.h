// trie.h
// Only deals with std::string or c-style strings and letters must
// be lowercase alphabetic characters
//
// Remember that a 26-Trie is either a NULL pointer or a pointer to a node
// which itself has 26 pointers to Tries.
// eh... I'm gonna count "proper" prefixes.

#ifndef HOME_DOCUMENTS_FOO_TRIE_H
#define HOME_DOCUMENTS_FOO_TRIE_H

//#include "node.h" // tries are recursive. No nodes. 

#include <string>
#include <vector>

using std::string;
using std::vector;

class Trie
{
  public:
    Trie();
    Trie(char c);
    ~Trie();
    void addWord(const string& s); // later make char * implementation
    int countWords(const string& s);
    int countPrefixes(const string& s);
  private:
    int index(char c);
    char c;
    int words;
    int prefixes;
    vector< Trie* > edges; // later make array implementation
};

#endif // HOME_DOCUMENTS_FOO_TRIE_H

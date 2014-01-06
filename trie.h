// trie.h
// Only deals with std::string or c-style strings and letters must
// be lowercase alphabetic characters
//
// Remember that a 26-Trie is either a NULL pointer or a pointer to a node
// which itself has 26 pointers to Tries.
// eh... I'm gonna count "proper" prefixes.

#ifndef HOME_NOAH_DOCUMENTS_FOO_TRIE_H
#define HOME_NOAH_DOCUMENTS_FOO_TRIE_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Trie
{
  public:
    Trie();
    explicit Trie(char c);
    ~Trie();
    int addWord(const string& s); // later make char * implementation
    int countWords(const string& s) const;
    int countPrefixes(const string& s) const;
  private:
    int index(char c) const;
    char c_;
    int words_;
    int prefixes_;
    vector< Trie* > edges_; // later make array implementation
    static const string valid_characters_;

    // disallow copy and assign
    Trie(Trie& t) = delete;
    Trie& operator=(Trie& t) = delete;
};

#endif // HOME_NOAH_DOCUMENTS_FOO_TRIE_H

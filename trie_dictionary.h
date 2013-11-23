// trie_dictionary.h
// Using the DictionaryInterface abstract base class, implements a 
// dictionary by using a trie. 
//
// Suppose: 
//  n is the number of words in the dictionary
//  m is the length of a given token 
//  k is the length of the average token
//  
//  Insertion is max(O(log(m)), O(m))
//  Finding whether a token is a valid prefix is  min(O(m), O(log(n)))
//  Finding whether a token is a valid word is    min(O(m), O(log(n)))
//  Space requirements are O(n k)
//  Time to initialize O(n k)
//
// This dictionary only considers valid input
// tokens which only contain alphabetic characters. The dictionary
// is not case sensitive.

#ifndef HOME_DOCUMENTS_FOO_TRIE_DICTIONARY_H 
#define HOME_DOCUMENTS_FOO_TRIE_DICTIONARY_H

#include "dictionary.h"
#include "trie.h"
#include <set>
#include <string>
#include <vector>

using std::string;

class TrieDictionary : public DictionaryInterface
{
  public:
    TrieDictionary();
    explicit TrieDictionary(const string& file);  
    ~TrieDictionary() {}
    bool isWord(string s);
    bool isPrefix(string s);
    int size();
  private:
    void init(const string& file);
    bool validWord(const string& s);
    void addWord(const string& s);
    Trie head_;
    int unique_words_;

    // disallow copy and assign
    TrieDictionary(TrieDictionary & t) = delete;
    TrieDictionary& operator=(TrieDictionary & t) = delete;
};

#endif // HOME_DOCUMENTS_FOO_TRIE_DICTIONARY_H

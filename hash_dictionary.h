// hash_dictionary.h
// Using the DictionaryInterface abstract base class, implements a 
// dictionary by using a STL set object (hash table). 
//
// Suppose: 
//  n is the number of words in the dictionary
//  m is the length of a given token 
//  k is the length of the average token
//  
//  Insertion is O(m)
//  Finding whether a token is a valid prefix is  O(m)
//  Finding whether a token is a valid word is    O(m)
//  Space requirements are O(n k^2)
//  Time to initialize O(n k^2)
//
// For the time being, this dictionary only considers valid input
// tokens which only contain alphabetic characters. The dictionary
// is not case sensitive.

#ifndef HOME_DOCUMENTS_FOO_HASH_DICTIONARY_H 
#define HOME_DOCUMENTS_FOO_HASH_DICTIONARY_H

#include "dictionary.h"
#include <set>
#include <string>

using std::string;
using std::set;

class HashDictionary : public DictionaryInterface
{
  public:
    HashDictionary();
    explicit HashDictionary(string file); 
    ~HashDictionary() {} 
    bool isWord(string s);
    bool isPrefix(string s);
    int size();
  private:
    // Reads tokens from file and inserts into words_ and prefixes_
    void init(string file);

    // Validating the words before inserting speeds up the program by
    // a factor of 3, so I'm not sure I want to remove this just yet.
    bool validWord(string word);
    set<string> words_;
    set<string> prefixes_;

    // optionally explicitly disallow copy and assign
};

#endif // HOME_DOCUMENTS_FOO_HASH_DICTIONARY_H

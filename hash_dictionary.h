// hash_dictionary.h
// Using the DictionaryInterface abstract base class, implements a 
// dictionary by using a STL unordered_map object (hash table). 
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
//
// Use of this class requires a compiler compliant with C++11 because
//  of the unordered_map object.

#ifndef HOME_NOAH_DOCUMENTS_FOO_HASH_DICTIONARY_H 
#define HOME_NOAH_DOCUMENTS_FOO_HASH_DICTIONARY_H

#include "dictionary_interface.h"
#include <unordered_map>
#include <string>

using std::string;
using std::unordered_map;

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
    // the "value" will always be the null byte
    unordered_map<string, char> words_;
    unordered_map<string, char> prefixes_;
};

#endif // HOME_NOAH_DOCUMENTS_FOO_HASH_DICTIONARY_H

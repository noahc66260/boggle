// dic.h
// Interface for the Dictionary class
// Suppose 
//  n is the number of words in the dictionary
//  m is the length of a given token (or the length of the average token,
//    depending on context)
// Implementation 1 is as a list
//  Insertion is O(m) (we must check that it is a valid word)
//  Finding whether a token is a valid prefix is O(n m)
//  Finding whether a token is a valid word is O(n m)
//  Space requirements are O(n m)
//  Time to initialize O(n m)
// Implementation 2 is as a trie
//  Insertion is max(O(log(m)), O(m))
//  Finding whether a token is a valid prefix is  min(O(m), O(log(n)))
//  Finding whether a token is a valid word is    min(O(m), O(log(n)))
//  Space requirements are O(n m)
//  Time to initialize O(n m)
// Implementation 3 is as a hash table (STL set)
//  Insertion is O(m)
//  Finding whether a token is a valid prefix is  O(m)
//  Finding whether a token is a valid word is    O(m)
//  Space requirements are O(n m^2)
//  Time to initialize O(n m^2)
//
//
// Even though there are three implementations, I suggest you use the
// second one. The list does not scale well with the dictionary size
// and is only useful for small data sets. The third implementation 
// takes longer to set up and once constructed has no distinct
// advantage over the second implementation. Currently the third
// implementation takes more than twice as long as the second.
//
// I have decided to call a word any token which contains only
// alphabetic characters. (Any token with punctuation is not a word.)
// This precludes hyphenated words.
// When this object is constructed, so is the internal dictionary of
// words. The default file is /usr/share/dict/words. If you don't use
// Ubuntu 13.04, you probably want to supply your own dictionary.
// When a dictionary is read, I use the input operator (>>) from a 
// C++ ifstream object, which generally means tokens will be read
// up to (but not including) any whitespace.
//
// This dictionary is case insensitive.

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <list>
#include <vector>
#include <set>

using namespace std;

class Dictionary
{
  public:
    Dictionary();
    Dictionary(string file);
    ~Dictionary(); 
    bool isWord(string s);
    bool isPrefix(string s);
    int size();
  private:
    //#include "dic_impl1.h" // list
    #include "dic_impl2.h"   // trie
    //#include "dic_impl3.h"   // hash table
};

#endif

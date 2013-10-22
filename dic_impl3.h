// dic_impl3.h
// Private variables and functions if we implement the Dictionary class
// from dic.h with the STL set object (hash table)

#ifndef DIC_IMPL3
#define DIC_IMPL3
  set<string> words;
  set<string> prefixes;
  int n; // size of dictionary

  // reads all tokens from file and inserts valid tokens (i.e. words)
  // into a set of words and a separate set of prefixes
  void initializeSets(string file);

  // valid words are tokens whose elements are alphabetic characters
  // (case does not matter).
  bool validWord(string word);

#endif

// dic_impl1.h
// Private variables and functions if we implement the Dictionary class
// from dic.h as a list of strings

#ifndef DIC_IMPL1
#define DIC_IMPL1
  list<string> d;
  int words;

  // reads all tokens from file and inserts valid tokens (i.e. words)
  // into a list
  void initializeList(string file);

  // valid words are tokens whose elements are alphabetic characters
  // (case does not matter).
  bool validWord(string word);

#endif

// trie.cc

#include "trie.h"
#include <algorithm>
#include <new>

const string Trie::valid_characters = "abcdefghijklmnopqrstuvwxyz";

Trie::Trie()
{
  c_ = '\0';
  words_ = 0;
  prefixes_ = 0;
  edges_ = vector< Trie* >(valid_characters.length(), NULL);
}

Trie::Trie(char c)
{
  c_ = c;
  words_ = 0;
  prefixes_ = 0;
  edges_ = vector< Trie* >(valid_characters.length(), NULL);
}

Trie::~Trie()
{
  for (unsigned i = 0; i < edges_.size(); ++i) {
    if (edges_[i]) {
      delete edges_[i];
    }
  }
}

//void Trie::addWord(const string& s)
int Trie::addWord(const string& s)
{
  if (s.empty()) {
    words_++;
    return words_;
  } else {
    prefixes_++;
    char k = s[0];
    if (!edges_[index(k)]) {
      edges_[index(k)] = new Trie(k);
    }
    string n = s.substr(1, s.length() - 1);
    Trie * r = edges_[index(k)];
    return r->addWord(n);
  }
}

int Trie::countWords(const string& s)
{
  if (s.empty()) {
    return words_;
  } else {
    char k = s[0];
    string n = s.substr(1, s.length() - 1);
    Trie * r = edges_[index(k)];
    if (r) {
      return r->countWords(n);
    } else {
      return 0;
    }
  }
}

int Trie::countPrefixes(const string &s)
{
  if (s.empty()) {
    return prefixes_;
  } else {
    char k = s[0];
    string n = s.substr(1, s.length() - 1);
    Trie * r = edges_[index(k)];
    if (r) {
      return r->countPrefixes(n);
    } else {
      return 0;
    }
  }
}

int Trie::index(char c)
{
  size_t index = valid_characters.find(c);
  if (index == string::npos)
    return -1;
  else
    return index;
}




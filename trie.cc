// trie.cc

#include "trie.h"
#include <algorithm>
#include <new>

using namespace std;

Trie::Trie()
{
  this->c = '\0';
  words = 0;
  prefixes = 0;
  edges = vector< Trie* >(26, NULL);
}

Trie::Trie(char c)
{
  this->c = c;
  words = 0;
  prefixes = 0;
  edges = vector< Trie* >(26, NULL);
}

Trie::~Trie()
{
  for (unsigned i = 0; i < edges.size(); ++i) {
    if (edges[i]) {
      delete edges[i];
    }
  }
}

//void Trie::addWord(const string& s)
int Trie::addWord(const string& s)
{
  if (s.empty()) {
    words++;
    return words;
  } else {
    prefixes++;
    char k = s[0];
    if (!edges[index(k)]) {
      edges[index(k)] = new Trie(k);
    }
    string n = s.substr(1, s.length() - 1);
    Trie * r = edges[index(k)];
    return r->addWord(n);
  }
}

int Trie::countWords(const string& s)
{
  if (s.empty()) {
    return words;
  } else {
    char k = s[0];
    string n = s.substr(1, s.length() - 1);
    Trie * r = edges[index(k)];
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
    return prefixes;
  } else {
    char k = s[0];
    string n = s.substr(1, s.length() - 1);
    Trie * r = edges[index(k)];
    if (r) {
      return r->countPrefixes(n);
    } else {
      return 0;
    }
  }
}

int Trie::index(char c)
{
  // using std::find;
  string alphabet = "abcdefghijklmnopqrstuvwxyz";
  size_t index = alphabet.find(c);
  if (index == string::npos)
    return -1;
  else
    return index;
}




// trie_dictionary.cc
//
// maybe i should get rid of transform commands as it's not in the specs

#include "trie_dictionary.h"
#include "trie.h"
#include <algorithm>
#include <fstream>


TrieDictionary::TrieDictionary()
{
  init("/usr/share/dict/words");
}

TrieDictionary::TrieDictionary(const string& file) 
{
  init(file);
}

bool TrieDictionary::isWord(string s) 
{
  std::transform(s.begin(), s.end(), s.begin(), ::tolower);
  if (!validWord(s)) {
    return false;
  } else {
    return head_.countWords(s);
  }
}

bool TrieDictionary::isPrefix(string s)
{
  if (s.empty()) {
    return true;
  }
  std::transform(s.begin(), s.end(), s.begin(), ::tolower);
  if (!validWord(s)) {
    return false;
  } else {
    return head_.countPrefixes(s);
  }
}

int TrieDictionary::size()
{
  return unique_words_;
}

void TrieDictionary::init(const string& file)
{
  unique_words_ = 0;
  head_ = Trie('\0'); 
  std::ifstream ifs(file.c_str());
  string word;

  // we want to avoid inserting an empty string
  while (ifs.good()) {
    ifs >> word;
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (validWord(word)) { 
      addWord(word);
    }
  }
  ifs.close();
}

bool TrieDictionary::validWord(const string& s)
{
  if (s.empty()) {
    return false;
  }
  using std::isalpha; 
  for (unsigned i = 0; i < s.length(); ++i) {
    if (!isalpha(s[i])) {
      return false;
    }
  }
  return true;
}

void TrieDictionary::addWord(const string& s)
{
  unique_words_ = (head_.addWord(s) > 1) ? unique_words_ : unique_words_ + 1;
}


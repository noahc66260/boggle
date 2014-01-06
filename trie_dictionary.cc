// trie_dictionary.cc
//

#include "trie_dictionary.h"
#include "trie.h"
#include <algorithm>
#include <fstream>

TrieDictionary::TrieDictionary() : head_('\0')
{
  init("/usr/share/dict/words");
}

TrieDictionary::TrieDictionary(const string& file) : head_('\0')
{
  init(file);
}

//bool TrieDictionary::isWord(string s) 
bool TrieDictionary::isWord(const string& s) const
{
  string t = s;
  std::transform(t.begin(), t.end(), t.begin(), ::tolower);
  if (!validWord(t)) {
    return false;
  } else {
    return head_.countWords(t);
  }
}

//bool TrieDictionary::isPrefix(string s)
bool TrieDictionary::isPrefix(const string& s) const 
{
  string t = s;
  if (t.empty()) {
    return true;
  }
  std::transform(t.begin(), t.end(), t.begin(), ::tolower);
  if (!validWord(t)) {
    return false;
  } else {
    return head_.countPrefixes(t);
  }
}

int TrieDictionary::size() const
{
  return unique_words_;
}

void TrieDictionary::init(const string& file)
{
  unique_words_ = 0;
  //head_ = Trie('\0'); 
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

bool TrieDictionary::validWord(const string& s) const
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


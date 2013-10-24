// trie_dictionary.cc
//
// maybe i should get rid of transform commands as it's not in the specs

#include "trie_dictionary.h"
#include "trie.h"
#include <algorithm>
#include <fstream>

using namespace std; // later phase out

TrieDictionary::TrieDictionary()
{
  init("/usr/share/dict/words");
}

TrieDictionary::TrieDictionary(string file) 
{
  init(file);
}

/*

TrieDictionary::~TrieDictionary()
{

}

*/

bool TrieDictionary::isWord(string s)
{
  // try out set next
  transform(s.begin(), s.end(), s.begin(), ::tolower);
  if (!validWord(s)) {
    return false;
  } else {
    return head.countWords(s);
  }
}

bool TrieDictionary::isPrefix(string s)
{
  transform(s.begin(), s.end(), s.begin(), ::tolower);
  if (!validWord(s)) {
    return false;
  } else {
    return head.countPrefixes(s);
  }
}

int TrieDictionary::size()
{
  return unique_words;
}

void TrieDictionary::init(string file)
{
  unique_words = 0;
  head = Trie('\0'); 
  ifstream ifs(file.c_str());
  string word;

  // we want to avoid inserting an empty string
  while (ifs.good()) {
    ifs >> word;
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (validWord(word)) { // && !word.empty()) { // somehow not required
      addWord(word);
    }
  }
  ifs.close();
}

bool TrieDictionary::validWord(string s)
{
  for (unsigned i = 0; i < s.length(); ++i) {
    if (!isalpha(s[i])) {
      return false;
    }
  }
  return true;
}

void TrieDictionary::addWord(string s)
{
  unique_words = (head.addWord(s) > 1) ? unique_words : unique_words + 1;
}


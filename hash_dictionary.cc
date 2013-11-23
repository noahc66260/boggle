// hash_dictionary.cc

#include "hash_dictionary.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <unordered_map>
#include <utility>

using std::string;

HashDictionary::HashDictionary(string file) : DictionaryInterface()
{
  init(file);
}

HashDictionary::HashDictionary() : DictionaryInterface()
{
  init("/usr/share/dict/words");
}

// Opens file argument and for each token it converts the token to 
// lowercase letters and then inserts each prefix
// into prefixes_ and inserts the entire token into words_.
// Reads input using ifstream object >> operator, which skips all
// whitespace and reads tokens delimited by whitespace.
void HashDictionary::init(string file)
{
  using std::transform;
  using std::ifstream;

  ifstream ifs(file.c_str());
  string word;
  ifs >> word;
  while (ifs.good()) {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (validWord(word)) {
      std::pair<string, char> entry = {"", '\0'};
      for (unsigned i = 0; i < word.length(); ++i) {
        entry.first = word.substr(0, i);
        prefixes_.insert(entry);
      }
      entry.first = word;
      prefixes_.insert(entry);
      words_.insert(entry);
    }
    ifs >> word;
  }
  ifs.close();
}

// Returns true if word contains only alphabetic characters.
// Using this function can speed up the init() function significantly
// if the file we read from contains many words which do not
// contain alphabetic characters.
bool HashDictionary::validWord(string word)
{
  for (unsigned i = 0; i < word.length(); ++i) {
    if (!isalpha(word[i])) {
      return false;
    }
  }
  return true;
}

// Returns true if s is in the dictionary (case insensitive).
bool HashDictionary::isWord(string s)
{
  using std::transform;

  transform(s.begin(), s.end(), s.begin(), ::tolower);
  if (words_.count(s) != 0) {
      return true;
  }
  return false;
}

// Returns true if s is a prefix in the dictionary (case insensitive).
bool HashDictionary::isPrefix(string s)
{
  using std::transform;

  transform(s.begin(), s.end(), s.begin(), ::tolower);
  if (prefixes_.count(s) != 0) {
    return true;
  }
  return false;
}

int HashDictionary::size()
{
  return words_.size();
}

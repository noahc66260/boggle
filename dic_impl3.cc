// dic_impl3.cpp
// Implementation of the Dictionary class from dic.h if we implement it
// as two STL set objects (for prefixes and words)

#include "dic.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <set>

using namespace std;

Dictionary::Dictionary(string file)
{
  n = 0;
  initializeSets(file);
}

Dictionary::Dictionary()
{
  n = 0;
  initializeSets("/usr/share/dict/words");
}

void Dictionary::initializeSets(string file)
{
  ifstream ifs(file.c_str());
  string word;
  ifs >> word;
  unsigned int old_size;
  while (ifs.good())
  {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (validWord(word))
    {
      for (unsigned i = 0; i < word.length(); i++)
        prefixes.insert(word.substr(0, i));
      prefixes.insert(word);
      old_size = words.size();
      words.insert(word);
      if (old_size < words.size())
        n++;
    }
    ifs >> word;
  }
  ifs.close();
}

bool Dictionary::validWord(string word)
{
  for (unsigned int i = 0; i < word.length(); i++)
    if (!isalpha(word[i]))
      return false;
  return true;
}

Dictionary::~Dictionary()
{
}

bool Dictionary::isWord(string s)
{
  transform(s.begin(), s.end(), s.begin(), ::tolower);
  if (words.count(s) != 0)
      return true;
  return false;
}

bool Dictionary::isPrefix(string s)
{
  transform(s.begin(), s.end(), s.begin(), ::tolower);
  if (prefixes.count(s) != 0)
    return true;
  return false;
}

int Dictionary::size()
{
  return n;
}

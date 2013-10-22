// dic_impl1.cpp
// Implementation of the Dictionary class from dic.h if we implement it
// as a list of strings

#include "dic.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

Dictionary::Dictionary(string file)
{
  words = 0;
  initializeList(file);
}

Dictionary::Dictionary()
{
  words = 0;
  initializeList("/usr/share/dict/words");
}

void Dictionary::initializeList(string file)
{
  ifstream ifs(file.c_str());
  string word;
  ifs >> word;
  while (ifs.good())
  {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (validWord(word))
    {
      d.push_back(word);
      words++;
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
  list<string>::iterator i;
  for (i = d.begin(); i != d.end(); i++)
  {
    if (!s.compare(*i))
      return true;
  }
  return false;
}

bool Dictionary::isPrefix(string s)
{
  transform(s.begin(), s.end(), s.begin(), ::tolower);
  list<string>::iterator i;
  string r;
  for (i = d.begin(); i != d.end(); i++)
  {
    r = (*i).substr(0, s.length());
    if (!s.compare(r))
      return true;
  }
  return false;
}

int Dictionary::size()
{
  return words;
}

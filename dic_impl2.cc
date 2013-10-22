// dic_impl2.cpp
// Implementation of Dictionary class from dic.h as a trie
//
// Each node must contain pointers to other nodes in the trie and
// I have chosen to represent this as an array of pointers to nodes.
// I have implemented it in two ways: as STL vectors and arrays.
// The array implementation is faster but contains naked new and
// delete calls, which is generally good to avoid in practice.
// If this code runs slowly, you can make it run ~40% faster by 
// commenting out lines commented by the phrase "vector implementation"
// and uncommenting lines commented by the phrase "array implementation"
// (hint: use CTRL-f)

#include "dic.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cassert>
#include <vector>
#include <algorithm>

#define SIZE_ALPHABET 26

using namespace std;

// it is the client's responsibility to provide a word with 
// only alphabetic elements
void Dictionary::addWord(string str)
{
  if (!validWord(str)) return;
  int index; 
  node *n = head;
  for (unsigned int i = 0; i < str.length(); i++)
  {
    index = nodeIndex(str[i]);
    if (NULL == n->next[index])
      addNode(n, str[i]);
    n = n->next[index];
  }
  if (false == n->isWord) // avoid counting duplicates
    words++;
  n->isWord = true;
}

// checked run-time error to provide a node n such that 
// the node we are to create was already initialized
// This function is used to create a new node which represents
// the next letter of a given word in our trie.
void Dictionary::addNode(node* n, char c)
{
  int index = nodeIndex(c);
  assert(NULL == n->next[index]);

  node *m = new node;
  initializeNode(m, c);
  n->next[index] = m;
}

void Dictionary::initializeNode(node *n, char c)
{
  n->letter = c;
  n->next = vector<node*>(SIZE_ALPHABET, NULL); // vector implementation
  //n->next = new node*[SIZE_ALPHABET];   // array implementation
  //for (int i = 0; i < SIZE_ALPHABET; i++)
  //  n->next[i] = NULL;
  n->isWord = false;
}

Dictionary::Dictionary()
{
  words = 0;
  initializeTrie("/usr/share/dict/words");
}

Dictionary::Dictionary(string file)
{
  words = 0;
  initializeTrie(file);
}

// valid words only contain alphanumeric characters and nothing else
bool Dictionary::validWord(string word)
{
  for (unsigned int i = 0; i < word.length(); i++)
    if (!isalpha(word[i]))
      return false;
  return true;
}

// this function was used to work with an actual dictionary
// but it could be used on other files as only tokens containing
// alphabetic letters will be added.
void Dictionary::initializeTrie(string file)
{
  head = new node;
  initializeNode(head, char(0));

  ifstream ifs(file.c_str());
  string word;
  //ifs >> word;
  while (ifs.good())
  {
    ifs >> word;
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (validWord(word)) 
      addWord(word);
    //ifs >> word;
  }
  ifs.close();
}


Dictionary::~Dictionary()
{
  freeNode(head);
}

// This is a recursive function.
// The maximum number of function calls on the stack will be
// the length of the longest word + 1 (for the root node)
void Dictionary::freeNode(node *n)
{
  for (int i = 0; i < SIZE_ALPHABET; i++)
    if (NULL != n->next[i])
      freeNode(n->next[i]);
  //delete [] n->next; // array implementation
  delete n;
}

bool Dictionary::isWord(string s)
{
  node *n = findNode(s);
  if (NULL == n)
    return false;
  else
    return n->isWord;
}

bool Dictionary::isPrefix(string s)
{
  node *n = findNode(s);
  return (NULL != n);
}

// returns the node we get by traversing the sequence of
// letters in str in our trie.
// Returns NULL if such a node does not exist in trie
// This search is not case sensitive (i.e. jonny works, so does JoNNy)
Dictionary::node* Dictionary::findNode(string str)
{
  if (!validWord(str)) return NULL;
  node *n = head;
  int index;
  for (unsigned int i = 0; i < str.length(); i++)
  {
    index = nodeIndex(str[i]);
    if (NULL == n)
      break;
    n = n->next[index];
  }
  return n;
}

// Gives a number corresponding to an index for letters a-z, regardless
// of case, inclusive.
// return -1 if the input doesn't correspond to any index
int Dictionary::nodeIndex(char c)
{
  string alphabet = "abcdefghijklmnopqrstuvwxyz";
  size_t index = alphabet.find(tolower(c));
  if (index == string::npos)
    return -1;
  else
    return index;
}

int Dictionary::size()
{
  return words;
}

#undef SIZE_ALPHABET 

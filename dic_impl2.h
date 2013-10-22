// dic_impl2.h
// Private variables and functions for trie implementation of 
// the Dictionary class from dic.h
//
// Each node stores a character and whether or not the path of nodes
// from the head represents a valid word. As it has been implemented
// each leaf does represent a valid word but not all valid words are leaves.
// The array implementation is about ~40% faster, but the vector
// implementation contains no "naked" new and delete calls so I have
// chosen the latter. If the vector implementation is not fast
// enough it can be changed to the array version by commenting
// and uncommenting several lines of code.

#ifndef DIC_IMPL2
#define DIC_IMPL2
  struct node // vector implementation
    { 
      char letter; 
      bool isWord; 
      vector<node*> next; 
    }; 
   //struct node { char letter; bool isWord; node** next; }; // array impl

  // finds node corresponding to path of letters in str in our trie
  node* findNode(string str);

  // adds path of letters in str to our trie
  void addWord(string str);

  // creates a new node which can be accessed by head->next[nodeIndex(c)]
  void addNode(node* head, char c);

  // sets default values for an extant node
  void initializeNode(node *n, char c);

  // gives the index from which we can access the child node with
  // the letter c if we already have the parent node
  int nodeIndex(char c);

  // recursive function to free all nodes in a trie
  void freeNode(node *n);

  // tells us if word is composed of valid letters for our trie
  bool validWord(string word);

  // takes tokens from a file and adds valid ones to a trie with
  // the head already initialized
  void initializeTrie(string file);

  node* head;
  int words; // number of valid words in trie, not nodes
#endif

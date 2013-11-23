// boggle_test.cpp
// Tests the Dictionary class from dic.h and boggle functions from boggle.h
//
// 1. I need to add functions to verify parsing in boggle.h and boggle.cc
// 2. Also... you need to check the at() function for BoggleBoard class

#include "boggle.h"
#include "dictionary.h"
#include "hash_dictionary.h"
#include "trie_dictionary.h"
#include "boggle_board.h"
#include "boggle_solver.h"
#include <gtest/gtest.h>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#include <set>
#include <cstdio>
#include <exception>
#include <stdexcept>
#include <utility>
#include <iostream>

#define ROWS 4
#define COLS 4

using namespace std;

// 1. add tests for BoggleSolver, alter tests for dfs_boggle

const string alphabet = "abcdefghijklmnopqrstuvwxyz"; // for random letters

// holy crap. This works!!!
// http://www.linuxjournal.com/content/embedding-file-executable-aka-hello-world-version-5967
extern char _binary_words_txt_start;
extern char _binary_words_txt_end;
string getDictionaryFile(void) {
  static bool flag = false;
  static string tmpfile;

  if (!flag) {
    char file[] = "/tmp/fileXXXXXX";
    mkstemp(file);
    ofstream ofs(file);
    char*  p = &_binary_words_txt_start;
    while ( p != &_binary_words_txt_end ) {
      ofs << *p++;
    }
    tmpfile = file;
    flag = true;
  }
  return tmpfile;
}
/*
// Tests that the validIndex() function returns false for indices
// that do not correspond to entries in a ROWS x COLS matrix
TEST(validIndexTest, badValues) {
  int k = 10;
  for (int i = 0 - k; i < ROWS + k; i++)
  {
    for (int j = 0 - k; j < COLS + k; j++) 
    {
      if (i < 0 || ROWS <= i)
        EXPECT_FALSE(valid_index(ROWS, COLS, i, j));
      else if (j < 0 || COLS <= j)
        EXPECT_FALSE(valid_index(ROWS, COLS, i, j));
    }
  }
}

// Tests that the validIndex() function returns true for indices
// that do correspond to entries in a ROWS x COLS matrix
TEST(validIndexTest, goodValues) {
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
      EXPECT_TRUE(valid_index(ROWS, COLS, i,  j));
}
*/

// If memory is not managed correctly, we may seg fault just
// constructing/deconstructing our dictionary
TEST(initializeDic, noSegFault) {
  string file = getDictionaryFile();
  TrieDictionary d = TrieDictionary(file);
}

// This is an exhaustive test on the words from /usr/share/dict/words
TEST(isWordTest, inDictionary) {
  string file = getDictionaryFile();
  TrieDictionary d = TrieDictionary(file);
  ifstream ifs(file.c_str());
  string word;
  bool validWord;
  while (ifs.good())
  {
    ifs >> word;
    validWord = true;
    for (unsigned i = 0; i < word.length(); i++)
      if (!isalpha(word[i]))
        validWord = false;
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (validWord)
      EXPECT_TRUE(d.isWord(word));
  }
}

// We initialize our dictionary with /usr/share/dict/words and then
// examine every word in the file. If it is contained in our dictionary,
// then randomly toggle the case of each letter and verify that
// Dictionary::isWord() still returns true.
TEST(isWordTest, caseInsensitive) {
  //string file = "/usr/share/dict/words";
  string file = getDictionaryFile();
  ifstream ifs(file.c_str());

  TrieDictionary d = TrieDictionary(file);
  string word;
  while (ifs.good())
  {
    ifs >> word;
    if (d.isWord(word))
    {
      for (unsigned i = 0; i < word.length(); i++)
        if (rand() % 2 == 0)
        {
          char c = word[i];
          word[i] = isupper(c) ? tolower(c) : toupper(c);
        }
      EXPECT_TRUE(d.isWord(word));
    }
  }
  ifs.close();
}

// Here I use the STL set to store all valid words in 
// /usr/share/dict/words. Then random characters are appended to invalid words
// which are checked in the set object. If the token is not
// in the set then it should not be in the dictionary and hence
// we can expect not to find it.
TEST(isWordTest, notInDictionary) {
  string file = getDictionaryFile();
  TrieDictionary d = TrieDictionary(file);
  set<string> d_copy = set<string>();
  string word;
  bool validWord;
  ifstream ifs(file.c_str());
  while (ifs.good())
  {
    ifs >> word;
    validWord = true;
    for (unsigned i = 0; i < word.length(); i++)
      if (!isalpha(word[i]))
        validWord = false;
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (validWord)
      d_copy.insert(word);
  }

  // This test has its limits considering our random number isn't over
  // a distribution of the most commonly used letters. 
  // For example, vowels are in every word, and there are 6 of them,
  // but each pick gets us a 6/26 chance of being selected, so
  // we're unlikely to form particularly long tokens
  word.clear();
  char c;
  int tries = 0;
  while (tries < 100000)
  {
    if (word.length() > 8) // arbitrary choice
      word.clear();
    c = alphabet[rand() % 26];
    word += string(1, c);
    if (0 == d_copy.count(word))
    {
      EXPECT_FALSE(d.isWord(word));
      tries++;
    }
  }
}

// A set is made that contains every valid prefix in 
// /usr/share/dict/words. We create random strings of text
// by appending randomly chosen characters.
// If said token is not a contained in our set, it should not
// be a prefix in our dictionary taken from the same file.
TEST(isPrefixTest, invalidPrefixes) {
  string file = getDictionaryFile();
  TrieDictionary d = TrieDictionary(file);
  set<string> prefixes = set<string>();
  string word;
  bool validWord;
  ifstream ifs(file.c_str()); // for some reason I can't use a string...
  while (ifs.good()) {
    ifs >> word;
    validWord = true;
    for (unsigned i = 0; i < word.length(); i++) {
      if (!isalpha(word[i])) {
        validWord = false;
      }
    }
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (validWord) {
      for (int i = word.length(); 0 < i; i--) {
        word = word.substr(0, i);
        prefixes.insert(word);
      }
    }
  }

  word.clear();
  char c;
  int tries = 0;
  while (tries < 100000) {
    if (word.length() > 8) // arbitrary choice
      word.clear();
    c = alphabet[rand() % 26]; 
    word += string(1, c);
    if (0 == prefixes.count(word)) {
      EXPECT_FALSE(d.isPrefix(word));
      tries++;
    }
  }
}

/*
// NOTE: prefix means proper prefix
// A word is trivially a prefix of itself, so every token which is a 
// word in our dictionary should also be a prefix in our dictionary
TEST(isPrefixTest, allWordsArePrefixes) {
  string file = "/usr/share/dict/words";
  TrieDictionary d = TrieDictionary(file);
  ifstream ifs(file.c_str());
  string word;
  while (ifs.good())
  {
    ifs >> word;
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (d.isWord(word))
      EXPECT_TRUE(d.isPrefix(word));
  }
}
*/

// Note: all prefixes are *proper* prefixes
// This is an exhaustive test on the words from /usr/share/dict/words.
// If this takes too long you may modify it to check one prefix substring
// of random length per word rather than all prefix substrings.
TEST(isPrefixTest, validPrefixes) {
  string file = getDictionaryFile();
  TrieDictionary d = TrieDictionary(file);
  ifstream ifs(file.c_str());
  string word;
  bool validWord;
  while (ifs.good()) {
    ifs >> word;
    validWord = true;
    for (unsigned i = 0; i < word.length(); i++)
      if (!isalpha(word[i]))
        validWord = false;
    //word = word.substr(0, rand() % word.length());
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (validWord) {
      for (int i = word.length() - 1; 0 < i; i--) {
        word = word.substr(0, i);
        EXPECT_TRUE(d.isPrefix(word));
      }
    }
  }
  EXPECT_TRUE(d.isPrefix(""));
}

// We initialize our dictionary with /usr/share/dict/words and then
// examine every word in the aformentioned file. We create a substring
// of random length, and if this token is a prefix in the dictionary,
// then we randomly toggle the case of each letter and verify that
// Dictionary::isPrefix() still returns true.
TEST(isPrefixTest, caseInsensitive) {
  string file = getDictionaryFile();
  ifstream ifs(file.c_str());

  TrieDictionary d = TrieDictionary(file);
  string prefix;
  while (ifs.good()) {
    ifs >> prefix;
    if (prefix.empty()) continue;
    prefix = prefix.substr(0, rand() % prefix.length());
    if (d.isPrefix(prefix)) {
      for (unsigned i = 0; i < prefix.length(); ++i)
        if (rand() % 2 == 0) {
          char c = prefix[i];
          prefix[i] = isupper(c) ? tolower(c) : toupper(c);
        }
      EXPECT_TRUE(d.isPrefix(prefix));
    }
  }
  ifs.close();
}

// /home/noah/Documents/foo/doubleWords was created by concatenating
// two copies of /usr/share/dict/words.
TEST(addWordTest, noDuplicates) {
  string file1 = getDictionaryFile();
  char file2[] = "/tmp/fileXXXXXX";
  mkstemp(file2);
  for (int i = 0; i < 2; ++i) {
    string s;
    ifstream ifs(file1.c_str());
    ofstream ofs(file2);
    while (ifs.good()) {
      ifs >> s;
      ofs << s << endl;
    }
    ifs.close();
    ofs.close();
  }

  TrieDictionary d1 = TrieDictionary(file1);
  TrieDictionary d2 = TrieDictionary(file2);
  int s1 = d1.size();
  int s2 = d2.size();

  EXPECT_EQ(s1, s2);
}

// checks that the file /home/noah/Documents/foo/vwoolf2.txt has 337
// strictly alphabetic and unique words (i.e. the size of the dictionary)
// I've checked this value by 
// tr ' ' '\n' < vwoolf2.txt | tr '[A-Z]' '[a-z]' | 
//    sort vwoolf2.txt | uniq | sed '/^$/d' | wc -l
// Here vwoolf2.txt has no punctuation.
//TEST(sizeTest, virginiaWoolf) {
//  TrieDictionary d = TrieDictionary("/home/noah/Documents/foo/vwoolf2.txt");
//  EXPECT_EQ(d.size(), 337);
//}

// We create random files with a random positive number of unique words
// with varying lengths using the STL set. We read this file into with
// our Dictionary class and compare the size of the dictionary with
// the size of the STL set used the create the file.
TEST(sizeTest, randomWords) {
  char file[] = "/tmp/fileXXXXXX";
  mkstemp(file);

  string word;
  for (int i = 0; i < 50; i++)
  {
    int n_words = rand() % 10000 + 1;
    set<string> words;
    while (words.size() < n_words) {
      string word;
      int word_length = rand() % 20 + 1;
      for (int j = 0; j < word_length; ++j) {
        word += alphabet[rand() % 26]; 
      }
      if (!words.count(word)) {
        words.insert(word);
      }
    }

    ofstream ofs(file);
    set<string>::iterator iter;
    for (iter = words.begin(); iter != words.end(); ++iter) {
      ofs << *iter << endl;
    }
    ofs.close();
    TrieDictionary d = TrieDictionary(file);
    EXPECT_EQ(d.size(), words.size());
  }
}

// If use an empty file for our Dictionary object then we should
// have a dictionary of size 0.
TEST(sizeTest, emptyFile) {
  char file[] = "/tmp/fileXXXXXX";
  mkstemp(file);

  TrieDictionary d = TrieDictionary(file);
  EXPECT_EQ(d.size(), 0);
}

// We test dfs_boggle() by creating a random boggle board and
// checking that each solution is a valid word in our dictionary.
TEST(dfsBoggleTest, solutionsAreValid) {
  string file = getDictionaryFile();
  TrieDictionary d1 = TrieDictionary(file);
  HashDictionary d2 = HashDictionary(file);
  set<string> solutions = set<string>();

  int rows = 4, cols = 4;
  for (int count = 0; count < 100; count++) {
    BoggleBoard board = BoggleBoard(rows, cols);
    for (int i = 0; i < board.rows(); ++i) {
      for (int j = 0; j < board.cols(); ++j) {
        board.at(i, j) = alphabet[rand() % 26]; 
      }
    }

    BoggleSolver solver = BoggleSolver();
    solver.setDictionary(d1);
    solutions = solver.solve(board);

    set<string>::iterator i;
    for (i = solutions.begin(); i != solutions.end(); ++i) {
      EXPECT_TRUE(d1.isWord(*i));
      EXPECT_TRUE(d2.isWord(*i));
    }
  }
}

// We create two objects to represent the boggle board.
// We fill in the first board with random alphabetic character
// values. Then we open a temporary file to write those values.
// Next we call readBoard() and store the return value in the second
// board object. Finally we compare the values in the indices of each
// board, which should be equal. We repeat this 1000 times.
TEST(BoggleBoard, readFromStream) {
  char b1[ROWS][COLS];

  char file[] = "/tmp/fileXXXXXX";
  mkstemp(file);
  ofstream ofs;
  ifstream ifs;

  for (int count = 0; count < 1000; count++)
  {
    // we don't need to add the spacing, but let's make it look
    // like how the user might prefer to write it
    ofs.open(file);
    for (int i = 0; i < ROWS; i++)
    {
      if (0 != i) ofs << endl;
      for (int j = 0; j < COLS; j++)
      {
        b1[i][j] = alphabet[rand() % 26];
        ofs << b1[i][j] << " ";
      }
    }
    ofs.close();
    ifs.open(file);
    BoggleBoard b2 = BoggleBoard();
    b2.readFromStream(ifs);
    ifs.close();

    for (int i = 0; i < ROWS; i++)
      for (int j = 0; j < COLS; j++)
        EXPECT_EQ(b1[i][j], b2.at(i,j));
  }
}

/*
// Gets a random board and record the number of solutions for all
// lower case. Toggle the cases of letters on this board and check that
// the number of solutions do not change. If we want to test exhaustively,
// we are testing 2^16 ~ 64000 boards. Because this test takes a long
// time, I have commented out code which may be used in place of
// the comprehensive test. It randomly toggles the case of words for
// each iteration, but does not test all cases.
TEST(dfsBoggleTest, caseInsensitiveBoard) {
  vector< vector<char> > board 
    = vector< vector<char> >(ROWS, vector<char>(COLS));

  string letters = "";
  for (int i = 0; i < 16; i++)
    letters += alphabet[rand() % 26];
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
      board[i][j] = letters[j + ROWS*i]; 

  vector< vector<bool> > visited = 
    vector< vector<bool> >(ROWS, vector<bool>(COLS, false));
  TrieDictionary d = TrieDictionary("/usr/share/dict/words");
  set<string> solutions;

  string s = "";
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
      dfs_boggle(solutions, board, pair<int, int>(i,j), s, visited, d);

  int n_solutions = solutions.size();
  solutions.clear();
  char c;

  
  // Use the following for a less-comprehensive but speedier test
  // It might take about 600 ms = .6 seconds
  for (int count = 0; count < 100; count++)
  {
    for (int i = 0; i < ROWS; i++)
      for (int j = 0; j < COLS; j++)
      {
        c = board[i][j];
        if (rand() % 2 == 0)
          board[i][j] = isupper(c) ? tolower(c): toupper(c);
      }
    for (int i = 0; i < ROWS; i++)
      for (int j = 0; j < COLS; j++)
        dfs_boggle(solutions, board, pair<int, int>(i,j), s, visited, d);
    EXPECT_EQ(solutions.size(), n_solutions);
    solutions.clear();
  }
  */
  
  /*
  // Use the following for an exhaustive test
  // The last time I ran it, it took 5 minutes. Be warned.
  int k;
  while (true)
  {
    // consider letters as a reverse binary string.
    // 0 for lower case, 1 for upper case.
    // We "add 1" to the left side and carry over.
    // We should loop 2^16 - 1 times.
    for (k = 0; k < ROWS*COLS; k++)
    {
      c = letters[k];
      if (islower(c))
      {
        letters[k] = toupper(c);
        break;
      }  
      else
        letters[k] = tolower(c);
    }
    if (k == ROWS*COLS)
      break;
    
    for (int i = 0; i < ROWS; i++)
      for (int j = 0; j < COLS; j++)
        board[i][j] = letters[j + ROWS*i]; 
    for (int i = 0; i < ROWS; i++)
      for (int j = 0; j < COLS; j++)
        dfs_boggle(solutions, board, pair<int, int>(i,j), s, visited, d);
    EXPECT_EQ(solutions.size(), n_solutions);
    solutions.clear();
  }
  */
/*
}
*/

// We check that using the constructor BoggleBoard() gives us a board
//  with 4 rows and 4 columns.
// We check that using the constructor BoggleBoard(r, c) gives
//  us a board with r rows and c columns for random values between
//  1 and 1000.
TEST(BoggleBoard, checkDimensions) {
  int rows, cols;
  int max = 1000;

  BoggleBoard board = BoggleBoard();
  EXPECT_EQ(4, board.rows());
  EXPECT_EQ(4, board.cols());

  for (int i = 0; i < 1000; ++i) {
    rows = rand() % max + 1;
    cols = rand() % max + 1;
    BoggleBoard board = BoggleBoard(rows, cols);
    EXPECT_EQ(rows, board.rows());
    EXPECT_EQ(cols, board.cols());
  }
}

// We check that an exception is raised if we specify a board
//  with at least one negative dimension.
TEST(BoggleBoard, negativeRowsOrColumns) {
  int rows, cols;
  int max = 1000;

  for (int i = 0; i < 1000; ++i) {
    rows = rand() % max - max / 2;
    cols = rand() % max - max / 2;
    if (rows < 0 || cols < 0) {
      EXPECT_ANY_THROW(BoggleBoard board = BoggleBoard(rows, cols););
    }
  }
}

// We construct a board that is guaranteed to contain at least one
// non-alphabetic character and call the BoggleBoard::isValid() function.
TEST(BoggleBoard, invalidBoardNonalphabeticCharacter) {
  char file[] = "/tmp/fileXXXXXX";
  mkstemp(file);
  ofstream ofs;
  ifstream ifs;
  string bad_characters = "1234567890?./!@$%^&*()-[];,+=):";
  string characters = alphabet + bad_characters;
  bool caught;
  BoggleBoard board = BoggleBoard(4, 4);

  for (int count = 0; count < 1000; count++)
  {
    ofs.open(file);
    for (int i = 0; i < 15; i++)
      ofs << characters[rand() % characters.length()];
    ofs << bad_characters[rand() % bad_characters.length()];
    ofs.close();
    ifs.open(file);
    board.readFromStream(ifs);
    EXPECT_FALSE(board.isValid());
    ifs.close();
  }
}

// We construct a board that is guaranteed to contain at least one
// non-alphabetic character and call the BoggleBoard::isValid() function.
TEST(BoggleBoard, validBoardAlphabeticCharacters) {
  char file[] = "/tmp/fileXXXXXX";
  mkstemp(file);
  ofstream ofs;
  ifstream ifs;
  string bad_characters = "1234567890?./!@$%^&*()-[];,+=):";
  string characters = alphabet + bad_characters;
  bool caught;
  BoggleBoard board = BoggleBoard(4, 4);

  for (int count = 0; count < 1000; count++)
  {
    ofs.open(file);
    for (int i = 0; i < 15; i++)
      ofs << characters[rand() % characters.length()];
    ofs << bad_characters[rand() % bad_characters.length()];
    ofs.close();
    ifs.open(file);
    board.readFromStream(ifs);
    EXPECT_FALSE(board.isValid());
    ifs.close();
  }
}

// An exception should be thrown if we try to read from a file
// with too few characters to make a boggle board. This test
// checks that the ios_base::failure exception is thrown.
TEST(readBoard, prematureEOF) {
  char file[] = "/tmp/fileXXXXXX";
  mkstemp(file);
  ofstream ofs;
  ifstream ifs;
  bool caught;
  BoggleBoard board = BoggleBoard(4,4);

  int max;
  for (int count = 0; count < 1000; count++)
  {
    ofs.open(file);
    max = rand() % 16;
    for (int i = 0; i < max; i++)
      ofs << alphabet[rand() % 26];
    ofs.close();
    ifs.open(file);
    EXPECT_FALSE(board.readFromStream(ifs));
    ifs.close();
  }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#undef ROWS
#undef COLS


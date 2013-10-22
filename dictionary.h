// dictionary.h (maybe I should rename of idictionary or dictionary_interface.h)
// Interface for a dictionary

#ifndef HOME_DOCUMENTS_FOO_DICTIONARY_H
#define HOME_DOCUMENTS_FOO_DICTIONARY_H

#include<string>

//using namespace std;

using std::string;

class DictionaryInterface
{
  public:
    //virtual DictionaryInterface() {} // no virtual constructors
    //virtual DictionaryInterface(string file) = 0; // no virt const.
    virtual ~DictionaryInterface() {} 
    virtual bool isWord(string s) = 0;
    virtual bool isPrefix(string s) = 0;
    virtual int size() = 0;
};

#endif // HOME_DOCUMENTS_FOO_DICTIONARY_H

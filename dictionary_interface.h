// dictionary_interface.h 


#ifndef HOME_NOAH_DOCUMENTS_FOO_DICTIONARY_INTERFACE_H
#define HOME_NOAH_DOCUMENTS_FOO_DICTIONARY_INTERFACE_H

#include <string>

using std::string;

class DictionaryInterface
{
  public:
    virtual ~DictionaryInterface() {} 
    virtual bool isWord(string s) = 0;
    virtual bool isPrefix(string s) = 0;
    virtual int size() = 0;
};

#endif // HOME_NOAH_DOCUMENTS_FOO_DICTIONARY_INTERFACE_H

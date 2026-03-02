/*******************************************
 * File: TokenStream.hpp                   *
 * Author: S. Blythe                       *
 * Date: 1/2025                            *
 * PURPOSE: defines a stream of tookens    *
 *   that can be read from or put back to *
 *******************************************/
#ifndef _TOKEN_STREAM_
#define _TOKEN_STREAM_

#include <iostream>
#include <list>

#include "Token.hpp"
#include "freeList.hpp"

class TokenStream
{
private:
  std::list<Token> _stream; // the list of avaialable tokens 
  std::istream& _istr;      // istream tokens are pulled from when needed
  freeList _list;
public:
  TokenStream(std::istream &is,freeList list) : _stream(), _istr(is), _list(list) {}

  freeList list() const {return _list;}
  freeList& list() {return _list;}

  Token get();  // get next token

  void ungetRear(const Token &tok);  // put a token back at (reader) end
  void ungetFront(const Token &tok); // put a token back at (writer) end
  
  void unget(const Token &tok) {ungetRear(tok);} // put token back
};

#endif

/*******************************************
 * File: TokenStream.hpp                   *
 * Author: S. Blythe                       *
 * Date: 1/2025                            *
 * PURPOSE: implements TokenStream class   *
 *******************************************/
#include "TokenStream.hpp"


// implements get
Token 
TokenStream::get()
{
  // nothing in list? we needto get another token from the actual input stream 
  if (_stream.empty())
  {
    Token t;
    t.get(_istr);
    return t;
  }
  else // tokens in list? just pull token from there. 
  {
    Token t = _stream.back();
    _stream.pop_back();
    return t;
  }
}

void
TokenStream::ungetRear(const Token &tok) {_stream.push_back(tok);}

void 
TokenStream::ungetFront(const Token &tok) {_stream.push_front(tok);}
  


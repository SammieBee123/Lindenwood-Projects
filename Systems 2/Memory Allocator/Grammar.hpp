#ifndef _GRAMMAR_HPP_
#define _GRAMMAR_HPP_

#include <iostream>
#include <string>

#include "TokenStream.hpp"


std::string prog(TokenStream &ts);
std::string slist(TokenStream &ts);
std::string stmt(TokenStream &ts);
std::string rhs(TokenStream &ts);



#endif

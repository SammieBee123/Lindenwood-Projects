/*******************************************
 * File: main.cpp                          *
 * Author: Sam Disbrow                     *
 * Date: 02/2025                           *
 * PURPOSE: driver file for project 2      *
 *******************************************/

#include <iostream>
#include <fstream>
#include <list>

#include "Token.hpp"

using namespace std;

int indent = 0;
void print(list <string> code, int length){//a simple function to print a list using input of the list and its length, giving no output.
  for (int i=0;i<length;i++){
    cout<<code.front();
    code.pop_front();
  }
  cout<<endl;
}

list<string> type(istream &is, list<string>code){//checks for int float and void, adding them to the end of the code if present, returning a blank list if not.
  Token tok;
  tok.get(is);
  if(tok.type()==INTEGER||tok.type()==VOID||tok.type()==FLOAT){//check if the next token is an int, void or float, adds it to the end of the code if it is, followed by a space
    code.push_back(tok.value());
    code.push_back(" ");
  }
  else{//if the token isn't int, void, or float, type is invalid and returns an empty list
    code.clear();
  }
  return code;
}

list<string> idlist(istream &is, list<string> code){//takes a list of strings and input stream, checks if the next token/set of tokens is a valid id list, returns the list of strings with them added to the end if so, returns an empty list if not
  unsigned pos=is.tellg();
  Token tok1;
  tok1.get(is);
  if(tok1.type()==ID){//the first token type must be an id, as an id is the start of any id list
    pos=is.tellg();//saving the current possition in case the next token is invalid
    code.push_back(tok1.value());//add the id to the code
    tok1.get(is);
    if(tok1.type()==COMMA){//if the next token is a comma, the id list must continue
      code.push_back(tok1.value());
      code.push_back(" ");
      return idlist(is, code);
    }
    else{
      is.seekg(pos);
      return code;
    }
  }
  else{//if this is not a valid id list, return an empty list
    code.clear();
    return code;
  }
}

list<string> expr(istream &is, list<string> code);//forward declaring so I can use expr and exprlist in factor
list<string> exprlist(istream &is, list<string> code);
list<string> factor(istream &is, list<string> code){
  streampos pos=is.tellg();
  Token tok;
  tok.get(is);
  if(tok.type()==ID){//if the next token is an ID, add it to the code
    code.push_back(tok.value());
    streampos pos = is.tellg();
    tok.get(is);
    if(tok.type()==LPAREN){//check for an LPAREN, if present, next must be an exprlist followed by an RPAREN or will need to seekg back to before the LPAREN was taken
      list<string> temp = exprlist(is, code);
      if(temp.empty()){
	is.seekg(pos);
      }
      else{
	tok.get(is);
	if(tok.type()!=RPAREN){
	  is.seekg(pos);
	}
	else{
	  code.push_back(tok.value());
	  return code;
	}
      }
    }
    else if(tok.type()==LBRACK){//check for an LBRACK, if present, next must be an exprlist followed by an RBRACK or will need to seekg back to before the LBRACK was taken
      list<string> temp = exprlist(is, code);
      if(temp.empty()){
	is.seekg(pos);
      }
      else{
	tok.get(is);
	if(tok.type()!=RBRACK){
	  is.seekg(pos);
	}
	else{
	  code.push_back(tok.value());
	  return code;
	}
      }
    }
    is.seekg(pos);//if it was neither of these, it's just an id, so add a space, and seekg back to before token was gotten.
    code.push_back(" ");
    return code;
  }
  else if(tok.type()==NUM_REAL){//checks for numreal
    code.push_back(tok.value());
    code.push_back(" ");
  }
  else if(tok.type()==NUM_INT){//checks for numint
    code.push_back(tok.value());
    code.push_back(" ");
  }
  else if(tok.type()==LPAREN){//checks for lparen (this time without an ID first) if one is present, next must be an exprlist followed by rparen
    code.push_back(tok.value());
    list<string> temp = exprlist(is, code);
      if(temp.empty()){
	return temp;
      }
      else{
	tok.get(is);
	if(tok.type()!=RPAREN){
	  code.clear();
	  return code;
	}
	else{
	  temp.push_back(tok.value());
	  return temp;
	}
      }
    }
  return code;
  
}
list<string> term(istream &is, list<string> code){//checks if the next token(s) in the input istream is a valid term, adds it to the input list if so, returns an empty list if not.
  code = factor(is, code);//first must be a factor
  streampos pos=is.tellg();
  if(code.empty()){
    is.seekg(pos);
    return code;
  }
  else{
    Token tok;
    tok.get(is);
    if(tok.type()==MULOP){//next check for mulop
      code.push_back(tok.value());
      code.push_back(" ");
      return term(is, code);//if theres a mulop, add it to the list, followed by a space, then another term
    }
    else{//if no mulop, "unget" the last token and return the factor
      is.seekg(pos);
      return code;
    }
  }
}

list<string> simpexpr(istream &is, list<string> code){//takes input of istream and a list of strings. checks if the next token(s) are a valid simpexpr, adds it to the provided list if so, returns an empty list if not.
  streampos pos=is.tellg();
  code = term(is, code);//first must be a term
  if(code.empty()){
    is.seekg(pos);
    return code;
  }
  else{
    pos=is.tellg();
    Token tok;
    tok.get(is);
    if(tok.type()==ADDOP){//check for an addop, if present, add it to the list, followed by a space, then another simpexpr
      code.push_back(tok.value());
      code.push_back(" ");
      return simpexpr(is, code);
    }
    else{//if there's no addop, simply return the term
      is.seekg(pos);
      return code;
    }
  }
}
list<string> expr(istream &is, list<string> code){//takes input of istream and a list of strings. checks if the next token(s) are a valid expr, adds it to the provided list if so, returns an empty list if not.
  code = simpexpr(is, code);//first must be a simpexpr
  streampos pos=is.tellg();
  if(code.empty()){
    is.seekg(pos);
    return code;
  }
  else{
    Token tok;
    tok.get(is);
    if(tok.type()==RELOP){//check for a relop, if present, add it to the list followed by a space, then another simpexpr
      code.push_back(tok.value());
      code.push_back(" ");
      return simpexpr(is, code);
    }
    else{//if theres no relop, just return the simpexpr
      is.seekg(pos);
      return code;
    }
  }
}

list<string> exprlist(istream &is, list<string> code){//takes input of istream and a list of strings. checks if the next token(s) are a valid exprlist, adds it to the provided list if so, returns an empty list if not.
  code = expr(is, code);//first must be an expr
  unsigned pos=is.tellg();
  if(code.empty()){
    is.seekg(pos);
    return code;
  }
  else{
    Token tok;
    tok.get(is);
    if(tok.type()==COMMA){//check for a comma, if present add it to the list followed by another exprlist
      code.push_back(tok.value());
      return exprlist(is, code);
    }
    else{//if no comma, just return the expr
      is.seekg(pos);
      return code;
    }
  }
}
list<string> compound(istream &is, list<string> code);//forward declaring so I can call compound in stmt
list<string> stmt(istream &is, list<string> code){//takes input of istream and a list of strings. checks if the next token(s) are a valid stmt, adds it to the provided list if so, returns an empty list if not.
  Token tok;
  tok.get(is);
  list<string> temp;
  streampos startPos = is.tellg();
  if(tok.type()==ID){//first check for an id, add it to the list if present
    code.push_back(tok.value());
    unsigned pos = is.tellg();
    tok.get(is);
    if(tok.type()==LPAREN){//check fo parenthasis
      code.push_back(" ");
      code.push_back(tok.value());
      code.push_back(" ");
      list<string> temp = exprlist(is, code);
      if(temp.empty()){
	is.seekg(pos);
      }
      else{
	tok.get(is);
	if(tok.type()!=RPAREN){
	  is.seekg(pos);
	}
	else{
	  temp.push_back(tok.value());
	  temp.push_back("\n");
	  for(int i=0;i<indent;i++){
	    temp.push_back("     ");
	  }
	  return temp;
	}
      }
    }
    else if(tok.type()==ASSIGNOP){//if its not an lparen check for assignop
      code.push_back(" ");
      code.push_back(tok.value());
      code.push_back(" ");
      streampos pos = is.tellg();
      list<string> temp = expr(is, code);//if theres an assignop, next must be expr
      if(temp.empty()){
	is.seekg(pos);
	return temp;
      }
      else{
	return temp;
      }
    }
    else{
      is.seekg(pos);
      return code;
    }
  }
  else if(tok.type()==IF){//check for if, which must be followed by an expr, then, a compound, else, and another compound.
    code.push_back(tok.value());
    code.push_back(" ");
    code = expr(is,code);
    indent++;
    if(code.empty()){
      is.seekg(startPos);
      return code;
    }
    else{
      tok.get(is);
      if(tok.type()!=THEN){
	is.seekg(startPos);
	code.clear();
	return code;
      }
      else{
	code.push_back(" ");
	code.push_back(tok.value());
	code = compound(is, code);
	if(code.empty()){
	  is.seekg(startPos);
	  return code;
	}
	else{
	  tok.get(is);
	  if(tok.type()!=ELSE){
	    is.seekg(startPos);
	    code.clear();
	    return code;
	  }
	  else{
	    indent--;
	    code.push_back("\n");
	    for(int i=0;i<indent;i++){
	      code.push_back("     ");
	    }
	    code.push_back(tok.value());
	    indent++;
	    code=compound(is,code);
	    if(code.empty()){
	      is.seekg(startPos);
	      return code;
	    }
	    else{
	      indent--;
	      return code;
	    }
	  }
	}
      }
    }
  }
  else if(tok.type()==WHILE){//check for while which must be followed by lparen, expr, rparen, and a compound
    code.push_back(tok.value());
    indent++;
    tok.get(is);
    if(tok.type()!=LPAREN){
      code.clear();
      return code;
    }
    code.push_back(tok.value());
    code.push_back(" ");
    code = expr(is,code);
    if(code.empty()){
      is.seekg(startPos);
      return code;
    }
    else{
      tok.get(is);
      if(tok.type()!=RPAREN){
	is.seekg(startPos);
	code.clear();
	return code;
      }
      else{
	code.push_back(tok.value());
	code = compound(is, code);
	indent--;
	if(code.empty()){
	  is.seekg(startPos);
	  return code;
	}
      }
    }
  }
  else{
    compound(is,code);
    return code;
  }
  return code;
}
list<string> stmtlist(istream &is, list<string> code){//takes input of istream and a list of strings. checks if the next token(s) are a valid stmtlist, adds it to the provided list if so, returns an empty list if not.
  Token tok;
  code = stmt(is, code);//first must be a statement
  unsigned pos=is.tellg();
  if(code.empty()){
    is.seekg(pos);
    return code;
  }
  else{
    tok.get(is);
    if(tok.type()==SEMICOLON){//check for a semicolon, which will be followed by another stmtlist
      code.push_back(tok.value());
      code.push_back("\n");
      for(int i=0;i<indent;i++){
	 code.push_back("     ");
      }
      return stmtlist(is, code);
    }
    else{//if no semicolon, just return the stmt
      code.push_back("\n");
      for(int i=0;i<indent;i++){
	 code.push_back("     ");
      }
      is.seekg(pos);
      return code;
    }
  }
}

list<string> compound(istream &is, list<string> code){//takes input of istream and a list of strings. checks if the next token(s) are a valid compound, adds it to the provided list if so, returns an empty list if not.
  unsigned pos = is.tellg();
  Token tok;
  tok.get(is);
  if(tok.type()!=BEGIN){//first must be begin
    is.seekg(pos);
    code.clear();
  }
  else{
    code.push_back("\n");
    for(int i=0;i<indent;i++){
       code.push_back("     ");
    }
    code.push_back(tok.value());
    indent++;
    code.push_back("\n");
    for(int i=0;i<indent;i++){
       code.push_back("     ");
    }
    code = stmtlist(is, code);//next must be stmtlist
    if(code.empty()){
      is.seekg(pos);
      return code;
    }
    else{
      tok.get(is);
      if(tok.type()!=END){//finally must be end
	is.seekg(pos);
	code.clear();
      }
      else{
	indent--;
	code.pop_back();
	code.push_back(tok.value());
      }
    }
  }
  return code;
}
list<string> declaration(istream &is, list<string> code){//takes input of istream and a list of strings. checks if the next token(s) are a valid declaration, adds it to the provided list if so, returns an empty list if not.
  streampos pos=is.tellg();
  code = type(is, code);//check for type
  if(code.empty()){
    is.seekg(pos);
  }
  else{
    code = idlist(is, code);//after type must be idlist
    if(code.empty()){
      is.seekg(pos);
    }
    else{
      Token tok;
      tok.get(is);
      if(tok.type()!=SEMICOLON){//after idlist must be semicolon
	is.seekg(pos);
	code.clear();
      }
      else{
	code.push_back(tok.value());
	code.push_back("\n");
	for(int i=0;i<indent;i++){
	  code.push_back("     ");
	}
      }
    }
  }
  return code;
}

list<string> program(istream &is, list<string> code){//takes input of istream and a list of strings. checks if the next token(s) are a valid program, adds it to the provided list if so, returns an empty list if not.
  streampos pos = is.tellg();
  list<string> temp;
  temp = declaration(is, code);//check for declaration
  if(temp.empty()){//if it's not a declaration, go back and check for compound
    is.seekg(pos);
    for(int i=0;i<indent;i++){
      code.push_back("     ");
    }
    code = compound(is, code);
    if(code.empty()){
      is.seekg(pos);
    }
    return code;
  }
  else{
    return program(is, temp);//if it is a declaration, it is followed by another program
  }
}

int main(int argc, char *argv[]){//a simple main to make sure valid args are passed, and print the appropriate output.
  // check to make sure an input file was specified. 
  if (argc!=2)
    {
      cerr << "USAGE: " << argv[0] << " <file>" << endl;
      return -1;
    }

  // open input file
  ifstream ifile(argv[1]);

  // if open was not successful, let user know. 
  if (!ifile)
    {
      cerr << "ERROR: Could not open file:\"" << argv[1] << "\"" <<endl;
      return -1;
    }
  list<string> beautified;
  beautified = program(ifile, beautified);
  if(beautified.empty()){
    cout<<"UNsuccessful code :( =========================="<<endl;
  }
  else{
    cout<<"Successful code :) ==========================="<<endl;
    print(beautified,beautified.size());
  }
  


  return 0;
}

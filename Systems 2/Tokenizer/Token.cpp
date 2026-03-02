/*******************************************
 * File: Token.cpp                         *
 * Author: S. Blythe                       *
 * Date: 12/2024                           *
 * PURPOSE: implementation for Token       *
 *******************************************/

#include "Token.hpp"

#include <fstream>
#include <iomanip>

using namespace std;

// the promised global for string equivalents of TokenType enumeration
string TokStr[]=
{ "ERROR", "EOF_TOK", "NUM_INT", "NUM_REAL", "ADDOP", "MULOP", "ID", "RELOP", "ASSIGNOP", "LPAREN", "RPAREN",  "SEMICOLON",  "LBRACK", "RBRACK", "COMMA", "AND", "OR", "INTEGER", "FLOAT", "WHILE", "IF", "THEN", "ELSE", "VOID", "BEGIN", "END"};

// This is a "list" of the keywords. Note that they are in the same order
//   as found in the TokenType enumaration. 
static string reserved[]={"int" , "float", "while", "if", "then", "else", "void", "begin", "end" };



/******************************************************
 *  just prints out the info describing this Token    *
 *    to specified stream                             *
 *                                                    *
 *   os  - the stream to add the Token to             *
 *                                                    *
 *   returns: the updated stream                      *
 ******************************************************/
ostream&
Token::print(ostream& os) const
{
  os
     << "{ Type:"   << left << setw(10) << TokStr[_type] 
     << " Value:"   << left << setw(10) << _value
     << " Line Number:" << _line_num
     << " }";
  return os;
}

/******************************************************
 *  Fills in information about this Token by reading  *
 *    it from specified input stream                  *
 *                                                    *
 *   is  - the stream to read the Token from          *
 *                                                    *
 *   returns: nothing                                 *
 *                                                    *
 *     Author: Sam Disbrow                            *
 ******************************************************/
void Token::get(istream &is)
{
  static int DFA[20][256]; //Creates the blank DFA
  static bool firstCall=true; //This is the first call
  static int lineNum = 1; //Start on line 1
  //fill in the table starting with all errors
  if(firstCall){
    for(int row=0; row<20; row++){
      for (int col=0;   col<256; col++){
	DFA[row][col]=-1;
      }
    }

    //All paths out of 0 (in order of next state)
    for (char ch='a'; ch<='z' ;ch++){
      DFA[0][(unsigned) ch]=1;
    }
    for (char ch='A';ch<='Z';ch++){
      DFA[0][(unsigned) ch]=1;
    }
    for (char ch='0';ch<='9';ch++){
      DFA[0][(unsigned) ch]=2;
    }
    DFA[0][(unsigned) '-']=5;
    DFA[0][(unsigned) '+']=5;
    DFA[0][(unsigned) '*']=6;
    DFA[0][(unsigned) '/']=6;
    DFA[0][(unsigned) '<']=7;
    DFA[0][(unsigned) '>']=7;
    DFA[0][(unsigned) '=']=9;
    DFA[0][(unsigned) '(']=10;
    DFA[0][(unsigned) ')']=11;
    DFA[0][(unsigned) '&']=12;
    DFA[0][(unsigned) '|']=14;
    DFA[0][(unsigned) ';']=16;
    DFA[0][(unsigned) '[']=17;
    DFA[0][(unsigned) ']']=18;
    DFA[0][(unsigned) ',']=19;

    //From state 1
    for (char ch='a'; ch<='z' ;ch++){
      DFA[1][(unsigned) ch]=1;
    }
    for (char ch='A';ch<='Z';ch++){
      DFA[1][(unsigned) ch]=1;
    }
    for (char ch='0';ch<='9';ch++){
      DFA[1][(unsigned) ch]=1;
    }
    //From state 2
    for (char ch='0';ch<='9';ch++){
      DFA[2][(unsigned) ch]=2;
    }
    DFA[2][(unsigned) '.']=3;
    //From state 3
    for (char ch='0';ch<='9';ch++){
      DFA[2][(unsigned) ch]=4;
    }
    //From state 4
    for (char ch='0';ch<='9';ch++){
      DFA[2][(unsigned) ch]=2;
    }
    //From state 7
    DFA[7][(unsigned) '=']=8;
    //From state 9
    DFA[9][(unsigned) '=']=8;
    //From state 12
    DFA[12][(unsigned) '&']=13;
    //From state 14
    DFA[14][(unsigned) '|']=15;

    firstCall=false;
  }
  //skip whitespace and comments
  char dummy;
  dummy = is.get();
  bool blank = false;
  if(isspace(dummy)||dummy=='#'){
    blank = true;
  }//Identifies if the next char is either whitespace or a # - the start of a comment
  while(blank){//As long as the above is true, keep taking care of comments or whitespace
    while(isspace(dummy)){//if it's white space, keep getting the next line until it's not
      if(dummy=='\n'){//if it's a new line, we have to increase the line number
	lineNum++;
       }
      dummy = is.get();
    }
    if(dummy == '#'){//if it's a comment, go through till new line, then increase the line number
      while(dummy!='\n'){
	dummy = is.get();
      }
      dummy=is.get();
      lineNum++;
    }
    if(isspace(dummy)||dummy=='#'){//check if it's still "blank", if so, restart the while, if not, continue
      blank = true;
    }
    else{
      blank=false;
    }
  }
  is.unget(); // the last char that dummy checked was NOT blank, so I need it to be part of my token
  if (!is){ //if this is the end of the file, token type is EOF_TOK, and theres no point in continuing, youre done
    _type=EOF_TOK;
    return;
  }
  int currState = 0;//start state
  int prevState = -1;//error
  string val = "";
  char ch;
  while(currState != -1){//as long as the next char is allowed to be added to the token, update the state
    ch = is.get();
    prevState = currState;
    currState = DFA[currState][(unsigned) ch];
    if(currState!=-1){//If the next char is valid, add the char to the value of the token
      val += ch;
    }
  }
  is.unget();//the last ch compared was NOT part of the token, so we need to give it back
  _value=val;//Set the token's value to my temporary "val"
  //Set the appropriate _type depending on prevState number.
  if(prevState==-1){
    _type=ERROR;
  }
  if(prevState==1){ //if it's an ID, check for keywords
    if(_value=="void"){
      _type=VOID;
    }
    else if(_value=="int"){
      _type=INTEGER;
    }
    else if(_value=="float"){
      _type=FLOAT;
    }
    else if(_value=="begin"){
      _type=BEGIN;
    }
    else if(_value=="end"){
      _type=END;
    }
    else if(_value=="if"){
      _type=IF;
    }
    else if(_value=="then"){
      _type=THEN;
    }
    else if(_value=="else"){
      _type=ELSE;
    }
    else if(_value=="while"){
      _type=WHILE;
    }
    else{
      _type=ID;
    }
  }
  if(prevState==2){
    _type=NUM_INT;
  }
  if(prevState==4){
    _type=NUM_REAL;
  }
  if(prevState==5){
    _type=ADDOP;
  }
  if(prevState==6){
    _type=MULOP;
  }
  if(prevState==7||prevState==8){
    _type=RELOP;
  }
  if(prevState==9){
   _type=ASSIGNOP;
  }
  if(prevState==10){
   _type=LPAREN;
  }
  if(prevState==11){
    _type=RPAREN;
  }
  if(prevState==13){
    _type=AND;
  }
  if(prevState==15){
    _type=OR;
  }
  if(prevState==16){
    _type=SEMICOLON;
  }
  if(prevState==17){
    _type=LBRACK;
  }
  if(prevState==18){
    _type=RBRACK;
  }
  if(prevState==19){
    _type=COMMA;
  }
  _line_num=lineNum;//set the token's linenumber
}

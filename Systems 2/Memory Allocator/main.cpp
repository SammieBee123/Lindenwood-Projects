/*******************************************
 * File: main.cpp                          *
 * Author: S. Blythe + Sam Disbrow         *
 * Date: 3/2025                            *
 * PURPOSE: driver file for project 3      *
 *******************************************/

#include <iostream>
#include <fstream>
#include <list>

#include "Grammar.hpp"
#include "Token.hpp"
#include "TokenStream.hpp"
#include "freeList.hpp"

using namespace std;

int main(int argc, char *argv[])
{

  int size;
  string is;  
  cout<<"Enter initial freelist size: ";
  cin>>size;
  cout<<"Enter input file name: ";
  cin>>is;
  ifstream ifile(is);
  if (!ifile)
  {
    cerr << "Could not open file: " << argv[1] << endl;
    return 1;
  }

  // my stream of input tokens to pick from
  list<freeList::data> varList;
  list<freeList::data> list;
  freeList freeList(size,list,varList);
  TokenStream tokens(ifile, freeList);
  //freeList::freeList list(size);
  string statement;
  prog(tokens);
  

  return 0;
}

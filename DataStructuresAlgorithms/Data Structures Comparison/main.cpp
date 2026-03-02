#include <iostream>
#include <fstream>

#include "AVLTree.hpp"
/*******************************************
 * File: main.cpp                          *
 * Author: Sam Disbrow                     *
 * Date: 03/2025                           *
 * PURPOSE: driver file for project 2      *
 *******************************************/

#include "AVLTreeNode.hpp"
#include "Person.hpp"
#include "hashTable.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  if((std::string(argv[2]).compare("avl"))==0){
  AVLTree myTree;
  std::string insName;
  std::string insPhone;
  ifstream ifile(argv[1]);
   //parse through the file, picking out names and phone numbers and making them into a person in myTree. Continues until the end of the file.
  while(ifile){
    ifile>>insName>>insPhone;
    myTree.insert(Person(insName, insPhone));
  }
  cout<<"avl"<<"tree height: "<<myTree.root()->height()<<endl;
  
   
 
    std::string upName;
    std::string upPhone;
    char input;
    cin >> input;//take single char input command
    while(input != 'q'){ //as long as the user doesnt want to quit, keep parsing commands.
      if(input == 'u'){// if u is entered, find the name entered and update the phone number to match the one entered
      cin >> upName >> upPhone;
      myTree.find(upName)->data().phone()=upPhone;
    }
    
      else if(input == 'g'){//if g is entered, find a name and print the coorisponding phone number
      cin >> upName;
      std::cout << myTree.find(upName)->data().phone() << std::endl;
    }
      cin >> input;//take the next single char input
    }
  }
  else if((std::string(argv[2]).compare("hash"))==0)  
    {
      hashTable myTable(atoi(argv[3]));
      std::string insName;
      std::string insPhone;
      ifstream ifile(argv[1]);
      ifile>>insName>>insPhone;
      while(ifile){ //parse through the file, picking out names and phone numbers and making them into a person in myTable. Continues until the end of the file.
	myTable.insert(Person(insName, insPhone));
	ifile>>insName>>insPhone;
      }
      cout<<"max chain length: "<<myTable.chain()<<endl;
       std::string upName;
       std::string upPhone;
       char input;
       cin >> input;//take single char input command
       while(input != 'q'){ //as long as the user doesnt want to quit, keep parsing commands.
	 if(input == 'u'){// if u is entered, find the name entered and update the phone number to match the one entered
	   cin >> upName >> upPhone;
	   myTable.find(upName).setPhone()=upPhone;
	 }
	 else if(input == 'g'){//if g is entered, find a name and print the coorisponding phone number
	   cin >> upName;
	   cout << myTable.find(upName).phone() << endl;
	 }
      cin >> input;//take the next single char input
    }
  }
      return 0;
}

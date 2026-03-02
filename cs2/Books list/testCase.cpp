//#include "BookNode.hpp"
#include "Book.hpp"
#include "Library.hpp"

#include <fstream>
#include <iostream>

using namespace std;

int main(){
//BookNode myNode;
Book fabGang("Chronicles of the Fabristinellis", "Fabristinelli", 2031);
Book two ("two", "Two", 2);
//myNode.data()=&fabGang;
//cout <<myNode<<endl;

Library myLibrary;
myLibrary+=fabGang;
cout << "mylibrary is " << myLibrary;
Library yourLibrary;
yourLibrary+=two;
Library ourLibrary;
ourLibrary = yourLibrary + myLibrary;
cout << "yourlibrary is " << yourLibrary;
cout << "ourlibrary is " << ourLibrary;
return 0;
}

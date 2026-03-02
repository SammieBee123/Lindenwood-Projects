#include "Book.hpp"
#include "Library.hpp"

#include <fstream>
#include <iostream>

using namespace std;

int main(){
  Book fabGang("Chronicles of the Fab Folks", "Fabristinelli", 2031);
  cout << "======= just the book fabGang =======" << endl;
  cout << fabGang << endl;
  cout<<endl;
  Book slay("We be Slayin'","Smith",1878);
  Book Yas ("Yaaas","Yaaaaaaas",2519);
  Book skylar("skylar","skylar",2024);
  Book hi("hi","Porter",9089);
  Book beep("boop","robot",1738);
  Library test;
  test+=fabGang;
  test+=slay;
  test+=Yas;
  test+=skylar;
  test+=hi;
  test+=beep;
  cout << endl;
  cout << "whole test library" << endl;
  cout << test << endl;
  Library two;
  two = test;
  Library three;
  three = test+two;
  cout << endl;
  cout << "whole three - should be identical" << endl;
  cout << three << endl;
  
  test -= slay;
  //cout << test << endl;
  
  return 0;
}

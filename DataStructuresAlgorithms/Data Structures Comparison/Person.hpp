/*******************************************
 * File: Person.hpp                        *
 * Author: Sam Disbrow                     *
 * Date: 03/2025                           *
 * PURPOSE: person implementation          *
 *******************************************/

#ifndef _PERSON_HPP_
#define _PERSON_HPP_

#include <string>

class Person
{
private:
  std::string _phone;
  std::string _name;
public:
  Person(): _phone(""), _name("") {}
  Person(std::string name, std::string phone):_phone(phone), _name(name){}

  std::string phone() const {return _phone;}
  std::string& setPhone() {return _phone;}

  std::string name() const {return _name;}
  std::string& name() {return _name;}
  
};

 #endif

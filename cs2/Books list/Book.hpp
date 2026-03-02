#ifndef _BOOK_HPP_
#define _BOOK_HPP_

#include <iostream>
#include <string>

class Book
{
    private:
      std::string _title;  // Book title
      std::string _author; // Book author
      int _year;           // Book year of copyright
      int _checkoutCount;  // Number of times book has been checked out
    public:
      // Default constructor
      // No title, author, -1 for year and no checkouts. 
      Book(): _title(), _author(), _year(-1), _checkoutCount(0) {}

      // Constructor to build a book out of a title, author, and year. Checkouts start at 0. 
      Book(const std::string &title, const std::string &author, int year):
        _title(title), _author(author), _year(year), _checkoutCount(0) {}

      // "Copy" constructor
      // Use existing book's data to create another book (checkouts set to 0.)
      Book(const Book &bookToCopy);

      // Accessor - get the title of this book.
      const std::string& title() const {return _title;}

      // Accessor - get the author of this book.
      const std::string& author() const {return _author;}

      // Accessor - get the copyright year of this book.
      int year() const {return _year;}

      // Accessor - get the number of times this book has been checked out. 
      int checkouts() const {return _checkoutCount;}
      // Modifier - return reference to the number of times this book has 
      //    been checked out. 
      int& checkouts() {return _checkoutCount;}

      // Overloaded ++ to increment the number of times this book has been
      //   checked out. 
      //  NOTE: This version only works as pre-increment (i.e. ++book)
      const Book& operator++(); 
      
      // Various overloaded comparison operators. 
      bool operator< (const Book &other) const;
      bool operator> (const Book &other) const;
      bool operator== (const Book &other) const;
      bool operator!= (const Book &other) const;
      
      // Read book data from input stream
      std::istream& read(std::istream &fromStream);

      // Output book data to an output stream
      std::ostream& print(std::ostream &toStream) const;
};

// Overload >> operator 
std::istream& operator>>(std::istream &is, Book &b);

// Overload << operator 
std::ostream& operator<<(std::ostream &os, const Book &b);

#endif

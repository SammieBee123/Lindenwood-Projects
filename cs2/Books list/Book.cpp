#include "Book.hpp"

using namespace std;

// Copy constructor
Book::Book(const Book &bookToCopy)
{
  // Most attributes are just copied over to new book.
  _title = bookToCopy._title;
  _author = bookToCopy._author;
  _year = bookToCopy._year;

  // Exception: checkoutCount in new book is set to 0. 
  _checkoutCount=0;
}

// Adds one to this book's checkout count. 
// Returns updated book. 
const Book&
Book::operator++()
{
  _checkoutCount++;
  return *this;
}

// Less than for two books. 
//  First,  check title
//  Second, check author
//  Finally, check year
bool
Book::operator< (const Book &other) const
{
  // Can we decide based on title?
  if (_title < other._title) return true;
  if (_title > other._title) return false;

  // If titles are equal, can we decide based on author?
  if (_author < other._author) return true;
  if (_author > other._author) return false;

  // If titles and authors are equal, decide based on year?
  return _year < other._year; 
}
  
// Greater than for two books.
//   Coder's trick: just use <
bool
Book::operator> (const Book &other) const
{
  return other < *this;
}

// Are two books the equal? 
bool
Book::operator== (const Book &other) const
{
  // Only equal if title, author, and year are the same
  // (Note that checkout count is not considered.) 
  return (_title==other._title &&
	  _author==other._author &&
	  _year==other._year);
}

// Are two books different? 
//   Coder's trick: This is the opposite of the books being the same. 
bool  
Book::operator!= (const Book &other) const
{
  return !operator==(other);
}
  
// Stand-alone function to remove all leading spaces from parameter(fromString)
static void stripLeadingSpaces(string &fromString)
{
  // Count number of leading spaces
  int pos;
  for (pos=0; pos < fromString.length() && isspace(fromString[pos]); pos++)
	;

  // Keep sub-string that skips over the number of spaces. 
  fromString = fromString.substr(pos);
}


// Read a book from the specified stream
std::istream&
Book::read(std::istream &is)
{
  // First two items are author's last name and copyright year
  is >> _author >> _year;
  // Rest of line is title. 
  getline(is, _title);

  
  // Modify _title to remive any (and all) leading spaces (see function above)
  stripLeadingSpaces(_title);

  // Return updated stream
  return is;
}

// Output (print) a book to the specified stream
std::ostream&
Book::print(std::ostream &os) const
{
  // Note that outputting omits the number of checkouts
  os << _author << ' ' << _year << ' ' << _title;

  // Return updated stream
  return os;
}

// Overloaded >> for Book
std::istream& operator>>(std::istream &is, Book &b)
{ 
  // Coder's "trick": use the above read() method
  return b.read(is);
}

// Overloaded << for Book
std::ostream& operator<<(std::ostream &os, const Book &b)
{
  // Coder's "trick": use the above print() method
  return b.print(os);
}

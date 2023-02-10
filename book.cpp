#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(std::string category, std::string name, double price, int qty, std::string isbn, std::string author) :
	Product(category, name, price, qty)
{
		isbn_ = isbn;
		author_ = author;
}

Book::~Book()
{
}


std::set<std::string> Book::keywords() const
{
	std::set<std::string> title = parseStringToWords(getName());
	std::set<std::string> author = parseStringToWords(author_);

	title.insert(isbn_);

	std::set<std::string> result = setUnion(title, author);
	return result;
}

std::string Book::displayString() const {
	std::string result = getName() + "\nAuthor: " + author_ + " ISBN: " + isbn_ + "\n";
	result += to_string(getPrice()) + " " + to_string(getQty()) + " left.";

	return result; 
}

void Book::dump(std::ostream& os) const{
	os<<"book"<<endl<<getName()<<endl<<getPrice()<<endl<<getQty()<<endl<<isbn_<<endl<<author_<<endl;
}



#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(std::string category, std::string name, double price, int qty, std::string genre, std::string rating) :
	Product(category, name, price, qty)
{
		genre_ = genre;
		rating_ = rating;
}

Movie::~Movie()
{
}


std::set<std::string> Movie::keywords() const
{
	std::set<std::string> title = parseStringToWords(getName());
	std::set<std::string> genre = parseStringToWords(genre_);

	std::set<std::string> result = setUnion(title, genre);
	return result;
}

std::string Movie::displayString() const{
	std::string result = getName() + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n";
	result += to_string(getPrice()) + " " + to_string(getQty()) + " left.";

	return result; 
}

void Movie::dump(std::ostream& os) const{
	os<<"movie"<<endl<<getName()<<endl<<getPrice()<<endl<<getQty()<<endl<<genre_<<endl<<rating_<<endl;
}

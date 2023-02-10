#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(std::string category, std::string name, double price, int qty, std::string size, std::string brand) :
	Product(category, name, price, qty)
{
		size_ = size;
		brand_ = brand;
}

Clothing::~Clothing()
{
}


std::set<std::string> Clothing::keywords() const
{
	std::set<std::string> title = parseStringToWords(getName());
	std::set<std::string> brand = parseStringToWords(brand_);


	std::set<std::string> result = setUnion(title, brand);
	return result;
}

std::string Clothing::displayString() const{
	std::string result = getName() + "\nSize: " + size_ + " Brand: " + brand_ + "\n";
std::string temp = to_string(getPrice());
	size_t per = temp.find(".") + 3;
	temp = temp.substr(0, per);
	result += temp + " " + to_string(getQty()) + " left.";

	return result; 
}

void Clothing::dump(std::ostream& os) const{
	os<<"clothing"<<endl<<getName()<<endl<<getPrice()<<endl<<getQty()<<endl<<size_<<endl<<brand_<<endl;
}

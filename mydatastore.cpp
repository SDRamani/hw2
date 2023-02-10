#include <iostream>
#include <sstream>
#include "product_parser.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include "util.h"
#include "mydatastore.h"
using namespace std;

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{
	for (size_t i = 0; i < prodList.size(); i++){
		delete prodList[i];
	}
	for (size_t i = 0; i < userList.size(); i++){
		delete userList[i];
	}
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
		std::set<Product*> result;
		//AND
		if (type == 0){
			for (size_t i = 0;i < terms.size();i++){
				std::map<std::string, std::set<Product*>>::iterator it = prodMap.find(terms[i]);
				if (it != prodMap.end()){
					if (result.empty()){
						result = it->second;
					}
					else{
						result = setIntersection(result, it->second);
					}
				}
			}

		}
		//OR
		else if (type == 1){
			for (size_t i = 0;i < terms.size();i++){
				std::map<std::string, std::set<Product*>>::iterator it = prodMap.find(terms[i]);
				if (it != prodMap.end()){
						result = setUnion(result, it->second);
				}
			}
		}

		std::vector<Product*> answer(result.size());
		std::copy(result.begin(), result.end(), answer.begin());
		return answer;
}

void MyDataStore::addProduct(Product* p)
{
		prodList.push_back(p);
		std::set<std::string> keyword = p->keywords();
		std::set<std::string>::iterator it;

		for (it = keyword.begin(); it != keyword.end(); ++it){
			std::map<std::string, std::set<Product*>>::iterator jt = prodMap.find(*it);
			if (jt != prodMap.end()){
				(jt->second).insert(p);
			}
			else{
				std::set<Product*> temp;
				temp.insert(p);
				prodMap.insert(std::make_pair(*it, temp));
			}
		}
}

void MyDataStore::addUser(User* u){
	userMap.insert(std::make_pair(u->getName(), u));
	userList.push_back(u);
	std::vector<Product*> temp;
	cart.insert(std::make_pair(u, temp));
}

void MyDataStore::dump(std::ostream& ofile){
	ofile << "<products>" << endl;
	for (size_t i = 0; i < prodList.size(); i++){
		(prodList[i])->dump(ofile);
	}
	ofile << "</products>" << endl << "<users>" << endl;
	for (size_t i = 0; i < userList.size(); i++){
		(userList[i])->dump(ofile);
	}
	ofile << "</users>" << endl;
}

void MyDataStore::addCart(std::string u, Product* p){
	std::map<std::string, User*>::iterator jt = userMap.find(u);
	if (jt == userMap.end()){
		cout << "Invalid request";
		return;
	}
	User* temp = jt->second;
	std::map<User*, std::vector<Product*>>::iterator it = cart.find(temp);
	if (it != cart.end()){
		(it->second).push_back(p);
	}
}

void MyDataStore::displayCart(std::string u){
	std::map<std::string, User*>::iterator jt = userMap.find(u);
	if (jt == userMap.end()){
		cout << "Invalid username";
		return;
	}
	User* temp2 = jt->second;
	std::map<User*, std::vector<Product*>>::iterator it = cart.find(temp2);
	std::vector<Product*> temp = it->second;
	for (size_t i = 0; i < temp.size(); i++){
		cout << "Item " << (i+1) << endl;
		cout << (temp[i])->displayString() << "\n";
	}
}

void MyDataStore::buyCart(std::string u){
	std::map<std::string, User*>::iterator jt = userMap.find(u);
	
	if (jt == userMap.end()){
		cout << "Invalid username";
		return;
	}
	User* temp2 = jt->second;
	std::map<User*, std::vector<Product*>>::iterator it = cart.find(temp2);
	if (it == cart.end()){
		cout << "Invalid request";
		return;
	}
	std::vector<Product*> temp = it->second;
	std::vector<int> remove;
	for (size_t i = 0; i < temp.size(); i++){
		double price = temp[i]->getPrice();
		if (temp2->getBalance() < price){
			continue;
		}
		else if (temp[i]->getQty() < 1){
			continue;
		}
		else{
			temp[i]->subtractQty(1);
			temp2->deductAmount(price);
			remove.push_back(i);
		}
	}
	for (size_t i = remove.size() - 1; i <= 0; i--){
		(it->second).erase((it->second).begin() + i);
	}
}
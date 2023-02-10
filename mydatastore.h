#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"

class MyDataStore : public DataStore{
public:
		MyDataStore();
		~MyDataStore();
		std::vector<Product*> search(std::vector<std::string>& terms, int type);
		void addProduct(Product* p);
		void addUser(User* u);
		void dump(std::ostream& ofile);
		void addCart(std::string u, Product* p);
		void displayCart(std::string u);
		void buyCart(std::string u);
private:
		std::map<std::string, std::set<Product*>> prodMap;
		std::vector<Product*> prodList;
		std::vector<User*> userList;
		std::map<std::string, User*> userMap;
		std::map<User*, std::vector<Product*>> cart;
};

#endif
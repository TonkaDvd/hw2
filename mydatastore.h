#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include <map>

class myDataStore : public DataStore {
public:
    myDataStore();
    ~myDataStore();

    void addProduct(Product* p) override; 

    void addUser(User* u) override;

    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

    void dump(std::ostream& ofile) override;

    void addingToCart(std::string userName, Product* p);
    void viewingTheCart(std::string userName);
    void buyingTheCart(std::string userName);


protected:
std::set<Product*> Products;
std::map<std::string, User*> Users;
std::map<std::string, std::set<Product*>> keywordMap_;
std::map<std::string, std::vector<Product*>> usersCarts;

};

#endif
#include "mydatastore.h"
#include "util.h"

using namespace std;

myDataStore::myDataStore(){

}

myDataStore::~myDataStore() {
    for (std::set<Product*>::iterator it = Products.begin(); it != Products.end(); ++it) {
        delete *it; 
    }

    for (std::map<std::string, User*>::iterator it = Users.begin(); it != Users.end(); ++it) {
        delete it->second; 
    }
}

void myDataStore::addProduct(Product* p){
    std::set<std::string> productsKeywords = p->keywords();

    for(std::set<std::string>:: iterator it = productsKeywords.begin(); it != productsKeywords.end(); ++it){
        if(!(keywordMap_.find(*it) == keywordMap_.end())){
            keywordMap_[*it].insert(p);
        } else{
            keywordMap_[*it] = std::set<Product*>{p};
        }
    }

    Products.insert(p);
}

void myDataStore::addUser(User* u){
    Users[convToLower(u->getName())] = u;
}

std::vector<Product*> myDataStore::search(std::vector<std::string>& terms, int type){
    std::set<Product*> s3;
    std::set<Product*> s4;
    std::vector<Product*> finished;

    if (terms.empty()) {
        return finished;
    }

    if (keywordMap_.find(terms[0]) != keywordMap_.end()) {
        s3 = keywordMap_[terms[0]];
    } else if (type == 0) {
        return finished; 
    }

    for(size_t i = 1; i < terms.size(); i++){
        if(type == 0){
            if(!(keywordMap_.find(terms[i]) == keywordMap_.end())){
                s4 = keywordMap_[terms[i]];
                s3 = setIntersection(s3, s4);
            } else{
                return finished; 
            }
        } else if (type == 1){
            if(!(keywordMap_.find(terms[i]) == keywordMap_.end())){
                s4 = keywordMap_[terms[i]];
                s3 = setUnion(s3, s4);
            }
        }
    }

    for(std::set<Product*>:: iterator it = s3.begin(); it != s3.end(); ++it){
        finished.push_back(*it);
    }

    return finished;
}

void myDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>\n";
    for (std::set<Product*>::iterator it = Products.begin(); it != Products.end(); ++it) {
        (*it)->dump(ofile); 
    }
    ofile << "</products>\n";

    ofile << "<users>\n";
    for (std::map<std::string, User*>::iterator it = Users.begin(); it != Users.end(); ++it) {
        it->second->dump(ofile);
    }
    ofile << "</users>\n";
}


void myDataStore::addingToCart(std::string userName, Product* p){
    userName = convToLower(userName);

    if (Users.find(userName) == Users.end()) {
        std::cout << "Invalid request" << std::endl;
        return;
    }

    if(!(usersCarts.find(userName) == usersCarts.end())){
        usersCarts[userName].push_back(p);
    } else{
        usersCarts[userName] = std::vector<Product*>{p};
    }
}

void myDataStore::viewingTheCart(std::string userName){
    userName = convToLower(userName);

    if (Users.find(userName) == Users.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    const std::vector<Product*>& cart = usersCarts[userName];
    int cartSize = usersCarts[userName].size();

    for(size_t i = 0; i < cartSize; i++){
        std::cout << "Item " << (i + 1) << "\n" << cart.at(i)->displayString() << '\n';
    }
}

void myDataStore::buyingTheCart(std::string userName){
    userName = convToLower(userName);
    if (Users.find(userName) == Users.end()) {
        std::cout << "Invalid username\n";
        return;
    }

    User* currentUser = Users[userName];
    std::vector<Product*> remainingItems;

    for (size_t i = 0; i < usersCarts[userName].size(); i++) {
        Product* currentProduct = usersCarts[userName][i];

        if (currentProduct->getQty() > 0 && currentUser->getBalance() >= currentProduct->getPrice()) {
            currentProduct->subtractQty(1);
            currentUser->deductAmount(currentProduct->getPrice());
        } else {
            remainingItems.push_back(currentProduct);
        }
    }

    usersCarts[userName] = remainingItems;
}


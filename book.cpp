#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string author, const std::string ISBN) : Product(category, name, price, qty)
{
    author_ = author;
    ISBN_ = ISBN;
}

Book::~Book()
{

}

std::set<std::string> Book::keywords() const {
    std::set<std::string> finalSet;

    std::set<std::string> name = parseStringToWords(name_);
    std::set<std::string> authorName = parseStringToWords(author_);

    finalSet = setUnion(name, authorName);

    finalSet.insert(convToLower(ISBN_));

    return finalSet;
}

std::string Book::displayString() const {
    string priceStr = to_string(price_);
    priceStr = priceStr.substr(0, priceStr.find('.') + 3);

    string information = name_ + '\n' + "Author: " + author_ + " ISBN: " + ISBN_ + '\n' + priceStr + " " + to_string(qty_) + " left.";

    return information;
}


void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << ISBN_ << "\n" << author_ << endl;
}

std::string Book::getAuthor() const{
    return author_;
}

std::string Book::getISBN() const{
    return ISBN_;
}




#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) : Product(category, name, price, qty)
{
    genre_ = genre;
    rating_ = rating;
}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const {
    std::set<std::string> finalSet;

    std::set<std::string> name = parseStringToWords(name_);

    finalSet = name;

    finalSet.insert(convToLower(genre_));

    return finalSet;
}

std::string Movie::displayString() const {
    string priceStr = to_string(price_);
    priceStr = priceStr.substr(0, priceStr.find('.') + 3);

    string information = name_ + '\n' + "Genre: " + genre_ + " Rating: " + rating_ + '\n' + priceStr + " " + to_string(qty_) + " left.";

    return information;
}


void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}

std::string Movie::getGenre() const{
    return genre_;
}

std::string Movie::getRating() const{
    return rating_;
}




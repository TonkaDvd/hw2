#include <sstream>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, 
                   const std::string size, const std::string brand) 
    : Product(category, name, price, qty), size_(size), brand_(brand)
{
}

Clothing::~Clothing()
{
}

std::set<std::string> Clothing::keywords() const {
    // Both name and brand get parsed into 2+ character word chunks
    std::set<std::string> nameWords = parseStringToWords(name_);
    std::set<std::string> brandWords = parseStringToWords(brand_);

    // Size is NOT a keyword per the spec
    return setUnion(nameWords, brandWords);
}

std::string Clothing::displayString() const {
    string priceStr = to_string(price_);
    priceStr = priceStr.substr(0, priceStr.find('.') + 3);

    string information = name_ + '\n' + "Size: " + size_ + " Brand: " + brand_ + '\n' + priceStr + " " + to_string(qty_) + " left.";

    return information;
}

void Clothing::dump(std::ostream& os) const {
    // Database format expects Size first, then Brand
    os << category_ << "\n" 
       << name_ << "\n" 
       << price_ << "\n" 
       << qty_ << "\n" 
       << size_ << "\n" 
       << brand_ << endl;
}

std::string Clothing::getSize() const {
    return size_;
}

std::string Clothing::getBrand() const {
    return brand_;
}
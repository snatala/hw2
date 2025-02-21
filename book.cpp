#include "book.h"
#include "util.h"
#include <sstream>
#include <iomanip>

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string author, const std::string isbn) : Product(category, name, price, qty)
{
  author_ = author;
  isbn_ = isbn;
}

Book::~Book()
{

}

std::set<std::string> Book::keywords() const
{
  std::set<std::string> authorSet = parseStringToWords(convToLower(author_));
  std::set<std::string> prodNSet = parseStringToWords(convToLower(name_));
  std::set<std::string> set;
  typename std::set<std::string>::iterator it;

  for(it = authorSet.begin(); it != authorSet.end(); ++it) {
    set.insert(*it);
  }

  for(it=prodNSet.begin(); it!=prodNSet.end(); ++it){
    set.insert(*it);
  }

  set.insert(isbn_);
  return set;
}

std::string Book::displayString() const
{
  std::stringstream ss;
  std::string setPrice;
  ss << std::setprecision(2) << std::fixed << price_;
  ss >> setPrice;

  std::string productDisplay = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + setPrice + " " + std::to_string(qty_) + " left.";

  return productDisplay;

  // ss << name_ << std::endl;
  // ss <<"Author: " << author_ << " ISBN: " << isbn_ << std::endl;
  // ss << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";
  // return ss.str();
}

void Book::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ <<"\n" << author_ << std::endl;
}

std::string Book::getAuthor() const {
  return author_;
}

std::string Book::getISBN() const {
  return isbn_;
}

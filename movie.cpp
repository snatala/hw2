#include "movie.h"
#include "util.h"
#include <sstream>
#include <iomanip>

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) : Product(category, name, price, qty), genre_(genre), rating_(rating)
{

}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const
{
  std::set<std::string> words = parseStringToWords(name_);
  words.insert(convToLower(genre_));
  return words;
}

std::string Movie::displayString() const
{
  std::stringstream ss;
  std::string setPrice;
  ss << std::setprecision(2) << std::fixed << price_;
  ss >> setPrice;

  std::string productDisplay = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + setPrice + " " + std::to_string(qty_) + " left.";

  return productDisplay;
  // std::stringstream ss;
  // ss << name_ << std::endl;
  // ss << "Genre: " << genre_ << " Rating: " << rating_ << std::endl;
  // ss << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";
  // return ss.str();
}

void Movie::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}

std::string Movie::getGenre() const {
  return genre_;
}

std::string Movie::getRating() const {
  return rating_;
}
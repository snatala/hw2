#include "mydatastore.h"
#include "util.h"
#include <algorithm>
#include <iostream>

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{
  std::map<std::string, Product*>::iterator it;
  for(it=productMap.begin(); it!=productMap.end(); ++it){
    delete it ->second;
  }

  std::map<std::string, User*>::iterator it2;
  for(it2=userMap.begin(); it2!=userMap.end(); ++it2){
    delete it2 -> second;
  }
}

void MyDataStore::addProduct(Product* p)
{
  std::set<std::string> keywords = p->keywords();
  
  for(std::set<std::string>::iterator it = keywords.begin(); it!=keywords.end(); ++it){
    key[*it].insert(p);
  }
  productMap[p->getName()] = p;
}

void MyDataStore::addUser(User* u)
{
  userMap[u->getName()] = u;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
  std::set<Product*> up; 

  for(size_t i = 0; i < terms.size(); i++){
    if(type==0){
      if(key.find(terms[i])!=key.end()){
        if(up.empty()) {
          up = key[terms[i]];
        } else {
          up = setIntersection(up, key[terms[i]]);
        }
      }
    }
    if(type==1){
      for(size_t i=0; i<terms.size(); i++){
        if(key.find(terms[i])!=key.end()){
          if(up.empty()){
            up = key[terms[i]];
          } else {
            up = setUnion(up, key[terms[i]]);
          }
        }
      }
    }
  }

  std::vector<Product*> result(up.begin(), up.end());
  return result;
}

void MyDataStore::dump(std::ostream& ofile)
{
  ofile << "<products>" << std::endl;
  std::map<std::string, Product*>::iterator it;
  for(it = productMap.begin(); it != productMap.end(); ++it) {
    it -> second -> dump(ofile);
  }

  ofile <<"</products>"<<std::endl;

  ofile <<"<users>"<<std::endl;
  std::map<std::string, User*>::iterator it2;
  for(it2 = userMap.begin(); it2 != userMap.end(); ++it2){
    it2->second->dump(ofile);
  }
  ofile <<"</users>"<<std::endl;
}

void MyDataStore::viewCart(const std::string& username){
  if(cart.find(username) != cart.end()){
    std::vector<Product*> temp = cart[username];

    for(size_t i=0;i<temp.size(); i++){
      std::cout<<"Item " << i+1<<std::endl;
      std::string s = temp[i]->displayString();
      std::cout << s << std::endl;
    }
  } else {
    std::cout << "Invalid username" << std::endl;
  }
}

void MyDataStore::addToCart(const std::string& username, Product* product)
{
  std::map<std::string, User*>::iterator it = userMap.find(username);

  if(it!=userMap.end()){
    if(product != nullptr)
    {
      cart[username].push_back(product);
      return;
    }
  } else {
    std::cout << "Invalid request" << std::endl;
    return;
  }
}

void MyDataStore::buyCart(std::string& username){
  std::string lowerUsername = convToLower(username);
  std::vector<Product*> current = cart[username];

  std::vector<Product*> unbought_products;

  if(userMap.find(username)!=userMap.end()){
    std::cout << "made it" << std::endl;

    if(current.size()>0) {
      std::cout << ">1 thing" << std::endl;
      for(size_t i=0; i<current.size(); i++){
        Product* product = current[i];
        if(product->getQty()>0 && userMap[username]->getBalance() >= product->getPrice()){
          userMap[username]->deductAmount(product->getPrice());
          product->subtractQty(1);
        }
        else {
          unbought_products.push_back(product);
        }
      }
    }
  }
  else {
    std::cout << "Invalid username" << std::endl;
  }

  current = unbought_products;
  cart[username] = current;
}

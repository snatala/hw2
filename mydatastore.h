#include "datastore.h"
#include "util.h"
#include <map>
#include <set>
#include <queue>
#include <vector>

class MyDataStore : public DataStore {
  public:
    MyDataStore();
    ~MyDataStore();

    virtual void addProduct(Product* p);

    virtual void addUser(User* u);

    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);

    virtual void dump(std::ostream& ofile);

    void viewCart(const std::string& username);

    void addToCart(const std::string& username, Product* product);

    void buyCart(std::string& username);

  private:
    std::map<std::string, std::set<Product*>> key;
    std::map<std::string, User*> userMap;
    std::map<std::string, Product*> productMap;
    std::map<std::string,std::vector<Product*>> cart; 
};
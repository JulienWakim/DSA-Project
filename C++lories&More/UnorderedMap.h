#include <string>
#include <vector>
#include <forward_list>

#ifndef C__LORIES_MORE_UNORDEREDMAP_H
#define C__LORIES_MORE_UNORDEREDMAP_H

using namespace std;

class UnorderedMap {
private:
    int bucketSize;
    double const MAX_LOAD_FACTOR = .8;
    double loadFactor;
    double numOfItems;
    vector<forward_list<pair<string, double>>> bucket;
    int hashFunction(string key);
    void rehash();
public:
    UnorderedMap();
    void insert(string newKey, double newValue);
    double &operator[](string key);
};


#endif //C__LORIES_MORE_UNORDEREDMAP_H

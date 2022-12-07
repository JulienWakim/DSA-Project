
#include "UnorderedMap.h"

UnorderedMap::UnorderedMap(){
    loadFactor = 0;
    numOfItems = 0;
    bucketSize = 1000;
    bucket.resize(1000);
}

void UnorderedMap::insert(string newKey, double newValue){
    int hashValue = hashFunction(newKey);
    int reduced = hashValue % bucketSize;

    if(bucket[reduced].empty()){
        bucket[reduced].push_front(make_pair(newKey, newValue));
        numOfItems++;
    }
    else{
        bool exists = false;
        for (auto it = bucket[reduced].begin(); it != bucket[reduced].end(); ++it) {
            if((*it).first == newKey){
                exists = true;
            }
        }
        if(!exists){
            bucket[reduced].push_front(make_pair(newKey, newValue));
            numOfItems++;
        }
    }

    loadFactor = numOfItems / (double) bucketSize;
    if (loadFactor == MAX_LOAD_FACTOR){
        bucketSize*=2;
        rehash();
    }
}

int UnorderedMap::hashFunction(string key){
    int sum = 0;
    for(int i = 0; i < key.length(); i++){
        sum+= (int) key[i];
    }
    return sum;
}

void UnorderedMap::rehash(){
    int oldBucketSize = bucketSize / 2;
    vector<pair<string, double>> items;
    for(int i = 0; i < oldBucketSize; i++){
        if(!bucket[i].empty()){
            for (auto it = bucket[i].begin(); it != bucket[i].end(); ++it) {
                items.push_back(*it);
            }
            bucket[i].clear();
        }
    }

    bucket.resize(bucketSize);
    numOfItems = 0;
    for(auto item: items){
        insert(item.first, item.second);
    }
}

double &UnorderedMap::operator[](string key){
    int hashValue = hashFunction(key);
    int reduced = hashValue % bucketSize;

    double value;
    if(bucket[reduced].empty()){
        throw "Key Does Not Exist";
    }
    else{
        for (auto it = bucket[reduced].begin(); it != bucket[reduced].end(); ++it) {
            if ((*it).first == key) {
                value = (*it).second;
            }
        }
    }
    return value;
}
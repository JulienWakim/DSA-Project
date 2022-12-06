
//
// Created by csesc_snhoakq on 12/5/2022.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
//FOR TESTING
#include <map>
#include <algorithm>
#include <iomanip>
using namespace std;
#ifndef C__LORIES_MORE_MAP_H
#define C__LORIES_MORE_MAP_H


class Map {
public :
    struct Node{
        Node *left;
        Node *right;
        string description;
        int calories;
    };
private:
    int size;
    Node* root;
    Node* newMapElement(string key, int value);
    void insertKeyValueHelper(Node* current,Node* element);
    double findHelper(string key, Node* current);
public:
    Map();
    Map(string key, int value);
    void insertKeyValue(string key, int value);
    double &operator[](string key);
    bool isEmpty();
};


#endif //C__LORIES_MORE_MAP_H



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
public : struct Node{
    public:
        Node *left;
        Node *right;
        string description;
        double calories;
    };
private:
    int size;
    Node* root;

public:
    Map();
    Map(string key, int value);
    void insert(string key, int value);
    Node* newMapElement(string key, int value);
    void insertKeyValueHelper(Node* current,Node* element);
    double findValue(string key);
    double findHelper(string key, Node* current);
    bool isEmpty();
};


#endif //C__LORIES_MORE_MAP_H


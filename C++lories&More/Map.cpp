
//
// Created by csesc_snhoakq on 12/5/2022.
//

#include "Map.h"

Map::Map(string key, int value) {
    root -> description = key;
    root -> calories = value;
    root -> left = nullptr;
    root -> right = nullptr;
    size = 1;
}

Map::Map() {
    root = nullptr;
    size = 0;
}

void Map::insertKeyValue(string key, int value) {
    Node* element = newMapElement(key,value);
    Node* current = root;

    if (element -> description > current -> description){
        if (current -> right != nullptr) {
            insertKeyValueHelper(current, element);
        }
        else {
            current -> right = element;
        }
    }
    else if (element -> description < current -> description){
        if (current -> left != nullptr) {
            insertKeyValueHelper(current, element);
        }
        else {
            current -> left = element;
        }
    }
    else if (element -> description == current -> description){
        cout << element -> description << " with " << element -> calories << " calories already in map" << endl;
    }


}

Map::Node *Map::newMapElement(string key, int value) {
    Node* temp = new Node;
    temp -> left = nullptr;
    temp -> right = nullptr;
    temp ->description = key;
    temp -> calories = value;
    size++;
    return temp;
}

void Map::insertKeyValueHelper(Node* current,Node* element) {
    if (element -> description > current -> description){
        if (current -> right != nullptr) {
            insertKeyValueHelper(current, element);
        }
        else {
            current -> right = element;
        }
    }
    else if (element -> description < current -> description){
        if (current -> left != nullptr) {
            insertKeyValueHelper(current, element);
        }
        else {
            current -> left = element;
        }
    }
    else if (element -> description == current -> description){
        cout << element -> description << " with " << element -> calories << " calories already in map" << endl;
    }
}

bool Map::isEmpty() {
    if (size == 0){
        return true;
    }
    return false;
}

double Map::findHelper(string key, Node* current) {
    double value = -1;
    if (key < current -> description){
        if (current ->left != nullptr){
            value = findHelper(key,current->left);
        }
        else{
            throw "Key Does Not Exist";
        }
    }
    else if (key > current -> description){
        if (current ->right != nullptr){
            value = findHelper(key,current->right);
        }
        else{
            throw "Key Does Not Exist";
        }
    }
    else if (key == current -> description){
        value = current -> calories;
    }
    return value;
}

double &Map::operator[](string key) {
    Node* current = root;
    double value = -1;
    if (key < current -> description){
        if (current ->left != nullptr){
            value = findHelper(key,current->left);
        }
        else{
            throw "Key Does Not Exist";
        }
    }
    else if (key > current -> description){
        if (current ->right != nullptr){
            value = findHelper(key,current->right);
        }
        else{
            throw "Key Does Not Exist";
        }
    }
    else if (key == current -> description){
        value = current -> calories;
    }
    return value;
}

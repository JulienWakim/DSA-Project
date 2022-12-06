
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

void Map::insert(string key, int value) {
    Node *element = newMapElement(key, value);
    if (root == nullptr) {
        root = element;
        return;
    }
    Node *current = root;

    insertKeyValueHelper(current, element);
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
            insertKeyValueHelper(current->right, element);
        }
        else {
            current -> right = element;
        }
    }
    else if (element -> description < current -> description){
        if (current -> left != nullptr) {
            insertKeyValueHelper(current->left, element);
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
    double value = -1.0;
    while (current != nullptr){
        if (key == current -> description){
            value = current ->calories;
            break;
        }
        else if (key < current -> description){
            current = current -> left;
        }
        else if (key > current -> description){
            current = current -> right;
        }
    }
    if (value == -1.0) {
        cout << "Key Does Not Exist" << endl;
    }
    return value;
}

double Map::findValue(string key) {
    Node* current = root;
    return findHelper(key,current);
}

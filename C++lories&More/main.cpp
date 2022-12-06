#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
//FOR TESTING
#include <map>
#include "UnorderedMap.h"
using namespace std;

string checkForQuotes(istringstream& stream, string word);

int main() {
    ifstream myfile ("nndb_flat.csv");
    string line, word;

    getline(myfile, line); //HEADER LINE
    map<string, double> test; //FOR TESTING PURPOSES
    UnorderedMap unordered;
    while (getline(myfile, line)) {
        istringstream stream(line);
        string id = checkForQuotes(stream, word); //ID
        checkForQuotes(stream, word); //FOOD GROUP
        checkForQuotes(stream, word); //SHORT DESCRIPTION
        string description = checkForQuotes(stream, word); //DESCRIPTION
        transform(description.begin(), description.end(), description.begin(), ::tolower);  //PUTS DESCRIPTION IN LOWERCASE
        checkForQuotes(stream, word); //COMMON NAME
        checkForQuotes(stream, word); //COMPANY NAME
        checkForQuotes(stream, word); //SCIENTIFIC NAME
        string calories = checkForQuotes(stream, word); //CALORIES (FOR 100 GRAMS)
        double cal = stod(calories);
        test[description] = cal;
        unordered.insert(description, cal);
    }

    cout << test["butter, salted"];
    cout << unordered["butter, salted"];
    return 0;
}


string checkForQuotes(istringstream& stream, string word){
    if (stream.peek() == '"') {
        stream >> quoted(word);
        string discard;
        getline(stream, discard, ',');
    }
    else {
        getline(stream, word, ',');
    }
    return word;
}

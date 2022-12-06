#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map> //FOR TESTING
#include "Map.h"
#include "UnorderedMap.h"
using namespace std;

string checkForQuotes(istringstream& stream, string word);
void toVector(string line, vector<string>& list);
double calculateAMR(bool man, double weight, double height, int age, int activityLevel);

int main() {
    //READS IN DATA FROM DATASET
    ifstream myfile ("nndb_flat.csv");
    if (myfile.is_open()){
        cout << "file open" << endl;
    }
    else{
        cout << "file not open" << endl;
    }

    string line, word;
    getline(myfile, line); //HEADER LINE

    map<string, double> test; //FOR TESTING PURPOSES
    UnorderedMap unordered;
    Map ordered;

    //ADDS FOOD DESCRIPTION AND CALORIE INTO MAPS
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
        ordered.insert(description,cal);

    }
    cout << "mollusks, snail, raw: " << ordered.findValue("mollusks, snail, raw") << endl;
    cout << "millet, puffed: " << ordered.findValue("millet, puffed") << endl;


    bool prepped = false;
    bool restrict = false;
    bool activity = false;
    bool healthInfo = false;
    vector<string> dietaryRestrict;
    vector<vector<string>> breakfastMeals = { {"Cloud Eggs", "Eggs, scrambled, frozen mixture", "Cheese, parmesan, grated", "Basil, fresh", "Tomatoes, red, ripe, cooked, with salt"},
    {"Ham and Swiss Omlet", "Cheese, swiss", "OSCAR MAYER, Ham (water added, baked cooked 96% fat free)", "Eggs, scrambled, frozen mixture", "Butter, salted"},
    {"Fruity Waffle Parfait", "KELLOGG'S, EGGO, NUTRI-GRAIN, Waffles, Low Fat", "Nuts, almond butter, plain, without salt added", "Yogurt, fruit variety, nonfat, fortified with vitamin D", "Snacks, banana chips", "Syrup, maple, Canadian"},
    {"Waffle Sandwich", "Eggs, scrambled, frozen mixture", "KELLOGG'S, EGGO, NUTRI-GRAIN, Waffles, Low Fat", "Canadian bacon, unprepared", "Cheese, parmesan, grated", "Syrup, maple, Canadian"},
    {"Applesauce Pancakes", "Pancakes, plain, dry mix, complete (includes buttermilk)", "Babyfood, fruit, applesauce, strained", "Syrup, maple, Canadian"},
    {"Yogurt Fruit Cup", "Tangerines, (mandarin oranges), raw", "Nuts, almond butter, plain, without salt added", "Yogurt, fruit variety, nonfat, fortified with vitamin D"},
    {"Sausage Omlet", "Eggs, scrambled, frozen mixture", "Sausage, Italian, pork, raw", "Dip, TOSTITOS, salsa con queso, medium"},
    {"Sausage Hashbrowns", "Oil, corn and canola", "Sausage, Italian, pork, raw", "Potatoes, canned, drained solids, no salt added", "Cheese, pasteurized process, cheddar or American, low sodium"} };

    vector<vector<string>> lunchMeals = {{"McDonald's McChicken", "McDONALD'S, McCHICKEN Sandwich", "McDONALD'S, Sweet 'N Sour Sauce"},
    {"McDonald's Chicken Nuggets", "McDONALD'S, Chicken McNUGGETS", "McDONALD'S, Barbeque Sauce"},
    {"Quick Lunch Meal", "CAMPBELL'S CHUNKY Microwavable Bowls, Old Fashioned Vegetable Beef Soup, ready-to-serve"},
    {"Quick Microwave Meal", "CAMPBELL'S CHUNKY Microwavable Bowls, Sirloin Burger with Country Vegetables Soup, ready-to-serve"},
    {"Avocado Toast", "Bread, Multi-Grain, toasted (includes whole-grain)", "Eggs, scrambled, frozen mixture", "Avocados, raw, California"},
    {"Mediterranean pasta", "Pasta, corn, dry", "Fish, salmon, coho (silver), raw (Alaska Native)", "Capers, canned"},
    {"Simple salmon quinoa", "Quinoa, uncooked", "Fish, salmon, coho (silver), raw (Alaska Native)", "Tomatoes, red, ripe, cooked, with salt"},
    {"Mini Healthy Pizza", "Cheese, ricotta, whole milk", "English muffins, plain, enriched, with ca prop (includes sourdough)", "Tomatoes, red, ripe, cooked, with salt"}};

    vector<vector<string>> dinnerMeals = {{"Chicken and Veggies", "Vegetables, mixed (corn, lima beans, peas, green beans, carrots) canned, no salt added", "Tomatoes, red, ripe, cooked, with salt", "Chicken, broilers or fryers, thigh, meat and skin, raw"},
    {"Pasta with Parmesan", "Sauce, pasta, spaghetti/marinara, ready-to-serve, low sodium", "Cheese, parmesan, grated"},
    {"Spaghetti Carbonara", "Sauce, pasta, spaghetti/marinara, ready-to-serve, low sodium", "Cheese, parmesan, grated", "Eggs, scrambled, frozen mixture"},
    {"Chicken and Fruit Salad", "Chicken breast tenders, breaded, cooked, microwaved", "Fruit salad, (peach and pear and apricot and pineapple and cherry), canned, water pack, solids and liquids"},
    {"Colorful Pasta Salad", "Arugula, raw", "Pasta, fresh-refrigerated, plain, cooked", "PREGO Pasta, Heart Smart- Roasted Red Pepper and Garlic Italian Sauce, ready-to-serve"},
    {"Balsamic Glazed Salmon", "Fish, salmon, coho (silver), raw (Alaska Native)", "Vinegar, balsamic"},
    {"Marinara Chicken Pasta", "Chicken breast tenders, breaded, cooked, microwaved", "Sauce, pasta, spaghetti/marinara, ready-to-serve, low sodium"},
    {"Breakfast for Dinner", "Pork, cured, bacon, cooked, microwaved", "Eggs, scrambled, frozen mixture", "KELLOGG'S, EGGO, NUTRI-GRAIN, Waffles, Low Fat"}};
    
    //Initializing health factors for default meal prep
    int activityLevel = 3;
    bool male;
    double weight = 150;
    double height = 65;
    int age = 20;
    bool lose = true;

    double maxCalories;
    double bfastCals;
    double lunchCals;
    double dinnerCals;

    cout << "--------------C++lories&More--------------\n";
    cout << "\t\t~Meal Prepping Made Easy~\n\n";
    while(!prepped) {
        cout << "Please Enter Menu Option:\n";
        cout << "1. Dietary Restrictions\n";
        cout << "2. Activity Level\n";
        cout << "3. Health Information\n";
        cout << "4. Curate Meal Plan\n";
        cout << "5. Quit\n";
        int option;
        cin >> option;

        string input;
        switch(option){
            case 1:
                cout << "\n\t\t~Dietary Restrictions~\n";
                if(restrict){
                    cout << "Dietary restrictions already entered!\nDo you want to change the information? (Y/N)\n";
                    cin >> input;
                }
                else{
                    input = "Y";
                }
                if(input == "Y") {
                    dietaryRestrict.clear();
                    cout << "Do you have any dietary restrictions? (Y/N)\n";
                    cin >> input;
                    if (input == "Y") {
                        cout << "Please list restrictions (each ingredient should be followed by a ','): \n";
                        cin >> input;
                        cout << "Adding information to algorithm...\n\n";
                        toVector(input, dietaryRestrict);
                    } else if (input == "N") {
                        dietaryRestrict.clear();
                        cout << "Adding information to algorithm...\n\n";
                    }
                    restrict = true;
                }
                else{
                    cout << "\n";
                }
                break;
            case 2:
                cout << "\n\t\t~Activity Level~\n";
                if(activity){
                    cout << "Activity level already entered!\nDo you want to change the information? (Y/N)\n";
                    cin >> input;
                }
                else{
                    input = "Y";
                }
                if(input == "Y") {
                    cout << "On a scale of 1-5, how active are you? \n(1 being not active and 5 being very active)\n";
                    cin >> activityLevel;
                    cout << "Adding information to algorithm...\n\n";
                    activity = true;
                }
                else{
                    cout << "\n";
                }
                break;
            case 3:
                cout << "\n\t\t~Health Information~\n";
                if(healthInfo){
                    cout << "Health information already entered!\nDo you want to change the information? (Y/N)\n";
                    cin >> input;
                }
                else{
                    input = "Y";
                }
                if(input == "Y") {
                    cout << "Are you a man or woman?\n";
                    cin >> input;
                    if (input == "man") {
                        male = true;
                    } else {
                        male = false;
                    }
                    cout << "How much do you currently weigh (in pounds)?\n";
                    cin >> weight;

                    cout << "What is your current height (in inches)?\n";
                    cin >> height;

                    cout << "What is your age?\n";
                    cin >> age;

                    cout << "Do you want to lose or gain weight?\n";
                    cin >> input;
                    if (input == "lose") {
                        lose = true;
                    } else {
                        lose = false;
                    }

                    cout << "Adding information to algorithm...\n\n";
                    healthInfo = true;
                }
                else{
                    cout << "\n";
                }
                break;
            case 4:
                cout << "\n\t\t~Meal Plan~\n";
                if(!restrict || !activity || !healthInfo){
                    cout << "You have not inputted all your information!\n"
                            "It is suggested to have all fields filled out in order to produce the best personal meal plan!\n"
                            "Are you sure you want to continue? (Y/N)\n";
                    cin >> input;
                    if(input == "Y"){
                        maxCalories = calculateAMR(male, weight, height, age, activityLevel);
                        if(lose){
                            maxCalories-= 350;
                        }
                        else{
                            maxCalories+= 350;
                        }
                        bfastCals = maxCalories * .2;
                        lunchCals = maxCalories * .4;
                        dinnerCals = maxCalories * .4;

                    }
                    else{
                        cout << "\n";
                    }
                    prepped = true;
                }

                break;
            case 5:
                prepped = true;
        }
    }
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

void toVector(string line, vector<string>& list) {
    stringstream ss(line);
    while (ss.good()) {
        string ingredient;
        getline(ss, ingredient, ',');
        transform(ingredient.begin(), ingredient.end(), ingredient.begin(), ::tolower);  //PUTS INGREDIENT IN LOWERCASE
        list.push_back(ingredient);
    }
}

double calculateAMR(bool man, double weight, double height, int age, int activityLevel){
    weight = weight / 2.2;
    height = height * 2.54;
    double BMR, AMR;
    if(man){
        BMR = 66.47 + (13.75 * weight) + (5.003 * height) - (6.755 * age);
    }
    else{
        BMR = 655.1 + (9.563 * weight) + (1.850 * height) - (4.676 * age);
    }
    switch (activityLevel) {
        case 1:
            AMR = BMR * 1.2;
            break;
        case 2:
            AMR = BMR * 1.375;
            break;
        case 3:
            AMR = BMR * 1.55;
            break;
        case 4:
            AMR = BMR * 1.725;
            break;
        case 5:
            AMR = BMR * 1.9;
            break;
    }
    return AMR;
}

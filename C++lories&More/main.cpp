#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Map.h"
#include "UnorderedMap.h"
using namespace std;

string checkForQuotes(istringstream& stream, string word);
void toVector(string line, vector<string>& list);
double calculateAMR(bool man, double weight, double height, int age, int activityLevel);
double curatePlanUnordered(double maxCals, vector<string>& restrictions, vector<vector<string>>& mealDatabase, UnorderedMap& unorderedNutrition);
double curatePlanOrdered(double maxCals, vector<string>& restrictions, vector<vector<string>>& mealDatabase, Map& orderedNutrition);

int main() {
    //READS IN DATA FROM DATASET
    ifstream myfile ("nndb_flat.csv");

    string line, word;
    getline(myfile, line); //HEADER LINE

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
        unordered.insert(description, cal);
        ordered.insert(description,cal);

    }

    bool prepped = false;
    bool restrict = false;
    bool activity = false;
    bool healthInfo = false;
    vector<string> dietaryRestrict;
    vector<vector<string>> breakfastMeals = {{"Cloud Eggs", "eggs, scrambled, frozen mixture", "cheese, parmesan, grated", "basil, fresh", "tomatoes, red, ripe, cooked, with salt"},
    {"Ham and Swiss Omelet", "cheese, swiss", "oscar mayer, ham (water added, baked cooked 96% fat free)", "eggs, scrambled, frozen mixture", "butter, salted"},
    {"Fruity Waffle Parfait", "kellogg's, eggo, nutri-grain, waffles, low fat", "nuts, almond butter, plain, without salt added", "yogurt, fruit variety, nonfat, fortified with vitamin d", "snacks, banana chips", "syrup, maple, canadian"},
    {"Waffle Egg Sandwich", "eggs, scrambled, frozen mixture", "kellogg's, eggo, nutri-grain, waffles, low fat", "canadian bacon, unprepared", "cheese, parmesan, grated", "syrup, maple, canadian"},
    {"Applesauce Pancakes", "pancakes, plain, dry mix, complete (includes buttermilk)", "babyfood, fruit, applesauce, strained", "syrup, maple, canadian"},
    {"Yogurt Fruit Cup", "tangerines, (mandarin oranges), raw", "nuts, almond butter, plain, without salt added", "yogurt, fruit variety, nonfat, fortified with vitamin d"},
    {"Sausage Omelet", "eggs, scrambled, frozen mixture", "sausage, italian, pork, raw", "dip, tostitos, salsa con queso, medium"},
    {"Sausage Hash-browns", "oil, corn and canola", "sausage, italian, pork, raw", "potatoes, canned, drained solids, no salt added", "cheese, pasteurized process, cheddar or american, low sodium"} };

    vector<vector<string>> lunchMeals = {{"McDonald's McChicken", "mcdonald's, mcchicken sandwich", "mcdonald's, sweet 'n sour sauce"},
    {"McDonald's Chicken Nuggets", "mcdonald's, chicken mcnuggets", "mcdonald's, barbeque sauce"},
    {"Quick Lunch Meal", "campbell's chunky microwavable bowls, old fashioned vegetable beef soup, ready-to-serve"},
    {"Quick Microwave Meal", "campbell's chunky microwavable bowls, sirloin burger with country vegetables soup, ready-to-serve"},
    {"Avocado Toast with Eggs", "bread, multi-grain, toasted (includes whole-grain)", "eggs, scrambled, frozen mixture", "avocados, raw, california"},
    {"Mediterranean pasta", "pasta, corn, dry", "fish, salmon, coho (silver), raw (alaska native)", "capers, canned"},
    {"Simple salmon quinoa", "quinoa, uncooked", "fish, salmon, coho (silver), raw (alaska Native)", "tomatoes, red, ripe, cooked, with salt"},
    {"Mini Healthy Pizza", "cheese, ricotta, whole milk", "english muffins, plain, enriched, with ca prop (includes sourdough)", "tomatoes, red, ripe, cooked, with salt"}};

    vector<vector<string>> dinnerMeals = {{"Chicken and Veggies", "vegetables, mixed (corn, lima beans, peas, green beans, carrots) canned, no salt added", "tomatoes, red, ripe, cooked, with salt", "chicken, broilers or fryers, thigh, meat and skin, raw"},
    {"Pasta with Parmesan", "sauce, pasta, spaghetti/marinara, ready-to-serve, low sodium", "cheese, parmesan, grated"},
    {"Spaghetti Carbonara", "sauce, pasta, spaghetti/marinara, ready-to-serve, low sodium", "cheese, parmesan, grated", "eggs, scrambled, frozen mixture"},
    {"Chicken and Fruit Salad", "chicken breast tenders, breaded, cooked, microwaved", "fruit salad, (peach and pear and apricot and pineapple and cherry), canned, water pack, solids and liquids"},
    {"Colorful Pasta Salad", "arugula, raw", "pasta, fresh-refrigerated, plain, cooked", "prego pasta, heart smart- roasted red pepper and garlic italian sauce, ready-to-serve"},
    {"Balsamic Glazed Salmon", "fish, salmon, coho (silver), raw (alaska native)", "vinegar, balsamic"},
    {"Marinara Chicken Pasta", "chicken breast tenders, breaded, cooked, microwaved", "sauce, pasta, spaghetti/marinara, ready-to-serve, low sodium"},
    {"Breakfast for Dinner", "pork, cured, bacon, cooked, microwaved", "eggs, scrambled, frozen mixture", "kellogg's, eggOo, nutri-grain, waffles, low fat"}};
    
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
        switch(option) {
            case 1:
                cout << "\n\t\t~Dietary Restrictions~\n";
                if (restrict) {
                    cout << "Dietary restrictions already entered!\nDo you want to change the information? (Y/N)\n";
                    cin >> input;
                } else {
                    input = "Y";
                }
                if (input == "Y") {
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
                } else {
                    cout << "\n";
                }
                break;
            case 2:
                cout << "\n\t\t~Activity Level~\n";
                if (activity) {
                    cout << "Activity level already entered!\nDo you want to change the information? (Y/N)\n";
                    cin >> input;
                } else {
                    input = "Y";
                }
                if (input == "Y") {
                    cout << "On a scale of 1-5, how active are you? \n(1 being not active and 5 being very active)\n";
                    cin >> activityLevel;
                    cout << "Adding information to algorithm...\n\n";
                    activity = true;
                } else {
                    cout << "\n";
                }
                break;
            case 3:
                cout << "\n\t\t~Health Information~\n";
                if (healthInfo) {
                    cout << "Health information already entered!\nDo you want to change the information? (Y/N)\n";
                    cin >> input;
                } else {
                    input = "Y";
                }
                if (input == "Y") {
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
                } else {
                    cout << "\n";
                }
                break;
            case 4:
                cout << "\n\t\t~Meal Plan~\n";
                if (!restrict || !activity || !healthInfo) {
                    cout << "You have not inputted all your information!\n"
                            "It is suggested to have all fields filled out in order to produce the best personal meal plan!\n"
                            "Are you sure you want to continue? (Y/N)\n";
                    cin >> input;
                } else {
                    input = "Y";
                }
                if (input == "Y") {
                    maxCalories = calculateAMR(male, weight, height, age, activityLevel);
                    if (lose) {
                        maxCalories -= 500;
                        cout << "\nIn order to lose weight, you should eat around " << maxCalories << " calories a day!\n";
                    } else {
                        maxCalories += 500;
                        cout << "\nIn order to gain weight, you should eat around " << maxCalories << " calories a day!\n";
                    }
                    bfastCals = maxCalories * .2;
                    lunchCals = maxCalories * .4;
                    dinnerCals = maxCalories * .4;

                    for(int i = 0; i < 7; i++){
                        double cal = 0;
                        switch(i){
                            case 0:
                                cout << "\t\t\t~Monday~\n";
                                break;
                            case 1:
                                cout << "\n\n\t\t\t~Tuesday~\n";
                                break;
                            case 2:
                                cout << "\n\n\t\t\t~Wednesday~\n";
                                break;
                            case 3:
                                cout << "\n\n\t\t\t~Thursday~\n";
                                break;
                            case 4:
                                cout << "\n\n\t\t\t~Friday~\n";
                                break;
                            case 5:
                                cout << "\n\n\t\t\t~Saturday~\n";
                                break;
                            case 6:
                                cout << "\n\n\t\t\t~Sunday~\n";
                                break;
                        }
                        cout << "Breakfast: \t";
                        cal = curatePlanUnordered(bfastCals, dietaryRestrict, breakfastMeals, unordered);
                        cout << "\nLunch: \t\t";
                        cal += curatePlanUnordered(lunchCals, dietaryRestrict, lunchMeals, unordered);
                        cout << "\nDinner: \t";
                        cal += curatePlanUnordered(dinnerCals, dietaryRestrict, dinnerMeals, unordered);
                        cout << "\nTotal Calories for the Day: " << cal;
                    }

                    prepped = true;
                } else {
                    cout << "\n";
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

double curatePlanUnordered(double maxCals, vector<string>& restrictions, vector<vector<string>>& mealDatabase, UnorderedMap& unorderedNutrition){
    double calories;
    for(int j = 0; j < mealDatabase.size(); j++){
        bool valid = true;
        calories = 0;
        for(int i = 1; i < mealDatabase[j].size(); i++){
            //Check to see if meal has a dietary restriction in it
            for(string restrict: restrictions){
                if(mealDatabase[j][i].find(restrict) != -1){
                    valid = false;
                }
            }
            //Calculate calorie count of ingredients
            calories += unorderedNutrition[mealDatabase[j][i]];
        }
        if(calories > maxCals){
            valid = false;
        }
        if(valid){
            cout << left << setw(30) << mealDatabase[j][0] << right << setw(30) << "Calories: " << calories;
            mealDatabase.erase(mealDatabase.begin()+j);
            break;
        }
    }
    return calories;
}


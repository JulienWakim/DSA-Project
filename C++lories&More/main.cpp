#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <random>
#include "Map.h"
#include "UnorderedMap.h"
using namespace std;
using namespace std::chrono;

string checkForQuotes(istringstream& stream, string word);
void toVector(string line, vector<string>& list);
double calculateAMR(bool man, double weight, double height, int age, int activityLevel);
double curatePlanUnordered(double maxCals, vector<string>& restrictions, vector<vector<pair<string, double>>>& mealDatabase, UnorderedMap& unorderedNutrition);

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

    //Placeholder variables for keeping track of restrictions
    bool prepped = false;
    bool restrict = false;
    bool activity = false;
    bool healthInfo = false;
    vector<string> dietaryRestrict;


    //Each meal name as the head of each inner vector for breakfast meals
    vector<vector<pair<string, double>>> breakfastMeals = {{make_pair("Cloud Eggs with Toast", 0), make_pair("bread, multi-grain, toasted (includes whole-grain)", 150), make_pair("eggs, scrambled, frozen mixture", 100), make_pair("basil, fresh", 5), make_pair("tomatoes, red, ripe, cooked, with salt", 40)},
    {make_pair("Ham and Swiss Omelet", 0), make_pair("cheese, swiss", 50), make_pair("oscar mayer, ham (water added, baked cooked 96% fat free)", 40), make_pair("eggs, scrambled, frozen mixture", 150), make_pair("butter, salted", 100)},
    {make_pair("Oatmeal and Peanut Butter", 0), make_pair("cereals, quaker, weight control instant oatmeal, maple and brown sugar", 100), make_pair("peanut butter, chunk style, with salt", 30)},
    {make_pair("Fruity Waffle Parfait", 0), make_pair("kellogg's, eggo, nutri-grain, waffles, low fat", 70), make_pair("nuts, almond butter, plain, without salt added", 23), make_pair("yogurt, fruit variety, nonfat, fortified with vitamin d", 50), make_pair("syrup, maple, canadian", 10)},
    {make_pair("Waffle Egg Sandwich", 0), make_pair("eggs, scrambled, frozen mixture", 100), make_pair("kellogg's, eggo, nutri-grain, waffles, low fat", 70), make_pair("canadian bacon, unprepared", 100), make_pair("cheese, parmesan, grated", 50), make_pair("syrup, maple, canadian", 50)},
    {make_pair("Applesauce Pancakes", 0), make_pair("pancakes, plain, dry mix, complete (includes buttermilk)", 200), make_pair("babyfood, fruit, applesauce, strained", 100), make_pair("syrup, maple, canadian", 10)},
    {make_pair("Yogurt Fruit Cup", 0), make_pair("tangerines, (mandarin oranges), raw", 50), make_pair("nuts, almond butter, plain, without salt added", 23), make_pair("yogurt, fruit variety, nonfat, fortified with vitamin d", 120)},
    {make_pair("Sausage Omelet", 0), make_pair("eggs, scrambled, frozen mixture", 120), make_pair("sausage, italian, pork, raw", 100), make_pair("dip, tostitos, salsa con queso, medium", 100)},
    {make_pair("Sausage Hash-browns", 0), make_pair("sausage, italian, pork, raw", 80), make_pair("potatoes, canned, drained solids, no salt added", 50), make_pair("cheese, pasteurized process, cheddar or american, low sodium", 20)},
    {make_pair("Pepper, Tomato & Ham Omelette", 0), make_pair("eggs, scrambled, frozen mixture", 150), make_pair("oscar mayer, ham (water added, baked cooked 96% fat free)", 200), make_pair("tomatoes, red, ripe, cooked, with salt", 120)},
    {make_pair("Avocado Toast with Eggs", 0), make_pair("bread, multi-grain, toasted (includes whole-grain)", 100), make_pair("eggs, scrambled, frozen mixture", 100), make_pair("avocados, raw, california", 100)},
    {make_pair("Anabolic French Toast", 0), make_pair("french toast, prepared from recipe, made with low fat (2%) milk", 380)},
    {make_pair("Honey-Bunches of Oats with Milk", 0), make_pair("cereals ready-to-eat, post, honey bunches of oats, with almonds", 100), make_pair("milk, fluid, nonfat, calcium fortified (fat free or skim)", 300)},
    {make_pair("Breakfast Taco", 0), make_pair("fast foods, taco with chicken, lettuce and cheese, soft", 400), make_pair("eggs, scrambled, frozen mixture", 200)},
    {make_pair("Breakfast Granola Bar and Fruit", 0), make_pair("breakfast bars, oats, sugar, raisins, coconut (include granola bar)", 130), make_pair("usda commodity, mixed fruit (peaches, pears, grapes), canned, light syrup, drained", 300)},
    {make_pair("Chocolate Protein Shake with Yogurt", 0), make_pair("protein supplement, milk based, muscle milk, powder", 80), make_pair("milk, fluid, nonfat, calcium fortified (fat free or skim)", 200), make_pair("yogurt, vanilla flavor, lowfat milk, sweetened with low calorie sweetener", 130)},
    {make_pair("Egg, Bacon, and Potatoes Plate", 0), make_pair("eggs, scrambled, frozen mixture", 100), make_pair("turkey bacon, unprepared", 40), make_pair("potatoes, canned, drained solids, no salt added", 40)}};

    //Each meal name as the head of each inner vector for lunch meals
    vector<vector<pair<string, double>>> lunchMeals = {{make_pair("McDonald's McChicken with Small Fries", 0), make_pair("restaurant, family style, french fries", 60), make_pair("mcdonald's, mcchicken sandwich", 140), make_pair("mcdonald's, sweet 'n sour sauce", 15)},
    {make_pair("Veggie Soup with Ham and Cheese", 0), make_pair("bread, multi-grain, toasted (includes whole-grain)", 100), make_pair("oscar mayer, ham (water added, baked cooked 96% fat free)", 80), make_pair("cheese, swiss", 40), make_pair("campbell's chunky microwavable bowls, old fashioned vegetable beef soup, ready-to-serve", 150)},
    {make_pair("Meat and Veggie Chilli", 0), make_pair("campbell's chunky microwavable bowls, sirloin burger with country vegetables soup, ready-to-serve", 700)},
    {make_pair("Buffalo Chicken Wraps", 0), make_pair("chicken breast tenders, breaded, cooked, microwaved", 100), make_pair("tortillas, ready-to-bake or -fry, flour, refrigerated", 30), make_pair("mcdonald's, spicy buffalo sauce", 50)},
    {make_pair("Mediterranean pasta", 0), make_pair("pasta, corn, dry", 240), make_pair("fish, salmon, coho (silver), raw (alaska native)", 80), make_pair("capers, canned", 50)},
    {make_pair("Simple salmon quinoa", 0), make_pair("quinoa, uncooked", 60), make_pair("fish, salmon, coho (silver), raw (alaska Native)", 80), make_pair("tomatoes, red, ripe, cooked, with salt", 50)},
    {make_pair("Ground Beef Tacos", 0), make_pair("restaurant, mexican, soft taco with ground beef, cheese and lettuce", 400)},
    {make_pair("Chicken & Cheese Quesadila", 0), make_pair("on the border, cheese quesadilla", 200), make_pair("chicken breast tenders, breaded, cooked, microwaved", 100)},
    {make_pair("McDonald's Chicken Nuggets with Small Fries", 0), make_pair("restaurant, family style, french fries", 65), make_pair("mcdonald's, chicken mcnuggets", 180), make_pair("mcdonald's, barbeque sauce", 10)},
    {make_pair("California Burrito", 0), make_pair("fast foods, burrito, with beans, cheese, and chili peppers", 230), make_pair("cheese, mozzarella, nonfat", 60), make_pair("avocados, raw, california", 140)},
    {make_pair("Homemade Cheeseburger", 0), make_pair("fast foods, cheeseburger; double, regular patty, with condiments and vegetables", 300)},
    {make_pair("Italian Sub", 0), make_pair("fast foods, submarine sandwich, cold cut on white bread with lettuce and tomato", 400)},
    {make_pair("Fish & Chips", 0), make_pair("restaurant, family style, fish fillet, battered or breaded, fried", 200), make_pair("restaurant, family style, french fries", 75)},
    {make_pair("Caesar Salad with Chicken", 0), make_pair("salad dressing, caesar, fat-free", 120), make_pair("fast foods, salad, vegetable, tossed, without dressing, with chicken", 500)},
    {make_pair("Mini Healthy Pizza", 0), make_pair("cheese, ricotta, whole milk", 50), make_pair("english muffins, plain, enriched, with ca prop (includes sourdough)", 50), make_pair("tomatoes, red, ripe, cooked, with salt", 100)}};

    //Each meal name as the head of each inner vector for dinner meals
    vector<vector<pair<string, double>>> dinnerMeals = {{make_pair("Chicken and Veggies", 0), make_pair("vegetables, mixed (corn, lima beans, peas, green beans, carrots) canned, no salt added", 170), make_pair("tomatoes, red, ripe, cooked, with salt", 80), make_pair("chicken, broilers or fryers, thigh, meat and skin, raw", 260)},
    {make_pair("Pasta with Parmesan", 0), make_pair("sauce, pasta, spaghetti/marinara, ready-to-serve, low sodium", 340), make_pair("cheese, parmesan, grated", 30)},
    {make_pair("Spaghetti Carbonara", 0), make_pair("sauce, pasta, spaghetti/marinara, ready-to-serve, low sodium", 600), make_pair("cheese, parmesan, grated", 50), make_pair("eggs, scrambled, frozen mixture", 100)},
    {make_pair("Chicken and Fruit Salad", 0), make_pair("chicken breast tenders, breaded, cooked, microwaved", 180), make_pair("fruit salad, (peach and pear and apricot and pineapple and cherry), canned, water pack, solids and liquids", 150)},
    {make_pair("Colorful Pasta Salad", 0), make_pair("arugula, raw", 100), make_pair("pasta, fresh-refrigerated, plain, cooked", 1500), make_pair("prego pasta, heart smart- roasted red pepper and garlic italian sauce, ready-to-serve", 150)},
    {make_pair("Balsamic Glazed Salmon with Rice", 0), make_pair("fish, salmon, coho (silver), raw (alaska native)", 200), make_pair("vinegar, balsamic", 100), make_pair("Rice, white, short-grain, raw, unenriched", 150)},
    {make_pair("Marinara Chicken Pasta", 0), make_pair("chicken breast tenders, breaded, cooked, microwaved", 260), make_pair("sauce, pasta, spaghetti/marinara, ready-to-serve, low sodium", 350)},
    {make_pair("Meat Lasagna", 0), make_pair("lasagna with meat & sauce, low-fat, frozen entree", 750)},
    {make_pair("Meat and Cheese-Filled Ravioli", 0), make_pair("ravioli, meat-filled, with tomato sauce or meat sauce, canned", 650)},
    {make_pair("Chicken and Rice Bowl", 0), make_pair("rice bowl with chicken, frozen entree, prepared (includes fried, teriyaki, and sweet and sour varieties)", 400)},
    {make_pair("Meat-Lovers' Pizza", 0), make_pair("pizza, meat and vegetable topping, rising crust, frozen, cooked", 300)},
    {make_pair("Pulled Pork with Mashed Potatoes", 0), make_pair("pulled pork in barbecue sauce", 250), make_pair("potatoes, mashed, home-prepared, whole milk and margarine added", 230)},
    {make_pair("Teriyaki Salmon with Fried Rice", 0), make_pair("fish, salmon, atlantic, wild, raw", 300), make_pair("restaurant, chinese, fried rice, without meat", 300)},
    {make_pair("Buffalo Wings", 0), make_pair("morningstar farms buffalo wings, frozen, unprepared", 400)},
    {make_pair("General Tso Chicken and Noodles", 0), make_pair("restaurant, chinese, general tso's chicken", 180), make_pair("restaurant, chinese, vegetable lo mein, without meat", 180)},
    {make_pair("Breakfast for Dinner (Bacon & Eggs)", 0), make_pair("pork, cured, bacon, cooked, microwaved", 120), make_pair("eggs, scrambled, frozen mixture", 80), make_pair("kellogg's, eggOo, nutri-grain, waffles, low fat", 50)}};

    //Initializing health factors for default meal prep
    int activityLevel = 3;
    bool male = true;
    double weight = 160;
    double height = 69;
    int age = 20;
    bool lose = true;

    //Setting placeholder variables for calorie counts
    double maxCalories;
    double bfastCals;
    double lunchCals;
    double dinnerCals;

    //Printing out menu and options
    cout << "--------------C++lories&More--------------\n";
    cout << "\t\t~Meal Prepping Made Easy~\n\n";
    while(!prepped) {
        cout << "Please Enter Menu Option:\n";
        cout << "1. Dietary Restrictions\n";
        cout << "2. Activity Level\n";
        cout << "3. Health Information\n";
        cout << "4. Curate Meal Plan\n";
        cout << "5. Time to Find Ingredient\n";
        cout << "6. Quit\n";

        int option;
        cin >> option;

        auto start = high_resolution_clock::now();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        double time1, time2;
        string lineForIngredient;

        string input;
        switch(option) {
            case 1:
                cout << "\n\t\t~Dietary Restrictions~\n";
                //If restrictions are already set it allows for changing them or leaving them as is
                if (restrict) {
                    cout << "Dietary restrictions already entered!\nDo you want to change the information? (Y/N)\n";
                    cin >> input;
                }
                else {
                    input = "Y";
                }
                //Setting dietary restrictions
                if (input == "Y") {
                    dietaryRestrict.clear();
                    cout << "Do you have any dietary restrictions? (Y/N)\n";
                    cin >> input;
                    if (input == "Y") {
                        cout << "Please list restrictions (each ingredient should be followed by a ','): \n";
                        cin >> input;
                        cout << "Adding information to algorithm...\n\n";
                        toVector(input, dietaryRestrict);
                    }
                    else if (input == "N") {
                        dietaryRestrict.clear();
                        cout << "Adding information to algorithm...\n\n";
                    }
                    restrict = true;
                }
                else {
                    cout << "\n";
                }
                break;

            case 2:
                cout << "\n\t\t~Activity Level~\n";
                //If activity level is already set it allows for changing them or leaving them as is
                if (activity) {
                    cout << "Activity level already entered!\nDo you want to change the information? (Y/N)\n";
                    cin >> input;
                }
                else {
                    input = "Y";
                }
                if (input == "Y") {
                    cout << "On a scale of 1-5, how active are you? \n(1 being not active and 5 being very active)\n";
                    cin >> activityLevel;
                    cout << "Adding information to algorithm...\n\n";
                    activity = true;
                }
                else {
                    cout << "\n";
                }
                break;

            case 3:
                cout << "\n\t\t~Health Information~\n";
                //If health info is already set it allows for changing it or leaving them as is
                if (healthInfo) {
                    cout << "Health information already entered!\nDo you want to change the information? (Y/N)\n";
                    cin >> input;
                }
                else {
                    input = "Y";
                }
                if (input == "Y") {
                    cout << "Are you a man or woman? (enter man or woman)\n";
                    cin >> input;
                    if (input == "man") {
                        male = true;
                    }
                    else {
                        auto rng = default_random_engine {};
                        shuffle(begin(breakfastMeals), std::end(breakfastMeals), rng);
                        shuffle(begin(lunchMeals), std::end(lunchMeals), rng);
                        shuffle(begin(dinnerMeals), std::end(dinnerMeals), rng);
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
                else {
                    cout << "\n";
                }
                break;

            case 4:
                cout << "\n\t\t\t\t\t\t\t\t~Meal Plan~\n";
                if (!restrict || !activity || !healthInfo) {
                    cout << "You have not inputted all your information!\n"
                            "It is suggested to have all fields filled out in order to produce the best personal meal plan!\n"
                            "Are you sure you want to continue? (Y/N)\n";
                    cin >> input;
                }
                else {
                    input = "Y";
                }
                if (input == "Y") {
                    maxCalories = calculateAMR(male, weight, height, age, activityLevel);
                    if (lose) {
                        maxCalories -= 500;
                        cout << "\nIn order to lose weight, you should eat under " << maxCalories << " calories a day!\n";
                    }
                    else {
                        maxCalories += 500;
                        cout << "\nIn order to gain weight, you should eat around " << maxCalories << " calories a day!\n";
                    }

                    bfastCals = maxCalories * .33;
                    lunchCals = maxCalories * .4;
                    dinnerCals = maxCalories * .4;

                    //Printing out meal plans for Monday - Friday
                    for (int i = 0; i < 5; i++) {
                        double cal = 0;
                        switch(i) {
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
                        }
                        cout << "Breakfast: \t";
                        cal = curatePlanUnordered(bfastCals, dietaryRestrict, breakfastMeals, unordered);
                        cout << "\nLunch: \t\t";
                        cal += curatePlanUnordered(lunchCals, dietaryRestrict, lunchMeals, unordered);
                        cout << "\nDinner: \t";
                        cal += curatePlanUnordered(dinnerCals, dietaryRestrict, dinnerMeals, unordered);
                        cout << "\nTotal Calories for the Day from Meals: " << cal;
                    }
                    prepped = true;
                }
                else {
                    cout << "\n";
                }
                break;
            case 5:
                cout << "\n\t\t~Comparing Maps~\n";
                cout << "Enter ingredient to search for: ";
                cin.ignore();
                getline(cin, lineForIngredient);

                start = high_resolution_clock::now();
                unordered[lineForIngredient];
                stop = high_resolution_clock::now();
                duration = duration_cast<microseconds>(stop - start);
                time1 = duration.count();

                start = high_resolution_clock::now();
                ordered.findValue(lineForIngredient);
                stop = high_resolution_clock::now();
                duration = duration_cast<microseconds>(stop - start);
                time2 = duration.count();

                cout << "It took " << time1 << " microseconds for the Unordered Map!\n";
                cout << "It took " << time2 << " microseconds for the Ordered Map!\n\n";

                cout << "Enter ingredient to add to map: ";
                cin.ignore();
                getline(cin, lineForIngredient);

                start = high_resolution_clock::now();
                unordered.insert(lineForIngredient, 0);
                stop = high_resolution_clock::now();
                duration = duration_cast<microseconds>(stop - start);
                time1 = duration.count();

                start = high_resolution_clock::now();
                ordered.insert(lineForIngredient, 0);
                stop = high_resolution_clock::now();
                duration = duration_cast<microseconds>(stop - start);
                time2 = duration.count();

                cout << "It took " << time1 << " microseconds for the Unordered Map!\n";
                cout << "It took " << time2 << " microseconds for the Ordered Map!\n\n";

                break;

            case 6:
                prepped = true;
                break;

            default:
                cout << "Invalid Input: Please input value 1-6!\n\n";
        }
    }
    return 0;
}

//Checking for quotes in CSV to avoid removing excess commas
string checkForQuotes(istringstream& stream, string word){
    if (stream.peek() == '"') {
        stream >> quoted(word);
        string discard;
        getline(stream, discard, ',');
    } else {
        getline(stream, word, ',');
    }
    return word;
}

//Taking the dietary restriction input and putting ingredients into a vector
void toVector(string line, vector<string>& list) {
    stringstream ss(line);
    while (ss.good()) {
        string ingredient;
        getline(ss, ingredient, ',');
        transform(ingredient.begin(), ingredient.end(), ingredient.begin(), ::tolower);  //PUTS INGREDIENT IN LOWERCASE
        list.push_back(ingredient);
    }
}

//Calculating AMR based on formula found on https://www.verywellfit.com/how-many-calories-do-i-need-each-day-2506873
double calculateAMR(bool man, double weight, double height, int age, int activityLevel){
    weight = weight / 2.2;
    height = height * 2.54;
    double BMR, AMR;
    if (man) {
        BMR = 66.47 + (13.75 * weight) + (5.003 * height) - (6.755 * age);
    } else {
        BMR = 65.1 + (9.563 * weight) + (1.850 * height) - (4.676 * age);
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

//Goes through every meal to see if the calorie count is adequate for user, and if it is,
//displayed to output and calorie count is returned
//For Unordered Map
double curatePlanUnordered(double maxCals, vector<string>& restrictions, vector<vector<pair<string, double>>>& mealDatabase, UnorderedMap& unorderedNutrition){
    double calories;
    for (int j = 0; j < mealDatabase.size(); j++) {
        bool valid = true;
        calories = 0;
        for (int i = 1; i < mealDatabase[j].size(); i++) {
            //Check to see if meal has a dietary restriction in it
            for (string restrict: restrictions) {
                if (mealDatabase[j][i].first.find(restrict) != -1) {
                    valid = false;
                }
            }
            //Calculate calorie count of ingredients
            calories = calories + (unorderedNutrition[mealDatabase[j][i].first] * mealDatabase[j][i].second / 100.0) ;
        }
        if (calories > maxCals) {
            valid = false;
        }
        else if (calories * 2 < maxCals){
            valid = false;
        }
        if (valid) {
            cout << left << setw(50) << mealDatabase[j][0].first << right << setw(30) << "Calories: " << calories;
            mealDatabase.erase(mealDatabase.begin()+j);
            break;
        }
    }
    return calories;
}

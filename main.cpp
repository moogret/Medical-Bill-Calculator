//
// Created by abhik on 12/2/2024.
//Mary Alice Hartman
// Mary^2 Slowik

#include <iostream>
#include "YouKnowAboutTheCodes.h"
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <cmath>
using namespace std;

BTree File_decode(string filename, string tree_name){
    BTree new_tree(50000);
    new_tree.name = tree_name;
    ifstream file(filename);
    if(!file.is_open()){
        cerr << "File not opened" << endl;
    }
    string line;
    getline(file, line);
    while(getline(file, line)){
        stringstream ss(line);
        string med_code;
        string cost;

        getline(ss, med_code, ',');
        getline(ss, cost);

        new_tree.insert(med_code, cost);
    }
    return new_tree;
}

//function to search the map for the correct BTree
BTree get_tree(map<string, BTree> insurance_map, string insurance){
    for(const auto &pair : insurance_map){
        if(pair.first == insurance){
            return pair.second;
        }
    }
    return NULL;
}

//function for adding a new cost
void add_to_total(string cost_to_add, double current_total, vector<string>& itemized){
    double new_cost = stof(cost_to_add);
    float rounded_value = round(new_cost * 100) / 100;
    current_total += rounded_value;
    itemized.push_back(cost_to_add);
}

int main(){
    cout << "Hello Teammates!" << endl;
    // Mary testing to see if Btree implementation works, praying to every single god
    // ITS WORKS LFG
    BTree btree(3);

    btree.insert("001", "General Checkup");
    btree.insert("002", "Blood Test");
    btree.insert("003", "X-Ray");
    btree.insert("004", "MRI Scan");
    btree.insert("005", "Ultrasound");

    cout << "B-Tree contents:" << endl;
    btree.display();

    // Search for a procedure code
    string code = "003";
    string result = btree.search(code);
    if(!result.empty()){
        cout << "Procedure " << code << ": " << result << endl;
    }
    else{
        cout << "Procedure " << code << " not found." << endl;
    }

    //Final Main Construction Below this line

    //creating insurance B Tree
    BTree united_health = File_decode("United_data.csv", "united_data");
    BTree florida_blue = File_decode("Florida_Blue_data.csv", "florida_blue_data");
    BTree cigna = File_decode("Cigna_data.csv", "cigna_data");

    //map initiation for 3 different insurances
    map<string, BTree> insurance_map;
    insurance_map.emplace("United Health", united_health);
    insurance_map.emplace("Florida Blue", florida_blue);
    insurance_map.emplace("Cigna", cigna);

    //initializing total
    vector<string> itemized_costs;
    double total_cost = 0.00f;

    //need to take in user input to search the map for the right tree for now this is for testing functionality
    cout << "enter insurance" << endl;
    string user_input_1;
    getline(cin, user_input_1);
    BTree current_tree = get_tree(insurance_map, user_input_1);

    //take in user inout for the code they want to add
    string user_input_2; //for now this is going to act as the user input for testing functionality
    cout << "enter code" << endl;
    getline(cin, user_input_2);

    //search for associated cost
    string cost_to_add;
    cost_to_add = current_tree.search(user_input_2);
    add_to_total(cost_to_add, total_cost, itemized_costs);
    for(string cost: itemized_costs){
        cout << cost << endl;
    }
    return 0;
}
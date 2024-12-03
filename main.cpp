//
// Created by abhik on 12/2/2024.
//Mary Alice Hartman
// Mary^2 Slowik

#include <iostream>
#include "YouKnowAboutTheCodes.h"
#include <fstream>
#include <sstream>
#include <map>
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
    char delimeter = ',';
    while(getline(file, line)){
        stringstream ss(line);
        string med_code;
        string cost;

        getline(ss, med_code, ',');
        getline(ss, cost);

        new_tree.insert(med_code, cost);
//        cout << "B-Tree contents:" << endl;
//        new_tree.display();
    }
    return new_tree;
}

//function to search the map for the correct BTree
BTree get_tree(map<string, BTree> insurance_map, string insurance){
    for(const auto &pair : insurance_map){
        if(pair.first == "insurance"){
            return pair.second;
        }
    }
    return NULL;
}

//function for adding a new cost
vector<string> add_to_total(string code, double current_total){

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

    File_decode("United_data.csv", "united_data"); //testing the file decoder function, works but all nodes at level zero

    //Final Main Construction Below this line

    //creating insurance B Tree
    BTree united_health = File_decode("United_data.csv", "united_data");
    BTree florida_blue = File_decode("Florida_Blue_data.csv", "florida_blue_data");
    BTree cigna = File_decode("Cigna_data", "cigna_data");

    //map initiation for 3 different insurances
    map<string, BTree> insurance_map;
    insurance_map.emplace("United Health", united_health);
    insurance_map.emplace("Florida Blue", florida_blue);
    insurance_map.emplace("Cigna", cigna);

    //initializing total
    vector<string> itemized_costs;
    double total_cost = 0.0;

    //need to take in user input to search the map for the right tree for now this is for testing functionality
    BTree current_tree = get_tree(insurance_map, "United Health");

    //take in user inout for the code they want to add




    return 0;
}
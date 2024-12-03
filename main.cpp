//
// Created by abhik on 12/2/2024.
//Mary Alice Hartman
// Mary^2 Slowik

#include <iostream>
#include "YouKnowAboutTheCodes.h"
#include <fstream>
#include <sstream>
using namespace std;

BTree* File_decode(string filename, string tree_name){
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
        cout << "B-Tree contents:" << endl;
        new_tree.display();
    }
    return &new_tree;
}

int main(){
    cout << "Hello Teammates!" << endl;
    // Mary testing to see if Btree implementation works, praying to every single god
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
    if (!result.empty()) {
        cout << "Procedure " << code << ": " << result << endl;
    } else {
        cout << "Procedure " << code << " not found." << endl;
    }

    File_decode("United_data.csv", "united_data"); //testing the file decoder function, works but all nodes at level zero
    return 0;
}
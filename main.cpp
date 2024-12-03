//
// Created by abhik on 12/2/2024.
//Mary Alice Hartman
// Mary^2 Slowik

#include <iostream>
#include "YouKnowAboutTheCodes.h"
using namespace std;

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

    return 0;
}
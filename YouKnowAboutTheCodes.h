//
// Created by marys on 12/2/2024.
//
#include <iostream>
#include <vector>
using namespace std;
#include <string>

// BTree Class: create a B Tree for each set of codes for different health cares and their policies
class BTreeNode {
public:
    // Public Variables
    vector<string> keys;  // procedure codes
    vector<string> values;  // associated data (e.g., descriptions)
    vector<BTreeNode*> children; // pointers to child nodes
    bool isLeaf; // true if the node is a leaf
    int t; // minimum degree of the B-Tree

    // Constructor
    BTreeNode(int t, bool isLeaf){
        this->t = t;
        this->isLeaf = isLeaf;
    }

    // Functions
    // Insert Non-Full: insert a key-value pair into a non-full node; not needed every piece of data will have key and value
    void insert_non_full(const string& key, const string& value){
        int i = keys.size() - 1;

        if(isLeaf){
            keys.push_back(""); // temporary space for the key
            values.push_back(""); // temporary space for the value
            while(i >= 0 && key < keys[i]){
                keys[i + 1] = keys[i];
                values[i + 1] = values[i];
                i--;
            }
            keys[i + 1] = key;
            values[i + 1] = value;
        }
        else{
            while(i >= 0 && key < keys[i]){
                i--;
            }
            i++;
            if(children[i]->keys.size() == (2 * t - 1)){
                split_child(i, children[i]);
                if(key > keys[i]){
                    i++;
                }
            }
            children[i]->insert_non_full(key, value);
        }
    }

    // Split Child: make sure the tree remains balanced; this is key for insert function
    void split_child(int i, BTreeNode* fullChild){
        BTreeNode* newChild = new BTreeNode(fullChild->t, fullChild->isLeaf);
        int mid = t - 1;

        keys.insert(keys.begin() + i, fullChild->keys[mid]);
        values.insert(values.begin() + i, fullChild->values[mid]);

        newChild->keys.assign(fullChild->keys.begin() + t, fullChild->keys.end());
        newChild->values.assign(fullChild->values.begin() + t, fullChild->values.end());
        fullChild->keys.resize(mid);
        fullChild->values.resize(mid);

        if(!fullChild->isLeaf){
            newChild->children.assign(fullChild->children.begin() + t, fullChild->children.end());
            fullChild->children.resize(t);
        }

        children.insert(children.begin() + i + 1, newChild);
    }

    // Search: search for a key in the subtree rooted at this node
    string search(const string& key){
        int i = 0;

        while(i < keys.size() && key > keys[i]){
            i++;
        }

        if(i < keys.size() && keys[i] == key){
            return values[i];
        }

        if(isLeaf){
            return "";
        }

        return children[i]->search(key);
    }

    // Search Prefix: simultaneously search trees for each digit added and then add to a vector to show drop down on gui
    void search_with_prefix(const string& prefix, vector<string>& results) {
        // traverse the keys in this node
        for (int i = 0; i < keys.size(); i++) {
            // if the key starts with the prefix, add its value to the results
            if (keys[i].substr(0, prefix.size()) == prefix) {
                results.push_back(values[i]);
            }

            // if this is not a leaf node, traverse the corresponding child
            if (!isLeaf) {
                children[i]->search_with_prefix(prefix, results);
            }
        }

        // traverse the last child if not a leaf
        if (!isLeaf) {
            children[keys.size()]->search_with_prefix(prefix, results);
        }
    }

    // Traverse: traverse to display the keys and their values
    void traverse(int level = 0){
        for(int i = 0; i < keys.size(); i++){
            if(!isLeaf){
                children[i]->traverse(level + 1);
            }
            cout << "Level " << level << " - Code: " << keys[i] << ", Value: " << values[i] << endl;
        }
        if(!isLeaf){
            children[keys.size()]->traverse(level + 1);
        }
    }
};

// BTree class yippee
class BTree{
private:
    BTreeNode* root;
    int t;

public:
    string name;
    // Constructor
    BTree(int t){
        root = nullptr;
        this->t = t;
    }

    // Functions
    // Insert: insert a key-value pair into the tree
    void insert(const string& key, const string& value){
        if(!root){
            root = new BTreeNode(t, true);
            root->keys.push_back(key);
            root->values.push_back(value);
        }
        else{
            if(root->keys.size() == (2 * t - 1)){
                BTreeNode* new_root = new BTreeNode(t, false);
                new_root->children.push_back(root);
                new_root->split_child(0, root);
                root = new_root;
                root->insert_non_full(key, value);
            }
            else{
                root->insert_non_full(key, value);
            }
        }
    }

    // Search: search for a key in the B-tree -> we have to change this so that we can compare this with another search algorithm
    string search(const string& key){
        return root ? root->search(key) : "";
    }

    // Wrapper Function for Search with Prefix Function
    vector<string> search_with_prefix(const string& prefix) {
        vector<string> results;
        if (root) {
            root->search_with_prefix(prefix, results);
        }
        return results;
    }

    // Display: display the entire B-tree
    void display(){
        if (root) {
            root->traverse();
        }
    }

};


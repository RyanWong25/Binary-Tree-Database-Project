#include "TreeDB.h"

//constructor
TreeDB::TreeDB() {
    root = NULL;
}

//destructor
TreeDB::~TreeDB() {
    if (root = NULL)
        return;
    clearHelp(root);
}

//inserts the entry pointed to by newEntry into the database. 
bool TreeDB::insert(DBentry* newEntry) {
    TreeNode* temp = new TreeNode(newEntry);
    if (root == NULL) {
        root = temp;
        return true;
    }
    return (insertHelp(root, temp));
}

//function to decide which subtree to go down and insert the newEntry into.
bool TreeDB:: insertHelp(TreeNode* node, TreeNode* temp) {
    string newName = temp -> getEntry() -> getName();
    string currentNodeName = node -> getEntry() -> getName();
    
    if (newName.compare(currentNodeName) == 0) {
        delete temp;
        return false;
    }
    else if (newName.compare(currentNodeName) > 0) {
        if (node -> getRight() == NULL) {
            node -> setRight(temp);
            return true;
        }
        else
            return insertHelp(node -> getRight(), temp);
    }
    else {
        if (node -> getLeft() == NULL) {
            node -> setLeft(temp);
            return true;
        }
        else
            return insertHelp(node -> getLeft(), temp);
    }
}

//searches the database for an entry with a key equal to name.
DBentry* TreeDB::find(string name) {
    if (root == NULL)
        return NULL;
    
    probesCount = 0;
    return (findHelp(root, name));
}

//function to find where in TreeDB the entry with name is, or if it exists.
DBentry* TreeDB::findHelp(TreeNode* node, string name) {
    string currentNodeName = node -> getEntry() -> getName();
    
    if (name.compare(currentNodeName) == 0) {
        probesCount++;
        return node -> getEntry();
    }
    else if (name.compare(currentNodeName) > 0) {
        if (node -> getRight() == NULL)
            return NULL;
        else {
            probesCount++;
            return findHelp(node -> getRight(), name);
        }
    }
    else {
        if (node -> getLeft() == NULL)
            return NULL;
        else {
            probesCount++;
            return findHelp(node -> getLeft(), name);
        }
    }
}

//deletes the entry with the specified name (key) from the database.
bool TreeDB::remove(string name) {
    if (root == NULL)
        return false;
    return root -> remove(name, root);
}

//deletes all the entries in the database.
void TreeDB::clear() {
    if (root == NULL)
        return;
    clearHelp (root);
    root = NULL;
}

//function deletes all the entries from the bottom subtrees up
void TreeDB::clearHelp(TreeNode* node) {
    if (node == NULL)
        return;
    clearHelp(node -> getLeft());
    clearHelp(node -> getRight());
    delete node;
    node = NULL;
}

//prints the number of probes stored in probesCount
void TreeDB::printProbes() const {
    cout << probesCount << endl;
}

//computes and prints out the total number of active entries in the database
void TreeDB::countActive() const {
    int count = 0;
    countActiveHelp(root, count);
    cout << count << endl;
}

//function traverses through the TreeDB to find which nodes are active
void TreeDB::countActiveHelp(TreeNode* node, int& ACount) const {
    if (node == NULL)
        return;
    countActiveHelp (node -> getLeft(), ACount);
    countActiveHelp (node -> getRight(), ACount);
    if (node -> getEntry() -> getActive())
        ACount++;
}

// Prints the entire tree, in ascending order of key/name
ostream& operator << (ostream& out, const TreeDB& rhs) {
    if (rhs.root == NULL)
        return out;
    rhs.printAllHelp(rhs.root);
    return out;
}

//function traverses the entire tree and prints all the nodes
void TreeDB::printAllHelp(TreeNode* node) const {
    if (node == NULL)
        return;
    printAllHelp(node -> getLeft());
    cout << *(node -> getEntry());
    printAllHelp(node -> getRight());
}
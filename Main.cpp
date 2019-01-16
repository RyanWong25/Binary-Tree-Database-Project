
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "TreeDB.h"
#include "TreeNode.h"
#include "DBentry.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    string input;
    string command;
    TreeDB tree;

    cout << "> ";
    getline(cin, input);
    
    while (!cin.eof()) {
        stringstream linestream(input);
        linestream >> command;
        
        //parse insert function
        if (command == "insert") {
            string name;
            int IPaddress;
            string status;
            DBentry* temp;
            linestream >> name >> IPaddress >> status;
            
            if (status == "active")
                temp = new DBentry(name, IPaddress, 1);
            else
                temp = new DBentry(name, IPaddress, 0);
           
            bool success = tree.insert(temp);
            if (success)
                cout << "Success" << endl;
            else
                cout << "Error: entry already exists" << endl;
        }
        
        //parse find function
        else if (command == "find") {
            string name;
            linestream >> name;
            
            DBentry* temp = tree.find(name);
            
            if (temp == NULL)
                cout << "Error: entry does not exist" << endl;
            else if (temp -> getActive())
                cout << temp -> getName() << " : " << temp -> getIPaddress() << " : active" << endl;
            else
                cout << temp -> getName() << " : " << temp -> getIPaddress() << " : inactive" << endl;
        }
        
        //parse remove function
        else if (command == "remove") {
            string name;
            linestream >> name;
            
            bool removed = tree.remove(name);
            
            if (removed)
                cout << "Success" << endl;
            else 
                cout << "Error: entry does not exist" << endl;
        }
        
        //parse printall function
        else if (command == "printall") {
            cout << tree;
        }
        
        //parse printprobes function
        else if (command == "printprobes") {
            string name;
            linestream >> name;
            
            DBentry* temp = tree.find(name);
            
            if (temp == NULL)
                cout << "Error: entry does not exist" << endl;
            else
                tree.printProbes();
        }
        
        //parse removeall function
        else if (command == "removeall") {
            tree.clear();
            cout << "Success" << endl;
        }
        
        //parse countactive function
        else if (command == "countactive") {
            tree.countActive();
        }
        
        //parse updatestatus function
        else if (command == "updatestatus") {
            string name;
            string status;
            linestream >> name >> status;
            
            DBentry* temp = tree.find(name);
            
            if (temp == NULL)
                cout << "Error: entry does not exist" << endl;
            else {
                if (status == "active")
                    temp -> setActive(true);
                else if (status == "inactive")
                    temp -> setActive(false);
                cout << "Success" << endl;
            }
        }
        
        cout << "> ";
        getline(cin, input);
    }
    
    return 0;
}

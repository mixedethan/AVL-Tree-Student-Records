#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <stack>
#include <cctype>

#include "Node.h"
#include "AVLTree.h"

using namespace std;

/*
 *
 *
 *              AVLTree Project
 *          Designed by: Ethan Wilson
 *                Version 1.0
 *
 *
 */


/// Main() Helper Functions

// UFID can only contain 8 digits & must be unique
bool isValidUFID(const string& UFID)
{
    //Checks UFID's length
    if(UFID.length() != 8){
        return false;
    }

    //Checks for only numbers in the UFID
    for(char c : UFID){
        if(!isdigit(c)){
            return false;
        }
    }
    return true;
}

// Names must only include [a-z,A-Z, & spaces]
bool isValidName (string name) {
    bool isValidName = true;

    for(int i = 0; i < name.length(); i++){
        if(!isalpha(name.at(i)) && !isspace(name.at(i))){
            isValidName = false;
            break;
        }
    }
    return isValidName;
}

// Verifies that the command is in the correct format
bool isValidCommand(const string& command) {
    for(char c : command) {
        if (!isdigit(c)) return false;
    }
    return true;
}

void handleInsert(const string& command, AVLTree &gatorTree) {
    if (command.empty()) {
        cout << "unsuccessful. Usage: insert \"Name\" UFID" << endl;
        return;
    }

    int index = command.find_first_of('\"');
    if (index == string::npos || command.find_last_of('\"') == index) {
        cout << "unsuccessful. Ensure the name is enclosed in double quotes." << endl;
        return;
    }

    string name = command.substr(0, index);
    string check = command.substr(index + 2);

    if (isValidUFID(check) && isValidName(name)) {
        int ID = stoi(check);
        Node* newRoot = gatorTree.insert(gatorTree.getRoot(), name, ID);
        gatorTree.setRoot(newRoot);
        cout << "successful" << endl;
    } else {
        cout << "unsuccessful. Ensure UFID is an 8-digit number." << endl;
    }
}

void handleRemove(const string& command, AVLTree &gatorTree) {
    if (command.empty() || !isValidUFID(command)) {
        cout << "unsuccessful" << endl;
        return;
    }

    int ID = stoi(command);
    if (gatorTree.doesUFIDExist(gatorTree.getRoot(), ID)) {
        gatorTree.setRoot(gatorTree.remove(gatorTree.getRoot(), ID));
        cout << "successful" << endl;
    } else {
        cout << "unsuccessful" << endl;
    }
}

void handleSearch(string command, AVLTree &gatorTree) {
    // If the input command is a name
    if (command[0] == '"') {
        string name = command.substr(1, command.length() - 2);
        if(isValidName(name)) {
            gatorTree.searchName(gatorTree.getRoot(), name);
        } else {
            cout << "unsuccessful" << endl;
        }
    // Else if the input command is an UFID
    } else {
        if (isValidUFID(command)) {
            int ID = stoi(command);
            gatorTree.searchID(gatorTree.getRoot(), ID);
        } else {
            cout << "unsuccessful" << endl;
        }
    }
}

void handleFunctions(string command, AVLTree &gatorTree) {
    // Takes in input e.g "insert "Brandon" 45679999"
    int index = command.find_first_of(' ');
    // Function hold the value of the first work e.g "insert"
    string function = command.substr(0, index);
    command = command.substr(index + 1);

    if (function == "insert") {
        command = command.substr(1);
        handleInsert(command, gatorTree);
    } else if (function == "remove") {
        handleRemove(command, gatorTree);
    } else if (function == "search") {
        handleSearch(command, gatorTree);
    } else if (function == "printInorder") {
        gatorTree.printInOrder(gatorTree.getRoot());
        cout << endl;
    } else if (function == "printPreorder") {
        gatorTree.printPreOrder(gatorTree.getRoot());
        cout << endl;
    } else if (function == "printPostorder") {
        gatorTree.printPostOrder(gatorTree.getRoot());
        cout << endl;
    } else if (function == "printLevelCount") {
        gatorTree.printLevelCount(gatorTree.getRoot());
    } else if (function == "removeInorder") {
        if(isValidCommand(command)) {
            int n = stoi(command);
            gatorTree.setRoot(gatorTree.removeInorder(gatorTree.getRoot(), n));
        } else {
            cout << "unsuccessful. Usage: removeInorder n (where n is a valid index)." << endl;
        }
    } else if (function == "help") {
        cout << "Available commands:\n"
             << "1. insert \"Name\" UFID       - Insert a student into the tree (e.g., insert \"John Doe\" 12345678)\n"
             << "2. remove UFID               - Remove a student by UFID (e.g., remove 12345678)\n"
             << "3. search \"Name\"            - Search for a student by name (e.g., search \"John Doe\")\n"
             << "4. search UFID               - Search for a student by UFID (e.g., search 12345678)\n"
             << "5. printInorder              - Print all students in ascending UFID order\n"
             << "6. printPreorder             - Print all students in pre-order traversal\n"
             << "7. printPostorder            - Print all students in post-order traversal\n"
             << "8. printLevelCount           - Print the number of levels in the tree\n"
             << "9. removeInorder n           - Remove the nth student in in-order traversal (e.g., removeInorder 2)\n"
             << "10. exit                     - Exit the program\n"
             << "11. help                     - Display this help message\n";
    } else {
        cout << "Invalid command. Type 'help' to see a list of valid commands." << endl;
    }
}

int main() {
    AVLTree tree;
    string command;
    bool isRunning = true;

    cout << "Welcome to the AVL Tree Student Records Manager!" << endl;
    cout << "==================================================" << endl;
    cout << "Available commands:" << endl;
    cout << "1. insert \"Name\" UFID       - Insert a student into the tree" << endl;
    cout << "2. remove UFID               - Remove a student by UFID" << endl;
    cout << "3. search \"Name\"            - Search for a student by name" << endl;
    cout << "4. search UFID               - Search for a student by UFID" << endl;
    cout << "5. printInorder              - Print all students in ascending UFID order" << endl;
    cout << "6. printPreorder             - Print all students in pre-order traversal" << endl;
    cout << "7. printPostorder            - Print all students in post-order traversal" << endl;
    cout << "8. printLevelCount           - Print the number of levels in the tree" << endl;
    cout << "9. removeInorder n           - Remove the nth student in in-order traversal" << endl;
    cout << "10. exit                     - Exit the program" << endl;
    cout << "11. help                     - Display this help message" << endl;
    cout << "==================================================" << endl;

    while (isRunning) {
        cout << "\nEnter a command: ";
        getline(cin, command);

        if (command.empty()) {
            cout << "Please enter a valid command." << endl;
            continue;
        }

        if (command == "exit") {
            cout << "Exiting the program. Goodbye!" << endl;
            isRunning = false;
        } else {
            try {
                handleFunctions(command, tree);
            } catch (const exception& e) {
                cout << "An error occurred: " << e.what() << endl;
            }
        }
    }

    return 0;
}

#include <iostream>
#include <string>
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
bool isValidUFID(const string& UFID) {
    if (UFID.length() != 8) {
        cout << "UFID invalid: Incorrect length" << endl;
        return false;
    }
    for (char c : UFID) {
        if (!isdigit(c)) {
            cout << "UFID invalid: Contains non-digit characters" << endl;
            return false;
        }
    }
    return true;
}

bool isValidName(string name) {
    for (char c : name) {
        if (!isalpha(c) && !isspace(c)) {
            cout << "Name invalid: Contains invalid characters" << endl;
            return false;
        }
    }
    return true;
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

    int firstQuote = command.find_first_of('\"');
    int lastQuote = command.find_last_of('\"');
    if (firstQuote == string::npos || lastQuote == firstQuote) {
        cout << "unsuccessful. Ensure the name is enclosed in double quotes." << endl;
        return;
    }

    string name = command.substr(firstQuote + 1, lastQuote - firstQuote - 1);
    string ufid = command.substr(lastQuote + 1);
    ufid.erase(0, ufid.find_first_not_of(" "));
    ufid.erase(ufid.find_last_not_of(" ") + 1);


    if (!isValidName(name)) {
        cout << "unsuccessful. Invalid name. Names should contain only letters and spaces." << endl;
        return;
    }

    if (!isValidUFID(ufid)) {
        cout << "unsuccessful. Invalid UFID. UFID must be an 8-digit number." << endl;
        return;
    }

    int ID = stoi(ufid);
    Node* newRoot = gatorTree.insert(gatorTree.getRoot(), name, ID);
    gatorTree.setRoot(newRoot);
    cout << "successful" << endl;
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



/*
 * A program that places numbers (entered by the user or from a file)
 * into a red-black tree. You can print out the tree.
 * Artur Drobot, Mar 2017.
 */
#include <iostream>
#include "RedBlackTree.hpp"
#include <fstream>

using namespace std;

void populate(RedBlackTree &redBlackTree, char *list);
void addFromInput(RedBlackTree &redBlackTree);
bool addFromFile(RedBlackTree &redBlackTree);


int main(){
    while(true){
        RedBlackTree redBlackTree;
        char input;
        cout << "Choose an option to populate the tree: \n(1) Enter numbers manually.\n(2) Enter file name.\n(q) Quit program." << endl;
        cin >> input;
        if(input == '1'){
            addFromInput(redBlackTree);
        }
        else if(input == '2'){
            if(!addFromFile(redBlackTree)){//Error opening file
                continue;
            }
        }
        else if (input == 'q'){
            break;
        }
        else{
            cout << "Command not recognized." << endl;
            continue;
        }
        
        while(true){
            cout << "What do you want to do now?: \n(1) Print out the tree.\n(2) Add number(s).\n(3) Add numbers from a file. \n(4) Start a new tree.\n(5) Check if a number is in the tree.\n(6) Remove a number from the tree.\n(q) Quit program.\n(9) Sleep for 9 hours." << endl;
            cin >> input;
            if(input == '1'){
                cout << "Tree:" << endl;
                redBlackTree.print();
            }
            else if (input == '2'){
                addFromInput(redBlackTree);
            }
            else if (input == '3'){
                addFromFile(redBlackTree);
            }
            else if (input == '4' || input == 'q'){
                break;
            }
            else if(input == '5'){
                int num;
                cout << "Enter your number: ";
                cin >> num;
                if(redBlackTree.isInTree(num)){
                    cout << "Your number is present in the tree." << endl;
                }
                else{
                    cout << "Your number was not found in the tree." << endl;
                }
            }
            else if(input == '6'){
                int num;
                cout << "Enter the number to remove: ";
                cin >> num;
                if(redBlackTree.remove(num)){
                    cout << "Number removed successfully." << endl;
                }
                else{
                    cout << "Number not found in the tree." << endl;
                }
            }
            else if (input == '9'){
                cout << "Access denied by the International Baccalaureate Programme. Your attempt has been logged." << endl;
            }
            else{
                cout << "Command not recognized." << endl;
            }
            cout << "Press enter to continue." << endl;
            cin.ignore();
            cin.get();
        }
        if(input == 'q'){
            break;
        }
        
    }
    return 0;
}

void populate(RedBlackTree &redBlackTree, char *list){
    int index = 0;
    while(list[index]){
        if(isdigit(list[index])){
            int num = list[index] - '0';
            while(isdigit(list[++index])){
                num = 10*num + (list[index] - '0');
            }
            redBlackTree.insert(num);
        }
        else{
            index++;
        }
    }
}

void addFromInput(RedBlackTree &redBlackTree){
    char list[150];
    cout << "Enter the numbers, separated by commas and/or spaces:" << endl;
    cin.ignore();
    cin.getline(list, 150);
    populate(redBlackTree, list);
}

bool addFromFile(RedBlackTree &redBlackTree){
    char filename[32];
    cout << "Enter the file name: ";
    cin >> filename;
    ifstream stream(filename);
    if(stream.is_open()){
        char list[16384];
        stream.getline(list, 16384, 0);
        stream.close();
        populate(redBlackTree, list);
        return true;
    }
    else{
        cout << "Could not open file." << endl;
        return false;
    }
}
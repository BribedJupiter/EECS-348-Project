/*
17 Calculator Co.
Version 1.0
Last Updated: 14 November 2023
*/

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>                                    //Use  stdexcept for error catching

using namespace std;

string collectInput();                                  // Declaring the functions in the program
void preValidateInput(string userInput);
vector<vector<char> > vectorify(string inputString);
bool isValid(vector<vector<char> > input);              //Input is in the first index, key is in the second
void printOutput(vector<char> output);


int main(){
    /*This is the main function for the program*/
    string userInput;
    while (true){
        userInput = collectInput();             //Collects user input as a string userInput
        if (userInput == "exit"){
            break;
        }
        try {
            preValidateInput(userInput);           //Performs a pre-check for invalid characters
        } catch (invalid_argument& e){
            cout << "Invalid input" << endl;
            continue;
        }
        vector<vector<char> > vectorifiedOutput = vectorify(userInput); //Vectorifies the input to a vector of vectors vectorifiedOutput
        if (isValid(vectorifiedOutput) == true){                        //If valid, your program below...
            cout << "Valid" << endl;
        }else{
            cout << "Invalid" << endl;
        }
    }
    return 0;
}

string collectInput(){
    /*This is the function that collects the input from the user*/
    string input;
    cout << "Enter an expression (or 'exit'): ";
    getline(cin, input);

    return input;
}

void preValidateInput(string userInput){
    /*This is the function that does a pre-check for invalid characters*/
    string validCharList = "0123456789+-*/()^%";
    string validInput;

    for (int i = 0; i < userInput.size(); i++){
        if (validCharList.find(userInput[i]) != string::npos){
            validInput.push_back(userInput[i]);
        }
    }
    if (validInput != userInput) {
        throw invalid_argument("Invalid input");
    }
}

vector<vector<char> > vectorify(string inputString){
    /*This function puts the input into a vector and creates a value independent 'key' copy of the user vector*/
    vector<vector<char> > output;
    vector<char> input;
    vector<char> key;

    for (int i = 0; i < inputString.size(); i++){
        input.push_back(inputString[i]);
    }

    for (int i = 0; i < inputString.size(); i++){
        if (inputString[i] == '1' || inputString[i] == '2' || inputString[i] == '3' || inputString[i] == '4' || inputString[i] == '5' || inputString[i] == '6' || inputString[i] == '7' || inputString[i] == '8' || inputString[i] == '9'){
            key.push_back('0');
        }else{
            key.push_back(inputString[i]);
        }
    }
    output.push_back(input);
    output.push_back(key);
    return output;
}

bool isValid(vector<vector<char> > inputVecVec){
    /*
    Valid statements must adhere to the following the the following only:
    1. For each opening paranthesis, there must be a closing paranthesis and vice versa
    2. The following operators must have an interger (or parenthesis) on either side: *, /, %, ^
    3. The following operators must have an interger (or parenthesis) on at least their right side: +, -
    4. An opening parenthisis must not have an interer on its left side
    5. A closing paranthesis must not have an integer on its right side
    */  
    vector<char> key = inputVecVec[1];
    for (int i = key.size() - 1; i > 0; i--){           //This loop reduces all adjacent 0's to one 0 in key
        if (key[i] == key[i-1] && key[i] == '0'){
            key.erase(key.begin() + i);
            i--;
        }

    }
    int openCount = 0;
    int closeCount = 0;
    for (int i = 0; i < key.size(); i++){       //This loop checks for equal number of open and close paranthesis
        if (key[i] == ')'){
            closeCount++;
        }
        if (key[i] == '('){
            openCount++;
        }
    if (openCount != closeCount){
        return false;
    }
    }
    for (int i = 0; i < key.size(); i++){
        if (key[i] == '*' || key[i] == '/' || key[i] == '%' || key[i] == '^'){
            try {
                if (key[i-1] != '0' || key[i+1] != '0'){
                    return false;
                }
            }catch (out_of_range& e){
                return false;
            }
        }
    }
    for (int i = 0; i < key.size(); i++){
        if (key[i] == '+' || key[i] == '-'){
            try {
                if (key[i+1] != '0'){
                    return false;
                }
            }catch (out_of_range& e){
                return false;
            }
        }
    }
    for (int i = 0; i < key.size(); i++){
        if (key[i] == '(' && i != 0){
            if (key[i-1] != '0'){
                return false;
            }
        }
        if (key[i] == ')' && i != key.size() - 1){
            if (key[i+1] != '0'){
                return false;
            }
        }
    } 
    return true;     
}

void printOutput(vector<char> output){
    /*This is the function that outputs the final result*/
    for (int i = 0; i < output.size(); i++){
        cout << output[i];
    }
}

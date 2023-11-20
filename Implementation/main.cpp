/*
17 Calculator Co.
Version 1.0
Last Updated: 14 November 2023
*/

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <stdexcept>                                    //Use  stdexcept for error catching

using namespace std;

string collectInput();                                  // Declaring the functions in the program
void preValidateInput(string userInput);
vector<vector<char> > vectorify(string inputString);
bool isValid(vector<vector<char> > input);              //Input is in the first index, key is in the second
void printOutput(vector<char> output);
void solveStep(vector<int>& numbers, vector<char>& key, int start_index);
int nextStep(vector<char> &keyVec, vector<int> &intVec);
void recSolve(vector<char> &keyVec, vector<int> &intVec);
vector<int> intify(vector<char> &expression, vector<char> &key);

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
        vector<vector<char>> vectorifiedOutput = vectorify(userInput); //Vectorifies the input to a vector of vectors vectorifiedOutput
        // input, key
        if (isValid(vectorifiedOutput) == true){                        //If valid, your program below...
            cout << "Valid" << endl;
            vector<int> intVec = intify(vectorifiedOutput[0], vectorifiedOutput[1]);
            recSolve(vectorifiedOutput[0], intVec);
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

vector<int> intify(vector<char> &expression, vector<char> &key) {
    /*This function combines split numbers, adds them to a new integer vector and updates the key accordingly*/
    vector<int> intVector;
    vector<char> newKey;

    int currentNumber = 0;
    bool isBuildingNumber = false;
    bool isNegative = false;

    for (size_t i = 0; i < expression.size(); ++i) { // Combines the numbers after finding them in the expression
        if (key[i] == '0') {
            if (!isBuildingNumber) {
                isBuildingNumber = true;
                currentNumber = 0;
                if (i > 0 && expression[i - 1] == '-' && (i == 1 || expression[i - 2] == '(')) { // Handles the expression if the combined number is negative
                    isNegative = true;
                }
            }
            currentNumber = currentNumber * 10 + (expression[i] - '0');
        } else { // If the character is not a number, it is added to the new key and the number is added to the integer vector
            if (isBuildingNumber) {
                intVector.push_back(isNegative ? -currentNumber : currentNumber);
                newKey.push_back('0');
                isBuildingNumber = false;
                isNegative = false;
            }
            intVector.push_back(0);
            newKey.push_back(key[i]);
        }
    }
    if (isBuildingNumber) { // Adds the last number to the integer vector
        intVector.push_back(isNegative ? -currentNumber : currentNumber);
        newKey.push_back('0');
    }

    key = newKey; // Updates the key

    return intVector;
}

bool isValid(vector<vector<char>> inputVecVec){
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

void printOutput(vector<int> output){
    /*This is the function that outputs the final result*/
    for (int i = 0; i < output.size(); i++){
        cout << output[i];
    }
}

void solveStep(vector<int>& numbers, vector<char>& key, int start_index) {
    // Take in an expression vector, a key vector, and what the next step to perform is and update the vectors to simplify the expression.
    
    int answer;  // Variable that holds the answer to the step
    if (key[start_index] == '('){  // Checks if the step is a paranthesis reduction step i.e. "(10)" -> "10"
        numbers[start_index] = numbers[start_index+1];
        key[start_index] = '0';
        numbers.erase(numbers.begin() + start_index+2);  // Edits the expression vector
        numbers.erase(numbers.begin() + start_index+1);
        key.erase(key.begin() + start_index+2);  // Edits the key vector
        key.erase(key.begin() + start_index+1);
    } else {  // If it's a normal math expression... 
        if (key[start_index + 1] == '+') {  // Checks what operation
            answer = numbers[start_index] + numbers[start_index + 2];
        } else if (key[start_index + 1] == '-'){
            answer = numbers[start_index] - numbers[start_index + 2];
        } else if (key[start_index + 1] == '*'){
            answer = numbers[start_index] * numbers[start_index + 2];
        } else if (key[start_index + 1] == '/'){
            answer = numbers[start_index] / numbers[start_index + 2];
        } else if (key[start_index + 1] == '%'){
            answer = numbers[start_index] % numbers[start_index + 2];
        }  else if (key[start_index + 1] == '^'){
            answer = pow(numbers[start_index], numbers[start_index + 2]);
        }
        
        numbers[start_index] = answer; // Sets the first number in expression to the answer (so that it works when there is only expression left)
        key[start_index] = '0';  // Updates key
        numbers.erase(numbers.begin() + start_index + 2);  // Gets rid of used elements
        numbers.erase(numbers.begin() + start_index + 1);
        key.erase(key.begin() + start_index + 2);
        key.erase(key.begin() + start_index + 1);
    }
}

// Input a 2D vector that contains the key and the expression
// Outputs nothing, but calls solveStep
// Input further defined --> 3+2
//      intVector - integers, Cannot be used to know where there is an operator, as we may have zeroes --> [302] - int vec
//      keyVector - 0 in place of integer, otherwise symbol --> [0+0] - char vec
int nextStep(vector<char> &keyVec, vector<int> &intVec) {
    // Find the index of the beginning of the next step

    // Case 1- Is there an instance (num) - pass out [(num)] --> e.g. (3)
    // keyVec.size() - 1 = the last index of keyVecs
    for (int i = 0; i <=  keyVec.size() - 1; i++) {
        if (keyVec[i] == '(') {
            if (keyVec[i+2] == ')') {
                // pass keyVec[i] - the start parenthesis
                return i;
            }
        }
    }

    // Case 2 - Is there an instance of (expression) - always take first found, but farthest in
    //      Iterate through and find last open, then find first close, and return last open index
    //      If have (3+4), pass out [expression] --> e.g. 3+4
    //      Case ((, case (3), case (3+4)
    for (int i = 0; i <= keyVec.size() - 1; i++) {
        if (keyVec[i] == '(') {
            if (keyVec[i+1] == '(') continue; // Case (( --> skip iteration, move to the next one in
            if (keyVec[i+2] == ')') continue; // Case (3) --> should be handled above, but check just in case
            if (keyVec[i+2] != '0') { // Case ([NUM][OPERATOR][NUM]), ) already checked
                // pass keyVec[i+1] - the start expression number
                return i+1;
            }
        }
    }

    // Case 3 - num-operator-num --> e.g. 3*2
    //      Handle in order of PEMDAS
    //      Valid operators --> [+, -, *, /, %, ^]   
    for (int i = 0; i < keyVec.size() - 2; i++) {
        if (keyVec[i] == '0' && keyVec[i+1] != '0' && keyVec[i+1] != '(' && keyVec[i+1] != ')' && keyVec[i+2] == '0') {
            if (keyVec[i+1] == '^') {
                return i;
            }
        }
    }

    for (int i = 0; i < keyVec.size() - 2; i++) {
        if (keyVec[i] == '0' && keyVec[i+1] != '0' && keyVec[i+1] != '(' && keyVec[i+1] != ')' && keyVec[i+2] == '0') {
            if (keyVec[i+1] == '*' or keyVec[i+1] == '/' or keyVec[i+1] == '%') {
                if (keyVec[i+1] == '^') {
                    return i;
                }
                else if (keyVec[i+1] == '*') {
                    return i;
                }
                else if (keyVec[i+1] == '/') {
                    return i;
                }
                else if (keyVec[i+1] == '%') {
                    return i;
                }
            }
        }
    }

    for (int i = 0; i < keyVec.size() - 2; i++) {
        if (keyVec[i] == '0' && keyVec[i+1] != '0' && keyVec[i+1] != '(' && keyVec[i+1] != ')' && keyVec[i+2] == '0') {
            if (keyVec[i+1] == '+' || keyVec[i+1] == ('-')) {
                if (keyVec[i+1] == '+') {
                    return i;
                }
                else if (keyVec[i+1] == '-') {
                    return i;
                }
            }
        }
    }
    return 0; // this is not ideal
}

void recSolve(vector<char> &keyVec, vector<int> &intVec) {
    // Recursively solve the expression
    while (intVec.size() >= 1) {
        if (intVec.size() == 1) {
            printOutput(intVec);
            break;
        }

        // nextStep returns start index
        // solveStep evaluates at index and updates keyVec and intVec
        solveStep(intVec, keyVec, nextStep(keyVec, intVec));
    }
}
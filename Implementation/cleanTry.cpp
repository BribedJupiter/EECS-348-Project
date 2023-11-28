/*
17 Calculator Co.
Version 1.0
Last Updated: 26 November 2023
*/

#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

bool isValid(string userInput);
vector<char> operatorVectorify(string userInput);
vector<double> doubleVectorify(string userInput);
void matcher(vector<char>& operatorVector, vector<double>& doubleVector);
int nextStep(vector<char> &keyVec, vector<double> &doubVec);
void solveStep(vector<double>& numbers, vector<char>& key, int start_index);
void solver(vector<char>& keyVec, vector<double>& doubVec);


int main(){
    string userInput;
    while (true){
        cout << "Enter an expression (or 'exit'): ";
        getline(cin, userInput);
        if (userInput == "exit"){
            break;
        }
        if (isValid(userInput)){
            cout << "Valid input!" << endl;

            vector<char> operatorVector = operatorVectorify(userInput);
            vector<double> doubleVector = doubleVectorify(userInput);
            matcher(operatorVector, doubleVector);

            cout << "The answer is: ";
            solver(operatorVector, doubleVector);
            cout << endl;
        } else {
            cout << "Invalid input!" << endl;
        }
    }
    return 0;
}

bool isValid(string userInput){
    string validCharString = "0123456789+-*/()^% ";
    for (int i = 0; i < userInput.size(); i++){
        if (validCharString.find(userInput[i]) == string::npos){
            cout << "Invalid character(s)!!! " << userInput[i] << endl;
            return false;
        }
    }

    vector<char> inputVector;

    for (int i = 0; i < userInput.size(); i++){
        if (userInput[i] == '1' || userInput[i] == '2' || userInput[i] == '3' || userInput[i] == '4' || userInput[i] == '5' || userInput[i] == '6' || userInput[i] == '7' || userInput[i] == '8' || userInput[i] == '9'){
            inputVector.push_back('0');
        }else if( userInput[i] != ' '){
            inputVector.push_back(userInput[i]);
        }
    }
    for (int i = inputVector.size() - 1; i > 0; i--){
        if (inputVector[i] == inputVector[i-1] && inputVector[i] == '0'){
            inputVector.erase(inputVector.begin() + i);
            i--;
        }
    }
    for (int i = inputVector.size() -1; i > 0; i--){
        if (inputVector[i] == ' '){
            inputVector.erase(inputVector.begin() + i);
            i--;
        }
    }

    int openCount = 0;
    int closeCount = 0;

    for (int i = 0; i < inputVector.size(); i++){
        if (inputVector[i] == ')'){
            closeCount++;
        }
        if (inputVector[i] == '('){
            openCount++;
        }
    }
    if (openCount != closeCount){
        cout << "Unmatched Paranethesis!"<<endl;
        return false;
        
    }

    for(int i = 0; i < inputVector.size(); i++){
        if (inputVector[i] == '*' || inputVector[i] == '/' || inputVector[i] == '%' || inputVector[i] == '^'){
            if (i == 0){
                cout << "Invalid usage of operator *, /, %, or ^" << endl;
                return false;
            }
            if (i == inputVector.size() - 1){
                cout << "Invalid usage of operator *, /, %, or ^" << endl;
                return false;
            }
            if (inputVector[i-1] != '0' && inputVector[i-1] != ')'){
                cout << "Invalid usage of operator *, /, %, or ^" << endl;
                return false;
            }
            if (inputVector[i+1] != '0' && inputVector[i+1] != '('){
                cout << "Invalid usage of operator *, /, %, or ^" << endl;
                return false;
            }
        }
    }
    for (int i = 0; i < inputVector.size(); i++){
        if (inputVector[i] == '+' || inputVector[i] == '-'){
            if (i == inputVector.size() - 1){
                cout << "Invalid usage of operator + or -" << endl;
                return false;
            }
            if (inputVector[i+1] != '0' && inputVector[i+1] != '(' && inputVector[i+1] != '-' && inputVector[i+1] != '-'){
                cout << "Invalid usage of operator + or -" << endl;
                return false;
            }
            if (i != 0){
                if (inputVector[i-1] != '0' && inputVector[i-1] != ')' && inputVector[i-1] != '(' && inputVector[i-1] != '-' && inputVector[i-1] != '+'){
                    cout << "Invalid usage of operator + or -" << endl;
                    return false;
                }
            }
        }
    }
    for (int i = 0; i < inputVector.size(); i++){
        if (inputVector[i] == '(' && i != 0){
            if (inputVector[i-1] == '0'){
                cout << "Missing operator before (" << endl;
                return false;
            }
        }
        if (inputVector[i] == ')' && i != inputVector.size() - 1){
            if (inputVector[i+1] == '0' || inputVector[i+1] == '('){
                cout << "Missing operator after )" << endl;
                return false;
            }
        }
    } 
    cout<< "Valid Input!" << endl;
    return true;
}

vector<char> operatorVectorify(string userInput){
    string digits = "0123456789";
    vector<char> operatorVector;
    for (int i = 0; i < userInput.size(); i++){
        if (digits.find(userInput[i]) != string::npos) {
            operatorVector.push_back('0');
        } else {
            operatorVector.push_back(userInput[i]);
        }
    }
    for (int i = operatorVector.size() - 1; i > 0; i--){
        if (operatorVector[i] == operatorVector[i-1] && operatorVector[i] == '0'){
            operatorVector.erase(operatorVector.begin() + i);
            i--;
        }
    }
    return operatorVector;
}

vector<double> doubleVectorify(string userInput){
    vector<double> doubleVector;
    string digits = "0123456789";

    double tempNum = -1;
    double placeValue = 1;

    for (int i = userInput.size(); i >= 0; i--){
        if (digits.find(userInput[i]) != string::npos){
            tempNum += userInput[i] * placeValue;
            placeValue++;
        }
        else if (digits.find(userInput[i]) == string::npos || i == 0){
            tempNum++;
            doubleVector.push_back(tempNum);
            tempNum = -1;
            placeValue = 1;
        }
        vector<double> tempVector = doubleVector;
        doubleVector.clear();
        for (i = 0; i < tempVector.size(); i++){
            doubleVector.push_back(tempVector[i]);
        }
    }
    return doubleVector;
}

void matcher(vector<char>& operatorVector, vector<double>& doubleVector){
    vector<double> tempDoubles;
    int doubleIndex = 0;
    for (int i = 0; i < operatorVector.size(); i++){
        if (operatorVector[i] == '0'){
            tempDoubles.push_back(doubleVector[doubleIndex]);
            doubleIndex++;
        }else{
            tempDoubles.push_back(operatorVector[i]);
        }
    }
    doubleVector = tempDoubles;
}

int nextStep(vector<char> &keyVec, vector<double> &doubVec) {
    /* Find the index of the beginning of the next step */

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

    // Case 3 - num-operator-num --> e.g. 3*2 or 5^1
    //      Handle in order of operations with modulo having the same precedence as multiplication and division.
    //      Valid operators --> [+, -, *, /, %, ^]
    //      Three groups of precedence. Each group is evaluated from left to right
    //                1: Exponentials: e.g. 5^3
    //                2: Multiplication / Division / Modulo: e.g. 3*2, 8/4, and 7%3 
    //                3: Addition / Subtraction: e.g. 6+9 or 2-1
    for (int i = 0; i < keyVec.size() - 2; i++) { // Iterates through the key vector
        if (keyVec[i] == '0' && keyVec[i+1] != '0' && keyVec[i+1] != '(' && keyVec[i+1] != ')' && keyVec[i+2] == '0') { // Checks for an instance of num-operator-num
            if (keyVec[i+1] == '^') { // If there is an instance of an exponential, it determines it to be the next step and returns the index of the first number in the grouping
                return i;
            }
        }
    }

    for (int i = 0; i < keyVec.size() - 2; i++) {
        if (keyVec[i] == '0' && keyVec[i+1] != '0' && keyVec[i+1] != '(' && keyVec[i+1] != ')' && keyVec[i+2] == '0') { // Checks again for an instance of num-operator-num in the key vector
            if (keyVec[i+1] == '*' or keyVec[i+1] == '/' or keyVec[i+1] == '%') { // If there is an instance of multiplication, division, or modulo, returns the index of the first number in the grouping
                if (keyVec[i+1] == '*') {
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
        if (keyVec[i] == '0' && keyVec[i+1] != '0' && keyVec[i+1] != '(' && keyVec[i+1] != ')' && keyVec[i+2] == '0') { // Checks again for an instance of num-operator-num in the key vector
            if (keyVec[i+1] == '+' || keyVec[i+1] == ('-')) { // If there is an instance of addition or subtraction, returns the index of the first number in the grouping
                if (keyVec[i+1] == '+') {
                    return i;
                }
                else if (keyVec[i+1] == '-') {
                    return i;
                }
            }
        }
    }
    return 0; // Should never be reached, but if none of the following situations are found, returns 0.
}

void solveStep(vector<double>& numbers, vector<char>& key, int start_index) {
    /* Take in an expression vector, a key vector, and what the next step to perform is and update the vectors to simplify the expression. */
    double answer;  // Variable that holds the answer to the step
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
            answer = (int)numbers[start_index] % (int)numbers[start_index + 2];
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

void solver(vector<char> &keyVec, vector<double> &doubVec) {
    while (doubVec.size() >= 1) {
        if (doubVec.size() == 1) {
            for (int i = 0; i < doubVec.size(); i++) {
                cout << doubVec[i];
            }
            break;
        }
        solveStep(doubVec, keyVec, nextStep(keyVec, doubVec));
    }
}

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

string collectInput();
bool isValid(string userInput);
vector<char> operatorVectorify(string userInput);
vector<double> doubleVectorify(string userInput);
double solver(string userInput);
double recSolver(vector<char> operatorVector, vector<double> doubleVector);

int main(){
    string userInput;
    while (true){
        userInput = collectInput();
        if (userInput == "exit"){
            break;
        }
        if (isValid(userInput) == true){
            cout << "Valid" << endl;
        }  
    }
    return 0;
}

string collectInput(){
    string input;
    cout << "Enter an expression (or 'exit'): ";
    getline(cin, input);

    return input;
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

    for (int i = userInput.size(); i > 1; i--){
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

double solver(string userInput){
    vector<char> operatorVector = operatorVectorify(userInput);
    vector<double> doubleVector = doubleVectorify(userInput);
    return recSolver(operatorVector, doubleVector);
}

double recSolver(vector<char> operatorVector, vector<double> doubleVector){
    /*
    eveything before this function has been tested and is valid

    operatorVector contains all operators in input order. All interger chars are replaces with zero. This does not include negative signs. 
    all negative signs should be treated as unary operators.

    doubleVector contains all numbers, as positive integers in input order.

    This function should start by calling on the lowest priority operators with slices of the operatorVector and doubleVector until base cases are met.

    Then the base cases should return up the stack, solving the higher priority operators until the final answer is returned. 


    addition / subtraction (right to left)
    multiplication / division / mod (right to left)
    exponents
    parentheses


    Base Cases: TBD
    */
    return 0;
}
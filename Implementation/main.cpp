/*
17 Calculator Co.
Version 1.0
Last Updated: 14 November 2023
*/

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>                                    //Make sure to use for error catching

using namespace std;

string collectInput();                                  // Declaring the functions in the program
string preValidateInput(string userInput);
void vectorify(string inputString);

int main(){
    /*This is the main function for the program*/
    string userInput = collectInput();                  // Collecting the user input
    string validInput = preValidateInput(userInput);    // Validating the user input
    vectorify(validInput);                              // Simplifying the user input

    cout << validInput << endl;                         // Just a test print for the time being. Will be removed later

    return 0;
}

string collectInput(){
    /*This is the function that collects the input from the user*/
    string input;
    cout << "Enter an expression: ";
    getline(cin, input);

    return input;
}

string preValidateInput(string userInput){
    /*This is the function that does a pre-check for invalid characters*/
    string validCharList = "0123456789+-*/()^";
    string validInput;

    for (char i : userInput){
        if (validCharList.find(i) != string::npos){
            validInput.push_back(i);
        }
    }
    return validInput;
}

void output(vector<char> output){
    /*This is the function that outputs the final result*/
    for (char i : output){
        cout << i;
    }
}

void vectorify(string inputString){
    /*This function simplifies the strings for furhter use*/
    vector<char> output;
    vector<char> key;

    for (char i : inputString){
        output.push_back(i);
    }

    for (char i : inputString){
        if (i == '1' || i == '2' || i == '3' || i == '4' || i == '5' || i == '6' || i == '7' || i == '8' || i == '9'){
            key.push_back('0');
        }
    }
    for (char i : inputString){
        key.push_back(i);
    }
}

/* 
Notes:

the input preVaildation program does not error when the user inputs a string with invalid characters 

the vecotrify function  returns turns the string into two vectors. The first contains user input
the second contains only the operators, parentheses, and zeroes in place of numbers.

I have not yet done the full checkVaild function.
*/

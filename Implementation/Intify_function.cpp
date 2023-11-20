#include <iostream>
#include <vector>

using namespace std;

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
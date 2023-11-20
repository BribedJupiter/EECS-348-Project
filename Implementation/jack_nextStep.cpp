#include <vector>
#include <iostream>
using namespace std;

// Input a 2D vector that contains the key and the expression
// Outputs nothing, but calls solveStep
// Input further defined --> 3+2
//      intVector - integers, Cannot be used to know where there is an operator, as we may have zeroes --> [302] - int vec
//      keyVector - 0 in place of integer, otherwise symbol --> [0+0] - char vec
void nextStep(vector<char> &keyVec, vector<int> &intVec) {
    // Find the index of the beginning of the next step

    // Case 1- Is there an instance (num) - pass out [(num)] --> e.g. (3)
    // keyVec.size() - 1 = the last index of keyVecs
    for (int i = 0; i <=  keyVec.size() - 1; i++) {
        if (keyVec[i] == '(') {
            if (keyVec[i+2] == ')') {
                // pass keyVec[i] - the start parenthesis
                cout << i; // returns index of num in middle of (num)
                return;
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
                cout << i+1;
                return;
            }
        }
    }

    // Case 3 - num-operator-num --> e.g. 3*2
    //      Handle in order of PEMDAS
    //      Valid operators --> [+, -, *, /, %, ^]   
    for (int i = 0; i < keyVec.size() - 2; i++) {
        if (keyVec[i] == '0' && keyVec[i+1] != '0' && keyVec[i+1] != '(' && keyVec[i+1] != ')' && keyVec[i+2] == '0') {
            if (keyVec[i+1] == '^') {
                std::cout << intVec[i] << "^" << intVec[i+2];
                return;
            }
        }
    }

    for (int i = 0; i < keyVec.size() - 2; i++) {
        if (keyVec[i] == '0' && keyVec[i+1] != '0' && keyVec[i+1] != '(' && keyVec[i+1] != ')' && keyVec[i+2] == '0') {
            if (keyVec[i+1] == '*' or keyVec[i+1] == '/' or keyVec[i+1] == '%') {
                if (keyVec[i+1] == '^') {
                    std::cout << intVec[i] << "^" << intVec[i+2];
                    return;
                }
                else if (keyVec[i+1] == '*') {
                    std::cout << intVec[i] << "*" << intVec[i+2];
                    return;
                }
                else if (keyVec[i+1] == '/') {
                    std::cout << intVec[i] << "/" << intVec[i+2];
                    return;
                }
                else if (keyVec[i+1] == '%') {
                    std::cout << intVec[i] << "%" << intVec[i+2];
                    return;
                }
            }
        }
    }

    for (int i = 0; i < keyVec.size() - 2; i++) {
        if (keyVec[i] == '0' && keyVec[i+1] != '0' && keyVec[i+1] != '(' && keyVec[i+1] != ')' && keyVec[i+2] == '0') {
            if (keyVec[i+1] == '+' || keyVec[i+1] == ('-')) {
                if (keyVec[i+1] == '+') {
                    std::cout << intVec[i] << "+" << intVec[i+2];
                    return;
                }
                else if (keyVec[i+1] == '-') {
                    std::cout << intVec[i] << "-" << intVec[i+2];
                    return;
                }
            }
        }
    }
}

int main() {
    vector<char> testKeyVec{'(', '0',  '+', '(', '0', ')', ')'};
    vector<int> intVec{0, 2, 0, 3, 0};
    nextStep(testKeyVec, intVec);
    return 0;
}
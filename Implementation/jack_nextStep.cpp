// This is Jack's work on nextStep()
#include <vector>
#include <iostream>
using namespace std;
// Input a 2D vector that contains the key and the expression
// Outputs nothing, but calls solveStep
// inputVecVec[0] = key?
// inputVecVec[1] = exp?
// Input further defined --> 3+2
// intVector - integers, Cannot be used to know where there is an operator, as we may have zeroes --> [302] - int vec
// keyVector - 0 in place of integer, otherwise symbol --> [0+0] - char vec
void nextStep(vector<char> &keyVec, vector<int> &intVec) {
    // Case 1- Is there an instance (num) - pass out [(num)] --> e.g. (3)
    // keyVec.size() - 1 = the last index of keyVecs
    for (int i = 0; i = keyVec.size() - 1; i++) {
        if (keyVec[i] == '(') {
            if (keyVec[i+2] == ')') {
                // pass keyVec[i]
                std::cout << keyVec[i+1];
                return;
            }
        }
    }

    // Case 2 - Is there an instance of (expression) - always take first found, but farthest in
    //      Iterate through and find last open, then find first close, and return inbetweem
    //      If have (3+4), pass out [expression] --> e.g. 3+4

    // Case 3 - num-operator-num --> e.g. 3*2
    //      Handle in order of PEMDAS
    //      Valid operators --> [+, -, *, /, %, ^] 
}

int main() {
    vector<char> testKeyVec{'(', '(', '3', ')', ')'};
    vector<int> intVec{0, 0, 3, 0, 0};
    nextStep(testKeyVec, intVec);
    return 0;
}
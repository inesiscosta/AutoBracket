#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    // Define the numbers involved in the expression
    //vector<string> numbers = {"2", "2", "2", "2", "1", "3"};
    //vector<string> numbers = {"1", "2", "2", "1"};
    vector<string> numbers = {"1", "2", "3", "4", "5", "6"};
    int n = numbers.size();
    
    // DP table for sub-expression combinations, using vector
    vector<vector<vector<string>>> parentizations(n, vector<vector<string>>(n));

    // Base case: each single number is a valid expression by itself
    for (int i = 0; i < n; i++) {
        parentizations[i][i].push_back(numbers[i]);
    }

    // Iterate over increasing lengths of sub-expressions (depth of nesting)
    for (int len = 2; len <= n; len++) {  // len is the length of the sub-expression
        for (int left = 0; left <= n - len; left++) {  // left boundary of the sub-expression
            int right = left + len - 1;  // right boundary of the sub-expression

            // Combine left and right sub-expressions, iterate mid in reverse order to prioritize deep nesting
            for (int mid = right - 1; mid >= left; mid--) {  // mid is the partition point, iterate backwards
                // Combine all left and right sub-expression pairs
                for (const string& leftStr : parentizations[left][mid]) {
                    for (const string& rightStr : parentizations[mid + 1][right]) {
                        string combined = "(" + leftStr + " " + rightStr + ")";
                        parentizations[left][right].push_back(combined);
                    }
                }
            }
        }
    }

    // Store the final combinations and print them in correct order
    vector<string> allCombinations = parentizations[0][n - 1];
    for (const string& combination : allCombinations) {
        cout << combination << endl;
    }

    return 0;
}

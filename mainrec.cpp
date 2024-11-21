#include <iostream>
#include <string>
#include <vector>

// Global variables for input data.
int _N, _M, desiredResult;
std::vector<std::vector<int>> operationTable;
std::vector<int> sequence;
std::vector<std::vector<std::vector<std::pair<bool, std::string>>>> memoizationTable;

// Recursive function to find the correct parenthesization.
std::pair<bool, std::string> solve(int i, int j, int target) {
    // Base case: when i == j, check if the element matches the target.
    if (i == j) {
        if (sequence[i] == target) {
            return {true, std::to_string(sequence[i])};
        } else {
            return {false, ""};
        }
    }

    // Check if the subproblem has already been computed.
    if (memoizationTable[i][j][target].first || !memoizationTable[i][j][target].second.empty()) {
        return memoizationTable[i][j][target];
    }

    // Try to split the sequence between i and j.
    for (int k = j - 1; k >= i; --k) {
        for (int left = 1; left <= _N; ++left) {
            for (int right = 1; right <= _N; ++right) {
                auto leftResult = solve(i, k, left);
                auto rightResult = solve(k + 1, j, right);
                if (leftResult.first && rightResult.first) {
                    int combinedVal = operationTable[left - 1][right - 1];
                    if (combinedVal == target) {
                        // Found a valid solution; store and return it.
                        std::string expr = "(" + leftResult.second + " " + rightResult.second + ")";
                        memoizationTable[i][j][target] = {true, expr};
                        return memoizationTable[i][j][target];
                    }
                }
            }
        }
    }

    // No valid parenthesization found for this subproblem.
    memoizationTable[i][j][target] = {false, ""};
    return memoizationTable[i][j][target];
}

int main() {
    std::cin >> _N >> _M;

    operationTable.resize(_N, std::vector<int>(_N));
    for (int i = 0; i < _N; ++i) {
        for (int j = 0; j < _N; ++j) {
            std::cin >> operationTable[i][j];
        }
    }

    sequence.resize(_M);
    for (int i = 0; i < _M; ++i) {
        std::cin >> sequence[i];
    }

    std::cin >> desiredResult;

    // Initialize memoization table with default invalid values.
    memoizationTable.resize(_M, std::vector<std::vector<std::pair<bool, std::string>>>(_M, std::vector<std::pair<bool, std::string>>(_N + 1, {false, ""})));

    auto result = solve(0, _M - 1, desiredResult);
    if (result.first) {
        std::cout << "1" << std::endl << result.second << std::endl;
    } else {
        std::cout << "0" << std::endl;
    }

    return 0;
}

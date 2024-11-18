#include <cstdio>
#include <string>
#include <vector>

// Define a struct to represent memoization entries.
struct MemoEntry {
    bool valid;
    std::string expr;
};

// Global variables for input data.
int _N, _M, desiredResult;
std::vector<std::vector<int>> operationTable;
std::vector<int> sequence;
std::vector<std::vector<std::vector<MemoEntry>>> memo;

// Recursive function to find the correct parenthesization.
MemoEntry solve(int i, int j, int target) {
    // Base case: when i == j, check if the element matches the target.
    if (i == j) {
        if (sequence[i] == target) {
            return {true, std::to_string(sequence[i])};
        } else {
            return {false, ""};
        }
    }

    // Check if the subproblem has already been computed.
    if (memo[i][j][target].valid) {
        return memo[i][j][target];
    }

    // Try to split the sequence between i and j.
    for (int k = j - 1; k >= j; --k) {
        for (int left = 1; left <= _N; ++left) {
            for (int right = 1; right <= _N; ++right) {
                MemoEntry leftResult = solve(i, k, left);
                MemoEntry rightResult = solve(k + 1, j, right);

                if (leftResult.valid && rightResult.valid) {
                    int combinedVal = operationTable[left - 1][right - 1];
                    if (combinedVal == target) {
                        // Found a valid solution; store and return it.
                        std::string expr = "(" + leftResult.expr + " " + rightResult.expr + ")";
                        memo[i][j][target] = {true, expr};
                        return memo[i][j][target];
                    }
                }
            }
        }
    }

    // No valid parenthesization found for this subproblem.
    memo[i][j][target] = {false, ""};
    return memo[i][j][target];
}

int main() {
    scanf("%d %d", &_N, &_M);

    operationTable.resize(_N, std::vector<int>(_N));
    for (int i = 0; i < _N; ++i) {
        for (int j = 0; j < _N; ++j) {
            scanf("%d", &operationTable[i][j]);
        }
    }

    sequence.resize(_M);
    for (int i = 0; i < _M; ++i) {
        scanf("%d", &sequence[i]);
    }

    scanf("%d", &desiredResult);

    // Initialize memoization table with default invalid values.
    memo.resize(_M, std::vector<std::vector<MemoEntry>>(_M, std::vector<MemoEntry>(_N + 1, {false, ""})));

    MemoEntry result = solve(0, _M - 1, desiredResult);
    if (result.valid) {
        printf("1\n%s\n", result.expr.c_str());
    } else {
        printf("0\n");
    }

    return 0;
}

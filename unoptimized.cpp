#include <iostream>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

int main() {
    int _N, _M, desiredResult;
    vector<vector<int>> operationTable;
    vector<int> sequence;

    // Reads the two sizes from the input
    cin >> _N >> _M;

    // Reads the lines that represent the results of the operations from the input
    operationTable.resize(_N, vector<int>(_N));
    for (int i = 0; i < _N; ++i) {
        for (int j = 0; j < _N; ++j) {
            cin >> operationTable[i][j];
        }
    }

    // Reads the sequence of integers to which the operation is applied from the input
    sequence.resize(_M, 0);
    for (int i = 0; i < _M; ++i) {
        cin >> sequence[i];
    }

    // Read the expected result from the input
    cin >> desiredResult;

    // DP table where dp[i][j] stores a vector of tuples (value, expression)
    vector<vector<vector<pair<int, string>>>> dp(_M, vector<vector<pair<int, string>>>(_M));

    // Base case: single elements
    for (int i = 0; i < _M; ++i) {
        dp[i][i].emplace_back(sequence[i], to_string(sequence[i]));
    }

    // Build solutions iteratively for subarrays of increasing length
    for (int length = 2; length <= _M; ++length) {  // length of the subarray
        for (int i = 0; i <= _M - length; ++i) {    // start index
            int j = i + length - 1;                // end index
            for (int k = i; k < j; ++k) {          // position to split
                for (const auto& left : dp[i][k]) {
                    for (const auto& right : dp[k + 1][j]) {
                        // Calculate the result using the table
                        int combined_val = operationTable[left.first - 1][right.first - 1]; // Adjust for 1-based index
                        string combined_expr = "(" + left.second + " " + right.second + ")";
                        dp[i][j].emplace_back(combined_val, combined_expr);
                    }
                }
            }
        }
    }

    // Extract valid expressions that match the target
    vector<string> valid_expressions;
    for (const auto& result : dp[0][_M - 1]) {
        if (result.first == desiredResult) {
            valid_expressions.push_back(result.second);
        }
    }

    if (!valid_expressions.empty()) {
        cout << "1" << endl << valid_expressions.back() << endl;
        return 0;
    } else {
        cout << "0" << endl;
        return 1;
    }
}

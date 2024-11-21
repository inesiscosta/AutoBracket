#include <iostream>
#include <string>
#include <vector>

int main() {
  // CIN/COUT optimizations to attempt to match SCANF/PRINTF
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  int _N, _M, desiredResult; // _N = size of a side of the operatorTable matrix, _M = length of the sequence
  std::vector<std::vector<int>> operatorTable;
  std::vector<int> sequence;

  std::cin >> _N >> _M;

  // Resize the operator table to _N x _N
  operatorTable.resize(_N, std::vector<int>(_N));
  for (int i = 0; i < _N * _N; ++i) {
    // Read the operator table values from stdin
    std::cin >> operatorTable[i / _N][i % _N];
  }

  // Initialize DP table and expressions table
  std::vector<std::vector<std::vector<bool>>> dp(_M, std::vector<std::vector<bool>>(_M, std::vector<bool>(_N + 1, false))); // Stores whether a specific result is achieved for a subsequence
  std::vector<std::vector<std::vector<std::string>>> expressions(_M, std::vector<std::vector<std::string>>(_M, std::vector<std::string>(_N + 1, ""))); // Stores the expression that achieves a specific result for a subsequence

  // Read the sequence
  sequence.resize(_M);
  for (int i = 0; i < _M; ++i) {
    std::cin >> sequence[i]; // Read the sequence values from stdin
    // All single elements are their own results and subexpressions
    dp[i][i][sequence[i]] = true; // Initialize DP table for single elements
    expressions[i][i][sequence[i]] = std::to_string(sequence[i]); // Initialize expressions for single elements
  }

  // Read the desired result from stdin
  std::cin >> desiredResult;

  // Process all sub-sequences of length 2 to _M
  for (int length = 2; length <= _M; ++length) {
    for (int i = _M - length; i >= 0; --i) { // Compute the start index of the subsequence
      int j = i + length - 1; // Compute the end index of the subsequence
      for (int k = j - 1; k >= i; --k) { // Try all possible split points
        for (int left = 1; left <= _N; ++left) { // Try all possible left operators
          if (!dp[i][k][left]) continue; // Skip if left part is not valid
          for (int right = 1; right <= _N; ++right) {
            if (!dp[k + 1][j][right]) continue; // Skip if right part is not valid
            int result = operatorTable[left - 1][right - 1]; // Compute the result using the operator table
            if (result == desiredResult && length == _M) {
              // If the result matches the desired result and the length is _M, print the expression
              std::cout << "1" << std::endl << "(" << expressions[i][k][left] << " " << expressions[k + 1][j][right] << ")" << std::endl;
              return 0; // Return 0 to indicate success
            }
            if (!dp[i][j][result]) {
              dp[i][j][result] = true; // Mark the result in the DP table as the one achieved from this subsequence
              expressions[i][j][result] = "(" + expressions[i][k][left] + " " + expressions[k + 1][j][right] + ")"; // Store the formatted expression
            }
          }
        }
      }
    }
  }

  // If no valid expression is found, print 0
  std::cout << "0" << std::endl;
  return 1; // Return 1 to indicate failure
}

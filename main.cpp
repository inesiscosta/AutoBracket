#include <iostream>
#include <string>
#include <vector>

int main() {
  // CIN/COUT optimizations to attempt to match SCANF/PRINTF
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  int n, m, desiredResult; // n = size of a side of the operatorTable matrix, m = length of the sequence

  std::cin >> n >> m;

  std::vector<std::vector<int>> operatorTable(n, std::vector<int>(n));
  std::vector<int> sequence(m);
  std::vector<std::vector<std::vector<bool>>> dp(m, std::vector<std::vector<bool>>(m, std::vector<bool>(n + 1, false))); // Stores whether a specific result is achieved for a subsequence
  std::vector<std::vector<std::vector<std::string>>> expressions(m, std::vector<std::vector<std::string>>(m, std::vector<std::string>(n + 1, ""))); // Stores the expression that achieves a specific result for a subsequence

  for (int i = 0; i < n * n; ++i) {
    std::cin >> operatorTable[i / n][i % n];
  }

  // Read the sequence
  for (int i = 0; i < m; ++i) {
    std::cin >> sequence[i]; // Read the sequence values from stdin
    // All single elements are their own results and subexpressions
    dp[i][i][sequence[i]] = true; // Initialize DP table for single elements
    expressions[i][i][sequence[i]] = std::to_string(sequence[i]); // Initialize expressions for single elements
  }

  // Read the desired result from stdin
  std::cin >> desiredResult;

  // Process all sub-sequences of length 2 to _M
  for (int length = 2; length <= m; ++length) {
    for (int i = m - length; i >= 0; --i) { // Compute the start index of the subsequence
      int j = i + length - 1; // Compute the end index of the subsequence
      for (int k = j - 1; k >= i; --k) { // Try all possible split points
        for (int left = 1; left <= n; ++left) { // Try all possible left operators
          if (!dp[i][k][left]) continue; // Skip if left part is not valid
          for (int right = 1; right <= n; ++right) {
            if (!dp[k + 1][j][right]) continue; // Skip if right part is not valid
            int result = operatorTable[left - 1][right - 1]; // Compute the result using the operator table
            if (result == desiredResult && length == m) {
              // If the result matches the desired result and the length is _M, print the expression
              std::cout << "1" << std::endl << "(" << expressions[i][k][left] << " " << expressions[k + 1][j][right] << ")" << std::endl;
              return 0;
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
  return 0;
}

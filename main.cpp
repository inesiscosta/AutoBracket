#include <iostream>
#include <vector>
#include <string>
#include <tuple>

std::string reconstruct(int i, int j, int result,
const std::vector<std::vector<std::vector<std::tuple<int, int, int, int>>>> &dp,
const std::vector<std::vector<int>> &operatorTable,
const std::vector<int> &sequence) {
  // Base case: If the subexpression is only one number it returns it self as a string.
  if (i == j)
    return std::to_string(sequence[i] + 1); // 1-Base Index adjustment for output
  for (const auto &finalVector : dp[i][j])
    if (std::get<0>(finalVector) == result) {
      int k = std::get<1>(finalVector);
      return "(" +
      reconstruct(i, k, std::get<2>(finalVector), dp, operatorTable, sequence) + " " +
      reconstruct(k + 1, j, std::get<3>(finalVector), dp, operatorTable, sequence) +
      ")";
    }
  return ""; // This should never happen.
}

int main() {
  // IOStream performance flags so it is closer to using stdio functions (scanf and printf)
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  // n - matrix size; m - sequence length
  int n, m;
  std::cin >> n >> m;

  // Reads the matrix from stdin and adjusts the values to 0-Base Index
  std::vector<std::vector<int>> operatorTable(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      std::cin >> operatorTable[i][j], --operatorTable[i][j];

  std::vector<int> sequence(m);
  // dp[i][j] = {result, k, leftResult, rightResult}
  std::vector<std::vector<std::vector<std::tuple<int, int, int, int>>>> dp
  (m, std::vector<std::vector<std::tuple<int, int, int, int>>>(m));

  // DP initialization
  for (int i = 0; i < m; ++i) {
    std::cin >> sequence[i], --sequence[i]; // 0-Base Index adjustment
    dp[i][i].emplace_back(sequence[i], -1, -1, -1);
  }

  int targetResult;
  // Reads the target result from stdin and adjusts the value to 0-Base Index
  std::cin >> targetResult, --targetResult;

  for (int len = 2; len <= m; ++len)
    // Iterate over all possible starting points of subexpressions
    for (int i = 0; i <= m - len; ++i) {
      int j = i + len - 1; // Ending point of the current subexpression
      // Track used results to avoid overwriting better expressions for the same result
      std::vector<bool> used(n, false);
      // Iterate over all possible split points
      for (int k = j - 1; k >= i && dp[i][j].size() <= static_cast<size_t>(n); --k)
        // Iterate over all possible results of the left subexpression
        for (const auto &left : dp[i][k]) {
          int leftResult = std::get<0>(left);
          // Iterate over all possible results of the right subexpression
          for (const auto &right : dp[k + 1][j]) {
            int rightResult = std::get<0>(right);
            int result = operatorTable[leftResult][rightResult];
            if (!used[result]) { // If this result has not been used yet
              dp[i][j].emplace_back(result, k, leftResult, rightResult); // Store the result, the split point and the left and right results used
              used[result] = true; // Mark this result as used
            }
            if (dp[i][j].size() >= static_cast<size_t>(n)) break; // Stop if we have enough results
          }
          if (dp[i][j].size() >= static_cast<size_t>(n)) break; // Stop if we have enough results
        }
    }

  for (const auto &finalVector : dp[0][m - 1])
    if (std::get<0>(finalVector) == targetResult) {
      std::cout << 1 << std::endl;
      // Calls recursive function to reconstruct the final expression
      std::string parenthesizedSequence = reconstruct
      (0, m - 1, targetResult, dp, operatorTable, sequence);
      std::cout << parenthesizedSequence << std::endl;
      return 0;
    }
  std::cout << 0 << std::endl; // Prints 0 to stdout if no solution is found
  return 0;
}

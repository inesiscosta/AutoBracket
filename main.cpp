#include <iostream>
#include <vector>
#include <string>

std::string reconstruct(int i, int j, const std::vector<std::vector<std::vector<std::pair<int, int>>>> &dp, const std::vector<std::vector<int>> &operatorTable, const std::vector<int> &sequence) {
  // Base case: If the subexpression is only one number it returns it self
  if (i == j) {
    return std::to_string(sequence[i] + 1); // 1-Base Index adjustment for output
  }

  // Gets the k split point that gives the desired result
  int k = dp[i][j].back().second;

  std::string leftExpr = reconstruct(i, k, dp, operatorTable, sequence);
  std::string rightExpr = reconstruct(k + 1, j, dp, operatorTable, sequence);
  return "(" + leftExpr + " " + rightExpr + ")";
}

int main() {
  // IOStream performance flags so it is closer to using stdio functions (scanf and printf)
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  // n - Matrix size; m - sequence length
  int n, m;
  std::cin >> n >> m;

  // Reads the matrix from stdin and adjusts the values to 0-Base Index
  std::vector<std::vector<int>> operatorTable(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      std::cin >> operatorTable[i][j], --operatorTable[i][j];

  std::vector<int> sequence(m);
  // dp[i][j] = {result, k}
  std::vector<std::vector<std::vector<std::pair<int, int>>>> dp(m, std::vector<std::vector<std::pair<int, int>>>(m, std::vector<std::pair<int, int>>(n, {-1, -1})));

  // DP base case initialization
  for (int i = 0; i < m; ++i) {
    std::cin >> sequence[i], --sequence[i];
    dp[i][i].push_back({sequence[i], i});
  }

  // Reads the target result from stdin and adjusts the value to 0-Base Index
  int targetResult;
  std::cin >> targetResult, --targetResult;

  for (int len = 2; len <= m; ++len)
    for (int i = 0; i <= m - len; ++i) {
      int j = i + len - 1;
      int results_count = 0;
      std::vector<bool> used(n, false);
      for (int k = j - 1; k >= i && results_count <= n; --k) {
        for (auto left : dp[i][k]) {
          if (left.first == -1) continue;
          for (auto right : dp[k + 1][j]) {
            if (right.first == -1) continue;
            int result = operatorTable[left.first][right.first];
            if (!used[result]) {
              dp[i][j].push_back({result, k});
              ++results_count;
              used[result] = true;
            }
            if (results_count >= n) break;
          }
          if (results_count >= n) break;
        }
      }
    }

  for (auto finalVector : dp[0][m - 1]) {
    if (finalVector.first == targetResult) {
      std::cout << 1 << std::endl;
      std::string parenthesizedSequence = reconstruct(0, m - 1, dp, operatorTable, sequence); // Calls recursive unction to reconstruct the solution expression
      std::cout << parenthesizedSequence << std::endl;
      return 0;
    }
  }
  std::cout << 0 << std::endl; // Prints 0 to stdout if no solution is found
  return 0;
}
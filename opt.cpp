#include <climits>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>


// This code is only finding and verifying if the most optimal expression is equal to the target result. It is not finding the most optimal expression for the target result.
// Also currently finding the rightmost expression instead of leftmost.
int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> operatorTable(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) std::cin >> operatorTable[i][j];

  std::vector<int> sequence(m);
  for (int i = 0; i < m; ++i) std::cin >> sequence[i];

  int targetResult;
  std::cin >> targetResult;

  std::vector<std::vector<std::tuple<std::string, int, int>>> dp(m, std::vector<std::tuple<std::string, int, int>>(m, std::make_tuple("", INT_MIN, -1)));

  for (int i = 0; i < m; ++i) dp[i][i] = std::make_tuple(std::to_string(sequence[i]), 0, sequence[i]);

  for (int len = 2; len <= m; ++len) {
    for (int i = 0; i <= m - len; ++i) {
      int j = i + len - 1;
      std::string expression = "";
      int score = INT_MIN;
      int result = -1;

      for (int k = i; k < j; ++k) {
        int totalScore = std::get<1>(dp[i][k]) + std::get<1>(dp[k + 1][j]) + (j - k);
        if (totalScore > score) {
            int leftResult = std::get<2>(dp[i][k]);
            int rightResult = std::get<2>(dp[k + 1][j]);
            if (leftResult == -1 || rightResult == -1) continue;
            result = operatorTable[leftResult - 1][rightResult - 1];
            expression = "(" + std::get<0>(dp[i][k]) + " " + std::get<0>(dp[k + 1][j]) + ")";
            score = totalScore;
        }
      }
      dp[i][j] = std::make_tuple(expression, score, result);
    }
  }

  std::tuple<std::string, int, int> solution = dp[0][m - 1];
  if (std::get<2>(solution) == targetResult) {
    std::cout << 1 << std::endl << std::get<0>(solution) << std::endl;
  } else {
    std::cout << 0 << std::endl;
  }
  return 0;
}

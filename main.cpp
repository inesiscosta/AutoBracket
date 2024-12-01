#include <iostream>
#include <vector>
#include <string>
#include <tuple>

std::string reconstruct(int i, int j, int result,
const std::vector<std::vector<std::vector<std::tuple<int, int, int, int>>>> &dp,
const std::vector<std::vector<int>> &operatorTable,
const std::vector<int> &sequence) {

  if (i == j) {
    return std::to_string(sequence[i] + 1); // 1-Base Index adjustment for output
  }

  for (const auto &finalVector : dp[i][j]) {
    if (std::get<0>(finalVector) == result) {
      int k = std::get<1>(finalVector);
      return "(" +
      reconstruct(i, k, std::get<2>(finalVector), dp, operatorTable, sequence) + " " +
      reconstruct(k + 1, j, std::get<3>(finalVector), dp, operatorTable, sequence) +
      ")";
    }
  }
  return "";  // This should never happen.
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> operatorTable(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i)
  for (int j = 0; j < n; ++j)
    std::cin >> operatorTable[i][j], --operatorTable[i][j];

  std::vector<int> sequence(m);
  std::vector<std::vector<std::vector<std::tuple<int, int, int, int>>>> dp
  (m, std::vector<std::vector<std::tuple<int, int, int, int>>>(m));

  for (int i = 0; i < m; ++i) {
    std::cin >> sequence[i], --sequence[i];
    dp[i][i].emplace_back(sequence[i], -1, -1, -1);
  }

  int targetResult;
  std::cin >> targetResult, --targetResult;

  for (int len = 2; len <= m; ++len) {
  for (int i = 0; i <= m - len; ++i) {
    int j = i + len - 1;
    std::vector<bool> used(n, false);
    for (int k = j - 1; k >= i && dp[i][j].size() <= static_cast<size_t>(n); --k) {
      for (const auto &left : dp[i][k]) {
        int leftResult = std::get<0>(left);
        for (const auto &right : dp[k + 1][j]) {
          int rightResult = std::get<0>(right);
          int result = operatorTable[leftResult][rightResult];
          if (!used[result]) {
            dp[i][j].emplace_back(result, k, leftResult, rightResult);
            used[result] = true;
          }
          if (dp[i][j].size() >= static_cast<size_t>(n)) break;
          }
          if (dp[i][j].size() >= static_cast<size_t>(n)) break;
        }
      }
    }
  }

  for (const auto &finalVector : dp[0][m - 1]) {
    if (std::get<0>(finalVector) == targetResult) {
      std::cout << 1 << std::endl;
      std::string parenthesizedSequence = reconstruct
      (0, m - 1, targetResult, dp, operatorTable, sequence);
      std::cout << parenthesizedSequence << std::endl;
      return 0;
    }
  }
  std::cout << 0 << std::endl;
  return 0;
}

#include <iostream>
#include <vector>
#include <string>

// Need to change how the reconstruct function works the rest is fine. Function needs to prioritize highest k values.
std::string reconstruct(int i, int j, int result, const std::vector<std::vector<std::vector<int>>> &dp, const std::vector<std::vector<int>> &operatorTable, const std::vector<int> &sequence) {
  if (i == j)
    return std::to_string(sequence[i] + 1);

  int k = -1;
  int leftResult = -1, rightResult = -1;

  for (int currentK = j - 1; currentK >= i; --currentK) {
    for (int left = operatorTable.size() - 1; left >= 0 && leftResult == -1; --left) {
      for (int right = operatorTable.size() - 1; right >= 0; --right) {
        if (dp[i][currentK][left] != -1 && dp[currentK + 1][j][right] != -1 && operatorTable[left][right] == result) {
          k = currentK;
          leftResult = left;
          rightResult = right;
          break;
        }
      }
    }
    if (leftResult != -1) break; // If a valid k is found, break out of the loop
  }

  std::string leftExpr = reconstruct(i, k, leftResult, dp, operatorTable, sequence);
  std::string rightExpr = reconstruct(k + 1, j, rightResult, dp, operatorTable, sequence);
  return "(" + leftExpr + " " + rightExpr + ")";
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
  std::vector<std::vector<std::vector<int>>> dp(m, std::vector<std::vector<int>>(m, std::vector<int>(n, -1)));

  for (int i = 0; i < m; ++i) {
    std::cin >> sequence[i], --sequence[i];
    dp[i][i][sequence[i]] = i;
  }

  int targetResult;
  std::cin >> targetResult, --targetResult;

  for (int len = 2; len <= m; ++len)
    for (int i = 0; i <= m - len; ++i) {
      int j = i + len - 1;
      int results_count = 0;
      for (int k = j - 1; k >= i && results_count < n; --k)
        for (int left = 0; left < n && results_count < n; ++left)
          if (dp[i][k][left] != -1)
            for (int right = 0; right < n && results_count < n; ++right)
              if (dp[k + 1][j][right] != -1) {
                int result = operatorTable[left][right];
                if (dp[i][j][result] == -1 || dp[i][j][result] < k) {
                  dp[i][j][result] = k;
                  ++results_count;
                }
              }
    }

  if (dp[0][m - 1][targetResult] == -1) {
    std::cout << 0 << std::endl;
  } else {
    std::string result = reconstruct(0, m - 1, targetResult, dp, operatorTable, sequence);
    std::cout << 1 << std::endl << result << std::endl;
  }
  return 0;
}

#include <iostream>
#include <vector>
#include <string>

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
  // dp[i][j] = {result, k}
  std::vector<std::vector<std::vector<std::pair<int, int>>>> dp(m, std::vector<std::vector<std::pair<int, int>>>(m, std::vector<std::pair<int, int>>(n, {-1, -1})));

  for (int i = 0; i < m; ++i) {
    std::cin >> sequence[i], --sequence[i];
    dp[i][i].push_back({sequence[i], i});
  }

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
      std::string parenthesizedSequence = reconstruct(0, m - 1, targetResult, dp, sequence, operatorTable);
      std::cout << parenthesizedSequence << std::endl;
      return 0;
    }
  }
  std::cout << 0 << std::endl;
  return 0;
}
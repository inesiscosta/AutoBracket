#include <cstdio>
#include <string>
#include <vector>

int main() {
  int _N, _M, desiredResult;
  std::vector<std::vector<int>> operationTable;
  std::vector<int> sequence;

  scanf("%d %d", &_N, &_M);

  operationTable.resize(_N, std::vector<int>(_N));
  for (int i = 0; i < _N; ++i) {
    for (int j = 0; j < _N; ++j) {
      scanf("%d", &operationTable[i][j]);
    }
  }

  // Initialize dp table
  std::vector<std::vector<std::vector<bool>>> dp(_M, std::vector<std::vector<bool>>(_M, std::vector<bool>(_N + 1, false)));
  std::vector<std::vector<std::vector<std::string>>> expr(_M, std::vector<std::vector<std::string>>(_M, std::vector<std::string>(_N + 1, "")));

  sequence.resize(_M);
  for (int i = 0; i < _M; ++i) {
    scanf("%d", &sequence[i]);
    dp[i][i][sequence[i]] = true;
    expr[i][i][sequence[i]] = std::to_string(sequence[i]);
  }

  scanf("%d", &desiredResult);

  for (int length = 2; length <= _M; ++length) {
    for (int i = _M - length; i >= 0; --i) {
      int j = i + length - 1;
      for (int k = j - 1; k >= i; --k) {
        for (int left = 1; left <= _N; ++left) {
          for (int right = 1; right <= _N; ++right) {
            if (dp[i][k][left] && dp[k + 1][j][right]) {
              int combined_val = operationTable[left - 1][right - 1];
              if (!dp[i][j][combined_val]) {
                dp[i][j][combined_val] = true;
                expr[i][j][combined_val] =
                "(" + expr[i][k][left] + " " + expr[k + 1][j][right] + ")";
                if (combined_val == desiredResult && length == _M) {
                  printf("1\n%s\n", expr[i][j][combined_val].c_str());
                  return 0;
                }
              }
            }
          }
        }
      }
    }
  }

  printf("0\n");
  return 0;
}
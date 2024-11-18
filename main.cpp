#include <string>
#include <vector>
#include <cstdio>

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

  sequence.resize(_M);
  for (int i = 0; i < _M; ++i) {
    scanf("%d", &sequence[i]);
  }

  scanf("%d", &desiredResult);

  std::vector<std::vector<std::vector<std::pair<int, std::string>>>> resultsTable(
  _M, std::vector<std::vector<std::pair<int, std::string>>>(_M));

  for (int i = 0; i < _M; ++i) {
    resultsTable[i][i].emplace_back(sequence[i], std::to_string(sequence[i]));
  }

  for (int length = 2; length <= _M; ++length) {
    for (int i = _M - length; i >= 0; --i) {
      int j = i + length - 1;
      for (int k = j - 1; k >= i; --k) {
        for (const auto& left : resultsTable[i][k]) {
          for (const auto& right : resultsTable[k + 1][j]) {
            int combined_val = operationTable[left.first - 1][right.first - 1];
            std::string combined_expr = "(" + left.second + " " + right.second + ")";
            resultsTable[i][j].emplace_back(combined_val, combined_expr);
            if (combined_val == desiredResult && length == _M) {
              printf("1\n%s\n", combined_expr.c_str());
              return 0;
            }
          }
        }
      }
    }
  }
  printf("0\n");
  return 0;
}

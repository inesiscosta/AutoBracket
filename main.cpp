#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  int _N, _M, desiredResult;
  vector<vector<int>> operationTable;
  vector<int> sequence;

  cin >> _N >> _M;

  operationTable.resize(_N, vector<int>(_N));
  for (int i = 0; i < _N; ++i) {
    for (int j = 0; j < _N; ++j) {
      cin >> operationTable[i][j];
    }
  }

  sequence.resize(_M);
  for (int i = 0; i < _M; ++i) {
    cin >> sequence[i];
  }

  cin >> desiredResult;

  vector<vector<vector<pair<int, string>>>> dp(
  _M, vector<vector<pair<int, string>>>(_M));

  for (int i = 0; i < _M; ++i) {
    dp[i][i].emplace_back(sequence[i], to_string(sequence[i]));
  }

  string correct_expression;
  bool final_found = false;
  for (int length = 2; length <= _M; ++length) {
    bool found = false;
    for (int i = _M - length; i >= 0 && !found; --i) {
      int j = i + length - 1;
      for (int k = j - 1; k >= i && !found; --k) {
        for (const auto& left : dp[i][k]) {
          for (const auto& right : dp[k + 1][j]) {
            int combined_val = operationTable[left.first - 1][right.first - 1];
            if (combined_val == desiredResult || dp[i][j].size() < 10) {
              string combined_expr =
              "(" + left.second + " " + right.second + ")";
              bool exists = false;
              for (const auto& p : dp[i][j]) {
                if (p.first == combined_val) {
                  exists = true;
                  break;
                }
              }
              if (!exists) {
                dp[i][j].emplace_back(combined_val, combined_expr);
              }
              if (combined_val == desiredResult && length == _M) {
                correct_expression = combined_expr;
                found = true;
                break;
              }
            }
          }
        }
        if (found) break;
      }
    }
    if (found && length == _M) {
      final_found = true;
      break;
    }
  }
  if (final_found) {
    cout << "1" << std::endl << correct_expression << endl;
    return 0;
  }
  cout << "0" << endl;
  return 0;
}
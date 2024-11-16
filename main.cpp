#include <iostream>
#include<vector>

int main() {

  int _N, _M, desiredResult;
  std::vector<std::vector<int>> operationTable;
  std::vector<int> sequence;

  /* FUNCTION readInput */
  //---------------------------------------------------------------
  // Reads the two sizes from the input
  std::cin >> _N >> _M;

  // Reads the lines that represnt the results of the operations from the input
  operationTable.resize(_N, std::vector<int>(_N));
  for (int i = 0; i < _N; ++i) {
    for (int j = 0; j < _N; ++j) {
      std::cin >> operationTable[i][j];
    }
  }

  // Reads the sequence of integers to wich the operation is applied from the input
  sequence.resize(_M, 0);
  for (int i = 0; i < _M; ++i) {
    std::cin >> sequence[i];
  }
  // Read the expeted result from the input
  std::cin >> desiredResult;
  //---------------------------------------------------------------
  /* END FUNCTION readInput */

  /* FUNCTION parentization */
  //---------------------------------------------------------------
  // Empty string to store the parentized sequence
  std::string parentizedSequence;

  int len_sequence = sequence.size();
  std::vector<std::vector<std::vector<int>>> dp(len_sequence, std::vector<std::vector<int>>(len_sequence));
  std::vector<std::vector<std::vector<std::string>>> parentizations(len_sequence, std::vector<std::vector<std::string>>(len_sequence));

  bool found = false;
  int result = 0;

  for (int i = 0; i < len_sequence; ++i) {
    dp[i][i] = {sequence[i]};
    parentizations[i][i] = {std::to_string(sequence[i])};
  }

  for (int len = 2; len <= len_sequence && !found; ++len) {
    for (int i = 0; i <= len_sequence - len && !found; ++i) {
      int j = i + len - 1;
      for (int k = i; k < j && !found; ++k) {
        for (int left : dp[i][k]) {
          for (int right : dp[k + 1][j]) {
            result = operationTable[left-1][right-1];
            dp[i][j].push_back(result);
            parentizations[i][j].push_back("(" + parentizations[i][k][0] + " " + parentizations[k + 1][j][0] + ")");
            if (result == desiredResult) {
              parentizedSequence = parentizations[i][j].back();
              found = true;
              break;
            }
          }
        }
      }
    }
  }
  //---------------------------------------------------------------
  /* END FUNCTION parentization

  // Print found result and parenthisised expression
  std::cout << result << std::endl << parentizedSequence << std::endl;
}

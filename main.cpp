#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <string>

int main() {
  int _N, _M, desiredResult;
  std::vector<std::vector<int>> operationTable;
  std::vector<int> sequence;

  /* FUNCTION readInput */
  //---------------------------------------------------------------
  // Reads the two sizes from the input
  std::cin >> _N >> _M;

  // Reads the lines that represent the results of the operations from the input
  operationTable.resize(_N, std::vector<int>(_N));
  for (int i = 0; i < _N; ++i) {
    for (int j = 0; j < _N; ++j) {
      std::cin >> operationTable[i][j];
    }
  }

  // Reads the sequence of integers to which the operation is applied from the input
  sequence.resize(_M, 0);
  for (int i = 0; i < _M; ++i) {
    std::cin >> sequence[i];
  }

  // Read the expected result from the input
  std::cin >> desiredResult;
  //---------------------------------------------------------------
  /* END FUNCTION readInput */

  /* FUNCTION parentization */
  //---------------------------------------------------------------
  // Empty string to store the parenthesized sequence
  std::string parentizedSequence;
  bool found = false;

  int len_sequence = sequence.size();
  std::vector<std::vector<int>> dp(len_sequence, std::vector<int>(len_sequence, -1)); // Dynamic programming table
  std::vector<std::vector<std::string>> parentizations(len_sequence, std::vector<std::string>(len_sequence));

  for (int i = 0; i < len_sequence; ++i) {
    dp[i][i] = sequence[i];
    parentizations[i][i] = std::to_string(sequence[i]);
  }
  
  for (int len = 2; len <= len_sequence; ++len) {
    for (int i = 0; i <= len_sequence - len; ++i) {
      int j = i + len - 1;
      for (int k = i; k < j; ++k) {
        int left = dp[i][k];
        int right = dp[k + 1][j];
        if (left != -1 && right != -1) {
          int result = operationTable[left-1][right-1];
          dp[i][j] = result;
          parentizations[i][j] = "(" + parentizations[i][k] + " " + parentizations[k + 1][j] + ")";
          if (result == desiredResult && len == len_sequence) {
            parentizedSequence = parentizations[i][j];
            found = true;
          }
        }
      }
    }
  }

  //---------------------------------------------------------------
  /* END FUNCTION parentization   */
  
  // Print found result and parenthisised expression
  if (found) {
      std::cout << "1" << std::endl << parentizedSequence << std::endl;
      return 0;
  }
  std::cout << "0" << std::endl;
  return 1;
}

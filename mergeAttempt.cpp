#include <iostream>
#include <string>
#include <vector>

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

  // Reads the sequence of integers to which the operation is applied from the
  // input
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
  std::vector<std::vector<std::vector<std::string>>> parentizations(len_sequence, std::vector<std::vector<std::string>>(len_sequence));
  std::vector<std::vector<int>> resultsTable(len_sequence, std::vector<int>(len_sequence, -1));

  // Initialize base case: each number is its own result
  for (int i = 0; i < len_sequence; i++) {
    parentizations[i][i].push_back(std::to_string(sequence[i]));
    resultsTable[i][i] = sequence[i];
  }

  for (int len = 2; len <= len_sequence && !found; len++) {
    for (int left = 0; left <= len_sequence - len && !found; left++) {
      int right = left + len - 1;
      for (int mid = right - 1; mid >= left && !found; mid--) {
        for (const std::string& leftStr : parentizations[left][mid]) {
          for (const std::string& rightStr : parentizations[mid + 1][right]) {
            std::string combined = "(" + leftStr + " " + rightStr + ")";
            parentizations[left][right].push_back(combined);
            int result = operationTable[resultsTable[left][mid] - 1][resultsTable[mid + 1][right] - 1];
            resultsTable[left][right] = result;
            if (len == len_sequence && result == desiredResult) {
              parentizedSequence = combined;
              found = true;
            }
            if (found) break;
          }
          if (found) break;
        }
      }
    }
  }

  //---------------------------------------------------------------
  /* END FUNCTION parentization   */

  // Print found result and parenthesized expression
  if (found) {
    std::cout << "1" << std::endl << parentizedSequence << std::endl;
    return 0;
  }
  std::cout << "0" << std::endl;
  return 1;
}

#include <string>
#include <vector>
#include <cstdio>

int main() {
  int _N, _M, desiredResult;
  std::vector<std::vector<int>> operationTable;
  std::vector<int> sequence;

  // Reads the two sizes from the input
  scanf("%d %d", &_N, &_M);

  // Reads the lines that represent the results of the operations from the input
  operationTable.resize(_N, std::vector<int>(_N));
  for (int i = 0; i < _N; ++i) {
    for (int j = 0; j < _N; ++j) {
      scanf("%d", &operationTable[i][j]);
    }
  }

  // DP table where dp[i][j] stores a vector of tuples (value, expression)
  std::vector<std::vector<std::vector<std::pair<int, std::string>>>> resultsTable(
  _M, std::vector<std::vector<std::pair<int, std::string>>>(_M));
  
  // Reads the sequence of integers to which the operation is applied from the input
  sequence.resize(_M);
  for (int i = 0; i < _M; ++i) {
    scanf("%d", &sequence[i]);
    // Base case: single elements
    resultsTable[i][i].emplace_back(sequence[i], std::to_string(sequence[i]));
  }

  // Read the expected result from the input
  scanf("%d", &desiredResult);

  // Build solutions iteratively for subarrays of increasing length
  for (int length = 2; length <= _M; ++length) {  // length of the subarray
    for (int i = _M - length; i >= 0; --i) {      // start index running in reverse
      int j = i + length - 1;                     // end index running in reverse
      for (int k = j - 1; k >= i; --k) {          // position to split
        for (const auto& left : resultsTable[i][k]) {
          for (const auto& right : resultsTable[k + 1][j]) {
            // Calculate the result using the table
            int combined_val = operationTable[left.first - 1][right.first - 1]; // Adjust for 1-based index
            std::string combined_expr = "(" + left.second + " " + right.second + ")";
            resultsTable[i][j].emplace_back(combined_val, combined_expr);
            // Checks if the solution is valid its result and length
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

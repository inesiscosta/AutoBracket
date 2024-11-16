#include <iostream>
#include<vector>

int main() {

  int N, M, result;
  std::vector<std::vector<int>> table;
  std::vector<int> sequence;

  // Reads the two sizes from the input
  std::cin >> N >> M;

  // Reads the lines that represnt the results of the operations from the input
  table.resize(N, std::vector<int>(N));
  for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
          std::cin >> table[i][j];
      }
  }

  // Reads the sequence of integers to wich the operation is applied from the input
  sequence.resize(M, 0);
  for (int i = 0; i < M; ++i) {
      std::cin >> sequence[i];
  }
  // Read the expeted result from the input
  std::cin >> result;

  // Checks if it is possible to parenthesize
  while (sequence.size() > 1) { // Acaba quando todas as operacoes foram feitas na sequencia sobra um numero
      std::vector<int> new_sequence; // Vetor temporario para guardar o resultado da primeira operacao e os restantes elementos da sequencia
      for (size_t i = 0; i < sequence.size() - 1; ++i) { // Percorre a sequencia mas incrementa primeiro de forma a evitar seg fault (nao gosto muito)
          int new_value = table[sequence[i] - 1][sequence[i + 1] - 1]; // Usa a tabela para ir buscar o valor correspondente a operacao (se calhar guardar a table sem indice para coincidir??)
          new_sequence.push_back(new_value);
      }
      sequence = new_sequence; // A sequencia passa a ser a nova sequencia resultado mais os restantes
  }

  // Print the final item in the sequence
  std::cout << sequence[0] << std::endl;
}
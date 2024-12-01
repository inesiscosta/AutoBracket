import os
import time
import csv
import subprocess
import psutil

def get_test_sizes(test_file):
    with open(test_file, 'r', encoding='utf-8') as file:
        first_line = file.readline().strip()
        matrix_size, sequence_size = map(int, first_line.split()[:2])
        return matrix_size, sequence_size

def run_program(test_file):
    start_time = time.time()
    process = subprocess.Popen(['./main'], stdin=open(test_file, 'r', encoding='utf-8'), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    memory_usage = psutil.Process(process.pid).memory_info().rss / 1024 ** 2  # This conversion doesnt seam right
    process.wait()
    end_time = time.time()
    execution_time = end_time - start_time
    return execution_time, memory_usage

def main():
    tests_folder = 'tests'
    results = []

    for test_file in os.listdir(tests_folder):
        if test_file.endswith('.in'):
            test_path = os.path.join(tests_folder, test_file)
            matrix_size, sequence_size = get_test_sizes(test_path)
            execution_time, memory_usage = run_program(test_path)
            results.append([test_file, matrix_size, sequence_size, execution_time, memory_usage])

    with open('results.csv', 'w', newline='', encoding='utf-8') as csvfile:
        csv_writer = csv.writer(csvfile)
        csv_writer.writerow(['Test File', 'OperationTable Size', 'Sequence Size', 'Execution Time (s)', 'Memory Usage (MB)'])
        csv_writer.writerows(results)

if __name__ == '__main__':
    main()
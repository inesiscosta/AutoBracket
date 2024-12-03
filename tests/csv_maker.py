import os
import time
import csv
import subprocess
import platform
import threading
import psutil

def get_test_sizes(test_file):
    with open(test_file, 'r', encoding='utf-8') as file:
        first_line = file.readline().strip()
        matrix_size, sequence_size = map(int, first_line.split()[:2])
        return matrix_size, sequence_size

def monitor_memory(process, memory_usage_list):
    while process.poll() is None:
        memory_usage_list.append(psutil.Process(process.pid).memory_info().rss / 1024 ** 2)
        time.sleep(0.1)  # Adjust the sleep time as needed

def run_program(test_file):
    start_time = time.time()
    process = subprocess.Popen(['../src/main'], stdin=open(test_file, 'r', encoding='utf-8'), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    memory_usage_list = []
    memory_thread = threading.Thread(target=monitor_memory, args=(process, memory_usage_list))
    memory_thread.start()
    
    process.wait()
    memory_thread.join()
    
    end_time = time.time()
    execution_time = end_time - start_time
    peak_memory_usage = max(memory_usage_list) if memory_usage_list else 0
    
    return execution_time, peak_memory_usage

def main():
    tests_folder = os.path.dirname(os.path.abspath(__file__))
    results = []

    for test_file in os.listdir(tests_folder):
        if test_file.endswith('.in'):
            test_path = os.path.join(tests_folder, test_file)
            matrix_size, sequence_size = get_test_sizes(test_path)
            execution_time, memory_usage = run_program(test_path)
            results.append([test_file, matrix_size, sequence_size, execution_time, memory_usage])

    platform_name = platform.system().lower()
    architecture = platform.machine().lower()
    with open( f'results_{platform_name}_{architecture}.csv', 'w', newline='', encoding='utf-8') as csvfile:
        csv_writer = csv.writer(csvfile)
        csv_writer.writerow(['Test File', 'OperationTable Size', 'Sequence Size', 'Execution Time (s)', 'Memory Usage (MB)'])
        csv_writer.writerows(results)

if __name__ == '__main__':
    main()
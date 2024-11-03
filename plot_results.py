import matplotlib.pyplot as plt
import pandas as pd

# Load the results from the CSV file
# result_1 = pd.read_csv('load_test_results_httperf_8.csv')
# result_2 = pd.read_csv('load_test_results_httperf_16.csv')
# result_3 = pd.read_csv('load_test_results_httperf_24.csv')
# result_4 = pd.read_csv('load_test_results_httperf_32.csv')
# result_5 = pd.read_csv('load_test_results_httperf_40.csv')

result_1 = pd.read_csv('load_test_results_ab_1_8.csv')
result_2 = pd.read_csv('load_test_results_ab_1_32.csv')
result_3 = pd.read_csv('load_test_results_ab_1_64.csv')
result_4 = pd.read_csv('load_test_results_ab_1_128.csv')

# Combine all results to find the global min and max
all_results = pd.concat([result_1, result_2, result_3, result_4])
y_min = all_results['RequestsPerSecond'].min()
y_max = all_results['RequestsPerSecond'].max()

# Plot the results
plt.plot(result_1['RequestRate'], result_1['RequestsPerSecond'], label='8')
plt.plot(result_2['RequestRate'], result_2['RequestsPerSecond'], label='32')
plt.plot(result_3['RequestRate'], result_3['RequestsPerSecond'], label='64')
plt.plot(result_4['RequestRate'], result_4['RequestsPerSecond'], label='128')
# plt.plot(result_5['RequestRate'], result_5['RequestsPerSecond'], label='40')

plt.xlabel('Concurrency')
plt.ylabel('Throughput (Requests Per Second)')
plt.ylim(y_min, y_max)  # Set the y-axis limits
plt.legend()
plt.grid(True)
plt.savefig('comparison_ab.png')
plt.show()
# README: Instructions for Executing the Server, Sending Requests, and Performing Load Testing

## **1. Overview**
This README provides step-by-step instructions on how to execute the server, send requests for various endpoints, and perform load testing for the functions implemented in Parts 5a and 5b. It also includes information about the load test scripts used to generate results and how to plot these results.

## **2. Prerequisites**
- **C Compiler**: You need GCC or another C compiler to compile the server code.
- **CivetWeb Library**: Make sure you have downloaded and compiled the CivetWeb library.
- **Apache Benchmark (ab)**: Install Apache Benchmark for load testing. Use the following command to install it:
  ```bash
  sudo apt-get install apache2-utils
  ```
- **Python**: For generating load test plots, Python 3 along with the `matplotlib` and `pandas` libraries is required.

## **3. Part 5a: Starting the Server**

### **Step 1: Compile the Server Code**
Use the provided `Makefile` to compile the server code. The `Makefile` includes all necessary dependencies and instructions:

#### **Makefile**
```Makefile
CC = gcc
CFLAGS = -I. -pthread
LDFLAGS = -lm

all: cflask

cflask: cflask.c functions.c url_map.c libcivetweb.a
	$(CC) $(CFLAGS) cflask.c functions.c url_map.c libcivetweb.a -o cflask $(LDFLAGS)

clean:
	rm -f cflask
```

To compile the server, simply run:
```bash
make
```
This command will create an executable named `cflask`.

### **Step 2: Start the Server**
Run the server with the desired port and thread pool size.
```bash
./cflask <port> <num_threads>
```
- Example:
  ```bash
  ./cflask 8080 8
  ```
  This starts the server on port 8080 with 8 worker threads.

## **4. Part 5a: Sending Requests to the Server**

You can use `curl` or a browser to send requests to various URLs as described below:

### **Available Endpoints**
1. **Index Page** (`/`):
   ```bash
   curl http://localhost:8080/
   ```
2. **Square Function** (`/square`):
   - Example with a parameter (`num=3`):
     ```bash
     curl "http://localhost:8080/square?num=3"
     ```
   - Default (no parameter):
     ```bash
     curl http://localhost:8080/square
     ```
3. **Cube Function** (`/cube`):
   - Example with a parameter (`num=7`):
     ```bash
     curl "http://localhost:8080/cube?num=7"
     ```
   - Default (no parameter):
     ```bash
     curl http://localhost:8080/cube
     ```
4. **Hello World** (`/helloworld`):
   - Example with a parameter (`str=Ashwin`):
     ```bash
     curl "http://localhost:8080/helloworld?str=Ashwin"
     ```
   - Default (no parameter):
     ```bash
     curl http://localhost:8080/helloworld
     ```
5. **PingPong** (`/pingpong`):
   - Example with a parameter (`str=cs695`):
     ```bash
     curl "http://localhost:8080/pingpong?str=cs695"
     ```
   - Default (no parameter):
     ```bash
     curl http://localhost:8080/pingpong
     ```
6. **Prime Check** (`/arithmetic/prime`):
   - Example with a parameter (`num=11`):
     ```bash
     curl "http://localhost:8080/arithmetic/prime?num=11"
     ```
   - Default (no parameter):
     ```bash
     curl http://localhost:8080/arithmetic/prime
     ```
7. **Fibonacci Function** (`/arithmetic/fibonacci`):
   - Example with a parameter (`k=10`):
     ```bash
     curl "http://localhost:8080/arithmetic/fibonacci?k=10"
     ```
   - Default (no parameter):
     ```bash
     curl http://localhost:8080/arithmetic/fibonacci
     ```

## **5. Part 5b: Load Testing the Server**

### **Step 1: Load Testing with Apache Benchmark (ab)**
To perform load testing on the server, use the Apache Benchmark (`ab`) tool. The following example demonstrates how to test the `/square` endpoint with different concurrency levels:

- **Run Load Test**:
  ```bash
  ab -n 9000 -c <concurrency_level> http://localhost:8080/square?num=5
  ```
  - **`-n 9000`**: Total number of requests.
  - **`-c <concurrency_level>`**: The number of concurrent requests.

- **Example**:
  ```bash
  ab -n 9000 -c 500 http://localhost:8080/square?num=5
  ```
  This sends 9000 requests with a concurrency level of 500.

### **Step 2: Automated Load Testing Script**
Use the provided Bash script (`load_test.sh`) to automate load testing with varying concurrency levels:

- **Script** (`load_test.sh`):
  ```bash
  #!/bin/bash
  
  ulimit -n 5000 # Increase the maximum number of open file descriptors
  
  SERVER="localhost"
  PORT=8080
  ENDPOINT="/square?num=5"
  OUTPUT_FILE="load_test_results_ab_128.csv"
  TOTAL_REQUESTS=9000
  
  echo "RequestRate,RequestsPerSecond,TimePerRequest" > $OUTPUT_FILE
  
  for CONCURRENCY in $(seq 100 250 3000)
  do
      echo "Testing with concurrency level: $CONCURRENCY"
  
      ab_output=$(ab -n $TOTAL_REQUESTS -c $CONCURRENCY "http://$SERVER:$PORT$ENDPOINT" 2>&1)
  
      if [[ $? -ne 0 ]]; then
          echo "Error: Apache Benchmark failed at concurrency level $CONCURRENCY."
          echo "$ab_output"
          exit 1
      fi
  
      requests_per_sec=$(echo "$ab_output" | grep "Requests per second" | awk '{print $4}')
      time_per_request=$(echo "$ab_output" | grep "Time per request:" | head -n1 | awk '{print $4}')
  
      echo "$CONCURRENCY,$requests_per_sec,$time_per_request" >> $OUTPUT_FILE
  
      echo "Results: $CONCURRENCY,$requests_per_sec,$time_per_request"
      
      sleep 1
  done
  
  echo "Load testing completed. Results saved to $OUTPUT_FILE."
  ```
  - Save the script and execute it to generate load testing data:
    ```bash
    chmod +x load_test.sh
    ./load_test.sh
    ```
  - Results will be saved in `load_test_results_ab_128.csv`.

## **6. Plotting the Results**

To visualize the load test results, use the provided Python script to generate plots:

- **Python Script (`plot_results.py`)**:
  ```python
  import matplotlib.pyplot as plt
  import pandas as pd
  
  # Load the results from the CSV file
  result_1 = pd.read_csv('load_test_results_ab.csv')
  result_2 = pd.read_csv('load_test_results_ab_32.csv')
  result_3 = pd.read_csv('load_test_results_ab_64.csv')
  result_4 = pd.read_csv('load_test_results_ab_128.csv')
  
  # Combine all results to find the global min and max
  all_results = pd.concat([result_1, result_2, result_3, result_4])
  y_min = all_results['RequestsPerSecond'].min()
  y_max = all_results['RequestsPerSecond'].max()
  
  # Plot the results
  plt.plot(result_1['RequestRate'], result_1['RequestsPerSecond'], label='8')
  plt.plot(result_2['RequestRate'], result_2['RequestsPerSecond'], label='32')
  plt.plot(result_3['RequestRate'], result_3['RequestsPerSecond'], label='64')
  plt.plot(result_4['RequestRate'], result_4['RequestsPerSecond'], label='128')
  
  plt.xlabel('Concurrency')
  plt.ylabel('Throughput (Requests Per Second)')
  plt.ylim(y_min, y_max)  # Set the y-axis limits
  plt.legend()
  plt.grid(True)
  plt.savefig('comparison_ab_square.png')
  plt.show()
  ```
- **Run the script**:
  ```bash
  python3 plot_results.py
  ```
  - This will generate and save the plot as `comparison_ab_square.png`.

## **7. Additional Notes**
- Ensure that the server is running before executing any load test or `curl` requests.
- Load testing on the same machine as the server may lead to resource contention, affecting results.
- Adjust thread pool sizes (`num_threads` parameter) in the server startup command to see the effects on performance.




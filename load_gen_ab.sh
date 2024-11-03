#!/bin/bash

ulimit -n 5000 # Increase the maximum number of open file descriptors

SERVER="localhost"
PORT=8080
# ENDPOINT="/arithmetic/fibonacci?k=10"
ENDPOINT="/"
OUTPUT_FILE="load_test_results_ab_2_64.csv"
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
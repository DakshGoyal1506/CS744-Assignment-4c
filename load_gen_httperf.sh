SERVER="localhost"
PORT=8080
ENDPOINT="/square?num=5"
OUTPUT_FILE="load_test_results_httperf_40.csv"
TOTAL_CONNECTIONS=90000

echo "RequestRate,RequestsPerSecond,AvgResponseTime" > $OUTPUT_FILE

for RATE in $(seq 16000 500 30000)
do
    echo "Testing with request rate: $RATE requests/sec"

    httperf_output=$(httperf --server $SERVER --port $PORT --uri $ENDPOINT --num-conns $TOTAL_CONNECTIONS --rate $RATE 2>&1)

    if [[ $? -ne 0 ]]; then
        echo "Error: httperf failed at request rate $RATE."
        echo "$httperf_output"
        exit 1
    fi

    requests_per_sec=$(echo "$httperf_output" | grep "Request rate:" | awk '{print $3}')
    avg_response_time=$(echo "$httperf_output" | grep "Reply time" | grep "response" | awk '{print $5}')

    echo "$RATE,$requests_per_sec,$avg_response_time" >> $OUTPUT_FILE

    echo "Results: $RATE,$requests_per_sec,$avg_response_time"

    sleep 1
done

echo "Load testing completed. Results saved to $OUTPUT_FILE."

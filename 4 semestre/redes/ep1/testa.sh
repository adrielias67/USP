#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Usage: $0 <number of queues> <total iterations> [ipv4:port]"
    exit 1
fi

TOTAL_ITERATIONS=$2
if [ $TOTAL_ITERATIONS -lt 1 ]; then
    TOTAL_ITERATIONS=999999999
fi

if [ $# -eq 3 ]; then
    ADDRESS=$3
else
    ADDRESS="127.0.0.1:5672"
fi

IP=$(echo $ADDRESS | cut -d: -f1)
PORT=$(echo $ADDRESS | cut -d: -f2)

echo "Start up your server and press enter to continue..."
read

# Declare queues
for i in $(seq 1 $1); do
    amqp-declare-queue -q "fila$i" --server=$IP --port=$PORT
done

# Function to clean up and terminate all child subshells
cleanup() {
    echo ""
    echo "Ctrl+C received. Terminating all subshells..."
    kill -s SIGINT $TSHARK_PID  # Terminate tshark process
    pkill -P $$  # Terminate child processes of this script's process ID

    # Compare files from consumers directory
    echo "Comparing files..."
    diff --from-file ./consumers/*

    # Calculate total execution time
    END_TIME=$(date +%s)
    TOTAL_TIME=$(($END_TIME - $START_TIME))

    # Calculate total packets
    TOTAL_PACKETS=$(tshark -r packet_capture.pcap -T fields -e frame.number -Y "tcp.port == $PORT" | wc -l)

    # Calculate network usage
    NETWORK_USAGE=$(tshark -r packet_capture.pcap -T fields -e frame.len -Y "tcp.port == $PORT" | awk '{sum += $1} END {print sum}')

    # Print results
    echo "Total execution time: $TOTAL_TIME seconds"
    echo "Total packets: $TOTAL_PACKETS"
    echo "Network usage (total bytes): $NETWORK_USAGE bytes"

    echo "Done."
    rm -f packet_capture.pcap
    exit 2
}

trap cleanup SIGINT  # Call cleanup() on SIGINT

# Creates a consumers directory
mkdir -p ./consumers

# Clears the consumers directory
rm -f ./consumers/*

# Creates a subprocess for each consumer
for i in $(seq 1 $1); do
    echo "Consumer $i setted up"
    touch ./consumers/consumidor$i
    (eval 'amqp-consume -q "fila$i" cat --server=$IP --port=$PORT > ./consumers/consumidor$i') &
done

# Set up tshark to capture network usage
if [ $IP == "127.0.0.1" ]; then
    NWIF="lo"
else
    NWIF=$(ip -o addr show to $IP | awk '{print $2}') # Get the network interface name
fi

tshark -i $NWIF -f "tcp port $PORT" -w packet_capture.pcap 2> /dev/null > /dev/null &
TSHARK_PID=$!

# Create cpu_usage.csv file
echo "Iteration;Time;CPU Usage" > cpu_usage.csv
START_TIME=$(date +%s)

# Publish messages to the queues every 2 seconds
I=0
while [ $I -lt $TOTAL_ITERATIONS ]; do
    I=$(($I+1))
    CPU_USAGE_SUM=0
    for i in $(seq 1 $1); do
        amqp-publish -r "fila$i" -b "Mensagem [$I]" --server=$IP --port=$PORT
        USAGE=$( top -b -n 1 | grep Cpu | awk 'BEGIN{FS="i"} {print $2}' | sed 's/ //g' | sed 's/,/./g' | cut -d "." -f 2,3 )  # Get CPU usage
        CPU_USAGE_SUM=$(echo "$CPU_USAGE_SUM + $USAGE" | bc -l)
    done
    echo "Published message [$I]"
    CPU_USAGE=$(echo "scale=2; $CPU_USAGE_SUM / $1" | bc -l)
    DELTA_TIME=$(($(date +%s) - $START_TIME))
    echo "$I;$DELTA_TIME;$CPU_USAGE" >> cpu_usage.csv
    sleep 2
done

cleanup

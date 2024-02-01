#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Usage: $0 <number of queues> [ipv4:port]"
    exit 1
fi

if [ $# -eq 2 ]; then
    ADDRESS=$2
else
    ADDRESS="127.0.0.1:5672"
fi

IP=$(echo $ADDRESS | cut -d: -f1)
PORT=$(echo $ADDRESS | cut -d: -f2)

# Function to clean up and terminate all child subshells
cleanup() {
    echo "Ctrl+C received. Terminating all subshells..."
    pkill -P $$  # Terminate child processes of this script's process ID
    exit 2
}

trap cleanup SIGINT  # Call cleanup() on SIGINT

# Creates a consumers directory
mkdir -p ./consumers

# Clears the consumers directory
rm -f ./consumers/*

# Creates a subprocess for each consumer
for i in $(seq 1 $1); do
    echo "Consumer $i set up"
    touch ./consumers/consumidor$i
    (eval 'amqp-consume -q "fila$i" cat --server=$IP --port=$PORT > ./consumers/consumidor$i') &
done

# Wait for all subprocesses to finish
wait
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

for i in $(seq 1 $1); do
    amqp-declare-queue -q "fila$i" --server=$IP --port=$PORT
done
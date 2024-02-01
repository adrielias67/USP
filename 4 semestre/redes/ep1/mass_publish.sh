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

# Publish messages to the queues every 2 seconds
I=1
while :; do
    for i in $(seq 1 $1); do
        amqp-publish -r "fila$i" -b "Mensagem [$I]" --server=$IP --port=$PORT
    done
    echo "Published message [$I]"
    I=$((I+1))
    sleep 2
done
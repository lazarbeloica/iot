#!/bin/bash

PIAPP_PATH=~/pi_app/pi_app
DEV_NAME=testDev3
CHIP=bme280

if [ ! -f ${PIAPP_PATH}} ]; then
    echo "pi_app not found!"
    exit 1
fi

echo "Starting the pi_app"
PIAPP_PATH start ${DEV_NAME} ${CHIP} &
echo "pi_app started"
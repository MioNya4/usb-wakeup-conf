#!/bin/bash

usb_wakeup_configuration -a
sleep 2
while (inotifywait /sys/bus/usb/devices/*)
do
    sleep 1
    usb_wakeup_configuration -a
    sleep 4
done

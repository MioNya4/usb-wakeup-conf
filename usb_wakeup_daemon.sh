#!/bin/bash

usb_wakeup_configuration -a
sleep 2
while (inotifywait /sys/bus/usb/devices/*)
do
    sleep 3
    usb_wakeup_configuration -a
    sleep 2
done

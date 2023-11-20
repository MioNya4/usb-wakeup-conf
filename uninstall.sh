#!/bin/bash
rm /usr/bin/usb_wakeup_configuration
rm /usr/bin/usb_wakeup_daemon.sh
rm /usr/share/polkit-1/actions/usb_wakeup_daemon.policy
rm /usr/share/polkit-1/actions/usb_wakeup_tool.policy
echo kill daemon or restart x session to fully get rid of this thing
echo pkill usb_wakeup_daemon.sh

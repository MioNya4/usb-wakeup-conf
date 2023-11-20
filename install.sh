#!/bin/bash
mkdir build
cd build
cmake ../
make clean
make
# install daemon and app to menu
cp usb_wakeup_configuration /usr/bin/
cp ../usb_wakeup_daemon.sh /usr/bin/
cp ../usb_wakeup.desktop /etc/xdg/autostart
cp ../usb_wakeup_tool.desktop /usr/share/applications/

#policies for polkit
cp ../usb_wakeup_daemon.policy /usr/share/polkit-1/actions/
chmod 644 /usr/share/polkit-1/actions/usb_wakeup_daemon.policy
cp ../usb_wakeup_tool.policy /usr/share/polkit-1/actions/
chmod 644 /usr/share/polkit-1/actions/usb_wakeup_tool.policy




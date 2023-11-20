#!/bin/bash
mkdir build
cd build
cmake ../
make clean
make
# install daemon and app to menu
cp usb_wakeup_configuration /usr/bin/
cp ../usb_wakeup_daemon.sh /usr/bin/
chmod +x /usr/bin/usb_wakeup_daemon.sh

cp ../usb_wakeup.desktop /etc/xdg/autostart
cp ../usb_wakeup_tool.desktop /usr/share/applications/

#policies for polkit
cp ../usb_wakeup_daemon.policy /usr/share/polkit-1/actions/
chmod 644 /usr/share/polkit-1/actions/usb_wakeup_daemon.policy
cp ../usb_wakeup_tool.policy /usr/share/polkit-1/actions/
chmod 644 /usr/share/polkit-1/actions/usb_wakeup_tool.policy

echo run usb wakeup tool from app menu to set up the first time
echo restart x session to run daemon that will watch and reapply devices automatically
echo dm me in https://t.me/l33tgraceful if anything is broken (i suspect my pkexec hack is broken but i check myself :<)




# usb-wakeup-conf
gui tool to help configure which usb devices can wake up the laptop from sleeping on ram

# build
```
mkdir build && cd build
cmake ..
make
```

# run
`sudo ./usb_wakeup_configuration`
if not, then maybe `sudo -E ./usb_wakeup_configuration`
or `pkexec ./usb_wakeup_configuration`
or `sudo bash -c "DISPLAY=:0 ./usb_wakeup_configuration` may work for you

# how to use
check box is checked if the device can wake the laptop, uncheck if u dont want this device to wake ur laptop up. Unchecking all of them should mostly be safe.

![text](https://github.com/MioNya4/usb-wakeup-conf/blob/main/Screenshot_20231119_165754.png)

# todo
0) add polkit file so it can run without asking sudo password, add desktop file for app menu
1) make pretty names for each device instead of their pci addresses
2) make config file that stores all of the devices states (vendorid:productid:state)
3) make the daemon that watches new usb devices connected and reapplies the config
4) make it start automatically as a background proccess via /etc/xdg/autostart i guess

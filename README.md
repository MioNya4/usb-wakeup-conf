# usb-wakeup-conf
gui tool to help configure which usb devices can wake up the laptop from sleeping on ram

# build
`sudo apt install build-essential gcc cmake`
```
git clone https://github.com/MioNya4/usb-wakeup-conf
cd usb-wakeup-conf
sudo bash install.sh
```

# run
`sudo usb_wakeup_configuration`


if not, then maybe `sudo -E usb_wakeup_configuration`
or `pkexec usb_wakeup_configuration`
or `sudo bash -c "DISPLAY=:0 usb_wakeup_configuration` may work for you

# how to use
check box is checked if the device can wake the laptop, uncheck if u dont want this device to wake ur laptop up. Unchecking all of them should mostly be safe.


then click apply button. changes are applied until reboot (for now). 
if a new usb device is connected, click refresh button.


(devices named like usb1..usb4 usually dont do anything, instead devices like 3-14 are actual usb devices but idk yet)

![text](https://github.com/MioNya4/usb-wakeup-conf/blob/v0.2/Screenshot_20231120_163028.png)

# todo

1) make pretty names for each device instead of their pci addresses
2) make daemon start/stop from gui tool (its not implemented yet)

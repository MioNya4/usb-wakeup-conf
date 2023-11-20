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
form app menu, or 

`sudo usb_wakeup_configuration`

if not, then maybe `sudo -E usb_wakeup_configuration`
or `pkexec usb_wakeup_configuration`
or `sudo bash -c "DISPLAY=:0 usb_wakeup_configuration` may work for you

unfortunately, in this version you have to restart x session to start the daemon as it only starts at the session start and i can't implement daemon restarter, unless ofc i make it via systemd\openrc service, which will also work for tty\X-less users but idk


maybe you also have to create /root/.config/usb_wakeup.conf file idk





# how to use
check box is checked if the device can wake the laptop, uncheck if u dont want this device to wake ur laptop up. Unchecking all of them should mostly be safe.


then click apply button. 

if a new usb device is connected, click refresh button.

all of the devices are remembered so if the daemon is running and you reconnect your mouse, it will automatically be applied according to config. config updates every time you click apply button


(devices named like usb1..usb4 usually dont do anything, instead devices like 3-14 are actual usb devices but idk yet)

![text](https://github.com/MioNya4/usb-wakeup-conf/blob/v0.2/Screenshot_20231120_163028.png)

# todo

1) make pretty names for each device instead of their pci addresses
2) make daemon start/stop from gui tool (its not implemented yet)
3) if config is updated while some device is not connected, it will not be in config anymore even if it was there before

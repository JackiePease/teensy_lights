# teensy_lights
Setting up teensyLC:
Instructions are here:
https://www.pjrc.com/teensy/td_download.html
Especially remember: sudo cp 49-teensy.rules /etc/udev/rules.d/

Problems with name of device changing all the time, so ran apt-get remove --purge modemmanager as suggested on https://www.pjrc.com/teensy/troubleshoot.html (this might cause problems when running more than one device though)

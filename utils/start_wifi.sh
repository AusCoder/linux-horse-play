#!/bin/bash
# this is a script to start the wifi, you can add more wifi passwords to the /etc/wpa_supplicant/example.conf file
# you should run it as root, and hope it does screw things up

# set the wifi device to up
PATH=/usr/sbin:/usr/bin:/usr/local/sbin:/usr/local/bin

# check if already connected
if [ "$(iw dev wls1 link | head -1)"="Connected to*" ]; then
    echo "already connected to $(iw dev wls1 link | head -2 | tail -1)";
    exit 0;
fi;

# you better be root to start the wifi
if [ $(id -u) -ne 0 ]; then
    echo "you need to be root to start wifi!";
    exit 1;
fi;

# put the wifi up
ip link set wls1 up

# turn on the wpa supplicant to connect to password protected wifi
wpa_supplicant -B -D nl80211,wext -i wls1 -c /etc/wpa_supplicant/example.conf

# get an ip addressp
dhcpcd wls1

#! /bin/bash

VM="archlinux"
# first mount the harddrive
if ! grep -qs '/home/archie/archvm' /proc/mount; then
        mount /dev/sda4 /home/archie/archvm;
fi


# start the vm in headless mode
VBoxHeadless -s $VM &

# start rdesktop
rdesktop -a 16 -K localhost:3389 &


# power off the vm
# VBoxManage controlvm $VM poweroff

# take a snapshot of the vm
#VBoxManage snapshot $VM take archvm1

# unmount the vm hdd
# umount /home/archie/archvm

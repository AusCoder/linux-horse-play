#! /bin/bash

# the name and hd size of the vm
VM="archlinux2"
SIZE=10000
ISO_PATH="/home/archie/Downloads/arch.iso"
BRIDGE_ADAPTER="enp0s25"
 
# create the hard disk
VBoxManage createhd --filename $VM.vdi --size $SIZE

# list the available ostypes
#VBoxManage list ostypes

# create the vm
VBoxManage createvm --name $VM --ostypes "Linux" --register

# add sata controller for the hd
VBoxManage storagectl $VM --name "SATA Controller" --add sata --controller IntelAHCI
VBoxManage storageattach $VM --storagectl "SATA Controller" --port 0 --device 0 --type hdd --medium $VM.vdi

# add ide controller with dvd drive
VBoxManage storagectl $VM --name "IDE Controller" --add ide
VBoxManage storageattach $VM --storagectl "IDE Controller" --port 0 --device 0 --type dvddrive --medium $ISO_PATH

# misc system settings
VBoxManage modifyvm $VM --ioapic on
VBoxManage modifyvm $VM --boot1 dvd --boot2 disk --boot3 none --boot4 none
VBoxManage modifyvm $VM --memory 1024 --vram 128
#VBoxManage modifyvm $VM --nic1 bridged --bridgeadapter1 $BRIDGE_ADAPTER

# to use nat networking
VBoxManage modifyvm $VM --nic1 nat
# allow port forwarding
VBoxManage modifyvm $VM --natpf1 "ssh,tcp,,3022,,22"

# start the vm
#VBoxHeadless -s $VM

# shutdown vm
#VBoxManage controllvm $VM poweroff

# eject dvd
#VBoxManage storageattach $VM --storagectl "IDE Controller" --port 0 --device 0 --type dvddrive --medium none

# delete vm
#VBoxManage unregistervm $Vm --delete

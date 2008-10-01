#!/bin/bash
 
exec 2>/dev/console
exec 1>/dev/console
 
echo
echo "        --- AppleTV Patchstick by ATVUSB-Creator ---"
 
echo "        * mounting OSBoot partition"
mkdir /OSBoot
fsck.hfsplus -f /dev/sda3
mount -t hfsplus -o rw,force /dev/sda3 /OSBoot

echo "       * mounting Media partition"
fsck.hfsplus -f /dev/sda4
mount -t hfsplus -o rw,force /dev/sda4 /OSBoot/mnt
 
echo "        * keeping the OSBoot partition r/w for plugins"
touch /OSBoot/.readwrite

# symlink /mnt/rootfs to /payloads to make the scripts easier to read
echo "       * symlinking /mnt/rootfs -> /payloads"
ln -s /mnt/rootfs/payloads /payloads

echo "       * create staging directory for install scripts"
mkdir -p /OSBoot/Users/Frontrow/staging
ln -s /OSBoot/Users/Frontrow/staging /staging

# 
for script in $( find /payloads/ -name install.sh -print ); do
  #echo $script
  /bin/bash $script
done


sync
umount /OSBoot/mnt
umount /OSBoot
echo "        * Please unplug your Apple TV to reboot/reset the device."
echo "        * Please ssh into Apple TV and see /.upgrade.log and check for errors."
echo "        * To ssh: ssh frontrow@appletv.local  Password: frontrow"
sleep 100000
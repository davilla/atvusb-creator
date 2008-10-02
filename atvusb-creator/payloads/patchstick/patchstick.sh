#!/bin/bash
 
exec 2>/dev/console
exec 1>/dev/console
 
echo
echo "        --- AppleTV Patchstick by ATVUSB-Creator ---"
 
echo "        * mounting OSBoot partition"
mkdir /OSBoot
fsck.hfsplus -f /dev/sda3
mount -t hfsplus -o rw,force /dev/sda3 /OSBoot

# if we successfully mount /OSBoot 
if [ -d "/OSBoot/dev" ]; then
	# symlink /mnt/rootfs to /payloads to make the scripts easier to read
	echo "       * symlinking /mnt/rootfs -> /payloads"
	ln -s /mnt/rootfs/payloads /payloads

	echo "        * keeping the OSBoot partition r/w for plugins"
	touch /OSBoot/.readwrite

	echo "       * mounting Media partition"
	fsck.hfsplus -f /dev/sda4
	mount -t hfsplus -o rw,force /dev/sda4 /OSBoot/mnt
	
	if [ -d "/OSBoot/Users/frontrow" ]; then
		echo "       * create staging directory for install scripts"
		mkdir -p /OSBoot/Users/frontrow/staging
		ln -s /OSBoot/Users/frontrow/staging /staging

		for script in $( find /payloads/ -name install.sh -print ); do
 			/bin/bash "${script}" 
		done
		echo "        * script installation successful!"
	else 
		echo "        * error mounting Media partition"
	fi	
else 
	echo "        * error mounting OSBoot partition"
fi

if [ -d "/OSBoot/Users/frontrow/staging" ]; then
	echo "       * removing staging directory"
	rm -rf /OSBoot/Users/frontrow/staging
fi
sync
umount /OSBoot/mnt
umount /OSBoot
echo "        * Please unplug your Apple TV to reboot/reset the device."
echo
echo "        * If you received no errors above, then you can plug in your Apple TV, "
echo "          wait 3 minutes, then open Terminal and type: ssh frontrow@appletv.local " 
echo "        * When prompted for a password, enter: frontrow"
echo
echo "        * For other ssh clients (putty, etc):  "
echo "          Hostname: appletv.local  Username: frontrow  Password: frontrow"
sleep 100000

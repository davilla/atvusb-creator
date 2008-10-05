#!/bin/bash
#

exec 2>/dev/console
exec 1>/dev/console
 
echo
echo "        --- AppleTV Rebuild Stick by ATVUSB-Creator ---"

REBDIR="/mnt/rootfs/payloads/rebuild"
FILES="OS.dmg boot.efi com.apple.Boot.plist mach_kernel.prelink BootLogo.png"

if [ -d "${REBDIR}" ]; then 
    for file in $FILES; do
	if [ ! -e "${REBDIR}/$file" ]; then
		echo "        * Error: ${REBDIR}/$file not found.  Please verify these were extracted from the OS.dmg"
		exit 1
	fi
    done
    DISKSIZE=`parted -s /dev/sda unit s print | grep Disk | awk '{print $3}' | sed s/s//` 
    # subtract 262145 from this
    let SECTORS=${DISKSIZE}-262145
    if [ "${DISKSIZE}" -gt "${SECTORS}" ]; then
	echo "        * WARNING:  YOUR APPLE TV HARD DISK WILL BE ERASED IN 30 SECONDS. TO ABORT, UNPLUG THE POWER CABLE AND THEN REMOVE THE USB STICK."
	sleep 30
    	echo "        * Wiping paritition table on /dev/sda ..."
    	dd if=/dev/zero of=/dev/sda bs=4096 count=1M
    	# create the GPT format
    	parted -s /dev/sda mklabel gpt
    	echo "        * Creating EFI partition /dev/sda1"
     	parted -s /dev/sda mkpart primary fat32 40s 69671s
    	parted -s /dev/sda set 1 boot on
    	echo "        * Creating Recovery partition /dev/sda2"
    	parted -s /dev/sda mkpart primary HFS 69672s 888823s
    	parted -s /dev/sda set 2 atvrecv on
     	echo "        * Creating OSBoot partition /dev/sda3"
    	parted -s /dev/sda mkpart primary HFS 888824s 2732015s
     	echo "        * Creating Media partition /dev/sda4"
        parted -s /dev/sda mkpart primary HFS 2732016s ${SECTORS}s
    	echo "        * Creating file systems on all 4 partitions..."
    	# make file systems for the four partitions
        mkfs.msdos -F 32 -n EFI /dev/sda1
        mkfs.hfsplus -v Recovery /dev/sda2
        mkfs.hfsplus -J -v OSBoot /dev/sda3
        mkfs.hfsplus -J -v Media /dev/sda4
        partprobe /dev/sda
        mkdir /dst
        fsck.hfsplus -f /dev/sda2
        mount -t hfsplus -o rw,force /dev/sda2 /dst
	echo "        * Copying data from rebuild dir to /dev/sda2"
        cp -arp ${REBDIR}/* /dst/
        sync &>/dev/null
        umount /dst
        echo "        * Restore complete!  Please unplug your Apple TV, plug back in, "
        echo "          and perform a factory restore."
     else
	echo "        * Error: Incorrect values for disk size.  Aborting."
     fi
else 
	echo "        * Error: Unable to locate rebuild dir: ${REBDIR}"
fi
sleep 100000

#!/bin/bash
#

exec 2>/dev/console
exec 1>/dev/console
 
echo
echo "        --- AppleTV Restore Stick by ATVUSB-Creator ---"

RESTDIR="/mnt/rootfs/payloads/restore"
GTP="/staging/org_gtp.txt"
FILES="OS.dmg boot.efi com.apple.Boot.plist mach_kernel.prelink BootLogo.png"

if [ -d "${RESTDIR}" ]; then
        echo "        * restore location found!"
        if [ -e "${RESTDIR}/recovery.tar.gz" ]; then
		for file in $FILES; do
			tar -tzf ${RESTDIR}/recovery.tar.gz $file 2> /dev/null 1> /dev/null
			if [ $? -ne 0 ]; then
				echo "        * Error:  $file missing from recovery image.  Aborting restore."
				exit 1
			fi
		done
		mkdir -p /staging 
		tar -C /staging -xzf ${RESTDIR}/recovery.tar.gz org_gtp.txt
        	if [ -e "${GTP}" ]; then
                	P1S=`grep " 1  " ${GTP} | awk '{print $2}'`
                	P1E=`grep " 1  " ${GTP} | awk '{print $3}'`
                	P2S=`grep " 2  " ${GTP} | awk '{print $2}'`
                	P2E=`grep " 2  " ${GTP} | awk '{print $3}'`
                	P3S=`grep " 3  " ${GTP} | awk '{print $2}'`
                	P3E=`grep " 3  " ${GTP} | awk '{print $3}'`
                	P4S=`grep " 4  " ${GTP} | awk '{print $2}'`
                	P4E=`grep " 4  " ${GTP} | awk '{print $3}'`
			echo "        * WARNING:  YOUR APPLE TV HARD DISK WILL BE ERASED IN 30 SECONDS. TO ABORT, UNPLUG THE POWER CABLE AND THEN REMOVE THE USB STICK."
 			sleep 30
                	echo "        * Wiping paritition table on /dev/sda ..."
                	dd if=/dev/zero of=/dev/sda bs=4096 count=1M
                	# create the GPT format
                	parted -s /dev/sda mklabel gpt
                	echo "        * Creating EFI partition /dev/sda1 - start ${P1S} end ${P1E}"
                	parted -s /dev/sda mkpart primary fat32 ${P1S} ${P1E}
                	parted -s /dev/sda set 1 boot on
	                echo "        * Creating Recovery partition /dev/sda2 - start ${P2S} end ${P2E}"
       		        parted -s /dev/sda mkpart primary HFS ${P2S} ${P2E}
               	 	parted -s /dev/sda set 2 atvrecv on
                	echo "        * Creating OSBoot partition /dev/sda3 - start ${P3S} end ${P3E}"
                	parted -s /dev/sda mkpart primary HFS ${P3S} ${P3E}
                	echo "        * Creating Media partition /dev/sda4 - start ${P4S} end ${P4E}"
                	parted -s /dev/sda mkpart primary HFS ${P4S} ${P4E}
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
			tar -C /dst -tzf ${RESTDIR}/recovery.tar.gz
			rm -f /dst/org_gtp.txt
                	sync &>/dev/null
                	umount /dst
		        echo "        * Restore complete!  Please unplug your Apple TV, plug back in, "
        		echo "          and perform a factory restore."
        	else 
               		echo "        * Error: Unable to locate partition map (org_gtp.txt). Aborting restore."
		fi
	else
		echo "        * Error: Valid recovery.tar.gz not found in ${RESTDIR}.  Aborting restore."
	fi
else 
	echo "        * Error: Unable to locate restore dir ${RESTDIR}.  Aborting restore."
fi
sleep 100000

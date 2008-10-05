#!/bin/bash
#
#
exec 2>/dev/console
exec 1>/dev/console
 
echo
echo "        --- AppleTV Backup Stick by ATVUSB-Creator ---"

BKUPDIR="/mnt/rootfs/payloads/backup"
MEDIA="/media/Scratch/Users/frontrow"
 
if [ -d "${BKUPDIR}" ]; then
	echo "        * backup location found!"
	if [ -e "${BKUPDIR}/recovery.tar.gz" ]; then
		echo "        * Error: It appears a backup has already run."
		echo "        * You need to remove recovery.tar.gz from payloads/backup on the Patchstick partition."
	else 
		echo "        * mounting Media partition on /media"
		fsck.hfsplus -f /dev/sda4
		mkdir /media
		mount -t hfsplus -o rw,force /dev/sda4 /media

		if [ -d "${MEDIA}" ]; then
			echo "       * create staging directory for install scripts"
			mkdir -p ${MEDIA}/staging
			ln -s ${MEDIA}/staging /staging
			echo "        * mounting Recovery partition readonly on /src"
			mkdir /src
			fsck.hfsplus -f /dev/sda2
			mount -t hfsplus -o ro,force /dev/sda2 /src
			if [ -e "/src/OS.dmg" ]; then
				echo "        * backing up recovery partition..."
				cp -arpf /src/* /staging
				parted -s /dev/sda unit s print > /staging/org_gtp.txt
				for i in /staging/*; do 
					file=`echo $i | sed s/\\\/staging\\\///` 
					tar -C /staging -rf ${BKUPDIR}/recovery.tar "$file"
				done
				if [ -e "${BKUPDIR}/recovery.tar" ]; then
					echo "        * compressing backup image..."
					gzip ${BKUPDIR}/recovery.tar
				fi
				#tar -C /staging -czvf ${BKUPDIR}/recovery.tar.gz `ls /staging`
				echo "        * backup complete!"
				echo "        * make sure you save payloads/backup/recovery.tar.gz if you wish to restore your Apple TV back to factory condition."
			else 
				echo "        * Error: unable to locate valid recovery files on Recovery partition."
			fi
		else
			echo "        * Error: unable to mount Media partition for use in staging."
		fi
	fi
else 
        echo "        * Error: backup location not found on Patchstick partition under payloads/backup."
fi
if [ -d "${MEDIA}/staging" ]; then
        echo "       * removing staging directory"
        rm -rf ${MEDIA}/staging
fi
sync &>/dev/null
umount /src
umount /media
echo "        * Please unplug your Apple TV to reboot/reset the device."
sleep 100000

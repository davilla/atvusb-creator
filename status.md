# Goals #
AppleTV USB Flash drive creator that runs under OSX, Linux and Windows. The creator consists of various Installers which are capable of delivering a payload. The payload contents depend on the chosen Installer.


---

# Installers and payloads #

  1. ATV-bootloader
    * payload - none
  1. ATVMod-patchstick
    * payload - packages such as openssh, samba, etc
    * payload - plugins such as ATVFiles, NitoTV, iScripts, etc
    * payload - specials such as mach\_kernel patchs or other items that override native functions.
  1. ATV Factory Restore
    * payload A - update dmg for recovery restore
    * payload B - update dmg for disk rebuild
  1. Linux USB distros

## Payload - Packages ##
(going to need a script that extracts Archive.pax.gz and repacks into a tar.gz)

These are apps such as openssh that consist of the app and deps. Usually build from MacPorts or some other source code distribution, a package is a pkg file that contains the app with additional individual pkg files containing the deps. The creator will build a payload on the host platform from selected items (as an mpkg) and eliminate any duplicate deps.
  * ssh, scp, sfpt, sftp-server via dropbear or openssh
  * samba
  * netatalk

## Payload - Plugins ##
These are frappliance apps that extend the functionality of FrontRow. They install under Finder.app/Contents/Plugins. Plugins do have a dependency on the AppleTV firmware. As such, plugins will have to be matched according to the version of the AppleTV firmware. In addition, plugins use many different package format so there will be a "install.sh" script required to unpack and insert.

**Important -** Since the payload partition is fat32 format any bash scripts will need to be invoked by bash (for example, bash install.sh). Direct execution of bash script will not be possble under fat32 as the execute flag cannot be set.
| AppleTV | v 1.0 | v 1.1 | v 2.01 | v 2.02 | v 2.10 | verified |
|:--------|:------|:------|:-------|:-------|:-------|:---------|
| ATVFiles | v 0.4.0 | v 1.1.1 | v 1.1.1 | v 1.1.1 | v 1.1.1 | yes |
| NitoTV | v 0.3.2  | v 0.3.2  | v 0.4.8 | v 0.4.8 | v 0.4.8 | yes |
| iScripts | none  | none  | v 1.2.2 | v 1.2.2 | none | yes |
| Sapphire | ?  | ?  | ? | ? | ? | ? |
|  | ? | ?  | ? | ? | ? | ? |


## Payload - Specials ##
  * mach\_kernel - USB whitelist bypass
  * mach\_kernel - turbo\_kext\_enabler
  * mach\_kernel - SSE3 Emulator
  * video - composite NTSC/PAL enable
  * 

## Linux USB distros ##


---

# ATVUSB-Creator #
  * disk image creation - The disk image is created by injecting boot.efi into a hfsplus partition image, then injecting the hfsplus partition image into a pre-crafted GPT formatted disk image. This two-step process is required because we will need to know the specific sector offset at which to inject a valid boot.efi file (replacing a zeroed dummy.efi). There are OSX tools that can determine this offset but only using a valid hfsplus partition and not that of the final "recovery" hfsplus partition. In addition, parted under Linux cannot create a vfat partition with the correct GUID (it's a bug), so the disk image needs to be pre-crated under OSX.
```
# Under OSX
dd if=/dev/zero of=atv_512MB.img bs=512 count=1000000
gpt create atv_512MB.img
gpt -r show atv_512MB.img
gpt add -b 40 -i 1 -s 948800 -t "EBD0A0A2-B9E5-4433-87C0-68B6B72699C7" atv_512MB.img
gpt add -b 948840 -i 2 -s 51000 -t "5265636F-7665-11AA-AA11-00306543ECAC" atv_512MB.img

#Under Linux
# format first partition
sudo losetup -o 20480 /dev/loop0 atv_512MB.img
sudo mkfs.vfat -F 32 -n "PATCHSTICK" /dev/loop0
sudo losetup -d /dev/loop0

# format second partition
sudo losetup -o 485806080 /dev/loop0 atv_512MB.img
sudo mkfs.hfsplus -v "Recovery" /dev/loop0
sudo losetup -d /dev/loop0

#need byte offset
#sudo mount -t vfat -o loop,rw,offset=20480 atv_512MB.img /mnt/atv1
#sudo mount -t hfsplus -o loop,rw,offset=485806080 atv_512MB.img /mnt/atv2

gtpsync atv_512MB.img

dd if=/dev/zero of=atv_recv.img bs=512 count=51000
sudo losetup /dev/loop0 atv_recv.img
sudo mkfs.hfsplus -v "Recovery" /dev/loop0
sudo losetup -d /dev/loop0
sudo mount -t hfsplus -o loop,rw  atv_recv.img /mnt/atv2
sudo cp recovery/boot.efi /mnt/atv2
sudo cp recovery/com.apple.Boot.plist /mnt/atv2
sudo cp recovery/mach_kernel /mnt/atv2
sudo cp -r recovery/System /mnt/atv2
sudo cp recovery/BootLogo.png /mnt/atv2
sudo umount /mnt/atv2

# Under OSX, find the offset to boot.efi. This will be a 4096 byte sector value.
hdiutil attach atv_recv.img
hfsdebug /Volumes/Recovery/boot.efi

startBlock = 0x64 = 100 (4096 byte sector)
blockCount = 0x49 = 73


7za a -t7z  atv_recv.7z atv_recv.img 
7za a -t7z  atv_512MB.7z atv_512MB.img

```



---

# Penbuntu Installation #
(Note to SDD to change the execution methods to bash invoked (bash /mnt/rootfs/patchstick.sh) and verify fat32 mounting)
## ATV Filesytem under penbuntu ##
Setup the mount points such that it looks exactly as under ATVOS except /dev/sda3 (OSBoot) is read/write.
```
mkdir /mnt/OSBoot
fsck.hfsplus -f /dev/sda3
mount -t hfsplus -o force,rw /dev/sda3 /mnt/OSBoot
  
fsck.hfsplus -f /dev/sda4
mount -t hfsplus -o force,rw /dev/sda4 /mnt/OSBoot/mnt
```

## Payload filesystem penbuntu ##
The ATVMod-patchstick is started using the standard atv-bootloader (atvboot=patchstick) method. The USB flash drive is setup with two partitions, the first is fat32 and holds the payload contents. The second is the standard atv-bootloader recovery contents. ATVBootloader will search for a "patchstick.sh" by finding disks and mounting the partitions at "/mnt/rootfs". The contents are organized as in the following example.
```
/mnt/rootfs/patchstick.sh

/mnt/rootfs/payload

/mnt/rootfs/payload/packages
/mnt/rootfs/payload/packages/zlib-1.2.3.pkg
/mnt/rootfs/payload/packages/file-4.25.pkg
... other packages ...

/mnt/rootfs/payload/plugings
/mnt/rootfs/payload/plugings/ATVFiles
/mnt/rootfs/payload/plugings/ATVFiles/install.sh
/mnt/rootfs/payload/plugings/ATVFiles/ATVFiles-1.1.0.tar.gz
... other plugins ...

/mnt/rootfs/payload/specials
/mnt/rootfs/payload/specials/turbo_kext_enabler/
/mnt/rootfs/payload/specials/turbo_kext_enabler/install.sh
/mnt/rootfs/payload/specials/turbo_kext_enabler/turbo_kext_enabler.bin
... other plugins ...

/mnt/rootfs/payload/restore
/mnt/rootfs/payload/restore/appleupdate-v2.1.tar.gz

/mnt/rootfs/payload/backup
/mnt/rootfs/payload/restore/recovery.tar.gz

```
  * "/mnt/rootfs/payload/restore" is only for factory restore usage
  * "/mnt/rootfs/payload/backup" is only for holding a backup of the recovery partition (contents)



```
ATV r2.0 mach kernel patch

./poke mach_kernel_patched.bin 0x51f55e 0x75:0x75 0x34:0x30
if [ $? -ne 0 ]; then exit 1; fi

./poke mach_kernel_patched.bin 0x52023e 0x75:0x75 0x34:0x30
if [ $? -ne 0 ]; then exit 1; fi

./poke mach_kernel_patched.bin 0x51f576 0x75:0x75 0x1c:0x18
if [ $? -ne 0 ]; then exit 1; fi

./poke mach_kernel_patched.bin 0x520256 0x75:0x75 0x1c:0x18
if [ $? -ne 0 ]; then exit 1; fi

```

```
ATV AppleTV 2.0.1, 2.0.2 or 2.1 mach kernel patch

./poke mach_kernel_patched.bin 0x52055E 0x75:0x75 0x34:0x30
if [ $? -ne 0 ]; then exit 1; fi

./poke mach_kernel_patched.bin 0x52123E 0x75:0x75 0x34:0x30
if [ $? -ne 0 ]; then exit 1; fi

./poke mach_kernel_patched.bin 0x520576 0x75:0x75 0x1c:0x18
if [ $? -ne 0 ]; then exit 1; fi

./poke mach_kernel_patched.bin 0x521256 0x75:0x75 0x1c:0x18
if [ $? -ne 0 ]; then exit 1; fi

```

```
ATV AppleTV 2.2 mach kernel patch

```

```
2.0 patch kernel watchdog

./poke mach_kernel_patched.bin 0xB94835 0x70:0x00 0xD1:0x00
if [ $? -ne 0 ]; then exit 1; fi

2.0.1 and 2.0.2 patch kernel watchdog (nito comment)

./poke mach_kernel_patched.bin 0xAC6835 0x90:0x00 0xC4:0x00
if [ $? -ne 0 ]; then exit 1; fi


```

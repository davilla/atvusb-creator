# Overview #

Apple TV runs on a custom version of OS X 10.4.7 which has a modified frontrow interface. To modify the Apple TV or create a "patchstick" we need to create a custom image with the software we wish to install. This USB is formatted in a special way that Apple TV understands by restoring a special image that is created with Apple TV Patchstick Creator. Apple TV boots a minimal Linux distribution (called atv-bootloader) of this USB drive and installs our desired software. A modified Apple TV is now in place.

# What you need to know #

To patchstick your Apple TV you don't need to know a lot. You should know your firmware version of your Apple TV. You can find this out by going to Settings > General > About. Apple TV Patchstick Creator only works on firmware 2.x and above. When opening Apple TV Patchstick Creator you should ensure that you select the version of firmware corresponding to your Apple TV. So if you have firmware 3.0.1, you should select 3.0.1 from the drop down list. Unfortunately, Apple remove old firmware periodically, which means that generally only the latest version of firmware is available to download from the drop down list. We have however, taken this into account and offered you the chance to specify your own source of firmware. This can be done by locating a file on your desktop or downloading firmware through the interface but beware of the risks of using images that come from irreputable sources, as well as the legality behind such an action. Alternatively, you can update your Apple TV to the latest firmware. To do this go to Settings > General > Update Software on your Apple TV.

Apple TV Firmware Updates often break things. Installing an update always erases any payloads installed which means repeating the patchstick process is required. To block updates, you need to redirect the update server (mesu.apple.com) to localhost in the HOSTS file. This redirects all requests and means that no updates are detected. This can be done by going to Launcher > Settings > Block Updates if Launcher is installed. Various 3rd party software programs can block updates for you, however if you can also block updates with this command over SSH:

sudo bash -c 'echo "127.0.0.1 mesu.apple.com" >> /etc/hosts'

Updates also break software compatibility. This is why there are updates of Launcher, Software Menu, NitoTV etc. Software is generally broken when a major release occurs (e.g. Apple Tv Take 2 or the 3.0 update).

We will always strive to update our software to support the latest firmware as soon as we can, however you must understand that this can take some time. To learn more about the differences between firmware versions see this [page](http://en.wikipedia.org/wiki/Apple_TV#Specifications) or for a more technical stance the AwkwardTV wiki [here](http://wiki.awkwardtv.org/)

# Technical Information #

On boot up Apple TV will search GPT Mass Storage Devices with a specific GUID for a boot.efi. If there is a match then Apple TV will boot our custom boot.efi which was formed by injecting the boot.efi from 2.hfs which in turn is from the firmware file used in patchsticking into the image containing the payloads desired by the user with the Linux distribution. Patchstick.sh contains the scripts to install the software desired by the user and it is automatically executed by atv-bootloader if it is found. atv-bootloader is loaded via a "modified" mach\_kernel which serves as the LLB.

Custom boot.efi consists of:

atv-bootloader (with patchstick.sh)

payloads (xbmc launcher, ssh distro, software menu)

binutils
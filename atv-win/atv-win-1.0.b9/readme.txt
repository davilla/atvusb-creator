These batch file can be used to create AppleTV patchstick disk images.
The minimum USB flash drive supported is 256MB. USB flash drives can
be restored back to full size using the HP USB Disk Storage Format
Tool from here -> http://files.extremeoverclocking.com/file.php?f=197

There are two disk image versions:

mk_atv-xbmc.bat will create a disk image that will install

  1) bintuils
  2) SoftwareMenu-0.741
  3) XBMCLauncher-0.8

Use this version if you already have ssh on your AppleTV that
was installed by a previous patchstick.


mk_atv-xbmc-ssh.bat will create a disk image that will install

  1) ssh
  2) bintuils
  3) SoftwareMenu-0.741
  4) XBMCLauncher-0.8

SoftwareMenu can be used to install other AppleTV Plugins.

XBMCLauncher is used to install and launch either XBMC or Boxee.

These batch files should be run from a command prompt.

Start -> Run -> cmd


Run either batch file and it will download, extract and inject boot.efi 
into the disk image. Everything will be automatically done so you don't
need to manually extract or download anything.

Once the disk image is created, use "USB Image Tool" to do the actual
copy to USB flash drive. Run "USB Image Tool", switch from "Volume Mode"
to "Device Mode". Select your USB flash drive then select the disk image 
using the "Restore" button. This tool does work in Vista but will need to
be run as administrator. To do this right-click on "USB Image Tool.exe" 
then select "run as administrator".

Good Luck, Issues can be posted here;

http://code.google.com/p/atvusb-creator/issues/list

Please be complete in describing any problems as we cannot see what has 
been done.

Enjoy and please be carefull selecting the desired USB flash drive :)

Scott "Mr AppleTV" Davilla






# Troubleshooting #

Below are a list of common problems and the solutions to them.

**Q**: Apple TV 3.0 firmware that has been patchsticked has broken Software and Launcher menus. What is the solution?

**A**: Use Apple TV Patchstick Creator for Windows 3.0. XBMCLauncher has been updated to support the new FW.

**Q**: I did not make a backup of my USB Drive with USB Image Tool. Now it's not showing full-size in explorer.

**A**: Fortunately, restoring an empty 512-byte boot sector will fix this problem. Download [this](http://www.alexpage.de/download/usbit/bootsector.img) file from the developer's website.

**Q**: I get error code 3 when trying to restore my to my USB.

**A**: This is because our patchstick wraps the bootloader as a GPT partition which is unrecognisable by Windows. As it is the active partition the payloads partition which is FAT32 is not visible. Go to Control Panel > Administrative Tools > Disk Management. Right click and delete the 25MB partition on the drive. Make sure it is the right drive selected. Windows will now recognise the USB again, and thus will USB Image Tool.

**Q**: How do I get rid of Launcher & XBMC/Boxee

**A**: To delete Launcher and XBMC:

sudo rm -rf /Applications/{Boxee,XBMC}.app/

sudo rm rf /System/Library/CoreServices/Finder.app/Contents/PlugIns/XBMCLauncher.frappliance/

To remove settings of Boxee & XBMC

rm -rf /Users/frontrow/Library/Application\ Support/{BOXEE,XBMC}/

**Q**: How do I delete Software Menu? (pre 3.x question)

**A**: sudo rm -rf /System/Library/CoreServices/Finder.app/Contents/PlugIns/SoftwareMenu.frappliance

**Q**: Patchstick boots but doesn't work right. What's wrong?

**A**: You probably have a message such as "Couldn't find patchstick.sh" "Starting telnetd". Remember to restore the patchstick in Device Mode!

**Q**: A new firmware has been released but there is no update to the patchstick creator yet. What can I do?

**A**: It is recommended that you wait for an update to the application, however if you are eager you can either select the new firmware file with Choose DMG or download it via the Firmware URL box in the application. You should not do this with major revisions.

**Q**: My question isn't answered? What can I do?

**A**: Raise an issue on the issues page. But please search thoroughly before doing so.
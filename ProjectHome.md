The uber USB flash drive creator for the AppleTV. Creates USB flash drive based installers that include patchstick, factory restore and various LInux distributions.

Brought to you by the creators of atv-bootloader and many others.


![http://atvusb-creator.googlecode.com/svn/branches/wiki-images/atv-bootloader.png](http://atvusb-creator.googlecode.com/svn/branches/wiki-images/atv-bootloader.png)


The Intel/PPC OSX version of  [atvusb-creator](http://atvusb-creator.googlecode.com/files/atvusb-creator-1.0.b13.zip).

The Windows XP/Vista interim solution [atv-win](http://atvusb-creator.googlecode.com/files/atv-win-3.0.zip)

**Note that the current version is atvusb-creator-1.0.b13 and atv-win-3.0.zip**

![http://atvusb-creator.googlecode.com/svn/branches/wiki-images/atv-win30-ss.png](http://atvusb-creator.googlecode.com/svn/branches/wiki-images/atv-win30-ss.png)


![http://atvusb-creator.googlecode.com/svn/branches/wiki-images/atvusb3x.png](http://atvusb-creator.googlecode.com/svn/branches/wiki-images/atvusb3x.png)


This version is comes with ssh, bin tools, and two plugins (XBMC/Boxee Installer/Launcher and SoftwareMenu). That's right, two full blown OSX applications with their own AppleTV plugin to launch AND get updates. And not only that but previous problems with launching an application into the front under all display resolutions has been resolved.

Remember that some USB flash drives just will not format correctly and if you have problems try another brand. Minimum flash size is 512MB. Follow the GUI and select "ATV Patchstick", make sure to select the correct disk and hit the circling arrows to the left of the drive menu if you insert the USB flash drive after launching atvusb-creator.

The contents of the patchstick will look like the following, if yours does not look similar or is empty, then the creation failed and you need to create again either by pre-formating two hfsplus partitions using disk utility or trying a different brand flash drive. All USB flash drive are different, some work, some do not work.

![http://atvusb-creator.googlecode.com/svn/branches/wiki-images/patchstick-contents.png](http://atvusb-creator.googlecode.com/svn/branches/wiki-images/patchstick-contents.png)


Standard patchstick rules: create the patchstick on your OSX box, power-down the AppleTV, insert the flash drive, power-up the AppleTV, wait for boot/patching, power-down again, remove flash drive and power up and enjoy XBMC for Mac (http://xbmc.org) or Boxee for Mac.(http://www.boxee.tv)  Remember that Boxee requires an account so if you don't have one, head on over to http://www.boxee.tv/atvusb and register for an account.

One final note (sure, sure), Both XBMC and Boxee are net installed from XBMC/Boxee launcher so remember to first select "Update" and install the individual applications.

Oh yes, atvusb-creator can be found in the [downloads section](http://code.google.com/p/atvusb-creator/downloads/list) so have at it and enjoy XBMC and Boxee native on the AppleTV OS.

The other two platform (Linux and Windows) will be released later.

**XBMC Launcher-0.8 has been released. Check the Update menu in either XBMC or Boxee Launchers. Not only can the Launcher update the Application but it can also update itself. Next for this version is the XBMC and Boxee Launchers have been combined into one. the launcher update will remove both of the older launchers and remove them with the new one. XBMC/Boxee Launcher issues should be goto http://code.google.com/p/atv-xbmc-launcher/issues/list**

Quick Help

1) if the sha1 checksum fails, then the download of the AppleTV update dmg failed and you need to delete it from the downloads folder.

2) **WARNING** DO NOT RUN atvusb-creator-1.0.0.b1 TWICE, there is an error that will require a AppleTV Factory Restore to fix if you run the PATCHSTICK twice. Much apologies if this has happened, do a factory restore and use b8. Once again, DO NOT RUN a patchstick made from atvusb-creator-1.0.0.b1.tar.gz TWICE.  UPDATE: This warning does not apply to versions greater than b1.

3) And take the spaces out of the name of the folder name in atvusb-creator-1.0.b2.tar.gz

4) Users need to stop highjacking other issue threads. If you have a problem, please take the time to create an issue with a description of the problem. Otherwise I can't see that someone has added something different and respond and more important, others can find a previously solved issue with having to read every comment.

5) This uses the AppleTV update dmg and NOT the MacOSXUpdCombo10.4.9Intel.dmg or any other dmg. We are pulling out boot.efi from the AppleTV update dmg. Only this boot.efi will work for booting the AppleTV. The text above the "Choose a DMG" says "Download AppleTV update DMG" for a reason and no other DMG will work.

6) I'm still seeing downloads of other version, the current version is atvusb-creator-1.0.b13 and this version does fix some issues that are present in the other versions.

7) **WARNING** Be very careful in selecting the correct USB device. Any USB mass storage devices are selectable and once you start the process, the contents are gone! A future version will have more info about the USB mass storage device selected and issue warning if the size is greater that 16GB.

8) If you are having problems under 10.5 getting the download to extract in Safari,  turn off auto expand in safari, then re-download and expand using the Finder.


# Uninstall XBMC/Boxee #

This is done on the terminal after logging into the atv by ssh, but still pretty easy, as there are only a few folders to delete (password is frontrow):

login (if appletv.local does not work use the IP address of your AppleTV)
```
ssh frontrow@appletv.local
```

delete launcher and XBMC / Boxee
```
sudo rm -rf /Applications/{Boxee,XBMC}.app/ 
sudo rm -rf /System/Library/CoreServices/Finder.app/Contents/PlugIns/XBMCLauncher.frappliance/
```

remove settings of Boxee and XBMC:
```
rm -rf /Users/frontrow/Library/Application\ Support/{BOXEE,XBMC}/
```

reboot and that's it
```
sudo reboot
```

[main](HomePage.md)
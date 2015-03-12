# Getting Started #

First, it is necessary to download the latest version of Apple TV Patchstick Creator. Head on over to the [downloads list](http://code.google.com/p/atvusb-creator/downloads/list) and download the latest version for Windows. All windows versions begin with the prefix "atv-win" so it is easy to distinguish between Windows versions and Mac versions.

# Running the software #

Extract the contents of the ZIP file and read any notes that are packaged with the accompanying executable. Now open the program.

After running it you will be presented with the interface shown below. Each part of the application has been numbered into a stage and each stage is addressed with a greater focus below.

![http://atvusb-creator.googlecode.com/svn/branches/wiki-images/atv-win-stagesscreenshot.png](http://atvusb-creator.googlecode.com/svn/branches/wiki-images/atv-win-stagesscreenshot.png)

## Stage 1 (Firmware Selection) ##

Despite no change to boot.efi, it is good if you ensure that the firmware you are patching is the same as the firmware on your Apple TV. For more information about firmware, see [the firmware guide](http://code.google.com/p/atvusb-creator/wiki/atvwinFirmwareGuide).

If the version of firmware you wish to create a patchstick is in the Firmware Version drop down menu, simply select it and the firmware URL box will be pre-populated. You can now move to Stage 2.

However, if you wish to patch a lower/higher firmware version than that listed in the drop down menu then you can do so. You can use the Choose DMG feature which will let you pick a custom firmware from your hard drive. This is often done for previous versions of Apple TV firmware that have been removed from the Apple TV site. Apple TV Patchstick Creator 3.0 will only accept .DMG files.

![http://atvusb-creator.googlecode.com/svn-history/r165/branches/wiki-images/atv-win-opencustfw-ss.png](http://atvusb-creator.googlecode.com/svn-history/r165/branches/wiki-images/atv-win-opencustfw-ss.png)

After you select this, atv-win will copy the firmware file to the working directory for usage. This can take a moment. When this is done you can move to Stage 2.

Alternatively, if you do not have the firmware file on your hard drive but rather it is on the Internet, Apple TV Patchstick Creator 3.0 can handle the download for you. This has been added because when new firmware is released many people like to repatch their aTV immediately. This can be done by simply copying and pasting the URL of a valid firmware file. Once this is done you can move to Stage 2.

Tech note: All URLS are evaluated with a regular expression. This will support FTP & HTTP protocols with custom ports specified. There is no longer a requirement for .dmg file extension.

## Stage 2 (Choosing Software) ##

Next you need to choose the software/payloads that you would like to be installed when you patchstick your Apple TV. XBMCLauncher provides you with the ability to run the Boxee and XBMC media centers on your Apple TV, where as SSH gives you remote SCP capabilities to your Apple TV.

XBMC Launcher version varies by atv-win version (see [changelog](http://code.google.com/p/atvusb-creator/wiki/atvwinChangelog) for differences. All versions of atv-win < 3.0 distribute dropbear as the SSH distribution. This has now changed to OpenSSH.

An image containing the software you choose is pulled off the server after you select what you would like to install.

Once you have done this, and you are satisfied continue to Stage 3.

## Stage 3 (Create Patchstick & Restore to USB) ##

While this may not seem to be a Stage and may seem to simply be clicking a button, one can be assured there is much more to it than that.

Once you click this button, you will be prompted as to where you wish to save the patchstick image you are about to generate. The interface will look similar to the displayed below:

![http://atvusb-creator.googlecode.com/svn/branches/wiki-images/atv-win-savepatchstick-ss.png](http://atvusb-creator.googlecode.com/svn/branches/wiki-images/atv-win-savepatchstick-ss.png)

Simply give the image a name and save it somewhere memorable. Avoid saving it in temporary locations and save it in more convinient places like the Desktop. You will need this image to put it on the USB Drive you are going to patch your Apple TV with.

After you click Save, there will be a series of popup boxes. This occurs as Apple TV Patchstick Creator for Windows downloads all the tools and software images (as well as firmware if not using "Custom DMG") needed for the patchstick process. Once this is done a command window may be displayed as modifications are made to the images based on your specifications.

After this you should receive a success window which will tell you any details specific to that version of atv-win.

You will be prompted to run USB Image Tool with a dialogue similar to that below:

![http://atvusb-creator.googlecode.com/svn/branches/wiki-images/atv-win-usbimgtool-ss.png](http://atvusb-creator.googlecode.com/svn/branches/wiki-images/atv-win-usbimgtool-ss.png)

Click Yes and you will be prompted with the USB Image Tool interface. Highlighted are points of interest.

![http://atvusb-creator.googlecode.com/svn/branches/wiki-images/atv-win-usbimgtool-gui-ss.png](http://atvusb-creator.googlecode.com/svn/branches/wiki-images/atv-win-usbimgtool-gui-ss.png)

First select the device you will be working with. Ensure that you are working with it in Device Mode and not Volume Mode. Restoring with the latter can cause errors during the patchstick process.

**Optional**
It is recommended that you dedicate a USB Drive to the patchstick process (only 256MB is required and they are very cheap), however if you would like to backup the contents of the stick, press the Backup button. You will be prompted to save a file. Again, remember that this is an important file that you will be restoring after you patchstick the Apple TV, so store it somewhere safe and convinient on the HDD.

![http://atvusb-creator.googlecode.com/svn/branches/wiki-images/atv-win-usbimg-tool-backup-gui-ss.png](http://atvusb-creator.googlecode.com/svn/branches/wiki-images/atv-win-usbimg-tool-backup-gui-ss.png)

Next, you need to restore the patchstick image that was created onto the USB. This is done by selecting restore and selecting the patchstick image as demonstrated below:

![http://atvusb-creator.googlecode.com/svn/branches/wiki-images/atv-win-usbimg-tool-restore-gui-ss.png](http://atvusb-creator.googlecode.com/svn/branches/wiki-images/atv-win-usbimg-tool-restore-gui-ss.png)

The process can take a few minutes.

# Patching the Apple TV #

It can't really get much simpler than this. Now that you have a flash drive with the modified image on it, you need to put it in the Apple TV. Hold MENU and - buttons while doing this to force the Apple TV to begin the recovery process. This will kick off the search for mass storage devices with recovery information.

Next, you should see Linux boot and a few commands scroll by. After a minute or two this will be done and you should be able to see a message telling you that it is possible to now restart your Apple TV. Before doing this though, remove the patchstick.

If you wish to restore your stick back to a backup, plug it back in the machine and use the same restore technique as you did before, however this time restoring the backup you created.
@ECHO OFF
ECHO.**********************************************************************
ECHO.** ATVUSB-Creator based patchstick creator for Windows XP           **
ECHO.** Creates a AppleTV bootable USB flash image that includes         **
ECHO.** ssh, binutils, SoftMenu-0.71 and XBMCLauncher-0.6 plugins        **
ECHO.**                                                                  **
ECHO.** Note that this batchfile creates just the disk image which must  **
ECHO.** manually copied to the USB flash drive using a disk image tool   **
ECHO.**********************************************************************
ECHO. 

IF EXIST boot.efi goto EFIEXISTS

IF EXIST 2Z694-5499.dmg goto DMGEXISTS
ECHO.
ECHO.** Fetching Apple r2.2 update DMG
ECHO.
tools\wget\wget.exe http://mesu.apple.com/data/OS/061-5262.20081002.tvap9/2Z694-5499.dmg
IF errorlevel 1 GOTO ERROR

:DMGEXISTS
IF EXIST 2.hfs goto HFSEXISTS
ECHO.
ECHO.** Extracting HFS partition from the Apple r2.2 update DMG
ECHO. this is a lengthy process and this will take 5-10 minutes
ECHO.
tools\7-zip\7z.exe e 2Z694-5499.dmg 2.hfs
IF errorlevel 1 GOTO ERROR

:HFSEXISTS
IF EXIST boot.efi goto EFIEXISTS
ECHO.
ECHO.** Extracting boot.efi from HFS partition
ECHO.
tools\7-zip\7z.exe e 2.hfs OSBoot\System\Library\CoreServices\boot.efi
IF errorlevel 1 GOTO ERROR

:EFIEXISTS
IF EXIST SoftwareMenu.tar.gz goto SOFTWAREMENUEXISTS
ECHO.
ECHO.** Fetching SoftMenu AppleTV plugin
ECHO.
REM The SoftwareMenu author wants to tag install counts so
REM we do a download of SoftwareMenu from his site but don't use it.
tools\wget\wget.exe http://iscripts.googlecode.com/files/SoftwareMenu.tar.gz
IF errorlevel 1 GOTO ERROR

:SOFTWAREMENUEXISTS
IF EXIST atv-xbmc-ssh.img goto INJECT
ECHO.
ECHO.** Extracting target disk image, this will take several minutes
ECHO.**  this is a lengthy process and this will take 5-10 minutes
ECHO.
REM created using 7za a -t7z atv-xbmc-ssh.7z atv-xbmc-ssh.img
REM md5 before injection should be 56444b582330c1767cffb5589cc81831
REM check with tools\wget\openssl dgst -md5 atv-xbmc-ssh.img
tools\7-zip\7z.exe e atv-xbmc-ssh.7z
IF errorlevel 1 GOTO ERROR

:INJECT
ECHO.
ECHO.** Injecting boot.efi into target disk image
ECHO.
REM Always injecting boot.efi never hurts so skip any testing
REM md5 after injection should be c2ffaf124f4f244b4c8d302779dc2b45
REM check with tools\wget\openssl dgst -md5 atv-xbmc-ssh.img
tools\injector.exe --infile=boot.efi --baseseek=2437120 --basefile=atv-xbmc-ssh.img
IF errorlevel 1 GOTO ERROR

:USBIMAGE_DOWNLOAD
IF EXIST usbit.zip goto USBIMAGE_UNZIP
ECHO.
ECHO.** Fetching USB Image Tool
ECHO.
tools\wget\wget.exe http://www.alexpage.de/download/usbit/usbit.zip
IF errorlevel 1 GOTO ERROR

:USBIMAGE_UNZIP
IF EXIST "USB Image Tool.exe" goto FINAL_INFO
tools\7-zip\7z.exe e usbit.zip
IF errorlevel 1 GOTO ERROR
GOTO FINAL_INFO

:ERROR
ECHO.**********************************************************************
ECHO.** Some sort of error has occured, aborting operation               **
GOTO COMPLETE

:FINAL_INFO
ECHO.
ECHO.** Run "USB Image Tool" (on Vista, right-click run as administrator),
ECHO.** switch to device mode, pick the correct USB flash drive, 
ECHO.** choose "restore" and select "atv-xbmc-ssh.img". Good Luck:)
ECHO.
:COMPLETE

REM Ignore This - it just fixes a line obscurity. 
echo off
cls
echo The final part of the patchstick process can take a while, please be patient...
7z.exe e FirmwareImage.dmg 2.hfs
7z.exe e 2.hfs OSBoot\System\Library\CoreServices\boot.efi
7z.exe e software.7z
injector.exe --infile=boot.efi --baseseek=2437120 --basefile=ImageFile.img

REM Ignore This - it just fixes a line obscurity.
echo off
cls
echo Apple TV Patchstick Creator 3.0 is performing the last few steps, this may take a few minutes...
start /wait 7z.exe e FirmwareImage.dmg 2.hfs
start /wait 7z.exe e 2.hfs OSBoot\System\Library\CoreServices\boot.efi
start /wait 7z.exe e SoftwareImage.7z
injector.exe --infile=boot.efi --baseseek=2437120 --basefile=ImageFile.img

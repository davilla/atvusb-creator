7z.exe e FirmwareImage.dmg 2.hfs
7z.exe e 2.hfs OSBoot\System\Library\CoreServices\boot.efi
7z.exe e software.7z
injector.exe --infile=boot.efi --baseseek=2437120 --basefile=ImageFile.img

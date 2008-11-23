# openssl dgst -sha1
atv_dmg_info = (
    {
        'name': 'AppleTV Update 2.3',
        'url' : 'http://mesu.apple.com/data/OS/061-5651.20081119.32VtA/2Z694-5573-24.dmg',
        'sha1': 'b228a747ed6c9393861a6f1445d210471106a377',
    },
)
#        'name': 'AppleTV Update 2.1',
#        'url' : 'http://mesu.apple.com/data/OS/061-4632.2080414.gt5rW/2Z694-5428-3.dmg',
#        'sha1': '65151a796164f202f0e0aa3554c5e9cad74e149d',

#        'name': 'AppleTV Update 2.2',
#        'url' : 'http://mesu.apple.com/data/OS/061-5262.20081002.tvap9/2Z694-5499.dmg',
#        'sha1': 'ed7256ee03b3a3fc5e0004089157f9b3ff3e6d4e',

#        'name': 'AppleTV Update 2.3',
#        'url' : 'http://mesu.apple.com/data/OS/061-5651.20081119.32VtA/2Z694-5573-24.dmg',
#        'sha1': 'b228a747ed6c9393861a6f1445d210471106a377',

osx_dmg_info = (
    {
        'name': 'OSX Intel Combo Update 10.4.9',
        'url' : 'http://supportdownload.apple.com/download.info.apple.com/Apple_Support_Area/Apple_Software_Updates/Mac_OS_X/downloads/061-3165.20070313.iU8y4/MacOSXUpdCombo10.4.9Intel.dmg',
        'sha1': '0000000000000000000000000000000000000000',
    },
)

usb_info = (
    {
        'name'  : 'atv_512MB.img',
        'file'  : 'atv_512MB.7z',
        'sha1'  : '0000000000000000000000000000000000000000',
        'size'  : 1000000 * 512,
        'p1_fs' : 'hfsplus',
        'p1_bgn': 40 * 512,
        'p1_cnt': 51000 * 512,
        'p2_fs' : 'fat32',
        'p2_bgn': 51040 * 512,
        'p2_cnt': 948800 * 512,
    },
)

fat_info = (
    {
        'name'  : 'atv_fat.img',
        'file'  : 'atv_fat.7z',
        'sha1'  : '0000000000000000000000000000000000000000',
        'size'  : 948800 * 512,
        'p1_fs' : 'fat32',
    },
)

# http://www.osxbook.com/software/hfsdebug/
# mkdir tmp
# hdiutil attach -mountpoint tmp atvusb_boot.img
# hfsdebug tmp/boot.efi
# hdiutil detach tmp
hfs_info = (
    {
        'name'  : 'atv_recv.img',
        'file'  : 'atv_recv',
        'sha1'  : '0000000000000000000000000000000000000000',
        'size'  : 51000 * 512,
        'p1_fs' : 'hfsplus',
        'efibgn': 100 * 4096,
        'eficnt': 298800,
    },
)



installers = (
    {
        'name'   : 'ATV-Bootloader',
        'pict'   : ':/atv-bootloader.png',
        'url'    : 'http://atv-bootloader.googlecode.com',
        'sha1'   : '0000000000000000000000000000000000000000',
        'enable' : True,
        'install': True,
        'option1': 'None',
        'option2': 'None',
        'option3': 'None',
    },
    {
        'name'   : 'ATV-Patchstick',
        'pict'   : ':atv-patchstick.png',
        'url'    : 'http://atvusb-creator.googlecode.com',
        'sha1'   : '0000000000000000000000000000000000000000',
        'enable' : True,
        'install': False,
        'option1': 'None',
        'option2': 'patchsticks',
        'option3': 'packages',
    },
    {
        'name'   : 'ATV Factory Restore',
        'pict'   : ':/restore.png',
        'url'    : 'http://atvusb-creator.googlecode.com',
        'sha1'   : '0000000000000000000000000000000000000000',
        'enable' : False,
        'install': False,
        'option1': 'restore',
        'option2': 'None',
        'option3': 'None',
    },
    {
        'name'  : 'USB - XBMC for Linux',
        'pict'  : ':/xbmc.png',
        'url'   : 'http://atvusb-creator.googlecode.com',
        'sha1'  : '0000000000000000000000000000000000000000',
        'enable': False,
        'install': False,
        'option1': 'linux_video',
        'option2': 'linux_ir',
        'option3': 'None',
    },
    {
        'name'   : 'USB - Boxee for Linux',
        'pict'   : ':/boxee.png',
        'url'    : 'http://www.boxee.org',
        'sha1'   : '0000000000000000000000000000000000000000',
        'enable' : False,
        'install': False,
        'option1': 'linux_video',
        'option2': 'linux_ir',
        'option3': 'None',
    },
    {
        'name'   : 'USB - Elisa for Linux',
        'pict'   : ':/elisa.png',
        'url'    : 'http://elisa.fluendo.com/',
        'sha1'   : '0000000000000000000000000000000000000000',
        'enable' : False,
        'install': False,
        'option1': 'linux_video',
        'option2': 'linux_ir',
        'option3': 'None',
    },
    {
        'name'   : 'USB - Mythbuntu',
        'pict'   : ':/mythbuntu.png',
        'url'    : 'http://atvusb-creator.googlecode.com',
        'sha1'   : '0000000000000000000000000000000000000000',
        'enable' : False,
        'install': False,
        'option1': 'linux_video',
        'option2': 'linux_ir',
        'option3': 'None',
    },
    {
        'name'   : 'USB - Knoppmyth',
        'pict'   : ':/knoppmyth.png',
        'url'    : 'http://atvusb-creator.googlecode.com',
        'sha1'   : '0000000000000000000000000000000000000000',
        'enable' : False,
        'install': False,
        'option1': 'linux_video',
        'option2': 'linux_ir',
        'option3': 'None',
    },
)

backup = (
    {
        'name'  : 'Backup Recovery Partition',
    },
    {
        'name'  : 'Skip Recovery Backup',
    },
)

restore = (
    {
        'name'  : 'Restore Recovery Partition',
    },
    {
        'name'  : 'Rebuild Disk and Restore',
    },
)

patchsticks = (
    {
        'name'   : 'AppleTV version 1.0',
        'enable' : False,
        'depends': 'atv-1.0',
    },
    {
        'name'   : 'AppleTV version 1.1',
        'enable' : False,
        'depends': 'atv-1.1',
    },
    {
        'name'   : 'AppleTV version 2.0',
        'enable' : False,
        'depends': 'atv-2.0',
    },
    {
        'name'   : 'AppleTV version 2.x',
        'enable' : True,
        'depends': 'atv-2.1',
    },
    {
        'name'   : 'custom defined list',
        'enable' : False,
        'depends': '',
    },
)

packages = (
    {
        'name'   : 'ssh tools',
        'enable' : True,
        'depends': 'atv-1.0, atv-1.1, atv-2.0, atv-2.1',
        'install': True,
        'url'    : 'binutils.tar.gz',
        'type'   : 'package',
        'pkgname': 'dropbear',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'bin utils',
        'enable' : True,
        'depends': 'atv-1.0, atv-1.1, atv-2.0, atv-2.1',
        'install': True,
        'url'    : 'dropbear.tar.gz',
        'type'   : 'package',
        'pkgname': 'binutils',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'ATVFiles',
        'enable' : False,
        'depends': 'atv-1.0, atv-1.1, atv-2.0, atv-2.1',
        'install': False,
        'url'    : 'http://ericiii.net/sa/appletv/ATVFiles-1.1.0.run',
        'type'   : 'plugin',
        'pkgname': 'ATVFiles',
        'loader' : 'sudo sh ATVFiles-1.0.1.run'
    },
    {
        'name'   : 'ATVLoader',
        'enable' : False,
        'depends': 'atv-1.0, atv-1.1',
        'install': False,
        'url'    : 'http://alanquatermain.net/projects/ATVLoader.zip',
        'type'   : 'plugin',
        'pkgname': 'ATVLoader',
        'loader' : 'sudo installer -pkg ATVLoader.pkg -target /'
    },
    {
        'name'   : 'ATVTorrents',
        'enable' : False,
        'depends': 'atv-1.0, atv-1.1, atv-2.0, atv-2.1',
        'install': False,
        'url'    : 'http://awkwardtorrents.googlecode.com/files/ATVrtorrent.frappliance.1.0.2.zip',
        'type'   : 'plugin',
        'pkgname': 'ATVTorrents',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'Couch Surfer',
        'enable' : False,
        'depends': 'atv-1.1, atv-2.0, atv-2.1',
        'install': False,
        'url'    : 'http://brandon-holland.com/downloads/couchsurfer/couchsurfer-0.3-2.0-installer.zip',
        'type'   : 'plugin',
        'pkgname': 'CouchSurfer',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'EyeTV',
        'enable' : False,
        'depends': 'atv-2.0, atv-2.1',
        'install': False,
        'url'    : '/Applications/EyeTV.app)',
        'type'   : 'application',
        'pkgname': 'EyeTV',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'Home MediaCloud',
        'enable' : False,
        'depends': 'atv-2.0',
        'install': False,
        'url'    : 'http://users.pandora.be/bruno.keymolen/HomeMediaCloud_ATV_Take2.zip',
        'type'   : 'plugin',
        'pkgname': 'MediaCloud',
        'loader' : 'install.sh'
        
    },
    {
        'name'   : 'iScripts',
        'enable' : False,
        'depends': 'atv-2.0, atv-2.1',
        'depends': 'None',
        'install': False,
        'url'    : 'http://iscripts.googlecode.com/files/Scripts-1.2.2.tar.gz',
        'type'   : 'plugin',
        'pkgname': 'iScripts',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'Jamen',
        'enable' : False,
        'depends': 'atv-2.0, atv-2.1',
        'install': False,
        'url'    : 'http://atvusb-creator.googlecode.com',
        'type'   : 'plugin',
        'pkgname': 'Jamen',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'rTorrent',
        'enable' : False,
        'depends': 'atv-2.0, atv-2.1',
        'install': False,
        'url'    : 'http://rtorrent-appletv.googlecode.com/files/rtorrent-0.7.9-osx.tar.bz2',
        'type'   : 'plugin',
        'pkgname': 'rTorrent',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'Sapphire',
        'enable' : False,
        'depends': 'atv-2.0, atv-2.1',
        'install': False,
        'url'    : 'http://appletv.nanopi.net/Files/Sapphire_1.0b6.1.zip',
        'type'   : 'plugin',
        'pkgname': 'Sapphire',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'SoftwareMenu',
        'enable' : True,
        'depends': 'atv-2.0, atv-2.1',
        'install': True,
        'url'    : 'SoftwareMenu.frappliance.tar.gz',
        'type'   : 'plugin',
        'pkgname': 'SoftwareMenu',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'Skype',
        'enable' : False,
        'depends': 'atv-1.1, ssh, vnc, watchdog-disable, kextload',
        'install': False,
        'url'    : 'http://brandon-holland.com/downloads/skypeplugin/skypeplugin-0.1-bin.tar.gz',
        'type'   : 'plugin',
        'pkgname': 'Skype',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'NitoTV',
        'enable' : False,
        'depends': 'atv-1.0, atv-1.1, atv-2.0, atv-2.1',
        'install': False,
        'url'    : 'http://nitosoft.com/nitoTVInstaller.zip',
        'type'   : 'plugin',
        'pkgname': 'NitoTV',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'XBMC/Boxee for Mac',
        'enable' : True,
        'depends': 'atv-2.0, atv-2.1',
        'install': True,
        'url'    : 'XBMCLauncher.frappliance.tar.gz',
        'type'   : 'plugin',
        'pkgname': 'XBMCLauncher',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'USB Mass Storage',
        'enable' : False,
        'depends': 'atv-1.0, atv-1.1, atv-2.0, atv-2.1',
        'install': False,
        'url'    : 'http://atvusb-creator.googlecode.com',
        'type'   : 'package',
        'pkgname': 'USBMassStorage',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'Apple File Services',
        'enable' : False,
        'depends': 'atv-1.0, atv-1.1',
        'install': False,
        'url'    : 'http://atvusb-creator.googlecode.com',
        'type'   : 'package',
        'pkgname': 'AppleFileServices',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'SMB/CILS File Services',
        'enable' : False,
        'depends': 'atv-1.0, atv-1.1',
        'install': False,
        'url'    : 'http://atvusb-creator.googlecode.com',
        'type'   : 'package',
        'pkgname': 'SMBFileServices',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'Composite NTSC video',
        'enable' : False,
        'depends': 'atv-1.0, atv-1.1, atv-2.0, atv-2.1',
        'install': False,
        'url'    : 'http://atvusb-creator.googlecode.com',
        'type'   : 'special',
        'pkgname': 'CompositeNTSC',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'Composite PAL video',
        'enable' : False,
        'depends': 'atv-1.0, atv-1.1, atv-2.0, atv-2.1',
        'install': False,
        'url'    : 'http://atvusb-creator.googlecode.com',
        'type'   : 'special',
        'pkgname': 'CompositePAL',
        'loader' : 'install.sh'
    },
)

linux_video = (
    {
        'name'  : 'HDMI - HD1080p',
    },
    {
        'name'  : 'HDMI - HD1080i',
    },
    {
        'name'  : 'HDMI - HD720p',
    },
    {
        'name'  : 'HDMI - HD576p',
    },
    {
        'name'  : 'HDMI - HD576i',
    },
    {
        'name'  : 'HDMI - HD480p',
    },
    {
        'name'  : 'HDMI - HD480i',
    },
    {
        'name'  : 'Component - HD1080p',
    },
    {
        'name'  : 'Component - HD1080i',
    },
    {
        'name'  : 'Component - HD720p',
    },
    {
        'name'  : 'Component - HD576p',
    },
    {
        'name'  : 'Component - HD576i',
    },
    {
        'name'  : 'Component - HD480p',
    },
    {
        'name'  : 'Component - HD480i',
    },
    {
        'name'  : 'Composite - NTSC',
    },
    {
        'name'  : 'Composite - PAL',
    },
    {
        'name'  : 'S-Video - NTSC',
    },
    {
        'name'  : 'S-Video - PAL',
    },
)

linux_ir = (
    {
        'name'  : 'AppleTV IR',
    },
    {
        'name'  : 'MS MCE USB IR',
    },
)









atv_dmg_info = (
    {
        'name': 'AppleTV Update 2.02',
        'url' : 'http://mesu.apple.com/data/OS/061-4632.2080414.gt5rW/2Z694-5428-3.dmg',
        'sha1': '65151a796164f202f0e0aa3554c5e9cad74e149d',
    },
)

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
        'p1_fs' : 'fat32',
        'p1_bgn': 40 * 512,
        'p2_cnt': 948800 * 512,
        'p2_fs' : 'hfsplus',
        'p2_bgn': 948840 * 512,
        'p2_cnt': 51000 * 512,
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
        'file'  : 'atv_recv.7z',
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
        'option1': 'backup',
        'option2': 'None',
        'option3': 'None',
    },
    {
        'name'   : 'ATVMod Patchstick',
        'pict'   : ':atvmod-patchstick.png',
        'url'    : 'http://www.atvmod.googlecode.com',
        'sha1'   : '0000000000000000000000000000000000000000',
        'enable' : True,
        'option1': 'backup',
        'option2': 'patchsticks',
        'option3': 'packages',
    },
    {
        'name'   : 'ATV Factory Restore',
        'pict'   : ':/restore.png',
        'url'    : 'http://www.atvmod.googlecode.com',
        'sha1'   : '0000000000000000000000000000000000000000',
        'enable' : True,
        'option1': 'restore',
        'option2': 'None',
        'option3': 'None',
    },
    {
        'name'  : 'USB - XBMC for Linux',
        'pict'  : ':/xbmc.png',
        'url'   : 'http://www.atvmod.com',
        'sha1'  : '0000000000000000000000000000000000000000',
        'enable': False,
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
        'option1': 'linux_video',
        'option2': 'linux_ir',
        'option3': 'None',
    },
    {
        'name'   : 'USB - Mythbuntu',
        'pict'   : ':/mythbuntu.png',
        'url'    : 'http://www.atvmod.com',
        'sha1'   : '0000000000000000000000000000000000000000',
        'enable' : False,
        'option1': 'linux_video',
        'option2': 'linux_ir',
        'option3': 'None',
    },
    {
        'name'   : 'USB - Knoppmyth',
        'pict'   : ':/knoppmyth.png',
        'url'    : 'http://www.atvmod.com',
        'sha1'   : '0000000000000000000000000000000000000000',
        'enable' : False,
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
        'enable' : True,
        'depends': 'atv-1.0',
    },
    {
        'name'   : 'AppleTV version 1.1',
        'enable' : True,
        'depends': 'atv-1.1',
    },
    {
        'name'   : 'AppleTV version 2.0',
        'enable' : True,
        'depends': 'atv-2.0',
    },
    {
        'name'   : 'AppleTV version 2.1',
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
        'url'    : 'http://www.atvmod.com',
        'type'   : 'package',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'ATVFiles',
        'enable' : True,
        'depends': 'atv-1.0, atv-1.1, atv-2.0, atv-2.1',
        'install': 'True',
        'url'    : 'http://ericiii.net/sa/appletv/ATVFiles-1.1.0.run',
        'type'   : 'plugin',
        'loader' : 'sudo sh ATVFiles-1.0.1.run'
    },
    {
        'name'   : 'ATVLoader',
        'enable' : True,
        'depends': 'atv-1.0, atv-1.1',
        'install': False,
        'url'    : 'http://alanquatermain.net/projects/ATVLoader.zip',
        'type'   : 'plugin',
        'loader' : 'sudo installer -pkg ATVLoader.pkg -target /'
    },
    {
        'name'   : 'ATVTorrents',
        'enable' : False,
        'depends': 'atv-1.0, atv-1.1, atv-2.0, atv-2.1',
        'install': False,
        'url'    : 'http://awkwardtorrents.googlecode.com/files/ATVrtorrent.frappliance.1.0.2.zip',
        'type'   : 'plugin',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'Couch Surfer',
        'enable' : False,
        'depends': 'atv-1.1, atv-2.0, atv-2.1',
        'install': False,
        'url'    : 'http://brandon-holland.com/downloads/couchsurfer/couchsurfer-0.3-2.0-installer.zip',
        'type'   : 'plugin',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'EyeTV',
        'enable' : False,
        'depends': 'atv-2.0, atv-2.1',
        'install': False,
        'url'    : '/Applications/EyeTV.app)',
        'type'   : 'application',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'Home MediaCloud',
        'enable' : False,
        'depends': 'atv-2.0',
        'install': False,
        'url'    : 'http://users.pandora.be/bruno.keymolen/HomeMediaCloud_ATV_Take2.zip',
        'type'   : 'plugin',
        'loader' : 'install.sh'
        
    },
    {
        'name'   : 'iScripts',
        'enable' : True,
        'depends': 'atv-2.0, atv-2.1',
        'depends': 'None',
        'install': False,
        'url'    : 'http://iscripts.googlecode.com/files/Scripts-1.2.2.tar.gz',
        'type'   : 'plugin',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'Jamen',
        'enable' : False,
        'depends': 'atv-2.0, atv-2.1',
        'install': False,
        'url'    : 'http://www.atvmod.com',
        'type'   : 'plugin',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'rTorrent',
        'enable' : False,
        'depends': 'atv-2.0, atv-2.1',
        'install': False,
        'url'    : 'http://rtorrent-appletv.googlecode.com/files/rtorrent-0.7.9-osx.tar.bz2',
        'type'   : 'plugin',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'Sapphire',
        'enable' : True,
        'depends': 'atv-2.0, atv-2.1',
        'install': False,
        'url'    : 'http://appletv.nanopi.net/Files/Sapphire_1.0b6.1.zip',
        'type'   : 'plugin',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'Skype',
        'enable' : False,
        'depends': 'atv-1.1, ssh, vnc, watchdog-disable, kextload',
        'install': False,
        'url'    : 'http://brandon-holland.com/downloads/skypeplugin/skypeplugin-0.1-bin.tar.gz',
        'type'   : 'plugin',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'NitoTV',
        'enable' : True,
        'depends': 'atv-1.0, atv-1.1, atv-2.0, atv-2.1',
        'install': True,
        'url'    : 'http://nitosoft.com/nitoTVInstaller.zip',
        'type'   : 'plugin',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'XBMC for Mac',
        'enable' : True,
        'depends': 'atv-2.0, atv-2.1',
        'install': True,
        'url'    : 'http://downloads.sourceforge.net/xbmc/XBMC_for_Mac-Atlantis-Beta_1.dmg',
        'type'   : 'plugin',
        'loader' : 'install.sh'
    },
    
    {
        'name'   : 'USB Mass Storage',
        'enable' : False,
        'depends': 'atv-1.0, atv-1.1, atv-2.0, atv-2.1',
        'install': False,
        'url'    : 'http://www.atvmod.com',
        'type'   : 'package',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'Apple File Services',
        'enable' : False,
        'depends': 'atv-1.0, atv-1.1',
        'install': False,
        'url'    : 'http://www.atvmod.com',
        'type'   : 'package',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'SMB/CILS File Services',
        'enable' : False,
        'depends': 'atv-1.0, atv-1.1',
        'install': False,
        'url'    : 'http://www.atvmod.com',
        'type'   : 'package',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'Composite NTSC video',
        'enable' : True,
        'depends': 'atv-1.0, atv-1.1, atv-2.0, atv-2.1',
        'install': False,
        'url'    : 'http://www.atvmod.com',
        'type'   : 'special',
        'loader' : 'install.sh'
    },
    {
        'name'   : 'Composite PAL video',
        'enable' : True,
        'depends': 'atv-1.0, atv-1.1, atv-2.0, atv-2.1',
        'install': False,
        'url'    : 'http://www.atvmod.com',
        'type'   : 'special',
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









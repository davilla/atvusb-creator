#ifndef DEFAULT_LIST_H
#define DEFAULT_LIST_H

#include "lists.h"
namespace default_data{
// openssl dgst -sha1
DMG_INFO atv_dmg_info = {
  "AppleTV Update 2.1",
  "http://mesu.apple.com/data/OS/061-4632.2080414.gt5rW/2Z694-5428-3.dmg",
  "65151a796164f202f0e0aa3554c5e9cad74e149d"
};
/*
DMG_INFO atv_dmg_info = {
  "AppleTV Update 2.2",
  "http://mesu.apple.com/data/OS/061-5262.20081002.tvap9/2Z694-5499.dmg",
  "ed7256ee03b3a3fc5e0004089157f9b3ff3e6d4e"
};
*/

DMG_INFO osx_dmg_info = {
  "OSX Intel Combo Update 10.4.9",
  "http://supportdownload.apple.com/download.info.apple.com/Apple_Support_Area/Apple_Software_Updates/Mac_OS_X/downloads/061-3165.20070313.iU8y4/MacOSXUpdCombo10.4.9Intel.dmg",
  "0000000000000000000000000000000000000000",
};

USB_INFO usb_info = {
  "atv_512MB.img",
  "atv_512MB.7z",
  "0000000000000000000000000000000000000000",
  1000000 * 512,
  "fat32",
  40 * 512,
  948800 * 512,
  "hfsplus",
  948840 * 512,
  51000 * 512,
};

// http://www.osxbook.com/software/hfsdebug/
// mkdir tmp
// hdiutil attach -mountpoint tmp atvusb_boot.img
// hfsdebug tmp/boot.efi
// hdiutil detach tmp
HFS_INFO hfs_info = {
  "atv_recv.img",
  "atv_recv.7z",
  "0000000000000000000000000000000000000000",
  51000 * 512,
  "hfsplus",
  100 * 4096,
  298800,
};

INSTALLER installers[8] = {
  {
    "ATV-Bootloader",
    ":/atv-bootloader.png",
    "http://atv-bootloader.googlecode.com",
    "0000000000000000000000000000000000000000",
    true,
    true,
    "None",
    "None",
    "None",
  },
  {
    "ATV-Patchstick",
    ":/atv-patchstick.png",
    "http://atvusb-creator.googlecode.com",
    "0000000000000000000000000000000000000000",
    true,
    false,
    "None",
    "patchsticks",
    "packages",
  },
  {
    "ATV Factory Restore",
    ":/restore.png",
    "http://atvusb-creator.googlecode.com",
    "0000000000000000000000000000000000000000",
    false,
    false,
    "restore",
    "None",
    "None",
  },
  {
    "USB - XBMC for Linux",
    ":/xbmc.png",
    "http://atvusb-creator.googlecode.com",
    "0000000000000000000000000000000000000000",
    false,
    false,
    "linux_video",
    "linux_ir",
    "None",
  },
  {
    "USB - Boxee for Linux",
    ":/boxee.png",
    "http://www.boxee.org",
    "0000000000000000000000000000000000000000",
    false,
    false,
    "linux_video",
    "linux_ir",
    "None",
  },
  {
    "USB - Elisa for Linux",
    ":/elisa.png",
    "http://elisa.fluendo.com",
    "0000000000000000000000000000000000000000",
    false,
    false,
    "linux_video",
    "linux_ir",
    "None",
  },
  {
    "USB - Mythbuntu",
    ":/mythbuntu.png",
    "http://atvusb-creator.googlecode.com",
    "0000000000000000000000000000000000000000",
    false,
    false,
    "linux_video",
    "linux_ir",
    "None",
  },
  {
    "USB - Knoppmyth",
    ":/knoppmyth.png",
    "http://atvusb-creator.googlecode.com",
    "0000000000000000000000000000000000000000",
    false,
    false,
    "linux_video",
    "linux_ir",
    "None",
  }
};

BACKUP backup[2] = {
  {
    "Backup Recovery Partition",
  },
  {
    "Skip Recovery Backup",
  },
};

RESTORE restore[2] = {
  {
    "Restore Recovery Partition",
  },
  {
    "Rebuild Disk and Restore",
  },
};

PATCHSTICK patchsticks[6] = {
  {
    "AppleTV version 1.0",
    false,
    "atv-1.0",
  },
  {
    "AppleTV version 1.1",
    false,
    "atv-1.1",
  },
  {
    "AppleTV version 2.0",
    false,
    "atv-2.0",
  },
  {
    "AppleTV version 2.1",
    true,
    "atv-2.1",
  },
  {
    "AppleTV version 2.2",
    false,
    "atv-2.2",
  },
  {
    "custom defined list",
    false,
    "",
  },
};


PACKAGE packages[21] = {
  {
    "ssh tools",
    true,
    "atv-1.0, atv-1.1, atv-2.0, atv-2.1, atv-2.2",
    true,
    "http://www.atvusb-creator.com",
    "package",
    "dropbear",
    "install.sh",
  },
  {
    "bin utils",
    true,
    "atv-1.0, atv-1.1, atv-2.0, atv-2.1, atv-2.2",
    true,
    "http://www.atvusb-creator.com",
    "package",
    "binutils",
    "install.sh",
  },
  {
    "ATVFiles",
    false,
    "atv-1.0, atv-1.1, atv-2.0, atv-2.1, atv-2.2",
    false,
    "http://ericiii.net/sa/appletv/ATVFiles-1.1.0.run",
    "plugin",
    "ATVFiles",
    "sudo sh ATVFiles-1.0.1.run",
  },
  {
    "ATVLoader",
    false,
    "atv-1.0, atv-1.1",
    false,
    "http://alanquatermain.net/projects/ATVLoader.zip",
    "plugin",
    "ATVLoader",
    "sudo installer -pkg ATVLoader.pkg -target /",
  },
  {
    "ATVTorrents",
    false,
    "atv-1.0, atv-1.1, atv-2.0, atv-2.1, atv-2.2",
    false,
    "http://awkwardtorrents.googlecode.com/files/ATVrtorrent.frappliance.1.0.2.zip",
    "plugin",
    "ATVTorrents",
    "install.sh",
  },
  {
    "Couch Surfer",
    false,
    "atv-1.1, atv-2.0, atv-2.1, atv-2.2",
    false,
    "http://brandon-holland.com/downloads/couchsurfer/couchsurfer-0.3-2.0-installer.zip",
    "plugin",
    "CouchSurfer",
    "install.sh",
  },
  {
    "EyeTV",
    false,
    "atv-2.0, atv-2.1, atv-2.2",
    false,
    "/Applications/EyeTV.app)",
    "application",
    "EyeTV",
    "install.sh",
  },
  {
    "Home MediaCloud",
    false,
    "atv-2.0",
    false,
    "http://users.pandora.be/bruno.keymolen/HomeMediaCloud_ATV_Take2.zip",
    "plugin",
    "MediaCloud",
    "install.sh",      
  },
  {
    "iScripts",
    false,
    "atv-2.0, atv-2.1",
    false,
    "http://iscripts.googlecode.com/files/Scripts-1.2.2.tar.gz",
    "plugin",
    "iScripts",
    "install.sh",
  },
  {
    "Jamen",
    false,
    "atv-2.0, atv-2.1",
    false,
    "http://www.atvusb-creator.com",
    "plugin",
    "Jamen",
    "install.sh",
  },
  {
    "rTorrent",
    false,
    "atv-2.0, atv-2.1",
    false,
    "http://rtorrent-appletv.googlecode.com/files/rtorrent-0.7.9-osx.tar.bz2",
    "plugin",
    "rTorrent",
    "install.sh",
  },
  {
    "Sapphire",
    false,
    "atv-2.0, atv-2.1",
    false,
    "http://appletv.nanopi.net/Files/Sapphire_1.0b6.1.zip",
    "plugin",
    "Sapphire",
    "install.sh",
  },
  {
    "Skype",
    false,
    "atv-1.1, ssh, vnc, watchdog-disable, kextload",
    false,
    "http://brandon-holland.com/downloads/skypeplugin/skypeplugin-0.1-bin.tar.gz",
    "plugin",
    "Skype",
    "install.sh",
  },
  {
    "NitoTV",
    false,
    "atv-1.0, atv-1.1, atv-2.0, atv-2.1, atv-2.2",
    false,
    "http://nitosoft.com/nitoTVInstaller.zip",
    "plugin",
    "NitoTV",
    "install.sh",
  },
  {
    "XBMC for Mac",
    true,
    "atv-2.0, atv-2.1, atv-2.2",
    true,
    "http://downloads.sourceforge.net/xbmc/XBMC_for_Mac-Atlantis-Beta_1.dmg",
    "plugin",
    "XBMCLauncher",
    "install.sh",
  },
  {
    "Boxee for Mac",
    true,
    "atv-2.0, atv-2.1, atv-2.2",
    true,
    "http://apt.boxee.tv/boxee-tiger3.dmg",
    "plugin",
    "BoxeeLauncher",
    "install.sh",
  },
  {
    "USB Mass Storage",
    false,
    "atv-1.0, atv-1.1, atv-2.0, atv-2.1, atv-2.2",
    false,
    "http://www.atvusb-creator.com",
    "package",
    "USBMassStorage",
    "install.sh",
  },
  {
    "Apple File Services",
    false,
    "atv-1.0, atv-1.1",
    false,
    "http://www.atvusb-creator.com",
    "package",
    "AppleFileServices",
    "install.sh",
  },
  {
    "SMB/CILS File Services",
    false,
    "atv-1.0, atv-1.1",
    false,
    "http://www.atvusb-creator.com",
    "package",
    "SMBFileServices",
    "install.sh",
  },
  {
    "Composite NTSC video",
    false,
    "atv-1.0, atv-1.1, atv-2.0, atv-2.1, atv-2.2",
    false,
    "http://www.atvusb-creator.com",
    "special",
    "CompositeNTSC",
    "install.sh",
  },
  {
    "Composite PAL video",
    false,
    "atv-1.0, atv-1.1, atv-2.0, atv-2.1, atv-2.2",
    false,
    "http://www.atvusb-creator.com",
    "special",
    "CompositePAL",
    "install.sh",
  }
};

LINUX_VIDEO linux_video[18] = {
  {
    "HDMI - HD1080p",
  },
  {
    "HDMI - HD1080i",
  },
  {
    "HDMI - HD720p",
  },
  {
    "HDMI - HD576p",
  },
  {
    "HDMI - HD576i",
  },
  {
    "HDMI - HD480p",
  },
  {
    "HDMI - HD480i",
  },
  {
    "Component - HD1080p",
  },
  {
    "Component - HD1080i",
  },
  {
    "Component - HD720p",
  },
  {
    "Component - HD576p",
  },
  {
    "Component - HD576i",
  },
  {
    "Component - HD480p",
  },
  {
    "Component - HD480i",
  },
  {
    "Composite - NTSC",
  },
  {
    "Composite - PAL",
  },
  {
    "S-Video - NTSC",
  },
  {
    "S-Video - PAL",
  },
};

LINUX_IR linux_ir[2] = {
  {
    "AppleTV IR",
  },
  {
    "MS MCE USB IR",
  },
};
}
#endif

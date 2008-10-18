# -*- coding: utf-8 -*-
#
# Copyright © 2008  Red Hat, Inc. All rights reserved.
#
# This copyrighted material is made available to anyone wishing to use, modify,
# copy, or redistribute it subject to the terms and conditions of the GNU
# General Public License v.2.  This program is distributed in the hope that it
# will be useful, but WITHOUT ANY WARRANTY expressed or implied, including the
# implied warranties of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.  You should have
# received a copy of the GNU General Public License along with this program; if
# not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
# Floor, Boston, MA 02110-1301, USA. Any Red Hat trademarks that are
# incorporated in the source code or documentation are not subject to the GNU
# General Public License and may only be used or replicated with the express
# permission of Red Hat, Inc.
#
# Author(s): Luke Macken <lmacken@redhat.com>
# 
# ATV-USB-Creator fork:
#            Scott Davilla <davilla@4pi.com>

"""
Our main LiveUSBCreator module.

This contains the LiveUSBCreator parent class, which is an abstract interface
that provides platform-independent methods.  Platform specific implementations
include the LinuxLiveUSBCreator and the WindowsLiveUSBCreator.
"""

import re
import os
import sys
import sha
import time
import string
import shutil
import logging
import commands
import tempfile
import subprocess

from StringIO import StringIO
from stat import ST_SIZE

from liveusb.lists import atv_dmg_info, usb_info, hfs_info
from liveusb.lists import installers
from liveusb.lists import backup, restore, patchsticks, packages
from liveusb.lists import linux_video, linux_ir


class LiveUSBError(Exception):
    """ A generic error message that is thrown by the LiveUSBCreator """


#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------
class LiveUSBCreator(object):
    """ An OS-independent parent class for Live USB Creators """
    dmg = None          # path to the AppleTV Update DMG
    bootefi = None      # path to the AppleTV boot.efi
    payloads  = None    # path to payloads
    downloads = None    # path to downloads
    drives = {}         # {device: {'label': label, 'mount': mountpoint}}
    pids = []           # a list of pids of all of our subprocesses
    output = StringIO() # log subprocess output in case of errors
    _drive = None       # mountpoint of the currently selected drive
    log = None
    
    packages = []
    installers = []
    patchsticks = []
    
    install_plugins = []
    install_specials = []
    install_packages = []

    drive = property(fget=lambda self: self._drive,
                     fset=lambda self, d: self._set_drive(d))

    #---------------------------------------------------------------------------------
    def __init__(self, opts):
        self.opts = opts
        self._setup_logger()
        self.load_installers()
        # preset some paths
        path = self.get_application_path();
        #print path
        abspath = os.path.abspath(path)
        #print abspath
        
        self.staging = os.path.join(abspath, 'staging')
        self.downloads = os.path.join(abspath, 'downloads')
        self.flashmount = tempfile.mkdtemp()

        if not os.path.exists(self.staging):
            os.mkdir(self.staging)
        if not os.path.exists(self.downloads):
            os.mkdir(self.downloads)

        self.bootefi = os.path.join(self.staging, "boot.efi")
        self.payloads = os.path.join('payloads')

    #---------------------------------------------------------------------------------
    def _setup_logger(self):
        self.log = logging.getLogger(__name__)
        level = logging.INFO
        if self.opts.verbose:
            level = logging.DEBUG
        self.log.setLevel(level)
        handler = logging.StreamHandler()
        handler.setLevel(level)
        formatter = logging.Formatter("[%(module)s:%(lineno)s] %(message)s")
        handler.setFormatter(formatter)
        self.log.addHandler(handler)

    #---------------------------------------------------------------------------------
    def _set_drive(self, drive):
        if not self.drives.has_key(drive):
            raise LiveUSBError("Cannot find device %s" % drive)
        self.log.debug("%s selected: %s" % (drive, self.drives[drive]))
        self._drive = drive

    #---------------------------------------------------------------------------------
    def write_log(self):
        """ Write out our subprocess stdout/stderr to a log file """
        out = file('liveusb-creator.log', 'a')
        out.write(self.output.getvalue())
        out.close()

    #---------------------------------------------------------------------------------
    def popen(self, cmd, **kwargs):
        """ A wrapper method for running subprocesses.

        This method handles logging of the command and it's output, and keeps
        track of the pids in case we need to kill them.  If something goes
        wrong, an error log is written out and a LiveUSBError is thrown.

        @param cmd: The commandline to execute.  Either a string or a list.
        @param kwargs: Extra arguments to pass to subprocess.Popen
        """
        self.log.info(cmd)
        self.output.write(cmd)
        proc = subprocess.Popen(cmd, stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE, stdin=subprocess.PIPE,
                                shell=True, **kwargs)
        self.pids.append(proc.pid)
        out, err = proc.communicate()
        self.output.write(out + '\n' + err + '\n')
        if proc.returncode:
            self.write_log()
            raise LiveUSBError("There was a problem executing the following "
                               "command: `%s`\nA more detailed error log has "
                               "been written to 'liveusb-creator.log'" % cmd)
        return proc

    #---------------------------------------------------------------------------------
    def load_installers(self):
        # load the enabled installers into an installers list
        for installer in installers:
            if installer['enable']:
                self.installers.append(installer)

    #---------------------------------------------------------------------------------
    def load_patchsticks(self):
        # load the enabled patchsticks into an patchsticks list
        self.patchsticks = []
        for patchstick in patchsticks:
            if patchstick['enable']:
                self.patchsticks.append(patchstick)

    #---------------------------------------------------------------------------------
    def load_packages(self, patchstick):
        # load the enabled packages that match the current patchstick
        # into a package list
        self.packages = []
        for package in packages:
            if patchstick['depends'] in package['depends'] and package['enable']:
                self.packages.append(package)
        
    #---------------------------------------------------------------------------------
    def get_atv_dmg_info(self):
        """ If the DMG is for a known release, return it. """
        dmgname = os.path.basename(self.dmg)
        for info in atv_dmg_info:
            if os.path.basename(info['url']) == dmgname:
                return info

    #---------------------------------------------------------------------------------
    def verify_image(self, progress):
        """ Verify the SHA1 checksum of our DMG if it is in our atv_dmg list """
        info = self.get_atv_dmg_info()
        if info:
            dmgsize = os.stat(self.dmg)[ST_SIZE]
            progress.set_max_progress(dmgsize / 1024)
            checksum = sha.new()
            dmgfile = file(self.dmg, 'rb')
            bytes = 1024**2
            total = 0
            while bytes:
                data = dmgfile.read(bytes)
                checksum.update(data)
                bytes = len(data)
                total += bytes
                progress.update_progress(total / 1024)
            return checksum.hexdigest() == info['sha1']

    #---------------------------------------------------------------------------------
    def extract_recovery(self, progress):
        # extract the hfs recovery image
        hfs_image = os.path.join(self.staging, hfs_info[0]['name'])
        if not os.path.exists(hfs_image):
            progress.status("Extracting recovery seed ...")
            image_dst = os.path.join(self.staging)
            archive = os.path.join(self.payloads, hfs_info[0]['file'])
            self.extract_zip_image(progress, archive, hfs_image, image_dst)


    #---------------------------------------------------------------------------------
    def create_image(self, progress):
        progress.status("Creating USB Image...")
        # unmount this disk
        self.umount_disk(progress)

        image_dst = os.path.join(self.staging)
        # extract the base disk image
        # created using "7za a -t7z atv_512MB.7z atv_512MB.img"
        archive = os.path.join(self.payloads, usb_info[0]['file'])
        usb_image = os.path.join(self.staging, usb_info[0]['name'])
        self.extract_7z_image(progress, archive, usb_image, image_dst)
        # extract the hfs recovery image
        # created using "7za a -t7z atv_recv.7z atv_recv.img"
        archive = os.path.join(self.payloads, hfs_info[0]['file'])
        hfs_image = os.path.join(self.staging, hfs_info[0]['name'])
        self.extract_7z_image(progress, archive, hfs_image, image_dst)
        #
        # overlay boot.efi into the hfs partition image
        # this will overwrite a dummy boot.efi
        progress.update_progress(0)
        progress.set_max_progress(hfs_info[0]['eficnt'])
        self.dd_inject(progress, self.bootefi, 0, hfs_image, hfs_info[0]['efibgn'], 1, hfs_info[0]['eficnt'])
        #
        # overlay the hfs partition image into usb disk image.
        progress.update_progress(0)
        progress.set_max_progress(usb_info[0]['p2_cnt'])
        self.dd_inject(progress, hfs_image, 0, usb_image, usb_info[0]['p2_bgn']/512, 512, usb_info[0]['p2_cnt']/512)
        #
        # dd the usb image to the USB flash drive
        progress.status("Imaging to USB Flash" )
        self.dd_disk_image(progress, usb_image)
        
        # now install the payloads onto the "PATCHSTICK" volume
        self.mount_disk(progress)
        
        for installer in installers:
            if installer['install']:
                self.install_payload(installer, self.volume_path)
                break
                
                
        #self.umount_disk(progress)
        
        return True

    #---------------------------------------------------------------------------------
    def install_payload(self, installer, mount_point):
        self.log.debug('mount_point: %s' % mount_point)
        if os.path.exists(mount_point):
            if installer['name'] == "ATV-Bootloader":
                pass

            elif installer['name'] == "ATV-Patchstick":
                # copy patchstick.sh script
                src = os.path.join(self.payloads, 'patchstick', 'patchstick.sh')
                self.log.debug('src: %s' % src)
                shutil.copy(src, mount_point)
            
                # create payloads directories
                
                # populate payloads
                for package in packages:
                    if package['install']:
                        if package['type'] == "package":
                            src = os.path.join(self.payloads, "patchstick", "packages", package['pkgname'])
                            dst = os.path.join(mount_point, 'payloads', "patchstick", "packages", package['pkgname'])
                        elif package['type'] == "plugin":
                            src = os.path.join(self.payloads, "patchstick", "plugins", package['pkgname'])
                            dst = os.path.join(mount_point, 'payloads', "patchstick", "plugins", package['pkgname'])

                        self.log.debug('src: %s dst: %s' % (src, dst))

                        # copy payload to patchstick
                        shutil.copytree(src, dst)
            elif installer['name'] == "ATV Factory Restore":
                pass
               
    #---------------------------------------------------------------------------------
    def dd_disk_image(self, progress, image):
        if os.path.exists(image):
            progress.status("Writing %s to %s" %(os.path.basename(image), self.drive) )
            os_cmd =""
            if sys.platform == "win32":
                os_cmd = os.path.join('tools', 'win', 'DD.exe ')
                os_cmd = os_cmd + 'if=%s of=%s bs=1M' %(image, rdrive)
                [status, rtn] = commands.getstatusoutput(os_cmd)
            elif sys.platform == "darwin":
                # dd usb disk image onto physical usb flash device
                # use the raw disk (rdisk) for speed
                #TODO - fix "/dev/disk#" to "/dev/rdisk#" convertion
                path = string.split(self.drive, "/")
                rdrive = "/" + path[1] + "/r" + path[2]
                [status, rtn] = commands.getstatusoutput("dd if=%s of=%s bs=1m" %(image, rdrive) )
            else:
                [status, rtn] = commands.getstatusoutput("dd if=%s of=%s bs=1M" %(image, self.drive) )
            #
            if status:
                self.log.warning('Unable write usb disk image')
                print rtn
                return
        pass

    #---------------------------------------------------------------------------------
    def extract_7z_image(self, progress, archive, image, image_dst):
        if os.path.exists(archive) and not os.path.exists(image):
            os_cmd =""
            if sys.platform == "win32":
                os_cmd = os.path.join('tools', 'win', '7z.exe ')
            elif sys.platform == "darwin":
                os_cmd = os.path.join('tools', 'osx', '7za ')
            else:
                os_cmd = os.path.join('tools', 'linux', '7za ')
            os_cmd = os_cmd + 'e -bd -y -o"%s" "%s"' %(image_dst, archive)
            #
            progress.status("  extracting %s" %(os.path.basename(archive) ) )
            [status, rtn] = commands.getstatusoutput(os_cmd)
            if status:
                self.log.warning(" unable to extract %s" %(os.path.basename(archive) ) )
                print rtn
                return

    #---------------------------------------------------------------------------------
    def extract_zip_image(self, progress, archive, image, image_dst):
        if os.path.exists(archive) and not os.path.exists(image):
            os_cmd = 'unzip "%s" -d "%s"' %(archive, image_dst)
            #
            progress.status("  extracting %s" %(os.path.basename(archive) ) )
            [status, rtn] = commands.getstatusoutput(os_cmd)
            if status:
                self.log.warning("  unable to extract %s" %(os.path.basename(archive) ) )
                print rtn
                return

    #---------------------------------------------------------------------------------
    def dd_inject(self, progress, ifile, iseek, ofile, oseek, bs, count):
        #print ifile
        #print ofile
        if os.path.exists(ifile) and os.path.exists(ofile):
            if sys.platform == "win32":
                os_cmd = os.path.join('tools', 'win', 'DD.exe conv=notrunc ')
            else:
                # 'dd' exists on all osx and linux distros
                os_cmd = 'dd conv=notrunc '
            #os_cmd = os_cmd + 'if=%s iseek=%s of=%s oseek=%s bs=%s count=%s' %(ifile, iseek, ofile, oseek, bs, count)
            os_cmd = os_cmd + 'if=%s skip=%s of=%s seek=%s bs=%s count=%s' %(ifile, iseek, ofile, oseek, bs, count)
            self.log.info(os_cmd)
            #
            progress.status("dd_inject %s" %(ifile) )
            [status, rtn] = commands.getstatusoutput(os_cmd)
            if status:
                self.log.warning("dd_inject: unable to inject %s" %(ifile) )
                print rtn
                return
                
    #---------------------------------------------------------------------------------
    def find_packager(self): 
        """ Detect packaging systems such as py2app and py2exe """ 
        frozen = getattr(sys, 'frozen', None) 
        if not frozen: 
            # COULD be certain cx_Freeze options or bundlebuilder, nothing to worry about though 
            return None 
        elif frozen in ('dll', 'console_exe', 'windows_exe'): 
            return 'py2exe' 
        elif frozen in ('macosx_app',): 
            return 'py2app' 
        elif frozen is True: 
            # it doesn't ALWAYS set this 
            return 'cx_Freeze' 
        else: 
            return '<unknown packager: %r>' % (frozen,) 

    #---------------------------------------------------------------------------------
    def get_application_path(self):
        packager = self.find_packager()
        if packager == 'py2exe':
            # note that another approach is
            return os.path.dirname(os.path.abspath(sys.argv[0]))
        elif packager == 'py2app':
            # from path/Foo.app/Contents/Resources -> path, even if something in your application chdir'ed in the meantime
            return os.path.dirname(os.path.dirname(os.path.dirname(os.environ['RESOURCEPATH'])))
        else:
          import __main__
          return os.path.dirname(__main__.__file__)
                              
    #---------------------------------------------------------------------------------
    def mount_disk(self, progress):
        raise NotImplementedError

    #---------------------------------------------------------------------------------
    def umount_disk(self, progress):
        raise NotImplementedError

    #---------------------------------------------------------------------------------
    def detect_removable_drives(self):
        """ This method should populate self.drives with removable devices """
        raise NotImplementedError

    #---------------------------------------------------------------------------------
    def extract_bootefi(self, progress):
        """ Extract boot.efi from the AppleTV Update DMG """
        raise NotImplementedError

    #---------------------------------------------------------------------------------
    def partition_disk(self, progress):
        """ Partition Disk """
        raise NotImplementedError

    #---------------------------------------------------------------------------------
    def install_recovery(self, progress):
        """ Install Recovery Partition Contents """
        raise NotImplementedError

    #---------------------------------------------------------------------------------
    def install_patchstick(self, progress):
        """ Install Patchstick Partition Contents """
        raise NotImplementedError

    #---------------------------------------------------------------------------------
    def get_proxies(self):
        """ Return a dictionary of proxy settings """
        return None

    #---------------------------------------------------------------------------------
    def terminate(self):
        """ Terminate any subprocesses that we have spawned """
        raise NotImplementedError

#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------
class LinuxLiveUSBCreator(LiveUSBCreator):
    bus = None # the dbus.SystemBus
    hal = None # an org.freedesktop.Hal.Manager dbus.Interface

    def __init__(self, opts):
        super(LinuxLiveUSBCreator, self).__init__(opts)
        self.volume_path = '/media/PATCHSTICK'
 
    #---------------------------------------------------------------------------------
    def mount_disk(self, progress):
        retries = 5
        while not os.path.exists(self.volume_path) and retries:
            self.popen('partprobe ' + self.drive)
            self.log.error('rescanning partition table failed to mount %s' %(self.volume_path) )
            time.sleep(2)
            retries -= 1

    #---------------------------------------------------------------------------------
    def umount_disk(self, progress):
        mount = self.drives[self.drive]['mount']
        if os.path.exists(mount):
            self.popen('umount ' + mount)

    #---------------------------------------------------------------------------------

    #---------------------------------------------------------------------------------
    def detect_removable_drives(self):
        """ Detect all removable USB storage devices using HAL via D-Bus """
        import dbus
        def _get_device(device):
            dev_obj = self.bus.get_object("org.freedesktop.Hal", device)
            return dbus.Interface(dev_obj, "org.freedesktop.Hal.Device")
            
        def _add_device(dev):
            mount = str(dev.GetProperty('volume.mount_point'))
            self.drives[str(dev.GetProperty('block.device'))] = {
                'mount'   : mount,
                'udi'     : dev,
                'mounted' : False,
            }

        self.drives = {}
        self.bus = dbus.SystemBus()
        hal_obj = self.bus.get_object("org.freedesktop.Hal",
                                      "/org/freedesktop/Hal/Manager")
        self.hal = dbus.Interface(hal_obj, "org.freedesktop.Hal.Manager")

        devices = []
        if self.opts.force:
            devices = self.hal.FindDeviceStringMatch('block.device',
                                                     self.opts.force)
        else:
            devices = self.hal.FindDeviceByCapability("storage")

        for device in devices:
            dev = _get_device(device)
            if self.opts.force or dev.GetProperty("storage.bus") == "usb" and \
               dev.GetProperty("storage.removable"):
                if dev.GetProperty("block.is_volume"):
                    _add_device(dev)
                    continue
                else: # iterate over children looking for a volume
                    children = self.hal.FindDeviceStringMatch("info.parent",
                                                              device)
                    for child in children:
                        child = _get_device(child)
                        if child.GetProperty("block.is_volume"):
                            _add_device(child)

        if not len(self.drives):
            raise LiveUSBError("Unable to find any USB drives")

    #---------------------------------------------------------------------------------
    def extract_bootefi(self, progress):
        """ Extract boot.efi from the AppleTV Update DMG """
        progress.status("Extracting boot.efi ...")
        progress.update_progress(0)
        progress.set_max_progress(100)
        self.tmpdir = tempfile.mkdtemp()
        self.popen('dmg2img %s' % self.dmg)
        self.dmg = os.path.extsep.join([self.dmg.split(os.path.extsep)[0], 'img'])
        progress.update_progress(33)
        self.popen('mount -t hfsplus -o loop %s %s' % (self.dmg, self.tmpdir))
        try:
            bootefi_src = os.path.join(self.tmpdir, 'System', 'Library', 'CoreServices', 'boot.efi')
            shutil.copy(bootefi_src, self.bootefi)
            progress.update_progress(66)
        finally:
            self.popen('umount ' + self.tmpdir)
        progress.update_progress(100)

    #---------------------------------------------------------------------------------
    def terminate(self):
        import signal
        self.log.info("Cleaning up...")
        for pid in self.pids:
            try:
                os.kill(pid, signal.SIGHUP)
                self.log.debug("Killed process %d" % pid)
            except OSError:
                pass

#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------
class DarwinLiveUSBCreator(LiveUSBCreator):

    def __init__(self, opts):
        super(DarwinLiveUSBCreator, self).__init__(opts)
 
    #---------------------------------------------------------------------------------
    def mount_disk(self, progress):
        # mount_hfs /dev/disk1s1 downloads
        os_cmd = 'diskutil mountDisk %s' %(self.drive)
        [status, rtn] = commands.getstatusoutput(os_cmd)
        self.log.debug('%s %s' % (status, rtn))
        progress.status("  mount_disk settling delay (10 seconds)")
        time.sleep(10)

    #---------------------------------------------------------------------------------
    def umount_disk(self, progress):
        os_cmd = 'diskutil unmountDisk %s' %(self.drive)
        [status, rtn] = commands.getstatusoutput(os_cmd)
        self.log.debug('%s %s' % (status, rtn))
        progress.status("  umount_disk settling delay (10 seconds)")
        time.sleep(10)

    #---------------------------------------------------------------------------------
    def detect_removable_drives(self):
        """ Detect all removable USB storage devices using DiskUtil"""
        self.drives = {}
        [status, rtn] = commands.getstatusoutput('diskutil list | grep ^/dev')
        drives = rtn.split("\n")
        for drive in drives:
            #print drive
            Protocol = None
            Ejectable = "No"
            [status, rtn] = commands.getstatusoutput('diskutil info "%s"' %(drive) )
            driveinfo = rtn.split("\n")
            for info in driveinfo:
                #print info
                words = string.split(info, ':')
                #print words
                if words[0].strip() == "Protocol":
                    Protocol = words[1].strip()
                if words[0].strip() == "Ejectable":
                    Ejectable = words[1].strip()
                if words[0].strip() == "Total Size":
                    DiskSize = words[1].strip()
            if Protocol == "USB" and Ejectable == "Yes":
                label = None
                self.drives[drive] = {
                    'mount'   : drive,
                    'udi'     : None,
                    'mounted' : False,
                }
        if not len(self.drives):
            raise LiveUSBError("Unable to find any USB drives")

    #---------------------------------------------------------------------------------
    def extract_bootefi(self, progress):
        """ Extract boot.efi from the AppleTV Update DMG """
        progress.status("Extracting boot.efi ...")
        progress.update_progress(0)
        progress.set_max_progress(100)
        # mount the dmg disk image
        mount_point = tempfile.mkdtemp()
        os_cmd = 'hdiutil attach "%s" -readonly -mountroot "%s"' %(self.dmg, mount_point)
        [status, rtn] = commands.getstatusoutput(os_cmd)
        if status:
            self.log.warning("Unable to mount device: %s" %(rtn) )
            return
        progress.update_progress(33)
        # copy boot.efi to downloads
        bootefi_src = os.path.join(mount_point, 'OSBoot', 'usr', 'standalone', 'i386', 'boot.efi')
        shutil.copy(bootefi_src, self.bootefi)
        progress.update_progress(66)
        # unmount the dmg disk image
        osboot = os.path.abspath( os.path.join(mount_point, 'OSBoot') )
        #print abspath
        [status, rtn] = commands.getstatusoutput('hdiutil detach "%s"' %(osboot) )
        if status:
            self.log.warning("Unable to unmount AppleTV Update DMG")
        progress.update_progress(100)
                        
                        
    #---------------------------------------------------------------------------------
    def create_image(self, progress):
        progress.status("Creating USB Flash Disk...")
        progress.update_progress(0)
        progress.set_max_progress(100)

        # unmount the target disk
        self.umount_disk(progress)

        # partition the target disk
        progress.update_progress(25)
        progress.status("  partition the target disk")
        status = self.partition_disk(progress)
        if (status == False):
            progress.status("  partition_disk failed")
            return status
        
        # install recovery onto target disk
        progress.update_progress(50)
        progress.status("  install recovery onto target disk")
        status = self.install_recovery(progress)
        if (status == False):
            progress.status("  install_recovery failed")
            return status
        
        # install patchstick onto target disk
        progress.update_progress(74)
        progress.status("  install patchstick onto target disk")
        status = self.install_patchstick(progress)
        if (status == False):
            progress.status("  install_patchstick failed")
            return status
        
        progress.update_progress(100)
        #self.umount_disk(progress)
        
        return True

    #---------------------------------------------------------------------------------
    def partition_disk(self, progress):
        # create a GPT format direct on the flash drive
        os_cmd = 'diskutil partitionDisk %s 2 GPTFormat ' %(self.drive)
        os_cmd = os_cmd + '"HFS+" "Recovery" 26112000B '
        os_cmd = os_cmd + '"MS-DOS FAT32" "PATCHSTICK" 485785600B'
        #os_cmd = os_cmd + '"HFS+" "PATCHSTICK" 485785600B'
        [status, rtn] = commands.getstatusoutput(os_cmd)
        if status:
            progress.status("Unable to partition device: %s" %(rtn) )
            return False
            
        time.sleep(10)
        self.umount_disk(progress)
        
        if 'EFI' in rtn:
            # disk is large enough for diskutil to automatically
            # insert an EFI partition as the first partition
            self.drive_efi = True;
            self.drive_recovery = self.drive + 's2'
            self.drive_patchstick = self.drive + 's3'
            self.log.info("diskutil included EFI on device: %s" %(self.drive) )
        else:
            self.drive_efi = False;
            self.drive_recovery = self.drive + 's1'
            self.drive_patchstick = self.drive + 's2'

        return True

    #---------------------------------------------------------------------------------
    def install_recovery(self, progress):
        # mount recovery partition at our specific mount point so we can find it
        os_cmd = 'mount_hfs "%s" "%s"' %(self.drive_recovery , self.flashmount)
        [status, rtn] = commands.getstatusoutput(os_cmd)
        if status:
            progress.status("Unable to mount recovery: %s" %(rtn) )
            return False

        # mount the hfs_image
        hfs_image = os.path.join(self.staging, hfs_info[0]['name'])
        mount_point = tempfile.mkdtemp()
        os_cmd = 'hdiutil attach "%s" -mountroot "%s"' %(hfs_image, mount_point)
        [status, rtn] = commands.getstatusoutput(os_cmd)
        if status:
            os_cmd = 'umount -f "%s"' %(self.flashmount)
            commands.getstatusoutput(os_cmd)
            progress.status("Unable to mount image: %s" %(rtn) )
            return False

        progress.status("  copy files to target disk")
        # copy contents of recovery seed to recovery on flash
        mount_point = mount_point + '/Recovery'
        shutil.copy(mount_point + '/mach_kernel', self.flashmount)
        shutil.copy(mount_point + '/BootLogo.png', self.flashmount)
        shutil.copy(mount_point + '/com.apple.Boot.plist', self.flashmount)
        shutil.copytree(mount_point + '/System', self.flashmount + '/System')
        shutil.copy(self.bootefi, self.flashmount)
        # always sync to force to physical disk
        commands.getstatusoutput('sync')
        
        # unmount hfs_image
        os_cmd = 'hdiutil detach "%s"' %(mount_point) 
        [status, rtn] = commands.getstatusoutput(os_cmd)
        if status:
            progress.status("Unable to unmount image: %s" %(rtn) )
            return False
        #
        # unmount recovery
        os_cmd = 'umount -f "%s"' %(self.flashmount)
        [status, rtn] = commands.getstatusoutput(os_cmd)
        if status:
            progress.status("Unable to unmount recovery: %s" %(rtn) )
            return False
        time.sleep(1)

        progress.status("  remove recovery hfsplus GUID")
        # change the partition to a appletv "recovery" type
        # remove original hfsplus (contents are not changed)
        if self.drive_efi == False:
            os_cmd = 'gpt remove -i 1 %s' %(self.drive)
        else:
            os_cmd = 'gpt remove -i 2 %s' %(self.drive)
        [status, rtn] = commands.getstatusoutput(os_cmd)
        if status:
            progress.status("Unable to remove fake recovery: %s" %(rtn) )
            return False
            
        # gpt removal will remount all partitions so unmount it
        time.sleep(10)
        self.umount_disk(progress)

        progress.status("  change recovery to real GUID")
        # add back as recovery GUID
        if self.drive_efi == False:
            os_cmd = 'gpt add -b 40 -i 1 -s 51000 -t "5265636F-7665-11AA-AA11-00306543ECAC" %s' %(self.drive)
        else:
            os_cmd = 'gpt add -b 409640 -i 2 -s 51000 -t "5265636F-7665-11AA-AA11-00306543ECAC" %s' %(self.drive)
        [status, rtn] = commands.getstatusoutput(os_cmd)
        if status:
            progress.status("Unable to add real recovery: %s" %(rtn) )
            return False
        print rtn
        #
        # adding will remount all partitions so unmount it again
        time.sleep(10)
        self.umount_disk(progress)

        return True

    #---------------------------------------------------------------------------------
    def install_patchstick(self, progress):
        os_cmd = 'mount_msdos "%s" "%s"' %(self.drive_patchstick , self.flashmount)
        #os_cmd = 'mount_hfs "%s" "%s"' %(self.drive_patchstick , self.flashmount)
        [status, rtn] = commands.getstatusoutput(os_cmd)
        if status:
            progress.status("Unable to mount PATCHSTICK: %s" %(rtn) )
            return False

        progress.status("  copy files to target disk")
        # now install the payloads onto the "PATCHSTICK" volume        
        for installer in installers:
            if installer['install']:
                self.install_payload(installer, self.flashmount)
                break
        # always sync to force to physical disk
        commands.getstatusoutput('sync')
                
        os_cmd = 'umount -f "%s"' %(self.flashmount)
        [status, rtn] = commands.getstatusoutput(os_cmd)
        if status:
            progress.status("Unable to unmount PATCHSTICK: %s" %(rtn) )
            return False
            
        return True

    #---------------------------------------------------------------------------------
    def terminate(self):
        import signal
        self.log.info("Cleaning up...")
        for pid in self.pids:
            try:
                os.kill(pid, signal.SIGHUP)
                self.log.debug("Killed process %d" % pid)
            except OSError:
                pass

#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------
class WindowsLiveUSBCreator(LiveUSBCreator):

    def __init__(self, opts):
        super(WindowsLiveUSBCreator, self).__init__(opts)
        # fixme
        self.volume_path = '/Volumes/PATCHSTICK'
 
    #---------------------------------------------------------------------------------
    def popen(self, cmd, **kwargs):
        import win32process
        if isinstance(cmd, basestring):
            cmd = cmd.split()
        tool = os.path.join('tools', 'win', '%s.exe' % cmd[0])
        if not os.path.exists(tool):
            raise LiveUSBError("Cannot find '%s'.  Make sure to extract the "
                               "entire liveusb-creator zip file before running "
                               "this program.")
        return LiveUSBCreator.popen(self, ' '.join([tool] + cmd[1:]),
                                    creationflags=win32process.CREATE_NO_WINDOW,
                                    **kwargs)

    #---------------------------------------------------------------------------------
    def mount_disk(self, progress):
        # fixme
        os_cmd = 'mountvol %s' %(self.drive)
        [status, rtn] = commands.getstatusoutput(os_cmd)

    #---------------------------------------------------------------------------------
    def umount_disk(self, progress):
        # fixme
        os_cmd = 'mountvol %s /D' %(self.drive)
        [status, rtn] = commands.getstatusoutput(os_cmd)

    #---------------------------------------------------------------------------------
    def detect_removable_drives(self):
        import win32file, win32api
        self.drives = {}
        for drive in [l + ':' for l in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ']:
            if win32file.GetDriveType(drive) == win32file.DRIVE_REMOVABLE or \
               drive == self.opts.force:
                try:
                    vol = win32api.GetVolumeInformation(drive)
                    label = vol[0]
                except:
                    label = None
                self.drives[drive] = {
                    'mount'   : drive,
                    'udi'     : None,
                    'mounted' : False,
                }
        if not len(self.drives):
            raise LiveUSBError("Unable to find any removable devices")

    #---------------------------------------------------------------------------------
    def extract_bootefi(self, progress):
        """ Extract boot.efi from DMG with 7-zip directly to the USB key """
        progress.status("Extracting boot.efi ...")
        self.popen('7z x "%s" -x![BOOT] -y -o%s' % (self.dmg, self.drive))

    #---------------------------------------------------------------------------------
    def get_proxies(self):
        proxies = {}
        try:
            import _winreg as winreg
            settings = winreg.OpenKey(winreg.HKEY_CURRENT_USER,
                                      'Software\\Microsoft\\Windows'
                                      '\\CurrentVersion\\Internet Settings')
            proxy = winreg.QueryValueEx(settings, "ProxyEnable")[0]
            if proxy:
                server = str(winreg.QueryValueEx(settings, 'ProxyServer')[0])
                if ';' in server:
                    for p in server.split(';'):
                        protocol, address = p.split('=')
                        proxies[protocol] = '%s://%s' % (protocol, address)
                else:
                    proxies['http'] = 'http://%s' % server
                    proxies['ftp'] = 'ftp://%s' % server
            settings.Close()
        except Exception, e:
            self.log.warning('Unable to detect proxy settings: %s' % str(e))
        self.log.debug('Using proxies: %s' % proxies)
        return proxies

    #---------------------------------------------------------------------------------
    def terminate(self):
        """ Terminate any subprocesses that we have spawned """
        import win32api, win32con, pywintypes
        for pid in self.pids:
            try:
                handle = win32api.OpenProcess(win32con.PROCESS_TERMINATE,
                                              False, pid)
                self.log.debug("Terminating process %s" % pid)
                win32api.TerminateProcess(handle, -2)
                win32api.CloseHandle(handle)
            except pywintypes.error:
                pass


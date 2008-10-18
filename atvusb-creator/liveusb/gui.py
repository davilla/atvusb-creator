# -*- coding: utf-8 -*-
#
# Copyright © 2008  Red Hat, Inc. All rights reserved.
# Copyright © 2008  Kushal Das <kushal@fedoraproject.org>
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
#            Kushal Das <kushal@fedoraproject.org>
#
# ATV-USB-Creator fork:
#            Scott Davilla <davilla@4pi.com>

"""
A cross-platform graphical interface ATVUSB-CREATOR
"""

import os
import sys

from time import sleep
from datetime import datetime
from PyQt4 import QtCore, QtGui

from liveusb import LiveUSBCreator, LiveUSBError
from liveusb.dialog import Ui_Dialog
from liveusb.lists import atv_dmg_info
from liveusb.lists import backup, restore, linux_video, linux_ir
from liveusb.urlgrabber.grabber import URLGrabber, URLGrabError
from liveusb.urlgrabber.progress import BaseMeter


#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------
class LiveUSBApp(QtGui.QApplication):
    """ Main application class """
    def __init__(self, opts, args):
        QtGui.QApplication.__init__(self, args) 
        self.mywindow = LiveUSBDialog(opts)
        self.mywindow.show()
        self.mywindow.activateWindow()
        
        if sys.platform == "darwin":
            # dawrin draws a grow box unless the window size is fixed
            # since I can not see to create the dialog with a fixed size,
            # this remove the darwin grow box and replaces it with a
            # fixed size grip that is very, very small.
            grip = QtGui.QStatusBar(self.mywindow);
            grip.setFixedSize(0,0);

        try:
            self.exec_()
        finally:
            self.mywindow.terminate()


#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------
class ReleaseDownloader(QtCore.QThread):

    def __init__(self, live, url, progress, proxies):
        QtCore.QThread.__init__(self)
        self.progress = progress
        self.proxies = proxies
        self.live = live
        self.url = url

    #---------------------------------------------------------------------------------
    def run(self):
        self.emit(QtCore.SIGNAL("status(PyQt_PyObject)"),
                  "Downloading %s..." % os.path.basename(self.url))
        grabber = URLGrabber(progress_obj=self.progress, proxies=self.proxies)
        try:
            dst = os.path.join(self.live.downloads, os.path.basename(self.url) )
            if os.path.exists(dst):
                #os.file.remove(dst)
                os.remove(dst)
            dmg = grabber.urlgrab(self.url, filename=dst, reget='simple')
        except URLGrabError, e:
            self.emit(QtCore.SIGNAL("dlcomplete(PyQt_PyObject)"), e.strerror)
        else:
            self.emit(QtCore.SIGNAL("dlcomplete(PyQt_PyObject)"), dmg)


#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------
class DownloadProgress(QtCore.QObject, BaseMeter):
    """ A QObject urlgrabber BaseMeter class.
    This class is called automatically by urlgrabber with our download details.
    This class then sends signals to our main dialog window to update the
    progress bar.
    """
    def start(self, filename=None, url=None, basename=None, size=None,
              now=None, text=None):
        self.emit(QtCore.SIGNAL("maxprogress(int)"), size)

    #---------------------------------------------------------------------------------
    def update(self, amount_read, now=None):
        """ Update our download progressbar.

        :read: the number of bytes read so far
        """
        self.emit(QtCore.SIGNAL("progress(int)"), amount_read)

    #---------------------------------------------------------------------------------
    def end(self, amount_read):
        self.update(amount_read)


#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------
class ProgressThread(QtCore.QThread):
    """ A thread that monitors the progress of Live USB creation.
    This thread periodically checks the amount of free space left on the 
    given drive and sends a signal to our main dialog window to update the
    progress bar.
    """
    totalsize = 0
    orig_free = 0
    drive = None
    get_free_bytes = None

    #---------------------------------------------------------------------------------
    def set_data(self, size, drive, freebytes):
        self.totalsize = size / 1024
        self.drive = drive
        self.get_free_bytes = freebytes
        self.orig_free = self.get_free_bytes()
        self.emit(QtCore.SIGNAL("maxprogress(int)"), self.totalsize)

    #---------------------------------------------------------------------------------
    def run(self):
        while True:
            free = self.get_free_bytes()
            value = (self.orig_free - free) / 1024
            self.emit(QtCore.SIGNAL("progress(int)"), value)
            if value >= self.totalsize:
                break
            sleep(4)

    #---------------------------------------------------------------------------------
    def terminate(self):
        self.emit(QtCore.SIGNAL("progress(int)"), self.totalsize)
        QtCore.QThread.terminate(self)

#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------
class LiveUSBThread(QtCore.QThread):
    def __init__(self, live, progress, parent=None):
        QtCore.QThread.__init__(self, parent)
        self.progress = progress
        self.parent = parent
        self.live = live

    #---------------------------------------------------------------------------------
    def status(self, text):
        self.emit(QtCore.SIGNAL("status(PyQt_PyObject)"), text)

    #---------------------------------------------------------------------------------
    def run(self):
        now = datetime.now()
        try:
            # if boot.efi is not present, extract it from the dmg
            if not os.path.exists(self.live.bootefi):
                # If the DMG looks familar, verify it's SHA1SUM
                if not self.parent.opts.noverify:
                    if self.live.get_atv_dmg_info():
                        self.status("Verifying SHA1 of DMG image...")
                        if not self.live.verify_image(progress=self):
                            self.status("Error: The SHA1 of your AppleTV Update DMG is "
                                        "invalid.  You can run this program with "
                                        "the --noverify argument to bypass this "
                                        "verification check.")
                            return
                self.live.extract_bootefi(progress=self)
            #
            self.live.extract_recovery(progress=self)
            status = self.live.create_image(progress=self)
            #
            duration = str(datetime.now() - now).split('.')[0]
            if (status == False): 
                self.status("Failed! (%s)" % duration)
            else:
                self.status("Complete! (%s)" % duration)
            
        except LiveUSBError, e:
            self.status(str(e))
            self.status("ATV-Bootloader creation failed!")

    #---------------------------------------------------------------------------------
    def set_max_progress(self, maximum):
        self.emit(QtCore.SIGNAL("maxprogress(int)"), maximum)

    #---------------------------------------------------------------------------------
    def update_progress(self, value):
        self.emit(QtCore.SIGNAL("progress(int)"), value)

    #---------------------------------------------------------------------------------
    def __del__(self):
        self.wait()

#-------------------------------------------------------------------------------------
class LiveUSBDialog(QtGui.QDialog, Ui_Dialog):
    """ Our main dialog class """
    def __init__(self, opts):
        QtGui.QDialog.__init__(self)
        Ui_Dialog.__init__(self)
        self.opts = opts
        self.setupUi(self)
        self.live = LiveUSBCreator(opts=opts)
        self.get_appletv_dmg_url()
        self.set_installers()
        self.set_installer_options()
        self.populate_devices()
        self.downloader = None
        self.progress_thread = ProgressThread()
        self.download_progress = DownloadProgress()
        self.live_thread = LiveUSBThread(live=self.live, progress=self.progress_thread, parent=self)
        self.connect_slots()
        self.confirmed = False
        
        # plugin name can get long so let the view size expand
        view = self.installMenu_3.view()
        view.setSizePolicy(QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Preferred);

    #---------------------------------------------------------------------------------
    # HACK - can not seem to disable the maximize button under OSX 
    def resizeEvent(self, event):
        #print 'eat this event'
        # eat the event
        self.size = event.oldSize()
        event.ignore();
        
    def paintEvent(self, event):
        #print 'got a paint event'
        pass

    #---------------------------------------------------------------------------------
    def get_appletv_dmg_url(self):
        #import urllib
        #from xml.dom import minidom
        #
        #xml_doc = minidom.parse(urllib.urlopen('http://mesu.apple.com/version.xml'))
        #self.atv_dmg_url = xml_doc.getElementsByTagName('dict')[1].getElementsByTagName('string')[1].firstChild.data
        #self.atv_dmg_url = 'http://mesu.apple.com/data/OS/061-4632.2080414.gt5rW/2Z694-5428-3.dmg'
        self.atv_dmg_url = atv_dmg_info[0]['url']
    
    #---------------------------------------------------------------------------------
    def set_installers(self):
        for info in self.live.installers:
            self.installerMenu.addItem(info['name'])
            #self.installerMenu.item[self.installerMenu.currentIndex].setSelectable(False)
        self.installerMenu.setCurrentIndex(1);

    #---------------------------------------------------------------------------------
    def set_installer_pict(self):
        # change the header image to match installer
        installer = self.live.installers[self.installerMenu.currentIndex()]
        self.headerLabel.setPixmap(QtGui.QPixmap( installer['pict'] ))
    
    #---------------------------------------------------------------------------------
    def set_installer_options(self):
        for installer in self.live.installers:
            installer['install'] = False;

        # populate first options menu
        installer = self.live.installers[self.installerMenu.currentIndex()]
        installer['install'] = True;
        
        #
        self.installMenu_1.clear()
        self.installMenu_1.setEnabled(True)
        option1 = installer['option1']
        if option1 == 'backup':
            for info in backup:
                self.installMenu_1.addItem(info['name'])
        elif option1 == 'restore':
            for info in restore:
                self.installMenu_1.addItem(info['name'])
        else:
            self.installMenu_1.setEnabled(False)
        # populate second options menu
        self.installMenu_2.clear()
        self.installMenu_2.setEnabled(True)
        option2 = installer['option2']
        if option2 == 'patchsticks':
            self.live.load_patchsticks();
            for info in self.live.patchsticks:
                self.installMenu_2.addItem(info['name'])
        elif option2 == 'linux_video':
            for info in linux_video:
                self.installMenu_2.addItem(info['name'])
        elif option2 == 'linux_ir':
            for info in linux_ir:
                self.installMenu_2.addItem(info['name'])
        else:
            self.installMenu_2.setEnabled(False)
        #
        # third options menu is always setup depending on the
        # contents of the second options menu
        self.update_options2();
        
    #---------------------------------------------------------------------------------
    def update_options2(self):
        # second options menu changed, update third options menu
        installer = self.live.installers[self.installerMenu.currentIndex()]
        #
        self.installMenu_3.clear()
        # watch the enable state, we start disabled here and
        # only enable it there are items in the menu
        self.installMenu_3.setEnabled(False)
        self.installCheckbox.setEnabled(False)
        if installer['option2'] == 'patchsticks':
            patchstick = self.live.patchsticks[self.installMenu_2.currentIndex()]
            if 'atv-' in patchstick['depends']:
                self.live.load_packages(patchstick);
                for package in self.live.packages:
                    if package['install']:
                        icon = QtGui.QIcon(":/install.png")
                    else:
                        icon = QtGui.QIcon(":/uninstall.png")
                    self.installMenu_3.addItem(icon, package['name'])
                self.installMenu_3.setCurrentIndex(0);
                #
                package = self.live.packages[self.installMenu_3.currentIndex()]
                if package['install']:
                    self.installCheckbox.setCheckState(QtCore.Qt.Checked)
                else:
                    self.installCheckbox.setCheckState(QtCore.Qt.Unchecked)
        if self.installMenu_3.count() > 0:
            self.installMenu_3.setEnabled(True)
            self.installCheckbox.setEnabled(True)

    #---------------------------------------------------------------------------------
    def update_options3(self):
        # third options menu changed, update checkbox state 
        package = self.live.packages[self.installMenu_3.currentIndex()]
        if package['install']:
            self.installCheckbox.setCheckState(QtCore.Qt.Checked)
        else:
            self.installCheckbox.setCheckState(QtCore.Qt.Unchecked)

    #---------------------------------------------------------------------------------
    def update_options3_fromcheckbox(self):
        # checkbox state changed, update third options menu icon 
        package = self.live.packages[self.installMenu_3.currentIndex()]
        # special check for only one composite video selection enabled.
        # this touches package so remember to reload it at end
        if 'Composite' in package['name']:
            # if the selection is a composite video entry, turn off
            # previous composite video entry
            index = 0
            for package in self.live.packages:
                if 'Composite' in package['name']:
                    package['install'] = False
                    icon = QtGui.QIcon(":/uninstall.png")
                    self.installMenu_3.setItemIcon(index, icon);
                index = index + 1
            package = self.live.packages[self.installMenu_3.currentIndex()]
        # now we can do the install toggle
        if self.installCheckbox.checkState() == QtCore.Qt.Checked:
            package['install'] = True
            icon = QtGui.QIcon(":/install.png")
        else:
            package['install'] = False
            icon = QtGui.QIcon(":/uninstall.png")
        self.installMenu_3.setItemIcon(self.installMenu_3.currentIndex(), icon);

    #---------------------------------------------------------------------------------
    def populate_devices(self):
        self.deviceCombo.clear()
        self.statusInfoEdit.clear()
        try:
            self.live.detect_removable_drives()
            for device, info in self.live.drives.items():
                self.deviceCombo.addItem(device)
            self.startButton.setEnabled(True)
        except LiveUSBError, e:
            self.statusInfoEdit.setPlainText(str(e))
            self.startButton.setEnabled(False)

    #---------------------------------------------------------------------------------
    def connect_slots(self):
        self.connect(self.browseButton, QtCore.SIGNAL("clicked()"), self.selectfile)
        self.connect(self.startButton,  QtCore.SIGNAL("clicked()"), self.build_installer)
        self.connect(self.installerMenu,  QtCore.SIGNAL("currentIndexChanged(int)"), self.set_installer_pict)
        self.connect(self.installerMenu,  QtCore.SIGNAL("currentIndexChanged(int)"), self.set_installer_options)
        self.connect(self.installMenu_2,  QtCore.SIGNAL("currentIndexChanged(int)"), self.update_options2)
        self.connect(self.installMenu_3,  QtCore.SIGNAL("currentIndexChanged(int)"), self.update_options3)
        self.connect(self.installCheckbox,  QtCore.SIGNAL("stateChanged(int)"), self.update_options3_fromcheckbox)
        self.connect(self.live_thread,  QtCore.SIGNAL("status(PyQt_PyObject)"), self.status)
        self.connect(self.live_thread,  QtCore.SIGNAL("finished()"), lambda: self.enable_widgets(True))
        self.connect(self.live_thread,  QtCore.SIGNAL("terminated()"), lambda: self.enable_widgets(True))
        self.connect(self.live_thread,  QtCore.SIGNAL("progress(int)"), self.progress)
        self.connect(self.live_thread,  QtCore.SIGNAL("maxprogress(int)"), self.maxprogress)
        self.connect(self.progress_thread, QtCore.SIGNAL("progress(int)"), self.progress)
        self.connect(self.progress_thread, QtCore.SIGNAL("maxprogress(int)"), self.maxprogress)
        self.connect(self.download_progress, QtCore.SIGNAL("progress(int)"), self.progress)
        self.connect(self.download_progress, QtCore.SIGNAL("maxprogress(int)"), self.maxprogress)
        self.connect(self.deviceRefreshButton, QtCore.SIGNAL("clicked()"), self.populate_devices)

    # not quite sure what this does and why it's hanging here
    @QtCore.pyqtSignature("QString")

    #---------------------------------------------------------------------------------
    def progress(self, value):
        self.progressBar.setValue(value)

    #---------------------------------------------------------------------------------
    def maxprogress(self, value):
        self.progressBar.setMaximum(value)

    #---------------------------------------------------------------------------------
    def status(self, text):
        self.statusInfoEdit.append(text)

    #---------------------------------------------------------------------------------
    def enable_widgets(self, enabled=True):
        self.startButton.setEnabled(enabled)
        self.browseButton.setEnabled(enabled)
        self.installerMenu.setEnabled(enabled)
        self.installMenu_1.setEnabled(enabled)
        self.installMenu_2.setEnabled(enabled)
        self.installMenu_3.setEnabled(enabled)
        self.installCheckbox.setEnabled(enabled)
        self.deviceCombo.setEnabled(enabled)
        self.deviceRefreshButton.setEnabled(enabled)

    #---------------------------------------------------------------------------------
    def get_selected_drive(self):
        return str(self.deviceCombo.currentText()).split()[0]

    #---------------------------------------------------------------------------------
    def build_installer(self):
        self.enable_widgets(False)
        self.live.drive = self.get_selected_drive()

        if os.path.exists(self.live.bootefi):
            # if boot.efi exits just use it
            self.live_thread.start()
        else:
            if self.live.dmg:
                # If the user has selected an DMG, use it.
                self.live_thread.start()
            else:
                # If no selected DMG, download one.
                self.downloader = ReleaseDownloader(
                        self.live,
                        self.atv_dmg_url,
                        progress=self.download_progress,
                        proxies=self.live.get_proxies())
                self.connect(self.downloader,
                             QtCore.SIGNAL("dlcomplete(PyQt_PyObject)"),
                             self.download_complete)
                self.connect(self.downloader,
                             QtCore.SIGNAL("status(PyQt_PyObject)"),
                             self.status)
                self.downloader.start()

    #---------------------------------------------------------------------------------
    def download_complete(self, dmg):
        """ Called by our ReleaseDownloader thread upon completion.

        Upon success, the thread passes in the filename of the downloaded
        release.  If the 'dmg' argument is not an existing file, then
        it is assumed that the download failed and 'dmg' should contain
        the error message.
        """
        if os.path.exists(dmg):
            self.status("Download complete!")
            self.live.dmg = dmg
            self.live_thread.start()
        else:
            self.status("Download failed: " + dmg)
            self.status("You can try again to resume your download")
            self.enable_widgets(True)

    #---------------------------------------------------------------------------------
    def selectfile(self):
        dmgfile = QtGui.QFileDialog.getOpenFileName(self, "Select AppleTV Update DMG",
                                                    ".", "DMG (*.dmg)" )
        if dmgfile:
            try:
                self.live.dmg = self._to_unicode(dmgfile)
            except Exception, e:
                self.live.log.error(str(e))
                self.status("Sorry, I'm having trouble encoding the filename "
                            "of your livecd.  You may have better luck if "
                            "you move your DMG to the root of your drive "
                            "(ie: C:\)")

            self.statusInfoEdit.append(os.path.basename(self.live.dmg) + ' selected')

    #---------------------------------------------------------------------------------
    def terminate(self):
        """ Terminate any processes that we have spawned """
        self.live.terminate()

    #---------------------------------------------------------------------------------
    def _to_unicode(self, obj, encoding='utf-8'):
        if hasattr(obj, 'toUtf8'): # PyQt4.QtCore.QString
            obj = str(obj.toUtf8())
        if isinstance(obj, basestring):
            if not isinstance(obj, unicode):
                obj = unicode(obj, encoding, 'replace')
        return obj

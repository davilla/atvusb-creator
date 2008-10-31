

#include <QtCore/QDir>
#include <QtCore/QProcess>
#include <QtCore/QStringList>
#include <QtCore/QTemporaryFile>


#include "atvusbcreatorosx.h"


//----------------------------------------------------------------------   
//----------------------------------------------------------------------   
AtvUsbCreatorOSX::AtvUsbCreatorOSX() : AtvUsbCreatorBase() {
}

//----------------------------------------------------------------------   
AtvUsbCreatorOSX::~AtvUsbCreatorOSX() {
}

//---------------------------------------------------------------------- 
void AtvUsbCreatorOSX::mount_disk() {
  QString         result;

  result = do_process(QString("/usr/sbin/diskutil"), QStringList() << "mountDisk" << m_drive);
  //self.log.debug('%s %s' % (status, rtn))
  emit status(QString("  mount_disk settling delay (10 seconds)") );
  qthread::sleep(10);
}

//---------------------------------------------------------------------- 
void AtvUsbCreatorOSX::umount_disk() {
  QString         result;

  result = do_process(QString("/usr/sbin/diskutil"), QStringList() << "unmountDisk" << m_drive);
  //self.log.debug('%s %s' % (status, rtn))
  emit status("  umount_disk settling delay (10 seconds)");
  qthread::sleep(10);
}

//---------------------------------------------------------------------- 
void AtvUsbCreatorOSX::detect_removable_drives() {
  QString         result;
  QStringList     devices;
  QStringList::const_iterator device;
  
  m_devices.clear();

  result = do_process(QString("/usr/sbin/diskutil"), QStringList() << "list");
  devices << result.split('\n');
  
  for (device = devices.begin(); device != devices.end(); ++device) {
    QString         protocol, ejectable, disksize;
    
    if (device->startsWith("/dev")) {
      //std::cout << QString(*device).toStdString() << std::endl;
      QStringList       device_info;
      QStringList::const_iterator info;

      result = do_process(QString("/usr/sbin/diskutil"), QStringList() << "info" << *device);
      device_info << result.split('\n');
      
      for (info = device_info.begin(); info != device_info.end(); ++info) {
        //std::cout << info->toStdString() << std::endl;
        QStringList       words = info->split(':');

        if (words[0].remove(' ') == "Protocol") {
          protocol = words[1].remove(' ');
        }
        if (words[0].remove(' ') == "Ejectable") {
          ejectable = words[1].remove(' ');
        }
        if (words[0].remove(' ') == "TotalSize") {
          disksize = words[1].remove(' ');
        }
      }
      
      if (protocol == "USB" && ejectable == "Yes") {
        m_devices << *device;
        //TODO: what is the other stuff for?
        /*
         //
         //label = None
         self.drives[drive] = {
         'mount'   : drive,
         'udi'     : None,
         'mounted' : False,
         }
         */
      }
    }
  }
  
  if (m_devices.empty()) {
    throw AtvUsbCreatorException("Unable to find any USB drives");
  }
}

//---------------------------------------------------------------------- 
void AtvUsbCreatorOSX::extract_bootefi() {
  QStringList     arguments;
  QString         result;
  QString         mount_point;
  QString         bootefi_src, osboot;

  emit status("Extracting boot.efi ...");
  emit progress(0);
  emit maxprogress(100);
  // mount the dmg disk image
  // TODO: need a temporary mount point, this is messy
  QDir            current_dir( QString(".") );
  {
    QTemporaryFile file;
    if (file.open()) {
      mount_point = file.fileName();
      // file.fileName() returns the unique file name
    }
    // the QTemporaryFile destructor removes the temporary file
  }
  current_dir.mkdir(mount_point);
  
  arguments << "attach" << m_dmg_path << "-readonly" << "-mountroot" << mount_point;
  result = do_process(QString("hdiutil"), arguments);
  //if
  //    self.log.warning("Unable to mount device: %s" %(rtn) )
  //    return
  emit progress(33);
  // copy boot.efi to staging
  bootefi_src = mount_point + "/OSBoot/usr/standalone/i386/boot.efi";
  result = do_process(QString("cp"), QStringList() << bootefi_src << m_bootefi_path);
  emit progress(66);
  // unmount the dmg disk image
  osboot =  mount_point + "/OSBoot";
  result = do_process(QString("hdiutil"), QStringList() << "detach" << osboot);
  //if status:
  //    self.log.warning("Unable to unmount AppleTV Update DMG")
  emit progress(100);

  /*
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
  # copy boot.efi to staging
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
  */
}   
                 
//---------------------------------------------------------------------- 
void AtvUsbCreatorOSX::extract_7z_image(QString const& fcr_archive_path, QString const& fcr_hfs_image_path, QString const& fcr_staging_folder){
  assert(QFile::exists(fcr_archive_path));
  assert(!QFile::exists(fcr_hfs_image_path));
  emit status(QString("  extracting %1").arg(fcr_archive_path));
  const QString cmd = "tools/osx/7za";
  int ret = QProcess::execute(cmd, QStringList() << "e" << "-bd" << "-y" << "-o" << fcr_staging_folder << fcr_archive_path);
  if(ret)
    emit status(QString(" unable to extract %1").arg(fcr_archive_path));
}

//---------------------------------------------------------------------- 
bool AtvUsbCreatorOSX::create_image() {
  bool ret;
  emit status("Creating USB Flash Disk...");
  emit progress(0);
  emit maxprogress(100);

  // unmount the target disk
  umount_disk();

  // partition the target disk
  emit progress(25);
  emit status("  partition the target disk");
  ret = partition_disk();
  if (!ret) {
    emit status("  partition_disk failed");
    return ret;
  }
  // install recovery onto target disk
  emit progress(50);
  emit status("  install recovery onto target disk");
  ret = install_recovery();
  if (!ret) {
      emit status("  install_recovery failed");
      return ret;
  }
  // install patchstick onto target disk
  emit progress(75);
  emit status("  install patchstick onto target disk");
  ret = install_patchstick();
  if (!ret) {
      emit status("  install_patchstick failed");
      return ret;
  }
  emit progress(100);
  umount_disk();

  return true;
}

//---------------------------------------------------------------------- 
bool AtvUsbCreatorOSX::partition_disk() {
/*
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
  */
  return true;
}

//---------------------------------------------------------------------- 
bool AtvUsbCreatorOSX::install_recovery() {
/*
  # mount recovery partition at our specific mount point so we can find it
  os_cmd = 'mount_hfs "%s" "%s"' %(self.drive_recovery , self.tmp_folder)
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
      os_cmd = 'umount -f "%s"' %(self.tmp_folder)
      commands.getstatusoutput(os_cmd)
      progress.status("Unable to mount image: %s" %(rtn) )
      return False

  progress.status("  copy files to target disk")
  # copy contents of recovery seed to recovery on flash
  mount_point = mount_point + '/Recovery'
  shutil.copy(mount_point + '/mach_kernel', self.tmp_folder)
  shutil.copy(mount_point + '/BootLogo.png', self.tmp_folder)
  shutil.copy(mount_point + '/com.apple.Boot.plist', self.tmp_folder)
  shutil.copytree(mount_point + '/System', self.tmp_folder + '/System')
  shutil.copy(self.bootefi, self.tmp_folder)
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
  os_cmd = 'umount -f "%s"' %(self.tmp_folder)
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
*/
  return true;
}

//---------------------------------------------------------------------- 
bool AtvUsbCreatorOSX::install_patchstick() {
  assert(m_drive_patchstick.count());
  int ret = QProcess::execute("mount_msdos", QStringList() 
                              << m_drive_patchstick << m_tmp_folder);
  if(ret){
    emit status(QString("Unable to mount PATCHSTICK: %1").arg(ret) );
    return false;
  }
  emit status("  copy files to target disk");
  // now install the payloads onto the "PATCHSTICK" volume
  std::vector<INSTALLER>::const_iterator it = getrInfoData().installers().begin();
  std::vector<INSTALLER>::const_iterator end = getrInfoData().installers().end();
  for(;it != end; ++it){
    if(it->install){
      install_payload(*it, m_tmp_folder);
      break;
    }
  }
  //always sync to force to physical disk
  QProcess::execute("sync");
  ret = QProcess::execute("umount", QStringList()
                          << "-f" << m_tmp_folder
                          );
  if(ret){
    emit status(QString("Unable to unmount PATCHSTICK: %1").arg(ret) );
    return false;
  }
  return true;
}

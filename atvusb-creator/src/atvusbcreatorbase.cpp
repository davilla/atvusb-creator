
#include <QtCore/QDir>
#include <QtCore/QFileInfo>

#include "atvusbcreatorbase.h"

//---------------------------------------------------------------------- 
//---------------------------------------------------------------------- 
AtvUsbCreatorBase::AtvUsbCreatorBase() {
  // find the launch path
  QDir        current_dir( QString(".") );
  
  // this folder should already exists as the payloads will be extracted from it
  m_payload_folder = current_dir.absolutePath() + QDir::separator() + "payloads";

  m_tmp_folder = current_dir.tempPath();
  // check for staging/downloads folders, make them if they don't exist
  m_staging_folder = current_dir.absolutePath() + QDir::separator() + "staging";
  m_download_folder = current_dir.absolutePath() + QDir::separator() + "downloads";
  if ( !current_dir.exists(m_staging_folder)) {
    current_dir.mkdir(m_staging_folder);
  }
  if ( !current_dir.exists(m_download_folder)) {
    current_dir.mkdir(m_download_folder);
  }

  // boot.efi is always extracted to staging/boot.efi
  m_bootefi_path = m_staging_folder + QDir::separator() + "boot.efi";

  // load up info_data from the default lists
  m_info_data.populateWithDefaults();
}

//---------------------------------------------------------------------- 
AtvUsbCreatorBase::~AtvUsbCreatorBase() {

}

//---------------------------------------------------------------------- 
void AtvUsbCreatorBase::setDMGPath(const QString &fcr_path) {
  m_dmg_path = fcr_path;
}

//---------------------------------------------------------------------- 
const QString& AtvUsbCreatorBase::getcrDMGPath() const {
  return m_dmg_path;
}

//---------------------------------------------------------------------- 
const QString& AtvUsbCreatorBase::getcrBootEFIPath() const {
  return m_bootefi_path;
}

//---------------------------------------------------------------------- 
void AtvUsbCreatorBase::setDrive(const QString &fcr_path) {
  m_drive = fcr_path;
}

//----------------------------------------------------------------------   
void AtvUsbCreatorBase::detect_removable_drives(){
  assert(0 && "implement me!");
}

//---------------------------------------------------------------------- 
const AtvUsbCreatorBase::tDeviceList& AtvUsbCreatorBase::getcrDevices(){
  return m_devices;
}

//---------------------------------------------------------------------- 
const QString& AtvUsbCreatorBase::getcrDownloadFolder(){
  return m_download_folder;
}

//---------------------------------------------------------------------- 
InfoData& AtvUsbCreatorBase::getrInfoData(){
  return m_info_data;
}

//---------------------------------------------------------------------- 
Logger& AtvUsbCreatorBase::logger() {
  return m_logger;
}


#include "atvusbcreatorbase.h"
//---------------------------------------------------------------------- 
AtvUsbCreatorBase::AtvUsbCreatorBase() {
  m_info_data.populateWithDefaults();
}

//---------------------------------------------------------------------- 
AtvUsbCreatorBase::~AtvUsbCreatorBase() {

}

//---------------------------------------------------------------------- 
void AtvUsbCreatorBase::setDMGPath(const std::string &fcr_path) {
  m_dmg_path = fcr_path;
}

//---------------------------------------------------------------------- 
const std::string& AtvUsbCreatorBase::getcrDMGPath() const {
  return m_dmg_path;
}

//---------------------------------------------------------------------- 
void AtvUsbCreatorBase::setBootEFIPath(const std::string &fcr_path) {
  m_bootefi_path = fcr_path;
}

//---------------------------------------------------------------------- 
const std::string& AtvUsbCreatorBase::getcrBootEFIPath() const {
  return m_bootefi_path;
}

//---------------------------------------------------------------------- 
void AtvUsbCreatorBase::setDrive(const std::string &fcr_path) {
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
InfoData& AtvUsbCreatorBase::getrInfoData(){
  return m_info_data;
}

//---------------------------------------------------------------------- 
Logger& AtvUsbCreatorBase::logger() {
  return m_logger;
}

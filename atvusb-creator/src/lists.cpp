#include "lists.h"
#include "default_list.h"

DMG_INFO& InfoData::atv_dmg_info(){
  return default_data::atv_dmg_info;
}

DMG_INFO& InfoData::osx_dmg_info(){
  return default_data::osx_dmg_info;
}

USB_INFO& InfoData::usb_info(){
  return default_data::usb_info;
}

HFS_INFO& InfoData::hfs_info(){
  return default_data::hfs_info;
}

std::vector<INSTALLER>& InfoData::installers(){
  return m_installers;
}

std::vector<BACKUP>& InfoData::backups(){
  return m_backup;
}

std::vector<RESTORE>& InfoData::restores(){
  return m_restore;
}

std::vector<PATCHSTICK>& InfoData::patchsticks(){
  return m_patchsticks;
}

std::vector<PACKAGE>& InfoData::packages(PATCHSTICK& fr_which_patchstick){
  return m_packages[fr_which_patchstick.name];
}

std::vector<LINUX_VIDEO>& InfoData::linux_video(){
  return m_linux_video;
}

std::vector<LINUX_IR>& InfoData::linux_ir(){
  return m_linux_ir;
}

//---------------------------------------------------------------------- 
void InfoData::populateWithDefaults(){
  load_installers();
  load_patchsticks();
  load_packages();
}

//---------------------------------------------------------------------- 
void InfoData::load_installers(void) {
  int       index;
  
  for( index = 0; index < 8; index++) {
    if ( default_data::installers[index].enable ) {
      m_installers.push_back(default_data::installers[index]);
    }
  }
  
  for( index = 0; index < 2; index++) {
    m_backup.push_back(default_data::backup[index]);
  }
  
  for( index = 0; index < 2; index++) {
    m_restore.push_back(default_data::restore[index]);
  }
  
  for( index = 0; index < 18; index++) {
    m_linux_video.push_back(default_data::linux_video[index]);
  }
  
  for( index = 0; index < 2; index++) {
    m_linux_ir.push_back(default_data::linux_ir[index]);
  }
}

//---------------------------------------------------------------------- 
void InfoData::load_patchsticks(void) {
  int       index;
  
  m_patchsticks.clear();
  
  for( index = 0; index < 6; index++) {
    if ( default_data::patchsticks[index].enable ) {
      m_patchsticks.push_back(default_data::patchsticks[index]);
    }
  }
}

//---------------------------------------------------------------------- 
void InfoData::load_packages() {
  int       index;
  
  m_packages.clear();
  for(unsigned int i = 0; i < m_patchsticks.size(); ++i){
  PATCHSTICK &patchstick = m_patchsticks[i];
  for( index = 0; index < 21; index++) {
    if ( default_data::packages[index].enable ) {
      std::string::size_type loc = default_data::packages[index].depends.find(patchstick.depends, 0);
      if( loc != std::string::npos ) {
        m_packages[patchstick.name].push_back(default_data::packages[index]);
      }
    }
  }
  }
}
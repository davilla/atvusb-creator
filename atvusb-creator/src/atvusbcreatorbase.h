//   -*- c++ -*------------------------------------------------------------
//
//   Author:            Scott Davilla / Stephan Diederich
//
//   Project name:      atvusb-creator
//
//   Date:              10/2008
//
//   Class:             AtvUsbCreatorBase
//
//   Base class:        
//
//   Derived class(es): AtvUsbCreator{Win32,OSX,Linux} 
//
//   Exceptions:        AtvUsbCreatorException (derived from std::runtime_error)
//
//   Description:       Base class for usb-creator functionality, specialized for the platform when needed
//   
//   Copyright (C) 2008  TeamXBMC
//   This program is free software; you can redistribute it and/or
//   modify it under the terms of the GNU General Public License
//   as published by the Free Software Foundation; either version 2
//   of the License, or (at your option) any later version.
//   
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//   
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//   ---------------------------------------------------------------------- 

#ifndef ATVUSBCREATORBASE_H
#define ATVUSBCREATORBASE_H

#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>

#include <QtCore/QString>

#include "lists.h"

struct AtvUsbCreatorException : public std::runtime_error{
  AtvUsbCreatorException(const std::string &fcr_message):std::runtime_error(fcr_message){
  }
};

//just a dummy for a proper logger
struct Logger {
  void error(const std::string& fcr_message){
    std::cerr << fcr_message << std::endl;
  }
};

//---------------------------------------------------------------------- 
class AtvUsbCreatorBase {
public:
          AtvUsbCreatorBase();
  virtual ~AtvUsbCreatorBase();

  void setDMGPath(const QString &fcr_path);
  const QString& getcrDMGPath() const;
  
  const QString& getcrBootEFIPath() const;
  
  void setDrive(const QString &fcr_path);
    
  typedef std::vector<std::string> tDeviceList;
  virtual void detect_removable_drives() = 0;
  const tDeviceList& getcrDevices();
  
  const QString& getcrDownloadFolder();
  
  //get access to InfoData
  InfoData& getrInfoData();
  
  //get access to logger functionality
  Logger& logger();
  
protected:
  tDeviceList             m_devices; //gets populated in platform specific implementation
  
private:
  Logger                  m_logger;
  InfoData                m_info_data;
  // absolute paths to various items/folders
  QString                 m_drive;
  QString                 m_dmg_path;
  QString                 m_bootefi_path;
  QString                 m_tmp_folder;
  QString                 m_payload_folder;
  QString                 m_staging_folder;
  QString                 m_download_folder;
};
#endif //ATVUSBCREATORBASE_H




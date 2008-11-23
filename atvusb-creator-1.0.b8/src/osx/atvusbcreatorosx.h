//   -*- c++ -*------------------------------------------------------------
//
//   Author:            Stephan Diederich
//
//   Project name:      atvusb-creator
//
//   Date:              10/2008
//
//   Class:             AtvUsbCreatorOSX
//
//   Base class:        AtvUsbCreatorBase
//
//   Derived class(es): 
//
//   Exceptions:        
//
//   Description:       platform specific implementation of AtvUsbCreatorBase interface
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

#ifndef ATVUSBCREATOROSX_H
#define ATVUSBCREATOROSX_H

#include "atvusbcreatorbase.h"

class AtvUsbCreatorOSX: public AtvUsbCreatorBase
{
public:
    // constructors
    AtvUsbCreatorOSX();

    ~AtvUsbCreatorOSX();

  virtual void mount_disk();
  virtual void umount_disk();
  // Detect all removable USB storage devices using DiskUtil
  virtual void detect_removable_drives();
  virtual void extract_bootefi();
  virtual void extract_7z_image(QString const& fcr_archive_path, QString const& fcr_hfs_image_path, QString const& fcr_staging_folder);
  virtual bool create_image();
  virtual bool partition_disk();
  virtual bool install_recovery();
  virtual bool install_patchstick();
private:

};
#endif //ATVUSBCREATOROSX_H

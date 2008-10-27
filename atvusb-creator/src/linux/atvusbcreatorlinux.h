// -*- c++ -*------------------------------------------------------------
//
/// @author Stephan Diederich
///
/// @date 10/2008
///
/// @class AtvUsbCreatorLinux
///
/// @brief platform specific implementation of AtvUsbCreatorBase interface
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
#ifndef ATVUSBCREATORLINUX_H
#define ATVUSBCREATORLINUX_H

// system includes

// project includes

// local includes
#include "atvusbcreatorbase.h"

class AtvUsbCreatorLinux : public AtvUsbCreatorBase
{
  public:
    // constructors
    AtvUsbCreatorLinux();

    ~AtvUsbCreatorLinux();
    
    ///Detects all removable USB storage devices using HAL via D-Bus
    virtual void detect_removable_drives();
private:


};
#endif // ATVUSBCREATORLINUX_H

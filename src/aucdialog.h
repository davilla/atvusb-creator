//   -*- c++ -*------------------------------------------------------------
//
//   Author:            Scott Davilla / Stephan Diederich
//
//   Project name:      atvusb-creator
//
//   Date:              10/2008
//
//   Class:             aucDialog
//
//   Base class:        
//
//   Derived class(es): -
//
//   Exceptions:        
//
//   Description:       Implementation file for main ui dialog. uses platform specific
//                      AtvUsbCreatorBase implementation
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

#ifndef aucDialog_H
#define aucDialog_H

#include <QtGui/QDialog>
#include "aucthread.h"
#include "aucprogressthread.h"
#include "aucreleasedownloader.h"

//forwards
namespace Ui{ struct aucDialog;};
class AtvUsbCreatorBase;
class AucReleaseDownloader;

class aucDialog : public QDialog
{
  Q_OBJECT;
public:
  aucDialog();
  ~aucDialog();
  
public slots:
  void status(QString f_message);
  void progress(int);
  void maxprogress(int);
  
private slots:
  void select_file(void);
  void set_installer_pict(void);
  void set_installer_options(void);
  void update_options2(void);
  void update_options3(void);
  void update_options3_fromcheckbox(void);
  void populate_devices(void);
  void build_installer(void);
  void enable_widgets(bool f_enable);
  void enable_widgets();
  
  /**
   * Called by our ReleaseDownloader thread upon completion.
   * Upon success, the thread passes in the filename of the downloaded release.
   * @param f_dmg   If the 'dmg' argument is not an existing file, then
   * it is assumed that the download failed and 'dmg' should contain
   * the error message.
   */
  void download_complete(QString f_dmg);
private:
  //private helpers
  void set_installers(void);
  void connect_slots(void);
  
  static AtvUsbCreatorBase* createPlatformSpecificCreator();

  QString get_selected_drive(void);
  QString get_appletv_dmg_url(void);
  
  //members
  Ui::aucDialog*        mp_ui;
  AtvUsbCreatorBase*    mp_creator;
  AucProgressThread     m_progress_thread;
  AucThread             m_thread;
  AucReleaseDownloader m_release_downloader;
};

#endif
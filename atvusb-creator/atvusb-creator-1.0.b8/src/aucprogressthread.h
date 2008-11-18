//   -*- c++ -*------------------------------------------------------------
//
//   Author:            Scott Davilla / Stephan Diederich
//
//   Project name:      atvusb-creator
//
//   Date:              10/2008
//
//   Class:             AucProgressThread
//
//   Base class:        
//
//   Derived class(es): 
//
//   Exceptions:        
//
//   Description:       formerly known as ProgressThread A thread that monitors the progress of Live USB creation.
//                      This thread periodically checks the amount of free space left on the 
//                      given drive and sends a signal to our main dialog window to update the
//                      progress bar.
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

#ifndef AUCPROGRESSTHREAD_H
#define AUCPROGRESSTHREAD_H

#include <QtCore/QThread>

class AucProgressThread : public QThread
{
  Q_OBJECT;
  
public:
	AucProgressThread(QObject* fp_parent = 0);
  ~AucProgressThread();
  
  void setData(int f_size, QString f_drive, int f_freebytes);
  
  void run();
  void terminate();
  
signals:
  void maxprogress(int);
  void progress(int);
  
private:
  int m_total_size;
  int m_orig_free;
  int m_get_free_bytes;
  QString m_drive;
};
#endif //AUCPROGRESSTHREAD_H

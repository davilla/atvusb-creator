//   -*- c++ -*------------------------------------------------------------
//
//   Author:            Scott Davilla / Stephan Diederich
//
//   Project name:      atvusb-creator
//
//   Date:              10/2008
//
//   Class:             AucThread
//
//   Base class:        
//
//   Derived class(es): 
//
//   Exceptions:        
//
//   Description:       formerly known as LiveUSBThread,  main creator thread
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

#ifndef AUCTHREAD_H
#define AUCTHREAD_H

#include <QtCore/QThread>

class AtvUsbCreatorBase;
class AucProgressThread;

class AucThread : public QThread
{
  Q_OBJECT;
public:
  //TODO:thread and creator are not optional, use references
  AucThread(AtvUsbCreatorBase* fp_creator, AucProgressThread* fp_progress, QObject* fp_parent = 0);
  ~AucThread();

  void setMaxProgress(int f_max){
    emit(maxprogress(f_max)); 
  }
  
  void updateProcess(int f_value){
      emit(progress(f_value));
  }
  
  void run();
  
signals:
  void progress(int);
  void maxprogress(int);
  void status(QString);
    
private:
  AtvUsbCreatorBase* mp_creator; 
  AucProgressThread* mp_progress; 
};
#endif //AUCTHREAD_H

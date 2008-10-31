#include "aucthread.h"

#include <cassert>
#include <QtCore/QDateTime>
#include <QtCore/QFile>

#include "aucprogressthread.h"
#include "atvusbcreatorbase.h"

//---------------------------------------------------------------------- 
//---------------------------------------------------------------------- 
AucThread::AucThread(AtvUsbCreatorBase* fp_creator, AucProgressThread* fp_progress, QObject* fp_parent):
  QThread(fp_parent), mp_creator(fp_creator), mp_progress(fp_progress) {

}

//---------------------------------------------------------------------- 
AucThread::~AucThread(){
  wait();
}

//---------------------------------------------------------------------- 
void AucThread::run(){
  QDateTime now = QDateTime::currentDateTime();

  try{
    //if boot.efi is not present, extract it from the dmg
    if(!QFile::exists(mp_creator->getcrBootEFIPath())){
      //If the DMG looks familar, verify it's SHA1SUM
      //TODO: false should read: if not self.parent.opts.noverify:
      if(false){
//         if self.live.get_atv_dmg_info():
         emit status("Verifying SHA1 of DMG image...");
//         if not self.live.verify_image(progress=self):
        emit status("Error: The SHA1 of your AppleTV Update DMG is "
        "invalid.  You can run this program with "
        "the --noverify argument to bypass this "
        "verification check.");
        return;
      }
      mp_creator->extract_bootefi();
    }
    bool ret = false;
    /*
self.live.extract_recovery(progress=self)
status = self.live.create_image(progress=self)
#
    */
  int duration = now.secsTo(QDateTime::currentDateTime());
  if (!ret)
    emit status(QString("Failed! (%1 sec)").arg(duration));
  else
    emit status(QString("Complete! (%1 sec)").arg(duration));
  } catch(AtvUsbCreatorException& e){
    emit status(QString::fromStdString(e.what()));
    emit status("ATV-Bootloader creation failed!");
  }
}
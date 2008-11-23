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
      //TODO: true should read: if not self.parent.opts.noverify:
      if(true){
        emit status("Verifying SHA1 of DMG image...");
        if(!mp_creator->verify_image()){
            emit status("Error: The SHA1 of your AppleTV Update DMG is "
                        "invalid.  You can run this program with "
                        "the --noverify argument to bypass this "
                        "verification check.");
          return;
        } else
          emit status("SHA1 matched!");
      }
      mp_creator->extract_bootefi();
    }
    mp_creator->extract_recovery();
    bool ret = mp_creator->create_image();
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
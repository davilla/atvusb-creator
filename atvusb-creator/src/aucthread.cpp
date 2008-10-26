#include "aucthread.h"
#include "aucprogressthread.h"
#include "atvusbcreatorbase.h"

AucThread::AucThread(AtvUsbCreatorBase* fp_creator, AucProgressThread* fp_progress, QObject* fp_parent):
  QThread(fp_parent), mp_creator(fp_creator), mp_progress(fp_progress)
{
}

AucThread::~AucThread(){
  wait();
}

void AucThread::run(){
  assert(0);
/*
  now = datetime.now()
  try:
# if boot.efi is not present, extract it from the dmg
  if not os.path.exists(self.live.bootefi):
# If the DMG looks familar, verify it's SHA1SUM
if not self.parent.opts.noverify:
if self.live.get_atv_dmg_info():
self.status("Verifying SHA1 of DMG image...")
if not self.live.verify_image(progress=self):
self.status("Error: The SHA1 of your AppleTV Update DMG is "
"invalid.  You can run this program with "
"the --noverify argument to bypass this "
"verification check.")
return
self.live.extract_bootefi(progress=self)
#
self.live.extract_recovery(progress=self)
status = self.live.create_image(progress=self)
#
duration = str(datetime.now() - now).split('.')[0]
if (status == False): 
self.status("Failed! (%s)" % duration)
else:
self.status("Complete! (%s)" % duration)

except LiveUSBError, e:
self.status(str(e))
self.status("ATV-Bootloader creation failed!")
*/
}
#include "aucprogressthread.h"

//---------------------------------------------------------------------- 
//---------------------------------------------------------------------- 
AucProgressThread::AucProgressThread(QObject* fp_parent):
  QThread(fp_parent), m_total_size(0), m_orig_free(0), m_get_free_bytes(0)
{
}

//---------------------------------------------------------------------- 
AucProgressThread::~AucProgressThread() {
  wait();
}

//---------------------------------------------------------------------- 
void AucProgressThread::setData(int f_size, QString f_drive, int f_freebytes) {
  m_total_size = f_size / 1024;
  m_drive = f_drive;
  m_get_free_bytes = f_freebytes;
  m_orig_free = m_get_free_bytes;
  emit maxprogress(m_total_size) ;
}


//---------------------------------------------------------------------- 
void AucProgressThread::run() {
  while (true){
    int value = (m_orig_free - m_get_free_bytes) / 1024;
    emit progress(value);
    if (value >= m_total_size)
      break;
    sleep(4000);
  }
}

//---------------------------------------------------------------------- 
void AucProgressThread::terminate() {

  emit progress(m_total_size);
  QThread::terminate();
}
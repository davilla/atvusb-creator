#include "atvusbcreatorosx.h"
#include <QtCore/QProcess>

void AtvUsbCreatorOSX::detect_removable_drives(){
  m_devices.clear();
  const QString program = "/usr/sbin/diskutil";
  QStringList arguments;
  arguments << "list";
  QProcess process;
  process.start(program, arguments);
  if(!process.waitForStarted())
    throw AtvUsbCreatorException((program + " could not be started").toStdString());
  if(!process.waitForFinished())
    throw AtvUsbCreatorException((program + " exited with failure %1").arg(process.exitCode()).toStdString());
  QList<QByteArray> devicelist_output = process.readAllStandardOutput().split('\n');
  for(QList<QByteArray>::const_iterator device_it = devicelist_output.begin(); device_it != devicelist_output.end(); ++device_it){
    QString device_name(*device_it);
    if(! device_name.startsWith("/dev"))
      continue;
    //print device
    //std::cout << QString(*it).toStdString() << std::endl;
    process.start(program, QStringList() << "info" << device_name);
    if(!process.waitForStarted())
      throw AtvUsbCreatorException((program + " could not be started").toStdString());
    if(!process.waitForFinished())
      throw AtvUsbCreatorException((program + " exited with failure %1").arg(process.exitCode()).toStdString());
    QList<QByteArray> device_output = process.readAllStandardOutput().split('\n');
    
    QString protocol, ejectable, disksize;
    for(QList<QByteArray>::const_iterator deviceinfo_it = device_output.begin(); deviceinfo_it != device_output.end(); ++deviceinfo_it){
      QString device_info(*deviceinfo_it);
//      std::cout << device_info.toStdString() << std::endl;
      QStringList words = device_info.split(':');
      if (words[0].remove(' ') == "Protocol"){
        protocol = words[1].remove(' ');
      }
      if (words[0].remove(' ') == "Ejectable")
        ejectable = words[1].remove(' ');  
      if (words[0].remove(' ') == "TotalSize")
        disksize = words[1].remove(' ');
    }
    if (protocol == "USB" && ejectable == "Yes"){
      m_devices.push_back(device_name.toStdString());
      //TODO: what is the other stuff for?
      /*
       //
       //label = None
       self.drives[drive] = {
       'mount'   : drive,
       'udi'     : None,
       'mounted' : False,
       }
       */
    }    
    }
  if (m_devices.empty())
    throw AtvUsbCreatorException("Unable to find any USB drives");
}
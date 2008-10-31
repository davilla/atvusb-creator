#include "atvusbcreatorlinux.h"
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusReply>
#include <QtCore/QStringList>
#include <QtCore/QDir>
#include <QtCore/QProcess>
#include <cassert>
//----------------------------------------------------------------------   
//----------------------------------------------------------------------   
AtvUsbCreatorLinux::AtvUsbCreatorLinux() : AtvUsbCreatorBase() {
}


//----------------------------------------------------------------------   
AtvUsbCreatorLinux::~AtvUsbCreatorLinux() {
}


//----------------------------------------------------------------------   
namespace {

  template <QVariant::Type T_Type>
      QVariant callAndReturnResponse(QDBusInterface& fr_dbus_interface, const QString& fr_method, const QString& fr_arg, QString f_arg_optional = QString()){
    QDBusMessage reply;
    if(f_arg_optional.isEmpty())
      reply = fr_dbus_interface.call( fr_method, fr_arg );
    else
      reply = fr_dbus_interface.call( fr_method, fr_arg, f_arg_optional);
    if(reply.type() != QDBusMessage::ReplyMessage){
      if(reply.type() == QDBusMessage::ErrorMessage)
        throw AtvUsbCreatorException("DBus error: " + reply.errorMessage().toStdString());
      throw AtvUsbCreatorException("Unknown DBus error");
    }
    if(!reply.arguments().size() || reply.arguments()[0].type() != T_Type)
      throw AtvUsbCreatorException("DBus error: Unknown DBUS response");
    return reply.arguments()[0];
  }

}

//----------------------------------------------------------------------   
void AtvUsbCreatorLinux::mount_disk() {
  assert(0 && "implement me! or better, what's the volume path?");
  QString volume_path; // = ????
  unsigned int retries = 5;
  QDir dir(volume_path);
  while (! dir.exists() && retries--) {
      QProcess::execute("partprobe", QStringList() << m_drive);
      emit status(QString("rescanning partition table failed to mount %1").arg(volume_path));
      qthread::sleep(1);
  }
}

//----------------------------------------------------------------------   
void AtvUsbCreatorLinux::umount_disk() {
  assert(0 && "implement me! fixup drives list");
  QString mount_point; // = self.drives[self.drive]['mount']
  QDir dir(mount_point);
  if( dir.exists() )
    QProcess::execute("umount ", QStringList() << mount_point);
}

//----------------------------------------------------------------------   
void AtvUsbCreatorLinux::detect_removable_drives()
{
  m_devices.clear();
  QDBusInterface computer("org.freedesktop.Hal", "/org/freedesktop/Hal/Manager", "org.freedesktop.Hal.Manager", QDBusConnection::systemBus());

  //TODO how to get force flag here?
//         if self.opts.force:
//           devices = self.hal.FindDeviceStringMatch('block.device',
//               self.opts.force)
//         else:
//           devices = self.hal.FindDeviceByCapability("storage")
  //get storage devices
  QStringList devices = callAndReturnResponse<QVariant::StringList>(computer, "FindDeviceByCapability", "storage" ).toStringList();
  for(unsigned int i = 0; i< devices.size(); ++i){
    QString current_device_string = devices[i];
    //get few infos about this device
    QDBusInterface device("org.freedesktop.Hal", current_device_string, "org.freedesktop.Hal.Device" , QDBusConnection::systemBus());
    QString bus = callAndReturnResponse<QVariant::String>(device, "GetPropertyString", "storage.bus" ).toString();
    bool removable = callAndReturnResponse<QVariant::Bool>(device, "GetPropertyBoolean", "storage.removable" ).toBool();
    if(bus == "usb" && removable){
      if(callAndReturnResponse<QVariant::Bool>(device, "GetPropertyBoolean", "block.is_volume" ).toBool()){
        m_devices << callAndReturnResponse<QVariant::String>(device, "GetPropertyString", "block.device").toString();
      } else {
        QStringList children = callAndReturnResponse<QVariant::StringList>(computer, "FindDeviceStringMatch", "info.parent", current_device_string).toStringList();
        for(unsigned int k = 0; k<children.size(); ++k){
          QString child_device_string = children[k];
          QDBusInterface child_device("org.freedesktop.Hal", child_device_string, "org.freedesktop.Hal.Device" , QDBusConnection::systemBus());
          if(callAndReturnResponse<QVariant::Bool>(child_device, "GetPropertyBoolean", "block.is_volume" ).toBool()){
            m_devices << callAndReturnResponse<QVariant::String>(device, "GetPropertyString", "block.device").toString();
          }
      }
    }
     //TODO
//       mount = str(dev.GetProperty('volume.mount_point'))
//       self.drives[str(dev.GetProperty('block.device'))] = {
//     'mount'   : mount,
//     'udi'     : dev,
//     'mounted' : False,
//       }
    }
  }
  if (m_devices.empty())
    throw AtvUsbCreatorException("Unable to find any USB drives");
}

//----------------------------------------------------------------------   
void AtvUsbCreatorLinux::extract_bootefi(){
  emit status("Extracting boot.efi ...");
  emit progress(0);
  emit maxprogress(100);
  QDir temp_dir(QDir::tempPath() + QDir::separator() + "atvusb-creatorExtractTemp");
  if(!temp_dir.exists())
    if(!temp_dir.mkpath(temp_dir.absolutePath())){
      emit status(QString("Could not create tempdir %1").arg(temp_dir.absolutePath()));
      return;
    }
  emit status(temp_dir.absolutePath());
  int exit_code = QProcess::execute("dmg2img ", QStringList() << m_dmg_path);
  if(exit_code){
    emit status("Ouch,  could not convert dmg2img");
    temp_dir.rmpath ( temp_dir.absolutePath() );
    return;
  }
  QString img_path = m_dmg_path;
  img_path[img_path.count() -1]='g';
  img_path[img_path.count() -2]='m';
  img_path[img_path.count() -3]='i';
  emit status(m_dmg_path);
  emit status(img_path);
  emit progress(33);
  exit_code = QProcess::execute("mount -t hfsplus -o loop ", QStringList() << img_path << temp_dir.absolutePath());
  if(exit_code){
    emit status("Ouch, could not mount dmg2img'ed image");
    temp_dir.rmpath ( temp_dir.absolutePath() );
    return;
  }      
  QString bootefi_src = temp_dir.absolutePath() + QDir::separator() + "System" + QDir::separator() + " Library" + QDir::separator() + "CoreServices" + QDir::separator() + "boot.efi";
  if(!QFile::copy(bootefi_src, m_bootefi_path)){
    emit status(QString("Ouch, could not copy %1 to %2").arg(bootefi_src).arg(m_bootefi_path));
  }
  emit progress(66);
  exit_code = QProcess::execute("umount", QStringList() << m_tmp_folder);
  if(exit_code){
    emit status(QString("Could not umount %1").arg(m_tmp_folder));
  }
  emit progress(100);
  temp_dir.rmpath ( temp_dir.absolutePath() );
}

//----------------------------------------------------------------------   
bool AtvUsbCreatorLinux::create_image(){
  assert(0 && "implement me!");
  return false;
}

//----------------------------------------------------------------------   
bool AtvUsbCreatorLinux::partition_disk(){
  assert(0 && "implement me!");
  return false;
}

//----------------------------------------------------------------------   
bool AtvUsbCreatorLinux::install_recovery(){
  assert(0 && "implement me!");
  return false;
}

//----------------------------------------------------------------------   
bool AtvUsbCreatorLinux::install_patchstick(){
  assert(0 && "implement me!");
  return false;
}



#include "atvusbcreatorlinux.h"
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusReply>
#include <QtCore/QStringList>

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
  assert(0 && "implement me!");
}

//----------------------------------------------------------------------   
void AtvUsbCreatorLinux::umount_disk() {
  assert(0 && "implement me!");
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
        m_devices.push_back(callAndReturnResponse<QVariant::String>(device, "GetPropertyString", "block.device").toString().toStdString());
      } else {
        QStringList children = callAndReturnResponse<QVariant::StringList>(computer, "FindDeviceStringMatch", "info.parent", current_device_string).toStringList();
        for(unsigned int k = 0; k<children.size(); ++k){
          QString child_device_string = children[k];
          QDBusInterface child_device("org.freedesktop.Hal", child_device_string, "org.freedesktop.Hal.Device" , QDBusConnection::systemBus());
          if(callAndReturnResponse<QVariant::Bool>(child_device, "GetPropertyBoolean", "block.is_volume" ).toBool()){
            m_devices.push_back(callAndReturnResponse<QVariant::String>(device, "GetPropertyString", "block.device").toString().toStdString());
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
  assert(0 && "implement me!");
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



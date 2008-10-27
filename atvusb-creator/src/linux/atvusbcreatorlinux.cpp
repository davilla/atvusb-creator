#include "atvusbcreatorlinux.h"
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusConnection>

AtvUsbCreatorLinux::AtvUsbCreatorLinux()
                : AtvUsbCreatorBase()
{
}


AtvUsbCreatorLinux::~AtvUsbCreatorLinux()
{
}

//         def _get_device(device):
//       dev_obj = self.bus.get_object("org.freedesktop.Hal", device)
//       return dbus.Interface(dev_obj, "org.freedesktop.Hal.Device")

//         def _add_device(dev):
//       mount = str(dev.GetProperty('volume.mount_point'))
//       self.drives[str(dev.GetProperty('block.device'))] = {
//     'mount'   : mount,
//     'udi'     : dev,
//     'mounted' : False,
//       }

void AtvUsbCreatorLinux::detect_removable_drives()
{
  QDBusInterface computer("org.freedesktop.Hal", "/org/freedesktop/Hal/Manager", "org.freedesktop.Hal.Manager");

//     computer.Reboot()

//   
//       import dbus
//
//
//       self.drives = {}
//       self.bus = dbus.SystemBus()
//           hal_obj = self.bus.get_object("org.freedesktop.Hal",
//                                         "/org/freedesktop/Hal/Manager")
//           self.hal = dbus.Interface(hal_obj, "org.freedesktop.Hal.Manager")
// 
//           devices = []
//         if self.opts.force:
//           devices = self.hal.FindDeviceStringMatch('block.device',
//               self.opts.force)
//         else:
//           devices = self.hal.FindDeviceByCapability("storage")
// 
//         for device in devices:
//           dev = _get_device(device)
//           if self.opts.force or dev.GetProperty("storage.bus") == "usb" and \
//                dev.GetProperty("storage.removable"):
//                 if dev.GetProperty("block.is_volume"):
//           _add_device(dev)
//           continue
//           else: # iterate over children looking for a volume
//           children = self.hal.FindDeviceStringMatch("info.parent",
//                   device)
//                     for child in children:
//           child = _get_device(child)
//                         if child.GetProperty("block.is_volume"):
//           _add_device(child)
// 
//         if not len(self.drives):
//           raise LiveUSBError("Unable to find any USB drives")

}



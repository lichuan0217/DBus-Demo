import sys
import traceback

import gobject

import dbus
import dbus.mainloop.glib

DBUS_PATH = '/org/example/Credentials'
DBUS_INTERFACE = 'org.example.Credentials'


if __name__ == '__main__':

    token = "TOKEN"
    bus = dbus.SystemBus()
    try:
        object = bus.get_object(DBUS_INTERFACE, DBUS_PATH)
        object.emitAuthSignal(token, dbus_interface=DBUS_INTERFACE)
        print "Signal Send!"
    except dbus.DBusException:
        traceback.print_exc()
        sys.exit(1)

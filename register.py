import sys
import traceback

import gobject

import dbus
import dbus.mainloop.glib

DBUS_PATH = '/org/example/Credentials'
DBUS_INTERFACE = 'org.example.Credentials'


def auth_signal_handler(token):
    print("Received signal (by connecting using remote object) and it says: "
          + token)

if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

    bus = dbus.SystemBus()
    try:
        object = bus.get_object(DBUS_INTERFACE, DBUS_PATH)
        object.connect_to_signal(
            "UserAuthenticated",
            auth_signal_handler,
            dbus_interface=DBUS_INTERFACE)
    except dbus.DBusException:
        traceback.print_exc()
        sys.exit(1)

    print "Regist Signal \"UserAuthenticated\" callback!"
    loop = gobject.MainLoop()
    loop.run()

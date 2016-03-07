import gobject

import dbus
import dbus.service
import dbus.mainloop.glib

DBUS_NAME = 'org.example.Credentials'
DBUS_PATH = '/org/example/Credentials'
DBUS_INTERFACE = 'org.example.Credentials'


class SomeObject(dbus.service.Object):

    @dbus.service.signal(DBUS_INTERFACE)
    def UserAuthenticated(self, token):
        print "UserAuthenticated called! + ", token

    @dbus.service.method(DBUS_INTERFACE,
                         in_signature='s', out_signature='')
    def emitAuthSignal(self, token):
        print "emit UserAuthenticated"
        self.UserAuthenticated(token)


if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

    bus = dbus.SystemBus()
    name = dbus.service.BusName(DBUS_NAME, bus)
    object = SomeObject(bus, DBUS_PATH)

    mainloop = gobject.MainLoop()
    print "Running Auth service."
    mainloop.run()

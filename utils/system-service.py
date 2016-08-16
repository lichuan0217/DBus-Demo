import dbus
for service in dbus.SystemBus().list_names():
    print(service)

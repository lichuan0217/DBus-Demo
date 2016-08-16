import dbus
for service in dbus.SessionBus().list_names():
    print(service)

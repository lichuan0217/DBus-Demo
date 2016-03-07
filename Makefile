system_listener: system_listener.c
	gcc -o system_listener system_listener.c `pkg-config --libs --cflags gtk+-2.0 dbus-1 dbus-glib-1`


auth_listener: auth_listener.c
	gcc -o auth_listener auth_listener.c `pkg-config --libs --cflags gtk+-2.0 dbus-1 dbus-glib-1`

clean:
	rm -f system_listener auth_listener
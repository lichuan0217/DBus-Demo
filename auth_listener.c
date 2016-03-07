#include <glib.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <stdio.h>
 
void on_user_authenticated(DBusGProxy *proxy, gchar* token,
        gpointer user_data)
{
    printf("Token get : %s\n", token);
}
 
int main()
{
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
 
    g_type_init();
 
    GError *error = NULL;
    DBusGConnection *conn = dbus_g_bus_get(DBUS_BUS_SYSTEM, &error);
 
    if (error != NULL) {
        g_error("D-BUS Connection error: %s", error->message);
        g_error_free(error);
    }
 
    if (!conn) {
        g_error("D-BUS connection cannot be created");
        return 1;
    }
 
    DBusGProxy *proxy = dbus_g_proxy_new_for_name(conn,
            "org.example.Credentials",
            "/org/example/Credentials",
            "org.example.Credentials");
 
    if (!proxy) {
        g_error("Cannot create proxy");
        return 1;
    }
 
    dbus_g_proxy_add_signal(proxy, "UserAuthenticated", G_TYPE_STRING,
            G_TYPE_INVALID);
 
    dbus_g_proxy_connect_signal(proxy, "UserAuthenticated",
            G_CALLBACK(on_user_authenticated), NULL, NULL);
 
    g_message("Waiting D-BUS proxy callback for signal");
    g_main_loop_run(loop);
 
    return 0;
}
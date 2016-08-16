#include <gio/gio.h>

#define DBUS_NAME   "org.example.Credentials"
#define DBUS_PATH   "/org/example/Credentials"
#define DBUS_INTERFACE  "org.example.Credentials"

static void
on_signal (GDBusProxy *proxy,
           gchar      *sender_name,
           gchar      *signal_name,
           GVariant   *parameters,
           gpointer    user_data)
{
  gchar *parameters_str;

  parameters_str = g_variant_print (parameters, TRUE);
  g_print (" *** Received Signal: %s: %s\n",
           signal_name,
           parameters_str);
  g_free (parameters_str);
}

int main(int argc, char const *argv[])
{
GError *error;
GDBusProxy *proxy;
GMainLoop *loop = g_main_loop_new(NULL, FALSE);

  //    g_type_init();
error = NULL;
proxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SYSTEM,
                             G_DBUS_PROXY_FLAGS_NONE,
                                          NULL,
                                          DBUS_NAME,
                                          DBUS_PATH,
                                          DBUS_INTERFACE,
                                          NULL,
                                          &error);
    if (proxy == NULL) {
        g_printerr ("Error creating proxy: %s\n", error->message);
        g_error_free (error);
        goto out;
    }

    g_signal_connect(proxy,
                     "g-signal",
                     G_CALLBACK (on_signal),
                     NULL);

    g_message("Waiting D-BUS proxy callback for signal");
    g_main_loop_run(loop);

out:
    if (proxy != NULL) {
        g_object_unref(proxy);
    }
    if (loop != NULL) {
        g_object_unref(loop);
    }
return 0;
}
#include <stdio.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib.h>
#include <glib.h>

static DBusHandlerResult
dbus_filter (DBusConnection *connection, DBusMessage *message, void *user_data)
{
   if ( dbus_message_is_signal(message, "org.example.Credentials", "UserAuthenticated" ) )
   {
      DBusError   error;
      const char *token;
      dbus_bool_t res;

      dbus_error_init (&error);
      res = dbus_message_get_args ( message,
                                    &error,
                                    DBUS_TYPE_STRING, &token,
                                    DBUS_TYPE_INVALID);
      if (res) {
         g_message("Message UserAuthenticated received: %s", token);
         return DBUS_HANDLER_RESULT_HANDLED;
      } else {
         g_message("Not Message UserAuthenticated received!");
         return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
      }
   }
   return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

int main()
{
   DBusConnection *connection;
   DBusError error;
   /* glib main loop */
   GMainLoop *loop;
   loop = g_main_loop_new(NULL,FALSE);

   dbus_error_init(&error);

   connection = dbus_bus_get(DBUS_BUS_SYSTEM, &error);

   if ( dbus_error_is_set(&error) )
   {
      printf("Error connecting to the daemon bus: %s",error.message);
      dbus_error_free(&error);
      return 1;
   }

   dbus_bus_add_match (connection, "type='signal',interface='org.example.Credentials'", NULL);
   dbus_connection_add_filter (connection, dbus_filter, loop, NULL);
   /* dbus-glib call */
   dbus_connection_setup_with_g_main(connection, NULL);
   g_message("Waiting D-BUS proxy callback for signal");
   /* run glib main loop */
   g_main_loop_run(loop);
   return 0;
}
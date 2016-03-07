#Simple system DBUS example

This demo contain two part: **python version** and **C version**.

## Running Environment

Ubuntu 12.04

## Python Version

### Installation

To use DBus in python, you need use python-dbus.

	$ sudo apt-get install python-dbus

The python demo contains 4 scripts: 

- service.py  --  Set up the System DBus service.
- register.py --  Regist a callback on a signal in this DBus service.
- sender.py   --  Call a method on DBus service and trigger a signal.
- org.example.Credentials.conf  --  The configuration file for this DBus service.

### How to use

- Copy the configuration file into /etc/dbus-1/system.d/
- Start the service	

```shell
$ sudo python service.py
```

- Rigist the callback

```shell	
$ python register.py
```

- Send the signal

```shell	
$ python sender.py
```

## C Version

*Note : This version use the old dbus-glib, which has deprecated!!*

### Installation

The C Version demo contains 3 files:

- system_listener.c  --  Use connection filter to monitor the signal
- auth_listener.c    --  Use dbus-glib`s signal api to monitor the siganl
- Makefile           --  Compile the listener.

### How to use

- Copy the configuration file into /etc/dbus-1/system.d/
- Start the service	
```shell
$ sudo python service.py
```

- Make the listeners

```shell
$ make system_listener
$ make auth_listener
```

-- Add listeners

```shell
$ ./system_listener
$ ./auth_listener
```


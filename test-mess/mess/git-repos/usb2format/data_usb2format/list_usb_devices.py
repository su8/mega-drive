#!/usr/bin/python2
import dbus

bus = dbus.SystemBus()
proxy = bus.get_object("org.freedesktop.UDisks", "/org/freedesktop/UDisks")
iface = dbus.Interface(proxy, "org.freedesktop.UDisks")
devs = iface.EnumerateDevices()
for dev in devs:
    dev_obj = bus.get_object("org.freedesktop.UDisks", dev)
    dev = dbus.Interface(dev_obj, "org.freedesktop.DBus.Properties")

    if str(dev.Get('', 'DriveConnectionInterface')) == 'usb' and not str(dev.Get('', 'PartitionType')) and str(dev.Get('', 'DeviceIsMediaAvailable')) == '1':
        path = str(dev.Get('', 'DeviceFile'))
        vend = str(dev.Get('', 'DriveVendor'))
        model = str(dev.Get('', 'DriveModel'))
        size = dev.Get('', 'PartitionSize')
        SYMBOLS = (' KB', ' MB', ' GB', ' TB', ' PB', ' EB', ' ZB', ' YB')
        PREFIX = {}

        for i, s in enumerate(SYMBOLS):
            PREFIX[s] = 1 << (i + 1) * 10

        def convert_bytes(n):
            for s in reversed(SYMBOLS):
                if n >= PREFIX[s]:
                    value = float(n) / PREFIX[s]
                    return '%.1f%s' % (value, s)
            return '%.1fB' % n

        size2 = convert_bytes(size)
        print vend + ' ' + size2 + ', ' + path
        #print size2 + ' - ' + vend + ' ' + model + ', ' + path
        #print vend + ' ' + model + ', ' + path
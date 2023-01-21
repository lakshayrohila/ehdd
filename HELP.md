## Help _(as returned by `ehdd --help`)_:
```
Usage: sudo ehdd [OPTIONS] or [DEVICE NAMES]

Option                Meaning
 -h, --help            Show this text.
 -v, --version         Provide version information.
 -V, --verbose         Do not suppress the output of eject and udisksctl.
 -E, --ejectonly       Only eject the device.
 -S, --shutdownonly    Only shutdown the device.
 --byname              Same as ehdd device.
 --bylabel             Eject and/or shutdown device by name. Same as ejecting /dev/disk/by-label/device.
 --byuuid              Eject and/or shutdown device by uuid. Same as ejecting /dev/disk/by-uuid/device.
```

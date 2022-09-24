## Help (as returned by ehdd --help):
Usage: sudo ./ehdd [OPTIONS] or [DEVICE NAME]

Option                Meaning
 -h, --help            Show this text.
 -v, --version         Provide version information.
 -V, --versbose        Do not suppress the output of eject and udisksctl.
 -E, --ejectonly       Only eject the device.
 -S, --shutdownonly    Only shutdown the device.
 --byname              Same as ./ehdd device.
 --bylabel             Eject and/or shutdown device by name. Same as ./ehdd /dev/disk/by-label/device.
 --byuuid              Eject and/or shutdown device by uuid. Same as ./ehdd /dev/disk/by-uuid/device.
(NOTE: No options can be mixed except that -V, -E and -S can be used with options starting with --by).
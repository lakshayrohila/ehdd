## Install ehdd:
Perform these steps to install **ehdd**-

1. Get the latest `ehdd` source code from [Releases page](https://github.com/lakshayrohila/ehdd/releases).
2. Open up a terminal in the directory in which file was downloaded in **Step 1**.

Run these commands in the terminal-

3. ``` $ tar -xvzf ehdd-*.zip```
(replace `ehdd-*.zip` with the name of the file that is downloaded in **Step 1**).
4. ``` $ cd ehdd-*/```
(replace `ehdd-*/` with the name of the directory that has been created in **Step 3**).
5. ``` $ make```
6. ``` $ make install```

This would install `ehdd` to `/usr/bin`. To uninstall `ehdd`, read [UNINSTALL.md](./UNINSTALL.md)

You can also create a program ready to be used with `gdb` by replacing **Step 5** with-\
` $ make gdb`

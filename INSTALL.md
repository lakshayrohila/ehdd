## Install ehdd:

**ehdd** can be installed by two ways-

1. Installation from **binary** sources (packed as **tar.gz**)

2. Installation by compiling from source (**gcc** required as compiler)

#### These are the steps:

##### Method-1:

Perform these steps to install **ehdd** from its **already built binary** sources. These are available as **Releases** on [ehdd's Releases page](https://github.com/lakshayrohila/ehdd/releases).

1. Get the latest `ehdd` from [ehdd's Latest Release page](https://github.com/lakshayrohila/ehdd/releases/latest).

   ![ehdd releases page screenshot-1](https://ibb.co/ct0jdZM)

   You will see some options here:-

   ![ehdd releases page screenshot-2](https://ibb.co/SfK0YHC)

   Ones named as `ehdd-v...-x...tar.gz` are already built binary sources, while those named as `Source Code (...)` are the source codes from which binaries have been built. Note the `-x86`/`-x86_64` part here -- these are the specific architectures for which the binary source has been built.

   Download `-x86` for `32-bit` and `-x86_64` for `64-bit` computers.

2. Open up a terminal in the directory in which file was downloaded in **Step 1**.
   
   Run these commands in the terminal-
   
   - `$ tar -xvzf ehdd-*.tar.gz` (replace `ehdd-*.tar.gz` with the name of the file that is downloaded in **Step 1**).
   
   - `$ cd ehdd-*/` (replace `ehdd-*/` with the name of the directory that has been created in **Step 3**).
   
   - `$ ./install_ehdd.sh`

This would install `ehdd` to `/usr/bin`.

To uninstall `ehdd`, read [UNINSTALL.md](./UNINSTALL.md).

# Update from here!

##### Method-2:

Perform these steps to install **ehdd** by compiling it-

1. Get the latest `ehdd` source code from [Releases page](https://github.com/lakshayrohila/ehdd/releases). It can be found under **Assets > Source Code (tar.gz)**.

2. Open up a terminal in the directory in which file was downloaded in **Step 1**.
   
   Run these commands in the terminal-
   
   - `$ tar -xvzf ehdd-*.tar.gz` (replace `ehdd-*.tar.gz` with the name of the file that is downloaded in **Step 1**).
   - `$ cd ehdd-*/` (replace `ehdd-*/` with the name of the directory that has been created in **Step 3**).
   - `$ make`
   - `$ make install`

This would install `ehdd` to `/usr/bin`.

To uninstall `ehdd`, read [UNINSTALL.md](./UNINSTALL.md).

You can also create a program ready to be used with `gdb` by replacing **Step 5** with- `$ make gdb`.

**NOTE**: With this method of installation, the version set would default to **undefined**. To change this behavior, set custom version in file **ehdd.c**, line **15** (saying `#define VERSION "undefined"`).

So, for example if you want to set the version to say `foo`, then you would have to replace 
```
#define VERSION "undefined"
```
with
```
#define VERSION "foo"
```

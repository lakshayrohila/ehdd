## Install ehdd:

**ehdd** can be installed by two ways-

1. Installation from **.tar.gz** (**no compiler** such as **gcc** required)

2. Installation by compiling from source (**gcc** required as compiler)

#### These are the steps:

##### Method-1:

Perform these steps to install **ehdd** from its **.tar.gz**-

1. Get the latest `ehdd` from [Releases page](https://github.com/lakshayrohila/ehdd/releases). It can be found as **Assets > ehdd-v*version*-x86_64.tar.gz** (here **x86_64** means **64-bit**. If you want to install ehdd on a **32-bit** machine, then download **ehdd-v*version*-x86.tar.gz**).

2. Open up a terminal in the directory in which file was downloaded in **Step 1**.
   
   Run these commands in the terminal-
   
   - `$ tar -xvzf ehdd-*.tar.gz` (replace `ehdd-*.tar.gz` with the name of the file that is downloaded in **Step 1**).
   
   - `$ cd ehdd-*/` (replace `ehdd-*/` with the name of the directory that has been created in **Step 3**).
   
   - `$ ./install.sh`

This would install `ehdd` to `/usr/bin`.

To uninstall `ehdd`, read [UNINSTALL.md](./UNINSTALL.md).

##### Method-2:

Perform these steps to install **ehdd** by compiling it-

1. Get the latest `ehdd` source code from [Releases page](https://github.com/lakshayrohila/ehdd/releases). It can be found under **Assets > Source Code (tar.gz)**.

2. Open up a terminal in the directory in which file was downloaded in **Step 1**.
   
   Run these commands in the terminal-
   
   - `$ tar -xvzf ehdd-*.tar.gz` (replace `ehdd-*.tar.gz` with the name of the file that is downloaded in **Step 1**).
   - `$ cd ehdd-*/` (replace `ehdd-*/` with the name of the directory that has been created in **Step 3**).
   - `$ make`
   - `$ make install`

This would install `ehdd` to `/usr/bin`. Note that with this method of installation, the version set would default to **undefined**. To change this behavior, set custom version in file **ehdd.c**, line **15** (saying `#define VERSION "undefined"`).

To uninstall `ehdd`, read [UNINSTALL.md](./UNINSTALL.md).

You can also create a program ready to be used with `gdb` by replacing **Step 5** with- `$ make gdb`

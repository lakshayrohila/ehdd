## Installing ehdd:

**ehdd** can be installed by two methods:

1. Installation from **binary** sources (packed as **tar.gz**)

2. Installation by compiling from source (**gcc** required as compiler)

### Method-1:

Perform these steps to install **ehdd** from its **already built binary** sources. These are available as **Releases** on [ehdd's Releases page](https://github.com/lakshayrohila/ehdd/releases).

1. Get the latest `ehdd` from [ehdd's Latest Release page](https://github.com/lakshayrohila/ehdd/releases/latest).
   
   Go to the **Assets** section here.
   
   ![ehdd releases page screenshot-2](https://i.ibb.co/0sfZ41b/ehdd-release2.png)
   
   You will see some options here:-
   
   Ones named as `ehdd-v...-arch.tar.gz` are already built binary sources, while those named as `Source Code (...)` are the source codes from which binaries have been built (You can use these sources for installation by [Method-2](#method-2)). Note the `-arch` part here -- these are the specific architectures for which the specific binary has been built. Read [Binary Architectures](#binary-architectures) for more information on each architecture.

2. Open up a terminal in the directory in which file was downloaded in **Step 1**.
   
   Run these commands in the terminal-
   
   - `$ tar -xvzf ehdd-*.tar.gz` (replace `ehdd-*.tar.gz` with the name of the file that is downloaded in **Step 1**).
   
   - `$ cd ehdd-*/` (replace `ehdd-*/` with the name of the directory that has been created in **Step 3**).
   
   - `$ ./install_ehdd.sh`

This would install `ehdd` to `/usr/bin`.

To uninstall `ehdd`, please read [Uninstalling ehdd](#uninstalling-ehdd).

#### Binary Architectures

**ehdd** uses [toolchains](https://github.com/dimkr/toolchains) (thanks to the developers of the software!) to build each of its **official** release (only those present at the [Release page](https://github.com/lakshayrohila/ehdd/releases)), thus statically linking to [musl libc](https://musl.libc.org/).

The builds are done for all the architectures `toolchains` supports. Here is what each architecture means:

1. `aarch64`: This build supports **ARM-64 little-endian** architecture.
# CONTINUE FROM HERE
# add $(file ehdd-*)

### Method-2:

Perform these steps to install **ehdd** by compiling it:

1. Get the latest `ehdd` source code from [Releases page](https://github.com/lakshayrohila/ehdd/releases/latest). It can be found under **Assets > Source Code (tar.gz)**. Otherwise, you can also clone/download the whole repository to your computer.

2. Open up a terminal in the directory in which file was downloaded in **Step 1**.
   
   Run these commands in the terminal-
   
   - `$ tar -xvzf ehdd-*.tar.gz` (replace `ehdd-*.tar.gz` with the name of the file that is downloaded in **Step 1**).
   - `$ cd ehdd-*/` (replace `ehdd-*/` with the name of the directory that has been created in **Step 3**).
   - `$ make`
   - `$ make install`

This will install `ehdd` to `/usr/bin`.

To uninstall `ehdd`, read [Uninstalling ehdd](#uninstalling-ehdd).

You can also create a program ready to be debugged (used with `gdb`) by replacing **Step 5** with: `$ make gdb`.

## Uninstalling ehdd

1. Open up a terminal.
2. Run this command in the terminal:
   ```
   $ wget -qO - https://raw.githubusercontent.com/lakshayrohila/ehdd/master/build_helper/github/src/uninstall_ehdd.sh | bash
   ```

This will uninstall `ehdd` from your computer.

## Installing ehdd:

**ehdd** can be installed by two methods:

1. Installation from **binary** sources (packed as **tar.gz**)

2. Installation by compiling from source (**gcc** required as compiler)

### Method-1:

Perform these steps to install **ehdd** from its **already built binary** sources. These are available as **Releases** on [ehdd's Releases page](https://github.com/lakshayrohila/ehdd/releases).

1. Get the latest `ehdd` from [ehdd's Latest Release page](https://github.com/lakshayrohila/ehdd/releases/latest).
   
   Go to the **Assets** section here.
   
   ![image to be changed](https://example.com/)
   
   **Explanation of each download option:**
   
   Ones named as `ehdd-v...-arch.tar.gz` are already built binary sources, while those named as `Source Code (...)` are the source codes from which binaries have been built (You can use these sources for installation by [Method-2](#method-2)).
   
   Note the `-arch` part here -- these are the specific architectures for which the specific binary has been built.
   
   Read [Binary Architectures](#binary-architectures) for more information on each architecture.

2. Open up a terminal in the directory in which file was downloaded in **Step 1**.
   
   Run these commands in the terminal-
   
   _NOTE: You may need to change `*` with downloaded ehdd version._
   
   - `$ tar -xvzf ehdd-*.tar.gz`
   
   - `$ cd ehdd-*/`
   
   - `$ ./install_ehdd.sh`

This will install `ehdd` to `/usr/bin`.

To uninstall `ehdd`, please read [Uninstalling ehdd](#uninstalling-ehdd).

#### Binary Architectures

**ehdd** uses [toolchains](https://github.com/dimkr/toolchains) (thanks to the developers of the software!) to build each of its **official** release (only those present at the [Release page](https://github.com/lakshayrohila/ehdd/releases)), thus statically linking to [musl libc](https://musl.libc.org/).

The builds are done for all the architectures `toolchains` supports. Here is what each architecture means:

_`$file ...` means output of `file` command ran on the specific build's executable._

1. `aarch64`: This build supports **ARM 64-bit little-endian** architecture.
   
   _Please read [Wikipedia-AArch64](https://wikipedia.org/wiki/AArch64) for more information._
   
   ```
   $ file ehdd-aarch64
   ehdd-aarch64: ELF 64-bit LSB executable, ARM aarch64, version 1 (SYSV), statically linked, with debug_info, not stripped
   ```
2. `armeb`: This build supports **ARM 32-bit big-endian** architecture.
   
   _Please read [Wikipedia-AArch32](https://wikipedia.org/wiki/ARM_architecture_family#AArch32) for more information._
   
   ```
   $ file ehdd-armeb
   ehdd-armeb: ELF 32-bit MSB executable, ARM, EABI5 version 1 (SYSV), statically linked, with debug_info, not stripped
   ```
3. `arm`: This build supports **ARM 32-bit little-endian** architecture.
   
   _Please read [Wikipedia-Endianness](https://wikipedia.org/wiki/Endianness) for difference between **big** and **little** endianness._
   
   ```
   $ file ehdd-arm
   ehdd-arm: ELF 32-bit LSB executable, ARM, EABI5 version 1 (SYSV), statically linked, with debug_info, not stripped
   ```
4. `mips`: This build supports **MIPS 32-bit big-endian** architecture.
   
   _Please read [Wikipedia-MIPS](https://wikipedia.org/wiki/MIPS_architecture) for more information._
   
   ```
   $ file ehdd-mips
   ehdd-mips: ELF 32-bit MSB executable, MIPS, MIPS-I version 1 (SYSV), statically linked, with debug_info, not stripped
   ```
5. `mipsel`: This build supports **MIPS 32-bit little-endian** architecture.
   
   _Please read [Wikipedia-Endianness](https://wikipedia.org/wiki/Endianness) for difference between **big** and **little** endianness._
   
   ```
   $ file ehdd-mipsel
   ehdd-mipsel: ELF 32-bit LSB executable, MIPS, MIPS-I version 1 (SYSV), statically linked, with debug_info, not stripped
   ```
4. `i386`: This build supports **Intel 80386 32-bit** architecture. Thus, this build should support all **x86** architectures <sup>[[1]](https://superuser.com/a/103205/1765585)</sup>.
   
   _Please read [Wikipedia-i386](https://wikipedia.org/wiki/I386) for more information._
   
   ```
   $ file ehdd-i386
   ehdd-i386: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), statically linked, with debug_info, not stripped
   ```
5. `x86_64`: This build supports **x86_64 64-bit** architecture.
   
   _Please read [Wikipedia-X86-64](https://wikipedia.org/wiki/X86-64) for more information._
   
   ```
   $ file ehdd-x86_64
   ehdd-x86_64: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), statically linked, not stripped
   ```

### Method-2:

Perform these steps to install **ehdd** by compiling it:

1. Get the latest `ehdd` source code from [Releases page](https://github.com/lakshayrohila/ehdd/releases/latest). It can be found under **Assets > Source Code (tar.gz)**. Otherwise, you can also clone/download the whole repository to your computer.

2. Open up a terminal in the directory in which file was downloaded in **Step 1**.
   
   Run these commands in the terminal-
   
   _NOTE: You may need to change `*` with downloaded ehdd version._
   
   - `$ tar -xvzf ehdd-*.tar.gz`
   - `$ cd ehdd-*/`
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

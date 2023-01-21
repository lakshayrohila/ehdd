```
     _
    | |       |     |
 _  | |     __|   __|
|/  |/ \   /  |  /  |
|__/|   |_/\_/|_/\_/|_/

```

## Overview

`ehdd` can be used for ejecting and shutdowning an ejectable storage device on a Linux system. The program makes use of the `eject` and `udisksctl` command, hence working as a wrapper around them, and in the way making it easier to perform each command.

## Installation and Uninstallation:

Read [INSTALL.md](./INSTALL.md) for installation and uninstallation help.

## Dependencies:

Here are all the program dependencies:-
  1. ```eject``` command
  2. ```udiskctl``` command (most Linuxes will have package `udisks2` for this)
  3. _'root access'_ (running the command as `sudo ehdd ...`)

In addition to these, if you're going to install the program using [Method-2](./INSTALL.md#method-2) (by compilation), you're going to need these programs installed as well:-
  1. ```gcc```

## Usage:

`ehdd` can be used for ejecting and shutdowning an ejectable storage device on a Linux system. Please read [Help](./HELP.md) for more information.

## Bug Reports and Contributions:

Bugs can be reported / features can be asked for in the [Issues](https://github.com/lakshayrohila/ehdd/issues) section provided in GitHub.

In order to contribute code, you can create a `fork` of this repository, do modifications and then `Create a pull request` (Learn how to [Create a pull request](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-a-pull-request)).

The code itself is tried to be well-commented and easily-readable so that everyone, who has the knowledge of, can understand and modify the code according to their needs; and if one wants to volunteer in developing `ehdd`, they can do so easily. `README.dir` files are created in most of the directories which explain the work done by the specific directory and files present in it.

## Credits and Legal Information

`ehdd` is free and unencumbered software released under the terms of the MIT license, so as to keep the program most permissive. See [LICENSE.md](LICENSE.md) for license info.

For a list of contributors, see [GitHub-Contributors](https://github.com/lakshayrohila/ehdd/graphs/contributors).

All the releases are built using [toolchains](https://github.com/dimkr/toolchains), which provides the compilers to build for different architecture targets, statically linking to [musl libc](https://musl.libc.org/).

The directory `legal`, which is a symbolic-link to `build_helper/github/src/legal/`, lists copyright notices of all the softwares used for development of `ehdd`.

The ASCII art logo at the top was made using [FIGlet](https://www.figlet.org/).

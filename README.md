This program can be used for ejecting and shutdowning an ejectable storage device on a linux device.

## NOTE:
This program needs 'eject', 'udiskctl' command (udisks2) and 'root access' (sudo), to work.

***
## COMPILE:
```
gcc ehdd.c -o output.filename -DVERSION=\"version\"
```

The program can be given any **name** or **version** on compile time. If **version** is not provided then the program will automatically use **unknown** as the **version**.

### TIP:
**version** is a string literal named `VERSION`, so it can be any string, even `foo` or `haha` can be used as **version**. The program uses `printf` statements as `printf("%s", argv[0])`, so there is no need to alter the program source code everytime to change its program name.
### For example:
```
gcc ehdd.c -o foo -DVERSION=\"2022.04\"
```
***
## BUG REPORTS AND PROGRAM MODIFICATIONS:
Bugs can be reported in the **Issues** section provided in Github. Same can be done to ask for any feature. In order to modify the program, you can create a `fork` of it, do modifications and then `Create a pull request`.
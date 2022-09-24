/*	This program is to eject and shut down an ejectable storage device.
 *  It can be given any name on compile time and any version as well (check next oneline comment under '#ifndef VERSION').
 *  This program needs 'eject' command, 'udiskctl' command (udisks2) and 'root access' (sudo) as well
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define VERSION "\033[1m0.1\033[0m"

// returns return code of the command
int pretcode(const char *cmd) {
    int status = system(cmd);

    if(status < 0) {
        return status;
    } else if(status > 0) {
        if(WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
    }
}

void checkverbose(unsigned short verbose, char option[]) {
    if(verbose) {
        // verbose used, return warning
        fprintf(stderr, "\033[35mWarning:\033[37m");
        fprintf(stderr, " --verbose with %s has no meaning.\n", option);
    }
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        // device name not provided, return error code 1
        fprintf(stderr, "\033[0;31mError:\033[37m ");
        fprintf(stderr, "Device name not provided.\n");
        return 1;
    } else if(geteuid() != 0) {
        // not run as root, return error code 1
        fprintf(stderr, "\033[31mError:\033[37m ");
        fprintf(stderr, "\033[1m%s\033[0m not run as root. Run \033[1msudo %s\033[0m.\n", argv[0], argv[0]);
        return 1;
    } else if(pretcode("udisksctl >/dev/null 2>/dev/null") == 127) {
        // udisksctl not found, return error code 1
        fprintf(stderr, "\033[31mError:\033[37m ");
        fprintf(stderr, "\033[1mudisksctl\033[0m not found. Install udisks or udisks2 to install udisksctl.\n");
        return 1;
    }

    unsigned short option_used = 0, device_name = 0, proc_to_do = -1, device_name_given = 0, verbose = 0, ejectonly = 0,
        shutdownonly = 0;
    // device_name will be used as argv[device_name]
    // proc_to_do -> 0: --help, 1: --bylabel, 2: --byuuid, 3: --byname, 4: --version

    for(int i = 1;i < argc;i++) {
        if(!strncmp("-", argv[i], 1)) {
            // option has been used by the user
            if(!strcmp("--verbose", argv[i]) || !strcmp("-V", argv[i])) {
                // set verbose to 1
                verbose = 1;
                continue;
            } else if(!strcmp("--ejectonly", argv[i]) || !strcmp("-E", argv[i])) {
                // set ejectonly flag to 1
                ejectonly = 1;
                continue;
            } else if(!strcmp("--shutdownonly", argv[i]) || !strcmp("-S", argv[i])) {
                // set byname flag to 1
                shutdownonly = 1;
                continue;
            }

            if(!strcmp("--help", argv[i]) || !strcmp("-h", argv[i])) {
                // asked for help, set help flag to 1
                if(device_name != 0) {
					// --help with device name used, return warning
					fprintf(stderr, "\033[35mWarning:\033[37m");
					fprintf(stderr, " --help with device name provided, ignoring --help.\n");
					continue;
				}
				proc_to_do = 0;
				device_name_given = 1;
            } else if(!strcmp("--version", argv[i]) || !strcmp("-v", argv[i])) {
                // set version flag to 1
                if(device_name != 0) {
					// --version with device name used, return warning
					fprintf(stderr, "\033[35mWarning:\033[37m");
					fprintf(stderr, " --version with device name provided, ignoring --version.\n");
					continue;
				}
				proc_to_do = 4;
				device_name_given = 1;
            } else if(!strcmp("--bylabel", argv[i])) {
                // set bylabel flag to 1
                proc_to_do = 1;
            } else if(!strcmp("--byuuid", argv[i])) {
                // set byuuid flag to 1
                proc_to_do = 2;
            } else if(!strcmp("--byname", argv[i])) {
                // set byname flag to 1
                proc_to_do = 3;
            } else {
                // unknown option used, return error code 1
                fprintf(stderr, "\033[31mError:\033[37m ");
                fprintf(stderr, "Unknown option '%s'.\n", argv[i]);
                return 1;
            }

            if(option_used) {
                // two or more options have been used, return error code 1
                fprintf(stderr, "\033[31mError:\033[37m ");
                fprintf(stderr, "Two conflicting options provided.\n");
                return 1;
            }

            option_used = 1;
        } else {
            if(proc_to_do == 4) {
                // --version with device name used, return warning
                fprintf(stderr, "\033[35mWarning:\033[37m");
                fprintf(stderr, " --version with device name provided, ignoring --version.\n");
                device_name_given = 0;
                proc_to_do = 3;
            } else if(proc_to_do == 0) {
                // --help with device name used, return warning
                fprintf(stderr, "\033[35mWarning:\033[37m");
                fprintf(stderr, " --help with device name provided, ignoring --help.\n");
                device_name_given = 0;
                proc_to_do = 3;
            }

            if(device_name_given) {
                // device name already given, return error code 1
                fprintf(stderr, "\033[31mError:\033[37m ");
                fprintf(stderr, "Two or more device names provided.\n");
                return 1;
            }

            device_name = i;
            device_name_given = 1;
        }
    }

    if(!device_name_given) {
        // device name not provided, return error code 1
        fprintf(stderr, "\033[31mError:\033[37m ");
        fprintf(stderr, "Device name not provided.\n");
        return 1;
    } else if(!option_used) {
        proc_to_do = 3;
    }

    if(ejectonly && shutdownonly && ((proc_to_do != 0) || (proc_to_do != 4))) {
        // both ejectonly and shutdownonly options used, return error code 1
        fprintf(stderr, "\033[31mError:\033[37m ");
        fprintf(stderr, "Both --ejectonly and --shutdownonly used.\n");
        return 1;
    }

    size_t device_name_len = strlen(argv[device_name]), device_path_len;
    char *device_path;

    if(proc_to_do == 0) {
        // print help message and exit with return code 0
        checkverbose(verbose, "--help");
        printf("Usage: sudo %s [OPTIONS] or [DEVICE NAME]\n\n\
Option                Meaning\n\
 -h, --help            Show this text.\n\
 -v, --version         Provide version information.\n\
 -V, --versbose        Do not suppress the output of \033[1meject\033[0m and \033[1mudisksctl\033[0m.\n\
 -E, --ejectonly       Only eject the device.\n\
 -S, --shutdownonly    Only shutdown the device.\n\
 --byname              Same as %s \033[3mdevice\033[0m.\n\
 --bylabel             Eject and/or shutdown device by name. Same as %s /dev/disk/by-label/\033[3mdevice\033[0m.\n\
 --byuuid              Eject and/or shutdown device by uuid. Same as %s /dev/disk/by-uuid/\033[3mdevice\033[0m.\n\
(NOTE: No options can be mixed except that -V, -E and -S can be used with options starting with --by).\n", argv[0], argv[0], argv[0], argv[0]);
            return 0;
    } else if(proc_to_do == 4) {
        // print version info
        checkverbose(verbose, "--version");
        printf("%s version %s.\n", argv[0], VERSION);
        return 0;
    } else if(proc_to_do == 1) {
        device_path = malloc(20);
        strcpy(device_path, "/dev/disk/by-label/");
        device_path_len = 20;
    } else if(proc_to_do == 2) {
        device_path = malloc(19);
        strcpy(device_path, "/dev/disk/by-uuid/");
        device_path_len = 19;
    } else if(proc_to_do == 3) {
        device_path = malloc(6);
        strcpy(device_path, "/dev/");
        device_path_len = 6;
    }

    char *cmd;
    int cmd_status;

    if(!shutdownonly) {
        // eject device first
        cmd = malloc(device_name_len+device_path_len+32);
 
        strcpy(cmd, (!verbose) ? "eject >/dev/null 2>/dev/null " : "eject ");
        strcat(cmd, device_path);
        strcat(cmd, argv[device_name]);

        if((cmd_status = pretcode(cmd)) != 0) {
            // unable to eject device, return error code 1
            fprintf(stderr, "\033[31mError:\033[37m ");
            fprintf(stderr, "Unable to eject device. \033[1meject\033[0m returned with code %d. Try running \033[1meject\
 %s%s\033[0m.\n", cmd_status, device_path, argv[device_name]);
            return 1;
        }

        printf("Device ejected succesfully.%s\n", (!ejectonly) ? " Now powering it off.\n" :
        " It might be unsafe to remove the device unless you know that powering the device off is not necessary.");
    }

    if(!ejectonly) {
        // power off the device, if it can
        cmd = malloc(device_name_len+device_path_len+49);

        strcpy(cmd, (!verbose) ? "udisksctl power-off -b >/dev/null 2>/dev/null " : "udisksctl power-off -b ");
        strcat(cmd, device_path);
        strcat(cmd, argv[device_name]);

        if((cmd_status = pretcode(cmd)) != 0) {
            // unable to power off device, return error code 1
            fprintf(stderr, "\033[31mError:\033[37m ");
            fprintf(stderr, "Unable to power off device. \033[1mudisksctl\033[0m returned with code %d. Try running \033[1mudisksctl\
 power-off -b %s%s\033[0m.\n", cmd_status, device_path, argv[device_name]);
            return 1;
        }

        printf("Device powered off succesfully. Now it is safe to be removed.");
    }

    free(cmd);
    free(device_path);

    return 0;
}
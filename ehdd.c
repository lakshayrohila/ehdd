/*
 * This program is to eject and shut down an ejectable storage device. Read 'README.md' for more information.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

enum {
    DO_NOTHING, EJECT_BYLABEL, EJECT_BYUUID, EJECT_BYNAME
} todo;

#define VERSION "\033[1m0.2\033[0m"

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

    return 0;
}

char *get_string_todo() {
    switch(todo) {
        case EJECT_BYLABEL:
            return "bylabel";
        case EJECT_BYUUID:
            return "byuuid";
        case EJECT_BYNAME:
            return "byname";
        default:
            return "";
    }
}

#include "parsecliflags.h"

void print_help() {
    printf("Usage: sudo ehdd [OPTIONS] or [DEVICE NAME]\n\n\
Option                Meaning\n\
 -h, --help            Show this text.\n\
 -v, --version         Provide version information.\n\
 -V, --versbose        Do not suppress the output of \033[1meject\033[0m and \033[1mudisksctl\033[0m.\n\
 -E, --ejectonly       Only eject the device.\n\
 -S, --shutdownonly    Only shutdown the device.\n\
 --byname              Same as ehdd \033[3mdevice\033[0m.\n\
 --bylabel             Eject and/or shutdown device by name. Same as ejecting /dev/disk/by-label/\033[3mdevice\033[0m.\n\
 --byuuid              Eject and/or shutdown device by uuid. Same as ejecting /dev/disk/by-uuid/\033[3mdevice\033[0m.\n\n");
}

void print_version() {
    printf("ehdd version %s.\n\n", VERSION);
}

int main(int argc, char *argv[]) {
    if(parsecliflags(argc, argv)) {
        return 1;
    }

    size_t device_name_len;
    char device_path_prefix[20];

    if(cli_flags.help) {
        print_help();
    } if(cli_flags.version) {
        print_version();
    }

    if(todo == EJECT_BYLABEL) {
        strcpy(device_path_prefix, "/dev/disk/by-label/");
    } else if(todo == EJECT_BYUUID) {
        strcpy(device_path_prefix, "/dev/disk/by-uuid/");
    } else if(todo == EJECT_BYNAME) {
        strcpy(device_path_prefix, "/dev/");
    }

    char *cmd = malloc(1);
    int cmd_status, exit_code = 0;

    for(long long i = 0;i < device_names_list.len;i++) {
        device_name_len = strlen(device_names_list.names[i]+1);

        printf("\033[1m%s device %s\033[0m\n", (cli_flags.ejectonly) ? "Ejecting" :
            ((cli_flags.shutdownonly) ? "Powering off" : "Ejecting and powering off"), device_names_list.names[i]);

        if(!cli_flags.shutdownonly) {
            // eject device first
            cmd = realloc(cmd, device_name_len+32);

            sprintf(cmd, "eject %s %s%s", (!cli_flags.verbose) ? ">/dev/null 2>/dev/null" : "", // | Set the command
                device_path_prefix, device_names_list.names[i]);                                // | to be run.

            if((cmd_status = pretcode(cmd)) != 0) {
                // unable to eject device, return error code 1
                printf("\033[31mError:\033[37m ");
                printf("Unable to eject device. \033[1meject\033[0m returned with code %d. Try running \033[1meject \
\"%s%s\"\033[0m.\n", cmd_status, device_path_prefix, device_names_list.names[i]);
                exit_code = 1;
                continue;
            }

            printf("Device ejected succesfully. %s\n", (cli_flags.shutdownonly) ? "Now powering it off.\n" :
                "It might be unsafe to remove the device unless you know that powering the device off is not necessary.");
        }

        if(!cli_flags.ejectonly) {
            // power off the device, if it can
            cmd = realloc(cmd, device_name_len+70);

            sprintf(cmd, "udisksctl power-off -b %s %s%s",                      // | Set the
                (!cli_flags.verbose) ? ">/dev/null 2>/dev/null" : "",           // | command
                device_path_prefix, device_names_list.names[i]);                // | to be run.

            if((cmd_status = pretcode(cmd)) != 0) {
                // unable to power off device, return error code 1
                fprintf(stderr, "\033[31mError:\033[37m ");
                fprintf(stderr, "Unable to power off device. \033[1mudisksctl\033[0m returned with code %d. Try \
running \033[1mudisksctl power-off -b \"%s%s\"\033[0m.\n", cmd_status, device_path_prefix, device_names_list.names[i]);
                exit_code = 1;
                continue;
            }

            printf("Device powered off succesfully. Now it is safe to be removed.");
        }
    }

    free(cmd);
    free(device_names_list.names);

    return exit_code;
}
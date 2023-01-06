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

#define VERSION "undefined"

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
    printf("Usage: sudo ehdd [OPTIONS] or [DEVICE NAMES]\n\n\
Option                Meaning\n\
 -h, --help            Show this text.\n\
 -v, --version         Provide version information.\n\
 -V, --verbose         Do not suppress the output of \033[1meject\033[0m and \033[1mudisksctl\033[0m.\n\
 -E, --ejectonly       Only eject the device.\n\
 -S, --shutdownonly    Only shutdown the device.\n\
 --byname              Same as ehdd \033[3mdevice\033[0m.\n\
 --bylabel             Eject and/or shutdown device by name. Same as ejecting /dev/disk/by-label/\033[3mdevice\033[0m.\n\
 --byuuid              Eject and/or shutdown device by uuid. Same as ejecting /dev/disk/by-uuid/\033[3mdevice\033[0m.\n");
}

void print_version() {
    printf("ehdd version %s.\n", VERSION);
}

struct _pr_out {
	char *out;
	int status;
} pr_out;

int save_cmd_out(const char *cmd) {
    size_t buf_size = 150*sizeof(char), fread_ret = 0;
    char *buf = malloc(buf_size+1);

    pr_out.out = NULL;

    FILE *cmd_fp = popen(cmd, "r");

    if(cmd_fp == NULL) {
        printf("\033[31mError:\033[37m ");
        printf("Unable to pipe command: %s\nPlease report this error at https://github.com/lakshayrohila/ehdd/issues.\n", strerror(errno));

        free(buf);

        return 1;
    }

    int i = 1;

    while(1) {
        if((fread_ret = fread(buf+((i-1)*buf_size), sizeof(char), buf_size, cmd_fp)) != buf_size) {
            buf[((i-1)*buf_size)+fread_ret] = '\0';
            break;
        }

        i++;
        buf = realloc(buf, (i*buf_size)+1);
    }

    int status = 0;

    if((status = pclose(cmd_fp)) == -1) {
        printf("\033[31mError:\033[37m ");
        printf("Unable to close pipe for command: %s\nPlease report this error at https://github.com/lakshayrohila/ehdd/issues.\n", strerror(errno));

        free(buf);

        return 1;
    }

    pr_out.out = buf;

    if(WIFEXITED(status)) {
        pr_out.status = WEXITSTATUS(status);
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if(parsecliflags(argc, argv)) {
        return 1;
    }

    size_t device_name_len;
    char device_path_prefix[20];

    if(cli_flags.help) {
        print_help();

        if(cli_flags.version) {printf("\n");}
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
    int exit_code = 0;

    for(long long i = 0;i < device_names_list.len;i++) {
        device_name_len = strlen(device_names_list.names[i]+1);

        printf("\033[1m%s device %s\033[0m\n", (cli_flags.ejectonly) ? "Ejecting" :
            ((cli_flags.shutdownonly) ? "Powering off" : "Ejecting and powering off"), device_names_list.names[i]);

        if(!cli_flags.shutdownonly) {
            // eject device first
            cmd = realloc(cmd, device_name_len+32);

            sprintf(cmd, "eject %s%s 2>&1", device_path_prefix, device_names_list.names[i]); // set the command to be run.

            if(save_cmd_out(cmd)) {
				exit_code = 1;
				break;
			}

			if(cli_flags.verbose) {
				printf("%s", pr_out.out);
			}

            if(pr_out.status != 0) {
                // unable to eject device, return error code 1
                printf("\033[31mError:\033[37m ");
                printf("Unable to eject device. \033[1meject\033[0m returned with error code %d. Here is its output:\n\
\033[33m%s\033[0mTry running \033[1meject \"%s%s\"\033[0m to check if the problem still persists.\n",
					pr_out.status, pr_out.out, device_path_prefix, device_names_list.names[i]);
                exit_code = 1;
                continue;
            }

            printf("Device ejected succesfully. %s\n", (!cli_flags.ejectonly) ? "Now powering it off." :
                "It might be unsafe to remove the device unless you know that powering the device off is not necessary.");

            free(pr_out.out);
        }

        if(!cli_flags.ejectonly) {
            // power off the device, if it can
            cmd = realloc(cmd, device_name_len+70);

            sprintf(cmd, "udisksctl power-off -b %s%s 2>&1", device_path_prefix, device_names_list.names[i]); // set the command to be run.

            if(save_cmd_out(cmd)) {
				exit_code = 1;
				break;
			}

			if(cli_flags.verbose) {
				printf("%s", pr_out.out);
			}

            if(pr_out.status != 0) {
                // unable to power off device, return error code 1
                printf("\033[31mError:\033[37m ");
                printf("Unable to power off device. \033[1mudisksctl\033[0m returned with error code %d. Here is its output:\n\
\033[33m%s\033[0mTry running \033[1mudisksctl power-off -b \"%s%s\"\033[0m.\n",
					pr_out.status, pr_out.out, device_path_prefix, device_names_list.names[i]);
                exit_code = 1;
                continue;
            }

            printf("Device powered off succesfully. Now it is safe to be removed.\n");
            free(pr_out.out);
        }
    }

    free(cmd);
    free(device_names_list.names);

    return exit_code;
}

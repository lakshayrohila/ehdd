#ifndef _INC_PARSECLIFLAGS_H
#define _INC_PARSECLIFLAGS_H

// this file includes functions which deal with parsing of command line options passed to the program
// only function 'parsecliflags' is used by 'main.c'

char OPTION_USED = 0;

struct {
    char **names;
    long long len;
} device_names_list;

struct _cli_flags {
    char version, help, verbose, ejectonly, shutdownonly;
} cli_flags;

int handle_hyphen_options(char *opt_str) {
    // this function returns 1 for error, else 0
    int i = 0;

    while(opt_str[++i] != '\0') {
        switch(opt_str[i]) {
            case 'h':
                cli_flags.help = 1;
                break;
            case 'v':
                cli_flags.version = 1;
                break;
            case 'V':
                cli_flags.verbose = 1;
                break;
            case 'E':
                cli_flags.ejectonly = 1;
                break;
            case 'S':
                cli_flags.shutdownonly = 1;
                break;
            default:
                printf("\033[31mError:\033[37m ");
                printf("Unknown command line option '-%c' (provided in '%s').\n", opt_str[i], opt_str);
                return 1;
        }
    }

    return 0;
}

int parsecliflags(int argc, char **argv) {
    // check for dependencies / root access
    if(pretcode("eject -h >/dev/null 2>/dev/null") == 127) {
        printf("\033[31mError:\033[37m ");
        printf("\033[1meject\033[0m: command not found.\n");
        return 1;
    } else if(pretcode("udisksctl help >/dev/null 2>/dev/null") == 127) {
        printf("\033[31mError:\033[37m ");
        printf("\033[1mudisksctl\033[0m: command not found. Install udisks2 to install udisksctl.\n");
        return 1;
    } else if(geteuid() != 0) {
        printf("\033[31mError:\033[37m ");
        printf("\033[1m%s\033[0m not run as root. Run \033[1msudo %s\033[0m.\n", argv[0], argv[0]);
        return 1;
    } else if(argc < 2) {
        printf("\033[0;31mError:\033[37m ");
        printf("Device name not provided.\n");
        return 1;
    }

    cli_flags.version = cli_flags.help = cli_flags.ejectonly = cli_flags.shutdownonly = cli_flags.verbose = 0;

    int current_argv = 0;

    todo = DO_NOTHING;

    device_names_list.names = (char **)malloc(1*sizeof(char *));
    if(check_dynamic_pointer((void*)device_names_list.names)) {
        return 1;
    }

    device_names_list.len = 0;

    while(++current_argv < argc) {
        if(!strncmp(argv[current_argv], "--", 2)) {
            if(!strcmp(argv[current_argv], "--help")) {
                cli_flags.help = 1;
            } else if(!strcmp(argv[current_argv], "--version")) {
                cli_flags.version = 1;
            } else if(!strcmp(argv[current_argv], "--verbose")) {
                cli_flags.verbose = 1;
            } else if(!strcmp(argv[current_argv], "--ejectonly")) {
                cli_flags.ejectonly = 1;
            } else if(!strcmp(argv[current_argv], "--shutdownonly")) {
                cli_flags.shutdownonly = 1;
            } else if(!strcmp(argv[current_argv], "--byname")) {
                if(todo != DO_NOTHING) {
                    printf("\033[31mError:\033[37m ");
                    printf("--%s used with %s.\n", get_string_todo(), argv[current_argv]);
                } else {
                    todo = EJECT_BYNAME;
                }
            } else if(!strcmp(argv[current_argv], "--bylabel")) {
                if(todo != DO_NOTHING) {
                    printf("\033[31mError:\033[37m ");
                    printf("--%s used with %s.\n", get_string_todo(), argv[current_argv]);
                } else {
                    todo = EJECT_BYLABEL;
                }
            } else if(!strcmp(argv[current_argv], "--byuuid")) {
                if(todo != DO_NOTHING) {
                    printf("\033[31mError:\033[37m ");
                    printf("--%s used with %s.\n", get_string_todo(), argv[current_argv]);
                } else {
                    todo = EJECT_BYUUID;
                }
            } else {
                printf("\033[31mError:\033[37m ");
                printf("Unknown command line option '%s'.\n", argv[current_argv]);
                return 1;
            }
        } else if(!strncmp(argv[current_argv], "-", 1)) {
            if(handle_hyphen_options(argv[current_argv])) {
                return 1;
            }
        } else {
            // argv[current_argv] is not an option (not starting with '-')

            device_names_list.len++;

            device_names_list.names = (char **)realloc(device_names_list.names, device_names_list.len*sizeof(char *));

            if(check_dynamic_pointer((void*)device_names_list.names)) {
                return 1;
            }

            *(device_names_list.names+device_names_list.len-1) = argv[current_argv];
        }
    }

    if((!device_names_list.len) && (!cli_flags.help) && (!cli_flags.version)) {
        // device name not provided, return error code 1
        printf("\033[0;31mError:\033[37m ");
        printf("Device name not provided.\n");
        return 1;
    }

    if(todo == DO_NOTHING) {
        todo = EJECT_BYNAME;
    }

    if(cli_flags.shutdownonly && cli_flags.ejectonly) {
        cli_flags.shutdownonly = cli_flags.ejectonly = 0;
    }

    return 0;
}

#endif

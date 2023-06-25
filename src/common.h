#ifndef _INC_EHDD_COMMON_H
#define _INC_EHDD_COMMON_H

#define GITHUB_REPO "https://github.com/lakshayrohila/ehdd/issues"

//---------------------------------------------------------------------------------------
// THIS FUNCTION CHECKS IF DYNAMIC ALLOCATION OF MEMORY FAILED

int check_dynamic_pointer(void *pointer) {
	if(pointer == NULL) {
		int err_sv = errno;

		if(err_sv == ENOMEM) {
			printf("\033[31mError:\033[37m ");
			printf("No memory left on device.\nTry closing other programs and then running ehdd.");
		} else {
			printf("\033[31mError:\033[37m ");
			printf("Error while allocating memory: %s\n", strerror(err_sv));
			printf("Please report this error at %s/issues.", GITHUB_REPO);
		}

		return 1;
	}

	return 0;
}

//---------------------------------------------------------------------------------------
// THIS SECTION DEALS WITH FUNCTIONS WHICH RUN COMMANDS AND SAVE THEIR OUTPUTS

// runs a command using system and returns its exit code
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

// this is used by 'main.c' to run and save command exit code + its output
struct _pr_out {
	char *out;
	int status;
} pr_out;

int save_cmd_out(const char *cmd) {
	size_t buf_size = 150*sizeof(char), fread_ret = 0;
	char *buf = malloc(buf_size+1);

	if(check_dynamic_pointer((void*)buf)) {
		return 1;
	}

	pr_out.out = NULL;

	FILE *cmd_fp = popen(cmd, "r");

	if(cmd_fp == NULL) {
		int err_sv = errno;

		printf("\033[31mError:\033[37m ");
		printf("Unable to pipe command: %s\nPlease report this error at %s/issues.\n", strerror(err_sv), GITHUB_REPO);

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

		if(check_dynamic_pointer((void*)buf)) {
			return 1;
		}
	}

	int status = 0;

	if((status = pclose(cmd_fp)) == -1) {
		printf("\033[31mError:\033[37m ");
		printf("Unable to close pipe for command: %s\nPlease report this error at %s/issues.\n", strerror(errno), GITHUB_REPO);

		free(buf);

		return 1;
	}

	pr_out.out = buf;

	if(WIFEXITED(status)) {
		pr_out.status = WEXITSTATUS(status);
	}

	return 0;
}

//---------------------------------------------------------------------------------------
// THIS SECTION DEALS WITH 'enum todo', WHICH DEFINES THE PROCESS TO DO
// 'todo' IS SET BY 'parsecliflags.h' AND LATER USED BY 'main.c'

enum {
	DO_NOTHING, EJECT_BYLABEL, EJECT_BYUUID, EJECT_BYNAME
} todo;

// todo is an enum; when printing information (error?), we need it to be in a string format
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

//---------------------------------------------------------------------------------------

#endif

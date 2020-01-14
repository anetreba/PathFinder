#include "pathfinder.h"

static void is_empty(char *file);
static void is_folder(char *file);
static void argument(int ac);
static void is_not_exist(char *file);
static void is_empty2(char *file);

bool mx_print_error2(int ac, char *av) {
	argument(ac);
	is_not_exist(av);
	is_folder(av);
	is_empty(av);
	is_empty2(av);
	return true;
}

static void is_empty2(char *file) {
	char *f = mx_file_to_str(file);
	bool flag = false;

	for (int i = 0; f[i]; i++)
		if (f[i] != '\n')
			flag = true;
	if (!flag) {
		mx_printerr(EMPTY_FILE);
		mx_printerr(file);
		mx_printerr(EMPTY_FILE2);
		exit (0);
	}
}

static void is_empty(char *file) {
    int fd = open(file, O_RDONLY);
    char buf;
    
	if (read(fd, &buf, 1) == 0) {
		close(fd);
		mx_printerr(EMPTY_FILE);
		mx_printerr(file);
		mx_printerr(EMPTY_FILE2);
		exit (0);
	}
}

static void is_folder(char *file) {
	int fd = open(file, O_RDONLY);

	if (read(fd, (void *)0, 0) < 0) {
 	    close(fd);
		mx_printerr(ERROR_USAGE);
	    exit (0);
    }
}

static void argument(int ac) {
	if (ac != 2) {
		mx_printerr(ERROR_USAGE);
		exit (0);
	}
}

static void is_not_exist(char *file) {
	int fd = open(file, O_RDONLY);

	if (fd < 0) {
	    close(fd);
	    mx_printerr(FILE_EXIST);
	   	mx_printerr(file);
	    mx_printerr(FILE_EXIST2);
	    exit (0);
	}
}

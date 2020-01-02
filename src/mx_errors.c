#include "pathfinder.h"

void mx_invalid_num_of_is() {
	mx_printerr("error: invalid number of islands\n");
	exit(0);
}

void mx_apex_count(char **WordsA) {
	if (!str_is_digit(WordsA[0])) {
		mx_printerr("error: line 1 is not valid\n");
		exit (0);
	}
}


void mx_print_erno(char *num) {
	mx_printerr(LINE_VALUE);
	mx_printerr(num);
	mx_printerr(LINE_VALUE2);
}

void mx_island_not_char(char **str) {
	char **s1;
	char **s2;

	for (int i = 1; str[i]; i++) {
		s1 = mx_strsplit(str[i], '-');
		s2 = mx_strsplit(s1[1], ',');
		if (!(mx_is_char(s1[0]))) {
			char *num = mx_itoa(i + 1);

			mx_print_erno(num);
			exit (0);
		}
		if (!(mx_is_char(s2[0]))) {
			char *num = mx_itoa(i + 1);

			mx_print_erno(num);
			exit (0);
		}
		mx_double_del(s1, s2);
	}
}

void mx_two_perenos(char *f) {
	int len = mx_strlen(f);
	int count = 0;

	for (int i = 0; f[i + 1]; i++) {
		if (f[i] == '\n')
			count++;
		if (f[i] == '\n' && f[i + 1] == '\n' && i != len - 1) {
			count++;
			char *num = mx_itoa(count);

			mx_print_erno(num);
			exit(0);
		}
	}
}

#include "pathfinder.h"

static void valid_island(char **WordsA);
static void range_validator(char **WordsA);
static void validator_znakov(char **WordsA);

bool str_is_digit(char *str) {
	for (int i = 0; str[i]; i++) {
		if (!mx_isdigit(str[i]))
			return false;
	}
	return true;
}

void mx_print_error1(char **WordsA, char *f) {
	mx_apex_count(WordsA);
	mx_island_not_char(WordsA);
	mx_two_perenos(f);
	validator_znakov(WordsA);
	range_validator(WordsA);
	valid_island(WordsA);
}

static void valid_island(char **WordsA) {
	for(int i = 1; WordsA[i]; i++) {
		char **str = mx_strsplit(WordsA[i], '-');

		if (str[0] == NULL || mx_arrlen(str) < 2) {
			char *num = mx_itoa(i + 1);
			mx_print_erno(num);
			mx_del_strarr(&str);
			exit (0);
		}
		char **str2 = mx_strsplit(str[1], ',');

		if (str2[0] == NULL || mx_arrlen(str2) < 2) {
			char *num = mx_itoa(i + 1);
			mx_print_erno(num);
			mx_del_strarr(&str2);
			exit (0);
		}
		mx_double_del(str, str2);
	}
}

static void range_validator(char **WordsA) {
	char *num = NULL;

	for (int i = 1; WordsA[i]; i++) {
		char **str = mx_strsplit(WordsA[i], ',');

		if (mx_arrlen(str) != 1) {
			if (!str_is_digit(str[1]) || mx_atoi(str[1]) == 0) {
				num = mx_itoa(i + 1);
				mx_printerr(LINE_VALUE);
				mx_printerr(num);
				mx_printerr(LINE_VALUE2);
				exit (0);
			}
		}
		mx_del_strarr(&str);
	}
}

static void validator_znakov(char **WordsA) {
	char minus = '-';
	char zap = ',';
	
	for (int i = 1; WordsA[i]; i++) {
		if (mx_char_count(WordsA[i], minus) != 1 
			|| mx_char_count(WordsA[i], zap) != 1) {
			char *num = mx_itoa(i + 1);

			mx_printerr(LINE_VALUE);
			mx_printerr(num);
			mx_printerr(LINE_VALUE2);
			exit (0);
		}
	}
}

#include "pathfinder.h"
#include <stdio.h>

static void program_start(char *f, char **str, int count);

void mx_parse_islands_dist(t_island *p, char **str, char *f, int count) {
	mx_parse_islands(p, str, count);
	mx_parse_dist(p, f, count, str);
	mx_del_strarr(&str);
	free(f);
}


int main(int ac, char **av) {
	if (mx_print_error2(ac, av[1])) {
		char *f = mx_file_to_str(av[1]);
		char **str = mx_strsplit(f, '\n');
		int count = mx_atoi(f);
		
		program_start(f, str, count);
	}
	return 0;
}

static void program_start(char *f, char **str, int count) {
	mx_print_error1(str, f);
	if (count == 0)
		mx_invalid_num_of_is();
	t_res **lst = (t_res **)malloc(sizeof(t_res *) * (count - 1));
	t_res **res = (t_res **)malloc(sizeof(t_res *) * (count - 1));
	t_island *p = (t_island *)malloc(sizeof(t_island) * (count));

	mx_parse_islands_dist(p, str, f, count);
	for (int i = 0; i < count - 1; i++) {
		lst[i] = mx_create_first_itter_list(p, i);
		res[i] = mx_algorithm(p, lst[i], count, i);
	}
	mx_sort_print_res(res, p, count);
}

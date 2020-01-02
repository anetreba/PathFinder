#include "pathfinder.h"

void mx_print_route(t_res *lst, t_island *p, int count, int i) {
	mx_printstr("Route: ");
	mx_printstr(p[i].name);
	mx_printstr(" -> ");
	for (int k = 1; k < lst->count; k++) {
		for (int l = 0; l < count; l++) {
			if (lst->road[k] == p[l].index_name) {
				mx_printstr(p[l].name);
				if (k != lst->count - 1) 
					mx_printstr(" -> ");
				else
					mx_printchar('\n');
			}
		}
	}
}

void mx_print_num(t_res *lst) {
	char *itoa = mx_itoa(lst->dist);

	mx_printstr(itoa);
	free(itoa);
}

void mx_print_dist(t_res *lst) {
	mx_printstr("Distance: ");
	if (lst->count == 2)
		mx_print_num(lst);
	else {
		for (int n = 0; n < lst->count - 1; n++) {
			char *itoa = mx_itoa(lst->road_dist[n]);

			mx_printstr(itoa);
			free(itoa);
			if (n != lst->count - 2)
				mx_printstr(" + ");
			else {
				mx_printstr(" = ");
				mx_print_num(lst);
			}
		}
	}
	mx_printchar('\n');
}

void mx_print_res(t_res *lst, t_island *p, int count) {
	while (lst) {
		for (int i = 0; i < count; i++) {
			if (lst->road[0] == p[i].index_name) {
				mx_printstr(ROVNO);
				mx_printstr("Path: ");
				mx_printstr(p[i].name);
				mx_printstr(" -> ");
				for (int j = 0; j < count; j++) {
					if (lst->road[lst->count - 1] == p[j].index_name) {
						mx_printstr(p[j].name);
						mx_printchar('\n');
					}
				}
				mx_print_route(lst, p, count, i);
				mx_print_dist(lst);
				mx_printstr(ROVNO);
			}
		}
		lst = lst->next;
	}
}

void mx_sort_print_res(t_res **res, t_island *p, int count) {
	for (int j = 0; j < count - 1; j++) {
		if (res[j]->dist != 0) {
			mx_sort_list_res3(res[j]);
			mx_sort_list_res4(res[j]);
			mx_sort_list_res2(res[j]);
			mx_print_res(res[j], p, count);
		}
	}
}

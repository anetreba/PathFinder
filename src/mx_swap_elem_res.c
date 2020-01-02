#include "pathfinder.h"

void mx_swap_elemint(int **s1, int **s2) {
	int *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}


void mx_swap_int(int *a, int *b) {
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void mx_swap_elements_res(t_res *lst) {
	mx_swap_int(&(lst->dist), &(lst->next->dist));
	mx_swap_int(&(lst->count), &(lst->next->count));
	mx_swap_elemint(&(lst->road_dist), &(lst->next->road_dist));
	mx_swap_elemint(&(lst->road), &(lst->next->road));
}

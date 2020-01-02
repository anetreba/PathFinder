#include "pathfinder.h" 

static bool is_new_island(char *name, t_island *p, int count);
static void add_elem_of_island(t_island *p, char *s, int *j);

bool mx_repeat_value(int *road, int k, int count) {
	for (int i = 0; i < count; i++) {
		if (road[i] == k)
			return false;
	}
	return true;
}

void mx_double_del(char **s1, char **s2) {
	mx_del_strarr(&s2);
	mx_del_strarr(&s1);
}


void mx_parse_islands(t_island *p, char **str, int count) {
	char **s1;
	char **s2;
	int j = 0;
	
	for (int i = 1; str[i]; i++) {
		s1 = mx_strsplit(str[i], '-');
		s2 = mx_strsplit(s1[1], ',');
		if (j == count && is_new_island(s1[0], p, j))
			mx_invalid_num_of_is();
		if (is_new_island(s1[0], p, j))
			add_elem_of_island(&p[j], s1[0], &j);
		if (j == count && is_new_island(s2[0], p, j)) 
			mx_invalid_num_of_is();
		if (is_new_island(s2[0], p, j))
			add_elem_of_island(&p[j], s2[0], &j);
		mx_double_del(s1, s2);
	}
	if (j != count)
		mx_invalid_num_of_is();
}

static bool is_new_island(char *name, t_island *p, int count) {
	for (int i = 0; i < count; i++) {
		if (mx_strcmp(name, p[i].name) == 0
			&& mx_strlen(name) == mx_strlen(p[i].name))
			return false;
	}
	return true;
}

static void add_elem_of_island(t_island *p, char *s, int *j) {
	p->index_name = *j;
	p->name = mx_strdup(s);
	(*j)++;
}

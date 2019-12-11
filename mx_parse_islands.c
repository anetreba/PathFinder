#include "inc/libmx.h"

void double_del(char **s1, char **s2) {
	mx_del_strarr(&s2);
	mx_del_strarr(&s1);
}

bool is_new_island(char *name, t_island *p, int count) {
	for (int i = 0; i < count; i++) {
		if (mx_strcmp(name, p[i].name) == 0)
			return false;
	}
	return true;
}

int index_point(char *str, int count, t_island *p) {
	for (int i = 0; i < count; i++)
	{
		if (mx_strcmp(p[i].name, str) == 0)
			return p[i].index_name;
	}
	return -1;
}

void mx_parse_dist(t_island *p, char *f, int count, char **str) {
	for (int i = 0; i < count; i++) {
		int k = 0;
		p[i].routes_count = mx_count_substr(f, p[i].name);
		p[i].d = (t_dist *)malloc(sizeof(t_dist) * p[i].routes_count);
		for (int j = 1; str[j]; j++) {
			char **s1 = mx_strsplit(str[j], '-');
			char **s2 = mx_strsplit(s1[1], ',');
			if (mx_strcmp(p[i].name, s1[0]) == 0) {
				p[i].d[k].index_point = index_point(s2[0], count, p);
				p[i].d[k].point = mx_strdup(p[p[i].d[k].index_point].name);
				p[i].d[k++].dist = mx_atoi(s2[1]);
			}
			if (mx_strcmp(p[i].name, s2[0]) == 0) {
				p[i].d[k].index_point = index_point(s1[0], count, p);
				p[i].d[k].point = mx_strdup(p[p[i].d[k].index_point].name);
				p[i].d[k++].dist = mx_atoi(s2[1]);
			}
			double_del(s1, s2);
		}
	}
}

void mx_parse_islands(t_island *p, char **str, int count) {
	char **s1;
	char **s2;
	int j = 0;
	
	for (int i = 1; str[i]; i++) {
		s1 = mx_strsplit(str[i], '-');
		s2 = mx_strsplit(s1[1], ',');
		if (is_new_island(s1[0], p, j)) {
			p[j].index_name = j;
			p[j++].name = mx_strdup(s1[0]);
		}
		if (is_new_island(s2[0], p, j)) {
			p[j].index_name = j;
			p[j++].name = mx_strdup(s2[0]);
		}
		double_del(s1, s2);
	}
}

void	print_island_struct(t_island *p, int count) {
	for (int i = 0; i < count; i++)
	{
		printf("****PRINT NEW ISLAND***********\n");
		printf("Name = %s, Index = %d Routes Count = %d\n", p[i].name, p[i].index_name, p[i].routes_count);
		for (int j = 0; j < p[i].routes_count; j++)
		{
			printf("point name = %s, index point = %d, distance = %d\n", p[i].d[j].point, p[i].d[j].index_point, p[i].d[j].dist);
		}
		printf("***********END ISLAND***********\n\n");
	}
}

int main(int ac, char **av) {
	t_island *p;
	char *f = mx_file_to_str(av[1]);
	int count = mx_atoi(f);
	char **str = mx_strsplit(f, '\n');

	p = (t_island *)malloc(sizeof(t_island) * (count));
	mx_parse_islands(p, str, count);
	mx_parse_dist(p, f, count, str);
	mx_del_strarr(&str);
	free(f);
	printf("----------------\n");
	print_island_struct(p, count);
	system("leaks -q a.out");
	return 0;
}

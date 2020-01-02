#include "pathfinder.h" 

static int index_point(char *str, int count, t_island *p);

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
			mx_double_del(s1, s2);
		}
	}
}

static int index_point(char *str, int count, t_island *p) {
	for (int i = 0; i < count; i++)
	{
		if (mx_strcmp(p[i].name, str) == 0)
			return p[i].index_name;
	}
	return -1;
}

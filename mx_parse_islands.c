#include "inc/libmx.h"



int mx_count_dist(char *f) {
	int count = 0;

	for (int i = 0; f[i]; i++) {
		if (f[i] == '\n')
			count++;
	}
	return count;
}

int mx_islands_index(t_island *p, int max_index, int current_index) {
	if (current_index == 0) {
		p[current_index].index_1 = 0;
		p[current_index].index_2 = 1;
		max_index = 1;
	}

	for (int j = 0; j <= current_index; j++) {
		if(mx_strcmp(p[current_index].p1, p[j].p1) == 0)
			p[current_index].index_1 = p[j].index_1;
		else if(mx_strcmp(p[current_index].p1, p[j].p2) == 0)
			p[current_index].index_1 = p[j].index_2;
		else if (p[current_index].index_1 == -1 && j == current_index - 1) {
			p[current_index].index_1 = max_index + 1;
			max_index++;
		}

		if (mx_strcmp(p[current_index].p2, p[j].p1) == 0)
			p[current_index].index_2 = p[j].index_1;
		else if (mx_strcmp(p[current_index].p2, p[j].p2) == 0)
			p[current_index].index_2 = p[j].index_2;
		else if (p[current_index].index_2 == -1 && j == current_index - 1) {
			p[current_index].index_2 = max_index + 1;
			max_index++;
		}
	}
	return max_index;
}


void mx_parse_islands(t_island *p, char *f) {
	char **str = mx_strsplit(f, '\n');
	char **s1;
	char **s2;
	int max_index = 0;
	
	for (int i = 0; str[++i]; ) {
		s1 = mx_strsplit(str[i], '-');
		s2 = mx_strsplit(s1[1], ',');
		p[i - 1].p1 = mx_strdup(s1[0]);
		p[i - 1].p2 = mx_strdup(s2[0]);
		p[i - 1].dist = mx_atoi(s2[1]);
		p[i - 1].index_1 = -1;
		p[i - 1].index_2 = -1;
		max_index = mx_islands_index(p, max_index, i - 1);
		mx_del_strarr(&s2);
		mx_del_strarr(&s1);
	}
	mx_del_strarr(&str);
}

int main(int ac, char **av) {
	t_island *p;
	char *f = mx_file_to_str(av[1]);
	int count = mx_count_dist(f);

	p = (t_island *)malloc(sizeof(t_island) * (count));
	mx_parse_islands(p, f);
	free(f);
	printf("----------------\n");
	for (int k = 0; k < count; k++) {
		printf("---Apex = %s\n---Apex = %s\n-distance = %d\n index a = %d\n index b = %d\n----------------\n",
			p[k].p1, p[k].p2, p[k].dist, p[k].index_1, p[k].index_2);
	}
	system("leaks -q a.out");
	return 0;
}

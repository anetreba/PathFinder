#include "inc/libmx.h"
t_res *test;
//*****************************************
t_res  *mx_create_res(int *road, int count, int *road_dist, int dist) {
	t_res *res = (t_res*)malloc(sizeof(t_res));

	res->road = (int*)malloc(sizeof(int) * count);
	res->road_dist = (int*)malloc(sizeof(int) * (count - 1));
 	res->road = mx_memcpy(res->road, road, sizeof(int) * count);
	res->road_dist = mx_memcpy(res->road_dist, road_dist, sizeof(int) * (count - 1));
	res->dist = dist;
	res->count = count;

	res->next = NULL;
	return res;
}

void mx_pop_front_res(t_res **head) {
	t_res *current = NULL;
	if (head && *head) {
		current = (*head)->next;
		free((*head)->road);
		free((*head)->road_dist);
		free(*head);
		*head = current;
	}
}

void mx_push_back_res(t_res **list, int *road, int count, int *road_dist, int dist) {
	if (list) {
		t_res *new = mx_create_res(road, count, road_dist, dist);
		if (*list) { 
			t_res *current = *list;

			while(current->next != NULL) {
				current = current->next;
			}
			current->next = new;
		}
		else 
			*list = new;
	}
}

void mx_push_front_res(t_res **list, int *road, int count, int *road_dist, int dist) {
	t_res *new_head = mx_create_res(road, count, road_dist, dist);

	new_head->next = *list;
	*list = new_head;
}

int mx_list_size_res(t_res *list) {
	int i = 0;
	if (list) {
		t_res *tmp = list;
		while (tmp != NULL){
			i++;
			tmp = tmp->next;
		}
	}
	return i;	
}


void mx_swap_elemint(int **s1, int **s2) {
	int *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}


t_res *mx_sort_list_res(t_res *lst) {
	int i = 0;
	int size = mx_list_size_res(lst);
	t_res *new = lst;

	while (i < size) {
		if (lst->dist > lst->next->dist) {
			int tmp = lst->dist;
			lst->dist = lst->next->dist;
			lst->next->dist = tmp;
			mx_swap_elemint(&(lst->road_dist), &(lst->next->road_dist));
			mx_swap_elemint(&(lst->road), &(lst->next->road));
		}
		lst = lst->next;
		i++;
		if (i == size - 1) {
			lst = new;
			i = 0;
			size--;
		}
	}
	return new;
}

//**********************************************

char *mx_strjoin_del(char *s1, char *s2) {
	char *new;

	if (s1 || s2) {
		if (!s2)
			return mx_strdup(s1);
		else if (!s1)
			return mx_strdup(s2);
		else if (s1 && s2) {
			new = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
			new = mx_strcat(mx_strcpy(new, s1), s2);
			free(s1);
			free(s2);
			return new;
		}
	}
	return NULL;
}

void mx_print_list(t_res *lst) {
	printf("****PRINT NEW ROAD***********\n");
	while (lst)
	{	
		printf("Road = ");
		for (int i = 0; i < lst->count; i++) {
			printf("%d,", lst->road[i]);
		}
		printf(" | ROAD_DIST = ");
		for (int i = 0; i < lst->count - 1; i++) {
			printf("%d,", lst->road_dist[i]);
		}
		printf(" | DIST = %d\n", lst->dist);
		lst = lst->next;
	}
	printf("***********END ROAD***********\n\n");
}

t_res *mx_create_first_itter_list(t_island *p) {
	t_res *lst;
	int road[2];
	int road_dist[1];
	int dist = 0;

	for (int k = 0; k < p[0].routes_count; k++) {
		road[0] = p[0].index_name;
		road[1] = p[0].d[k].index_point;
		road_dist[0] = p[0].d[k].dist;
		dist += p[0].d[k].dist;
		if (k == 0)
			lst = mx_create_res(road, 2, road_dist, p[0].d[k].dist);
		else
			mx_push_back_res(&lst, road, 2, road_dist, p[0].d[k].dist);
	}
	mx_print_list(lst);
	return lst;
}


t_res *mx_algorithm(t_island *p, t_res *lst, int count) {
	static int i = 1;
	int *road = NULL;
	int *road_dist = NULL;
	int dist;
	t_res *res;

	lst = mx_sort_list_res(lst);
	i = lst->road[lst->count - 1];
	for (int k = 0; k < p[i].routes_count; k++) {
		road = mx_realloc(lst->road, sizeof(int) * (lst->count + 1));
		road[lst->count] = p[i].d[k].index_point;
		road_dist = mx_realloc(lst->road_dist, sizeof(int) * (lst->count));
		road_dist[lst->count - 1] = p[i].d[k].dist;
		dist = lst->dist + p[i].d[k].dist;
		mx_push_back_res(&lst, road, lst->count + 1, road_dist, dist);
	}
	if (lst->count == 2)
		res = mx_create_res(lst->road, lst->count, lst->road_dist, lst->dist);
	else 
		mx_push_back_res(&lst, lst->road, lst->count, lst->road_dist, lst->dist);
	mx_pop_front_res(&lst);
	i++;
	mx_algorithm(p, lst, count);
	if (i == count)
		test = res;
		return res;
}

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
	t_res *lst;
	

	p = (t_island *)malloc(sizeof(t_island) * (count));
	mx_parse_islands(p, str, count);
	mx_parse_dist(p, f, count, str);
	mx_del_strarr(&str);
	free(f);
	// printf("----------------\n");
	// print_island_struct(p, count);

	lst = mx_create_first_itter_list(p);
	lst = mx_algorithm(p, lst, count);
	lst = test;
	mx_print_list(lst);
	system("leaks -q a.out");
	return 0;
}

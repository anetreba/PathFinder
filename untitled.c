#include "inc/libmx.h"


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

	if (i != size - 1) {
		while (i < size) {
			if (lst->dist > lst->next->dist) {
				int tmp = lst->dist;
				lst->dist = lst->next->dist;
				lst->next->dist = tmp;
				tmp = lst->count;
				lst->count = lst->next->count;
				lst->next->count = tmp;
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
	}
	return new;
}

int mx_find_iter(t_res *lst) {
	int i = 0;

	if (!lst)
		return -1;
	for (t_res *tmp1 = lst; tmp1; tmp1 = tmp1->next) {
		i = 0;
		for (t_res *tmp2 = lst; tmp2; tmp2 = tmp2->next) {
			if ((tmp1->road[tmp1->count - 1] == tmp2->road[tmp2->count - 1]) && tmp2->dist > tmp1->dist)
				return i;
			i++;
		}
	}
	return -1;
}

void mx_pop_back_res(t_res **head) {
	t_res *temp = NULL;

	if (head && *head && (*head)->next) {
		temp = *head;

		while (temp->next->next)
			temp = temp->next;
		free(temp->next->road);
		free(temp->next->road_dist);
		free(temp->next);
		temp->next = NULL;
	}
	else if (head && *head) {
		free((*head)->road);
		free((*head)->road_dist);
		free(*head);
		*head = NULL;
	}
}


void mx_pop_elem_of_list(t_res *lst) {
	if (lst) {
		int count;
		t_res *tmp = lst;
		t_res *tmp2;
		 t_res *prv;


		while ((count = mx_find_iter(lst)) != -1) {
			if (count == 0)
				mx_pop_front_res(&lst);
			else if (count == mx_list_size_res(lst) - 1)
				mx_pop_back_res(&lst);
			else {
				for (int i = 0; i < count; i++) {

					prv = tmp; 
         			tmp = tmp->next; 
				}
				prv->next = tmp->next; 
    			free(tmp->road);
			 	free(tmp->road_dist);				
				free(tmp);  // Free memory

			}
		}
	}
}

//**********************************************


void mx_print_list(t_res *lst) {
	t_res *tmp = lst;
	while (tmp)
	{	
		printf("****PRINT NEW ROAD***********\n");
		printf("Road = ");
		for (int i = 0; i < tmp->count; i++) {
			printf("%d,", tmp->road[i]);
		}
		printf(" | ROAD_DIST = ");
		for (int i = 0; i < tmp->count - 1; i++) {
			printf("%d,", tmp->road_dist[i]);
		}
		printf(" | DIST = %d\n", tmp->dist);
		tmp = tmp->next;
		printf("***********END ROAD***********\n\n");
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++++

t_res *mx_create_first_itter_list(t_island *p, int i) {
	t_res *lst;
	int road[2];
	int road_dist[1];
	int dist = 0;

	for (int k = 0; k < p[i].routes_count; k++) {
		road[0] = p[i].index_name;
		road[1] = p[i].d[k].index_point;
		road_dist[0] = p[i].d[k].dist;
		dist = p[i].d[k].dist;
		if (k == 0)
			lst = mx_create_res(road, 2, road_dist, p[i].d[k].dist);
		else
			mx_push_back_res(&lst, road, 2, road_dist, p[i].d[k].dist);
	}
	return lst;
}

bool mx_repeat_value(int *road, int k, int count) {
	for (int i = 0; i < count; i++) {
		if (road[i] == k)
			return false;
	}
	return true;
}

void init(bool *active_islands, int count)
{
	for (int i = 0; i < count; i++)
		active_islands[i] = true;
}

t_res *mx_algorithm(t_island *p, t_res *lst, int count, int itter) {
	bool active_islands[count];
	int i;
	int *road = NULL;
	int *road_dist = NULL;
	int dist;
	t_res *res = NULL;
	int k = 0;

	init(active_islands, count);
	active_islands[itter] = false;
	while (lst) {
		lst = mx_sort_list_res(lst);
		i = lst->road[lst->count - 1];

		for (int k = 0; k < p[i].routes_count && lst->road[lst->count - 1] != count - 1; k++) {
			if (active_islands[p[i].d[k].index_point]) {
				road = (int *)malloc(sizeof(int) * (lst->count + 1));
				road_dist = (int *)malloc(sizeof(int) * (lst->count));
				road = mx_memcpy(road, lst->road, sizeof(int) * lst->count);
				road[lst->count] = p[i].d[k].index_point;
				road_dist = mx_memcpy(road_dist, lst->road_dist, sizeof(int) * (lst->count - 1));
				road_dist[lst->count - 1] = p[i].d[k].dist;
				dist = lst->dist + p[i].d[k].dist;
				mx_push_back_res(&lst, road, lst->count + 1, road_dist, dist);
				free(road);
				free(road_dist);
			}
		}
		if (lst->count == 2 && k == 0 && lst->road[0] < lst->road[lst->count - 1]) {
			res = mx_create_res(lst->road, lst->count, lst->road_dist, lst->dist);
		}
		else if (lst->road[0] < lst->road[lst->count - 1])
			mx_push_back_res(&res, lst->road, lst->count, lst->road_dist, lst->dist);
		mx_pop_front_res(&lst);

		if (mx_find_iter(lst) != -1)
			mx_pop_elem_of_list(lst);
		k++;
		active_islands[i] = false;
	}
	if (!res) {
		res = (t_res *)malloc(sizeof(t_res));
		mx_memset(res, 0, sizeof(res));
	}
	// printf("  RES ++++++++++++++++\n");
	// mx_print_list(res);
	// printf("+++++++++++++++++++++++++\n");
	return res;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
//parseeeeeeeeeeeeee===============================
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

//======================================================

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
//=====================================================

#define ROVNO "========================================\n"

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
				mx_printstr("Distance: ");
				if (lst->count == 2)
					mx_printstr(mx_itoa(lst->dist));
				else {
					for (int n = 0; n < lst->count - 1; n++) {
						mx_printstr(mx_itoa(lst->road_dist[n]));
						if (n != lst->count - 2)
							mx_printstr(" + ");
						else {
							mx_printstr(" = ");
							mx_printstr(mx_itoa(lst->dist));
						}
					}
				}
				mx_printchar('\n');
				mx_printstr(ROVNO);
			}
		}
		lst = lst->next;
	}
}

t_res *mx_sort_list_res2(t_res *lst) {
	int i = 0;
	int size = mx_list_size_res(lst);
	t_res *new = lst;

	if (i != size - 1) {
		while (i < size) {
			if (lst->road[lst->count - 1] > lst->next->road[lst->count - 1]) {
					int tmp = lst->dist;
					lst->dist = lst->next->dist;
					lst->next->dist = tmp;
					tmp = lst->count;
					lst->count = lst->next->count;
					lst->next->count = tmp;
					mx_swap_elemint(&(lst->road_dist), &(lst->next->road_dist));
					mx_swap_elemint(&(lst->road), &(lst->next->road));
			}
			for (int j = 1; j < lst->count; j++) {
				if (lst->road[j] > lst->next->road[j]) {
					int tmp = lst->dist;
					lst->dist = lst->next->dist;
					lst->next->dist = tmp;
					tmp = lst->count;
					lst->count = lst->next->count;
					lst->next->count = tmp;
					mx_swap_elemint(&(lst->road_dist), &(lst->next->road_dist));
					mx_swap_elemint(&(lst->road), &(lst->next->road));
				}
			}
			lst = lst->next;
			i++;
			if (i == size - 1) {
				lst = new;
				i = 0;
				size--;
			}
		}
	}
	return new;
}



int main(int ac, char **av) {
	t_island *p;
	char *f = mx_file_to_str(av[1]);
	int count = mx_atoi(f);
	char **str = mx_strsplit(f, '\n');
	t_res **lst = (t_res **)malloc(sizeof(t_res *) * (count - 1));
	t_res **res = (t_res **)malloc(sizeof(t_res *) * (count - 1));
	

	p = (t_island *)malloc(sizeof(t_island) * (count));
	mx_parse_islands(p, str, count);
	mx_parse_dist(p, f, count, str);
	mx_del_strarr(&str);
	free(f);
	// printf("----------------\n");
	// print_island_struct(p, count);
	for (int i = 0; i < count - 1; i++) {
		lst[i] = mx_create_first_itter_list(p, i);
		res[i] = mx_algorithm(p, lst[i], count, i);
	}
	for (int j = 0; j < count - 1; j++) {
		if (res[j]->dist != 0) {
			res[j] = mx_sort_list_res2(res[j]);	
			mx_print_res(res[j], p, count);
		}
	}
	
	// mx_print_list(lst);
	// system("leaks -q a.out");
	return 0;
}

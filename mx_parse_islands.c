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

t_res *mx_sort_list_res(t_res *lst) {
	int i = 0;
	int size = mx_list_size_res(lst);
	t_res *new = lst;

	if (i != size - 1) {
		while (i < size) {
			if (lst->dist > lst->next->dist) {
				mx_swap_elements_res(lst);
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

void del_el_list(t_res *tmp) {
	free(tmp->road);
	free(tmp->road_dist);
	free(tmp); // Free memory
}

void mx_pop_elem_of_list(t_res *lst) {
	if (lst) {
		t_res *tmp = lst;
		t_res *tmp2;
		t_res *prv;

		while (mx_find_iter(lst) != -1) {
			tmp = lst;
			if (mx_find_iter(lst) == 0)
				mx_pop_front_res(&lst);
			else if (mx_find_iter(lst) == mx_list_size_res(lst) - 1)
				mx_pop_back_res(&lst);
			else {
				for (int i = 0; i < mx_find_iter(lst); i++) {
					prv = tmp; 
         			tmp = tmp->next; 
				}
				prv->next = tmp->next; 
				del_el_list(tmp);
			}
		}
	}
}

//**********************************************


// void mx_print_list(t_res *lst) {
// 	t_res *tmp = lst;
// 	while (tmp)
// 	{	
// 		printf("****PRINT NEW ROAD***********\n");
// 		printf("Road = ");
// 		for (int i = 0; i < tmp->count; i++) {
// 			printf("%d,", tmp->road[i]);
// 		}
// 		printf(" | ROAD_DIST = ");
// 		for (int i = 0; i < tmp->count - 1; i++) {
// 			printf("%d,", tmp->road_dist[i]);
// 		}
// 		printf(" | DIST = %d\n", tmp->dist);
// 		tmp = tmp->next;
// 		printf("***********END ROAD***********\n\n");
// 	}
// }

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

void init(bool *active_islands, int count, int itter)
{
	for (int i = 0; i < count; i++)
		active_islands[i] = true;
	active_islands[itter] = false;
}

void mx_create_res_active_island(t_res *lst, t_island p, int count, bool *active_islands) {
	for (int k = 0; k < p.routes_count && lst->road[lst->count - 1] != count - 1; k++) {
		if (active_islands[p.d[k].index_point]) {
			int *road = (int *)malloc(sizeof(int) * (lst->count + 1));
			int *road_dist = (int *)malloc(sizeof(int) * (lst->count));
			int dist = lst->dist + p.d[k].dist;
		
			road = mx_memcpy(road, lst->road, sizeof(int) * lst->count);
			road[lst->count] = p.d[k].index_point;
			road_dist = mx_memcpy(road_dist, lst->road_dist, sizeof(int) * (lst->count - 1));
			road_dist[lst->count - 1] = p.d[k].dist;
			mx_push_back_res(&lst, road, lst->count + 1, road_dist, dist);
			free(road);
			free(road_dist);
		}
	}
}

void mx_res_empty(t_res *res) {
	res = (t_res *)malloc(sizeof(t_res));
	mx_memset(res, 0, sizeof(res));
}

t_res *mx_algorithm(t_island *p, t_res *lst, int count, int itter) {
	bool active_islands[count];
	t_res *res = NULL;

	init(active_islands, count, itter);
	for (int k = 0; lst; k++) {
		lst = mx_sort_list_res(lst);
		int i = lst->road[lst->count - 1];

		mx_create_res_active_island(lst, p[i], count, active_islands);
		if (lst->count == 2 && k == 0 && lst->road[0] < lst->road[lst->count - 1])
			res = mx_create_res(lst->road, lst->count, lst->road_dist, lst->dist);
		else if (lst->road[0] < lst->road[lst->count - 1])
			mx_push_back_res(&res, lst->road, lst->count, lst->road_dist, lst->dist);
		mx_pop_front_res(&lst);
		mx_pop_elem_of_list(lst);
		active_islands[i] = false;
	}
	if (!res)
		mx_res_empty(res);
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

void mx_printerr(char *str) {
	write(2, str, mx_strlen(str));
}

void mx_invalid_num_of_is() {
	mx_printerr("error: invalid number of islands\n");
	exit(0);
}

static void add_elem_of_island(t_island *p, char *s, int *j) {
	p->index_name = *j;
	p->name = mx_strdup(s);
	(*j)++;
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
		double_del(s1, s2);
	}
	if (j != count)
		mx_invalid_num_of_is();
}

//======================================================

// void	print_island_struct(t_island *p, int count) {
// 	for (int i = 0; i < count; i++)
// 	{
// 		printf("****PRINT NEW ISLAND***********\n");
// 		printf("Name = %s, Index = %d Routes Count = %d\n", p[i].name, p[i].index_name, p[i].routes_count);
// 		for (int j = 0; j < p[i].routes_count; j++)
// 		{
// 			printf("point name = %s, index point = %d, distance = %d\n", p[i].d[j].point, p[i].d[j].index_point, p[i].d[j].dist);
// 		}
// 		printf("***********END ISLAND***********\n\n");
// 	}
// }
//=====================================================

#define ROVNO "========================================\n"


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

void mx_print_dist(t_res *lst, t_island *p, int count, int i) {
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
				mx_print_dist(lst, p, count, i);
				mx_printstr(ROVNO);
			}
		}
		lst = lst->next;
	}
}


void mx_sort_list_res2(t_res *lst) {
	bool sorted = false;
	t_res *head = lst;

	while (!sorted) {
		sorted = true;
		while (lst->next) {
			if ((lst->road[lst->count - 1] == lst->next->road[lst->next->count - 1]) 
				&& (lst->count == lst->next->count)) {
				for (int j = 1; j < lst->count - 1; j++) {
					if (lst->road[j] > lst->next->road[j]) {
						mx_swap_elements_res(lst);
						sorted = false;
					}
				}
			}
			lst = lst->next;
		}
		lst = head;
	}
}


void	mx_sort_list_res3(t_res *lst) {
	bool sorted = false;
	t_res *head = lst;

	while (!sorted) {
		sorted = true;
		while (lst->next) {
			if (lst->road[lst->count - 1] > lst->next->road[lst->next->count - 1]) {
				mx_swap_elements_res(lst);
				sorted = false;
			}
			lst = lst->next;
		}
		lst = head;
	}
}

void	mx_sort_list_res4(t_res *lst) {
	bool sorted = false;
	t_res *head = lst;

	while (!sorted) {
		sorted = true;
		while (lst->next) {
			if (lst->road[lst->count - 1] == lst->next->road[lst->next->count - 1]) {
				if (lst->count < lst->next->count) {
					mx_swap_elements_res(lst);
					sorted = false;
				}
			}
			lst = lst->next;
		}
		lst = head;
	}
}

int mx_arrlen(char **arr) {
	int i = 0;
	int j = 0;
	
	while (arr[i]) {
		while (arr[j])
			j++;
		i++;
	}
	return i;
}

int mx_char_count(char *str, char c) {
	int count = 0;

	for (int i = 0; str[i]; i++) {
		if (str[i] == c)
			count++;
	}
	return count;
}

/***************************************************************************************************/

bool str_is_digit(char *str) {
	for (int i = 0; str[i]; i++) {
		if (!mx_isdigit(str[i]))
			return false;
	}
	return true;
}

/***************************************************************************************************/

void is_empty(char *file) {
    int fd = open(file, O_RDONLY);
    char buf;
    
	if (read(fd, &buf, 1) == 0) {
		close(fd);
		mx_printerr(EMPTY_FILE);
		mx_printerr(file);
		mx_printerr(EMPTY_FILE2);
		exit (0);
	}
}

/***************************************************************************************************/

void is_folder(char *file) {
	int fd = open(file, O_RDONLY);

	if (read(fd, (void *)0, 0) < 0) {
 	    close(fd);
		mx_printerr(ERROR_USAGE);
	    exit (0);
    }
}

/***************************************************************************************************/

void validator_znakov(char *file, char **WordsA) {
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

/***************************************************************************************************/

void range_validator(char *file, char **WordsA) {
	for (int i = 1; WordsA[i]; i++) {
		char **str = mx_strsplit(WordsA[i], ',');
		if (!str_is_digit(str[1])) {
			char *num = mx_itoa(i + 1);
			mx_printerr(LINE_VALUE);
			mx_printerr(num);
			mx_printerr(LINE_VALUE2);
			exit (0);
		}
		mx_del_strarr(&str);
	}
}

/***************************************************************************************************/

void argument(int ac, char *file) {
	if (ac != 2) {
		mx_printerr(ERROR_USAGE);
		exit (0);
	}
}

/***************************************************************************************************/

void is_not_exist(char *file) {
	int fd = open(file, O_RDONLY);

	if (fd < 0) {
	    close(fd);
	    mx_printerr(FILE_EXIST);
	   	mx_printerr(file);
	    mx_printerr(FILE_EXIST2);
	    exit (0);
	}
}

/***************************************************************************************************/

void mx_print_erno(char *num) {
	mx_printerr(LINE_VALUE);
	mx_printerr(num);
	mx_printerr(LINE_VALUE2);
}


void valid_island(char **WordsA) {
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
		double_del(str, str2);
	}
}



bool mx_is_char(char *s) {
	for (int i = 0; s[i]; i++) {
		if (!((s[i] >= 65 && s[i] <= 90)
			|| (s[i] >= 97 && s[i] <= 122)))
			return false;
	}
	return true;
}

void mx_island_not_char(char **str) {
	char **s1;
	char **s2;
	
	for (int i = 1; str[i]; i++) {
		s1 = mx_strsplit(str[i], '-');
		s2 = mx_strsplit(s1[1], ',');
		if (!(mx_is_char(s1[0]))) {
			char *num = mx_itoa(i + 1);
			mx_print_erno(num);
			exit (0);
		}
		if (!(mx_is_char(s2[0]))) {
			char *num = mx_itoa(i + 1);
			mx_print_erno(num);
			exit (0);
		}
		double_del(s1, s2);
	}
}

/***************************************************************************************************/

void apex_count(char **WordsA) {
	if (!str_is_digit(WordsA[0])) {
		mx_printerr("error: line 1 is not valid\n");
		exit (0);
	}
}

/***************************************************************************************************/

void print_error1(char *av, char **WordsA) {
	apex_count(WordsA);
	mx_island_not_char(WordsA);
	validator_znakov(av, WordsA);
	range_validator(av, WordsA);
	valid_island(WordsA);
}

void print_error2(int ac, char *av) {
	argument(ac, av);
	is_not_exist(av);
	is_folder(av);
	is_empty(av);
}

/***************************************************************************************************/

int main(int ac, char **av) {
	t_island *p;
	
	print_error2(ac, av[1]);
	char *f = mx_file_to_str(av[1]);
	char **str = mx_strsplit(f, '\n');
	int count = mx_atoi(f);
	print_error1(av[1], str);
	
	if (count == 0)
		mx_invalid_num_of_is();
	t_res **lst = (t_res **)malloc(sizeof(t_res *) * (count - 1));
	t_res **res = (t_res **)malloc(sizeof(t_res *) * (count - 1));

	p = (t_island *)malloc(sizeof(t_island) * (count));
	mx_parse_islands(p, str, count);
	mx_parse_dist(p, f, count, str);
	mx_del_strarr(&str);
	free(f);
	for (int i = 0; i < count - 1; i++) {
		lst[i] = mx_create_first_itter_list(p, i);
		res[i] = mx_algorithm(p, lst[i], count, i);
	}
	for (int j = 0; j < count - 1; j++) {
		if (res[j]->dist != 0) {
			mx_sort_list_res3(res[j]);
			mx_sort_list_res4(res[j]);
			mx_sort_list_res2(res[j]);
			mx_print_res(res[j], p, count);
		}
	}
	
	// system("leaks -q a.out");
	
	return 0;
}

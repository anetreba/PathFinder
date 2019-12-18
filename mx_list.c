#include "inc/libmx.h"

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


int mx_find_iter(t_res *lst) {
	int i = 0;

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
	int count;
	t_res *tmp = lst;
	t_res *tmp2;

	while ((count = mx_find_iter(lst)) != -1) {
		if (count == 0)
			mx_pop_front_res(&lst);
		else if (count == mx_list_size_res(lst) - 1)
			mx_pop_back_res(&lst);
		else {
			for (int i = 0; i < count; i++) {
				tmp = tmp->next;
			}
			tmp2 = tmp->next->next;
			free(tmp->next->road);
			free(tmp->next->road_dist);
			free(tmp->next);
			tmp->next = tmp2;
		}
	}
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

int main() {
	int road2[3] = {1, 3, 5};
	int road1[2] = {1, 4};
	int road[3] = {1, 2, 4};

	int road_dist[1] = {1};
	
	int dist2 = 4;
	int dist = 1;
	int dist1 = 3;


	t_res *lst = mx_create_res(road2, 3, road_dist, dist2);
	mx_push_back_res(&lst, road1, 2, road_dist, dist);
	mx_push_back_res(&lst, road, 3, road_dist, dist1);
	int i = mx_find_iter(lst);
	printf(" itter = %d\n", i);
	mx_pop_elem_of_list(lst);
	mx_print_list(lst);
	system("leaks -q a.out");
}


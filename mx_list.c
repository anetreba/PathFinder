#include "inc/libmx.h"

t_res  *mx_create_res(char *road, char *road_dist, int dist) {
	t_res *res = (t_res*)malloc(sizeof(t_res));

 	res->road = mx_strdup(road);
	res->road_dist = mx_strdup(road_dist);
	res->dist = dist;

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

void mx_push_back_res(t_res **list, char *road, char *road_dist, int dist) {
	if (list) {
		t_res *new = mx_create_res(road, road_dist, dist);
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

void mx_push_front_res(t_res **list, char *road, char *road_dist, int dist) {
	t_res *new_head = mx_create_res(road, road_dist, dist);

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

t_list *mx_sort_list_res(t_res *lst) {
	int i = 0;
	int size = mx_list_size_res(lst);
	t_res *new = lst;

	while (i < size) {
		if (lst->dist > lst->next->dist) {
			mx_swap_elem(&(lst->dist), &(lst->next->dist));
			mx_swap_elem(&(lst->road_dist), &(lst->next->road_dist));
			mx_swap_elem(&(lst->road), &(lst->next->road));
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

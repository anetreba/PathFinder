#include "pathfinder.h"

t_res  *mx_create_res(int *road, int count, int *road_dist, int dist) {
	t_res *res = (t_res*)malloc(sizeof(t_res));

	res->road = (int*)malloc(sizeof(int) * count);
	res->road_dist = (int*)malloc(sizeof(int) * (count - 1));
 	res->road = mx_memcpy(res->road, road, sizeof(int) * count);
	res->road_dist = mx_memcpy(res->road_dist, road_dist
		, sizeof(int) * (count - 1));
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

void mx_push_back_res(t_res **list, int *road, int count
	, int *road_dist, int dist) {
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

void mx_push_front_res(t_res **list, int *road, int count
	, int *road_dist, int dist) {
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

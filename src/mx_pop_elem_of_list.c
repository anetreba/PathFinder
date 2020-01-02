#include "pathfinder.h"

int mx_find_iter(t_res *lst) {
	int i = 0;

	if (!lst)
		return -1;
	for (t_res *tmp1 = lst; tmp1; tmp1 = tmp1->next) {
		i = 0;
		for (t_res *tmp2 = lst; tmp2; tmp2 = tmp2->next) {
			if ((tmp1->road[tmp1->count - 1] == tmp2->road[tmp2->count - 1])
				&& tmp2->dist > tmp1->dist)
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
	free(tmp);
}

void mx_pop_elem_of_list(t_res *lst) {
	if (lst) {
		t_res *tmp = lst;
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

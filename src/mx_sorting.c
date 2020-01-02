#include "pathfinder.h"

t_res *mx_sort_list_res(t_res *lst) {
	int i = 0;
	int size = mx_list_size_res(lst);
	t_res *new = lst;

	if (i != size - 1) {
		while (i < size) {
			if (lst->dist > lst->next->dist)
				mx_swap_elements_res(lst);
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

void mx_sort_list_res2(t_res *lst) {
	int i = 0;
	int size = mx_list_size_res(lst);
	t_res *new = lst;

	if (i != size - 1)
		while (i < size) {
			if ((lst->road[lst->count - 1]
				== lst->next->road[lst->next->count - 1]) 
				&& (lst->count == lst->next->count))
				for (int j = 1; j < lst->count - 1; j++)
					if (lst->road[j] > lst->next->road[j])
						mx_swap_elements_res(lst);
			lst = lst->next;
			i++;
			if (i == size - 1) {
				lst = new;
				i = 0;
				size--;
			}	
		}
}


void mx_sort_list_res3(t_res *lst) {
	bool sorted = false;
	t_res *head = lst;

	while (!sorted) {
		sorted = true;
		while (lst->next) {
			if (lst->road[lst->count - 1]
				> lst->next->road[lst->next->count - 1]) {
				mx_swap_elements_res(lst);
				sorted = false;
			}
			lst = lst->next;
		}
		lst = head;
	}
}

void mx_sort_list_res4(t_res *lst) {
	bool sorted = false;
	t_res *head = lst;

	while (!sorted) {
		sorted = true;
		while (lst->next) {
			if (lst->road[lst->count - 1]
				== lst->next->road[lst->next->count - 1]) {
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

#include <stdio.h>
#include "inc/libmx.h"

void mx_print_list(t_res *lst) {
	printf("****PRINT NEW ROAD***********\n");
	while (lst)
	{	
		printf("Road = %s, Road_dist = %s dist = %d\n", lst->road, lst->road_dist, lst->dist);
		lst = lst->next;
	}
	printf("***********END ROAD***********\n\n");
}


t_res *mx_create_first_itter_list(t_island *p, int count) {
	char *tmp1 = NULL;
	char *tmp2 = NULL;
	t_res *lst;
	int i = 0;
	char *s = ",";

	//for (int i = 0; i < count; i++) {
		if (i == 0) {
			for (int k = 0; k < p[i].routes_count; k++) {
				tmp1 = mx_strjoin(tmp1, mx_itoa(p[i].index_name));
				tmp1 = mx_strjoin(tmp1, s);
				tmp1 = mx_strjoin(tmp1, mx_itoa(p[i].d[k].index_point));
				tmp2 = mx_strjoin(tmp2, mx_itoa(p[i].d[k].dist));
				if (k == 0)
					lst = mx_create_res(tmp1, tmp2, p[i].d[k].dist);
				else
					mx_push_back_res(&lst, tmp1, tmp2, p[i].d[k].dist);
			}
		}
	//}
	mx_print_list(lst);
	return lst;
}

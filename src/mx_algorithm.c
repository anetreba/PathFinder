#include "pathfinder.h"

static void init(bool *active_islands, int count, int itter);

t_res *mx_create_first_itter_list(t_island *p, int i) {
	t_res *lst;
	int road[2];
	int road_dist[1];
	unsigned int dist = 0;

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

void mx_create_res_active_island(t_res *lst, t_island p,
 	int count, bool *active_islands) {
	for (int k = 0; k < p.routes_count
		&& lst->road[lst->count - 1] != count - 1; k++) {
		if (active_islands[p.d[k].index_point]) {
			int *road = (int *)malloc(sizeof(int) * (lst->count + 1));
			int *road_dist = (int *)malloc(sizeof(int) * (lst->count));
			unsigned int dist = lst->dist + p.d[k].dist;
		
			road = mx_memcpy(road, lst->road, sizeof(int) * lst->count);
			road[lst->count] = p.d[k].index_point;
			road_dist = mx_memcpy(road_dist, lst->road_dist
				, sizeof(int) * (lst->count - 1));
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

t_res *mx_algorithm(t_island *p, t_res *l, int count, int itter) {
	bool active_islands[count];
	t_res *res = NULL;

	init(active_islands, count, itter);
	for (int k = 0; l; k++) {
		l = mx_sort_list_res(l);
		int i = l->road[l->count - 1];

		mx_create_res_active_island(l, p[i], count, active_islands);
		if (l->count == 2 && k == 0 && l->road[0] < l->road[l->count - 1])
			res = mx_create_res(l->road, l->count, l->road_dist, l->dist);
		else if (l->road[0] < l->road[l->count - 1])
			mx_push_back_res(&res, l->road, l->count, l->road_dist, l->dist);
		mx_pop_elem_of_list(l);
		mx_pop_front_res(&l);
		active_islands[i] = false;
	}
	if (!res)
		mx_res_empty(res);
	return res;
}

static void init(bool *active_islands, int count, int itter) {
	for (int i = 0; i < count; i++)
		active_islands[i] = true;
	active_islands[itter] = false;
}

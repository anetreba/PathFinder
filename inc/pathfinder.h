#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "libmx/inc/libmx.h"

typedef struct s_dist {
	char *point;
	int index_point;
	unsigned int dist;
}				t_dist;

typedef struct  s_island {
	char *name;
	int index_name;
	int	routes_count;
	struct s_dist *d;
} 				t_island;

typedef struct s_res {
	int *road;
	int *road_dist;
	int dist;
	int count;
	struct s_res *next;
}				t_res;

#define ERROR_USAGE "usage: ./pathfinder [filename]\n"
#define FILE_EXIST "error: file "
#define FILE_EXIST2 " does not exist\n"
#define EMPTY_FILE "error: file "
#define EMPTY_FILE2 " is empty\n"
#define LINE_ERROR "error: line 1 is not valid\n"
#define LINE_VALUE "error: line "
#define LINE_VALUE2 " is not valid\n"
#define INVALID_ISLANDS "error: invalid number of islands\n"
#define ROVNO "========================================\n"


t_res *mx_create_res(int *road, int count, int *road_dist, int dist);
void mx_pop_front_res(t_res **head);
void mx_push_back_res(t_res **list, int *road, int count
	, int *road_dist, int dist);
void mx_push_front_res(t_res **list, int *road, int count
	, int *road_dist, int dist);
int mx_list_size_res(t_res *list);
void mx_swap_elemint(int **s1, int **s2);
void mx_swap_int(int *a, int *b);
void mx_swap_elements_res(t_res *lst);
t_res *mx_sort_list_res(t_res *lst);
int mx_find_iter(t_res *lst);
void mx_pop_back_res(t_res **head);
void del_el_list(t_res *tmp);
void mx_pop_elem_of_list(t_res *lst);
t_res *mx_create_first_itter_list(t_island *p, int i);
bool mx_repeat_value(int *road, int k, int count);
void mx_create_res_active_island(t_res *lst, t_island p
	, int count, bool *active_islands);
void mx_res_empty(t_res *res);
t_res *mx_algorithm(t_island *p, t_res *l, int count, int itter);
void mx_double_del(char **s1, char **s2);
void mx_parse_dist(t_island *p, char *f, int count, char **str);
void mx_invalid_num_of_is();
void mx_parse_islands(t_island *p, char **str, int count);
void mx_print_route(t_res *lst, t_island *p, int count, int i);
void mx_print_num(t_res *lst);
void mx_print_dist(t_res *lst);
void mx_print_res(t_res *lst, t_island *p, int count);
void mx_sort_list_res2(t_res *lst);
void mx_sort_list_res3(t_res *lst);
void mx_sort_list_res4(t_res *lst);
void mx_print_error1(char **WordsA, char *f);
void mx_apex_count(char **WordsA);
void mx_print_erno(char *num);
void mx_island_not_char(char **str);
void mx_two_perenos(char *f);
void mx_print_route(t_res *lst, t_island *p, int count, int i);
void mx_print_num(t_res *lst);
void mx_print_res(t_res *lst, t_island *p, int count);
void mx_sort_print_res(t_res **res, t_island *p, int count);
bool mx_print_error2(int ac, char *av);
bool str_is_digit(char *str);


#endif

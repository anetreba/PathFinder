NAME = pathfinder

INC = pathfinder.h

SRC = main.c \
	mx_swap_elem_res.c \
	mx_sorting.c \
	mx_res_list.c \
	mx_print_res.c \
	mx_print_error2.c \
	mx_print_error1.c \
	mx_pop_elem_of_list.c \
	mx_parse_islands.c \
	mx_parse_dist.c \
	mx_errors.c \
	mx_algorithm.c

OBJ = main.o \
	mx_swap_elem_res.o \
	mx_sorting.o \
	mx_res_list.o \
	mx_print_res.o \
	mx_print_error2.o \
	mx_print_error1.o \
	mx_pop_elem_of_list.o \
	mx_parse_islands.o \
	mx_parse_dist.o \
	mx_errors.o \
	mx_algorithm.o


CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install clean

install:
	@make install -sC libmx
	@cp $(addprefix src/, $(SRC)) .
	@cp $(addprefix inc/, $(INC)) .
	@clang $(CFLAGS) -c $(SRC) -I $(INC)
	@clang $(CFLAGS) libmx/libmx.a $(OBJ) -o $(NAME)
	@mkdir -p obj
	@mv $(OBJ) ./obj

uninstall: clean
	@make uninstall -sC libmx
	@rm -rf $(NAME)

clean:
	@make clean -sC libmx
	@rm -rf $(INC) $(SRC) ./obj

reinstall: uninstall install
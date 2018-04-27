NAME = lem-in

#CC = gcc
CC = gcc -Wall -Wextra -Werror
#CC = gcc -Wall -Wextra -Werror -g -fsanitize=address

C_DIR = srcs
C_FILES = $(addprefix $(C_DIR)/, \
				tools_1.c \
				tools_2.c \
				tools_3.c \
				get_data.c \
				first_init.c \
				delete_and_clear.c \
				put_piece.c \
				border_weight_calc.c \
				border_weight_clear.c \
				heat_weight_calc_1.c \
				heat_weight_calc_2.c \
				strat_map_calc.c \
				strat_adjustment.c \
				check_borders.c \
				main.c)


O_DIR = objs
O_FILES = $(C_FILES:$(C_DIR)/%.c=$(O_DIR)/%.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
H_DIR = includes

LIB = -L$(LIBFT_DIR) -lft
INCL = -I$(H_DIR) -I$(LIBFT_DIR)/includes

################################################################################
#################################### RULES #####################################
################################################################################

all : $(NAME)

$(LIBFT) :
	@echo "\033[1;31m-- LIBFT ----------------------\033[0m"
	@make -C $(LIBFT_DIR)
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"
	@echo "\033[1;31m-- OBJECTS ---------------------\033[0m"

$(NAME) : $(LIBFT) $(O_FILES)
	@$(CC) $(O_FILES) -o $@ $(LIB)
	@echo "\033[1;31m-- EXEC ------------------------\033[0m"
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

$(O_DIR)/%.o: $(C_DIR)/%.c $(H_DIR)
	@mkdir -p $(O_DIR)
	@$(CC) -o $@ -c $< $(INCL)
	@printf  "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

clean :
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(O_DIR)

fclean : clean
	@make fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME)

re : fclean all

.PHONY : clean all fclean re

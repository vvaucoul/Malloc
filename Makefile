# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/27 18:18:37 by vvaucoul          #+#    #+#              #
#    Updated: 2022/10/28 21:12:11 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

##****************************************************************************##
##							        PATH 									  ##
##****************************************************************************##

PATH_HEADER = ./includes/
PATH_LIBFT = ./libft
PATH_OBJS = ./objs
PATH_SRCS = ./srcs

################################################################################
#								 	 COLORS				  					   #
################################################################################

# This is a minimal set of ANSI/VT100 color codes
_END=$'\033[0m
_BOLD=$'\033[1m
_UNDER=$'\033[4m
_REV=$'\033[7m

# Colors
_GREY=$'\033[30m
_RED=$'\033[31m
_GREEN=$'\033[32m
_YELLOW=$'\033[33m
_BLUE=$'\033[34m
_PURPLE=$'\033[35m
_CYAN=$'\033[36m
_WHITE=$'\033[37m

# Inverted, i.e. colored backgrounds
_IGREY=$'\033[40m
_IRED=$'\033[41m
_IGREEN=$'\033[42m
_IYELLOW=$'\033[43m
_IBLUE=$'\033[44m
_IPURPLE=$'\033[45m
_ICYAN=$'\033[46m
_IWHITE=$'\033[47m

##****************************************************************************##
##							     COMPILATION 								  ##
##****************************************************************************##

CC = clang
CFLAGS = -I$(PATH_HEADER) -I$(PATH_LIBFT)/includes -Wall -Wextra -Werror -fPIC -g3 -pthread -Werror
LIB_FLAGS = -fPIC -shared -L./libft
LIBFT_NAME = 42_PCC_LIBFT.a

##****************************************************************************##
##							     EXECUTABLE 								  ##
##****************************************************************************##

NAME = libft_malloc_$(HOSTTYPE).so
LIB_NAME = libft_malloc.so

TEST_MALLOC = test_malloc
TEST_FREE = test_free
TEST_REALLOC = test_realloc
TEST_SPEED = test_speed
TEST_THREAD_SAFE = test_thread_safe
TEST_SHOW_ALLOC_MEM = test_show_alloc_mem

##****************************************************************************##
##							     	FILES	 								  ##
##****************************************************************************##

SRCS = 	$(PATH_SRCS)/utils.c \
		$(PATH_SRCS)/malloc.c \
		$(PATH_SRCS)/meta_heap.c \
		$(PATH_SRCS)/defragmentation.c \
		$(PATH_SRCS)/free.c \
		$(PATH_SRCS)/meta_block.c \
		$(PATH_SRCS)/realloc.c \
		$(PATH_SRCS)/show_alloc_mem.c \
		$(PATH_SRCS)/show_alloc_mem_ex.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
	@printf "\r                                                               "
	@$(PRINT_COMP) $@
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

##****************************************************************************##
##							     	PRINT	 								  ##
##****************************************************************************##

PRINT_COMP		=	printf "\r$(_BOLD)$(_WHITE)- $(_BOLD)$(_CYAN)[%s]\r\t\t\t\t $(_BOLD)$(_WHITE)[✓]\n"

##****************************************************************************##
##							     	RULES	 								  ##
##****************************************************************************##

all: $(NAME)

$(NAME): $(OBJS)
	@cd libft && make && cd .. && cp libft/$(LIBFT_NAME) .
	@$(CC) $(CFLAGS) $(LIB_FLAGS) $^ -o $(NAME)
	@printf "$(_BOLD)$(_GREEN)$(NAME) created !$(_END)\n"
	@rm -f $(LIB_NAME)
	@ln -fs $(NAME) $(LIB_NAME)
	@printf "$(BOLD)$(_GREEN)Symbolic Link: $(LIB_NAME) created !$(_END)\n"

$(PATH_OBJS)/%.o: $(PATH_SRCS)/%.c
	@mkdir -p $(@D)
	$(CC) -c -o $@ $(CFLAGS) $^ -O0 -g -I $(PATH_HEADER)

$(TEST_MALLOC): all
	@rm -f $(TEST_MALLOC)
	@$(CC) $(NAME) tests/$(TEST_MALLOC).c tests/lib_test.c -I$(PATH_HEADER) \
	-I./$(PATH_LIBFT)/includes -L. $(LIB_NAME) -L. $(LIBFT_NAME) $(LIBFT_NAME) \
	-o $(TEST_MALLOC) -fPIC -g3
	@printf "$(_BOLD)$(_RED)Test Malloc created !$(_END)\n"

$(TEST_FREE): all
	@rm -f $(TEST_FREE)
	@$(CC) $(NAME) tests/$(TEST_FREE).c tests/lib_test.c -I$(PATH_HEADER) \
	-I./$(PATH_LIBFT)/includes -L. $(LIB_NAME) -L $(LIBFT_NAME) $(LIBFT_NAME) \
	-o $(TEST_FREE) -fPIC -g3
	@printf "$(_BOLD)$(_RED)Test Free created !$(_END)\n"

$(TEST_REALLOC): all
	@rm -f $(TEST_REALLOC)
	@$(CC) $(NAME) tests/$(TEST_REALLOC).c tests/lib_test.c -I$(PATH_HEADER) \
	-I./$(PATH_LIBFT)/includes -L. $(LIB_NAME) -L $(LIBFT_NAME) $(LIBFT_NAME) \
	-o $(TEST_REALLOC) -fPIC -g3
	@printf "$(_BOLD)$(_RED)Test Realloc created !$(_END)\n"

$(TEST_SPEED): all
	@rm -f $(TEST_SPEED)
	@$(CC) $(NAME) tests/speed_tests/malloc/speed_test_malloc.c tests/lib_test.c -I$(PATH_HEADER) \
	-I./$(PATH_LIBFT)/includes -L. $(LIB_NAME) -L $(LIBFT_NAME) $(LIBFT_NAME) \
	-o $(TEST_SPEED) -fPIC -g3
	@printf "$(_BOLD)$(_RED)Test Speed created !$(_END)\n"

$(TEST_THREAD_SAFE): all
	@rm -f $(TEST_THREAD_SAFE)
	@$(CC) $(NAME) tests/test_malloc_thread_safe.c tests/lib_test.c -I$(PATH_HEADER) \
	-I./$(PATH_LIBFT)/includes -L. $(LIB_NAME) -L $(LIBFT_NAME) $(LIBFT_NAME) \
	-o $(TEST_THREAD_SAFE) -fPIC -g3 -lpthread
	@printf "$(_BOLD)$(_RED)Test Thread Safe created !$(_END)\n"

$(TEST_SHOW_ALLOC_MEM): all
	@rm -f $(TEST_SHOW_ALLOC_MEM)
	@$(CC) $(NAME) tests/test_show_alloc_mem.c tests/lib_test.c -I$(PATH_HEADER) \
	-I./$(PATH_LIBFT)/includes -L. $(LIB_NAME) -L $(LIBFT_NAME) $(LIBFT_NAME) \
	-o $(TEST_SHOW_ALLOC_MEM) -fPIC -g3
	@printf "$(_BOLD)$(_RED)Test Show Alloc Mem created !$(_END)\n"

test_all: $(TEST_MALLOC) $(TEST_FREE) $(TEST_REALLOC) $(TEST_SPEED) $(TEST_THREAD_SAFE) $(TEST_SHOW_ALLOC_MEM)

clean:
	@cd libft && make clean && cd .. &&  rm -f $(LIBFT_NAME)
	@rm -rf $(OBJS)
	@rm -rf $(PATH_OBJS)
	@rm -f $(TEST_MALLOC) $(TEST_FREE) $(TEST_REALLOC) $(TEST_SPEED) $(TEST_THREAD_SAFE) $(TEST_SHOW_ALLOC_MEM)
	@printf "$(_BOLD)$(_YELLOW)libft_malloc cleaned...$(_END)\n"

fclean: clean
	@cd libft && make fclean
	@rm -f $(NAME) $(LIB_NAME)
	@printf "$(_BOLD)$(_YELLOW)$(NAME) deleted...$(_END)\n"

re: fclean lib all

tests: all $(TEST_MALLOC) $(TEST_FREE) $(TEST_REALLOC)

lib: all
	@sh export_env.sh
	@printf "$(_BOLD)$(_PURPLE)export library...$(_END)\n"

.PHONY: all clean fclean re tests lib test_all $(TEST_MALLOC) $(TEST_FREE) $(TEST_REALLOC) $(TEST_SPEED) $(TEST_THREAD_SAFE) $(TEST_SHOW_ALLOC_MEM)







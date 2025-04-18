NAME		:=	philo
BONUS_NAME	:=	philo_bonus

#==============================COMPIL===========================#

CC			:=	cc
CFLAGS		:=	-MP -MMD -Wall -Wextra -Werror

ifeq ($(DEBUG), 1)
	CFLAGS += -g
endif

ifeq ($(SAN), 1)
	CFLAGS += -fsanitize=thread
endif

MAKEFLAGS	:=	--no-print-directory

#================================COUNT============================#

NB_COMP	:=	1

ifndef RECURSION
TO_COMP :=	$(shell make RECURSION=1 -n | grep Compiling | wc -l)
else
TO_COMP	:=	1
endif

PERCENT	:= 0

#NB_COMP_BONUS := 1
#ifndef RECURSION
#TO_COMP_BONUS := $(shell make bonus RECURSION=1 -n | grep Compiling | wc -l)
#else
#TO_COMP_BONUS := 1
#endif

#==============================COLORS==============================#
NOC			= \e[0m
BOLD		= \e[1m
DIM			= \e[2m
UNDERLINE	= \e[4m
BLACK		= \e[1;30m
RED			= \e[1m\e[38;5;196m
GREEN		= \e[1m\e[38;5;76m
YELLOW		= \e[1m\e[38;5;220m
BLUE		= \e[1m\e[38;5;33m
PURPLE		= \e[1;35m
CYAN		= \e[1;36m
WHITE		= \e[1;37m

BLACK_BG 	= \033[0;40m
RED_BG 		= \033[0;41m
GREEN_BG 	= \033[0;42m
YELLOW_BG 	= \033[0;43m
BLUE_BG 	= \033[0;44m
MAGENTA_BG 	= \033[0;45m
CYAN_BG 	= \033[0;46m
WHITE_BG 	= \033[0;47m
RESET_BG	= \033[0m

#================================DIRS============================#

SRC_DIR			:=  srcs
SRC_BONUS_DIR	:=	bonus
INCLUDES_DIR	:=	includes
BUILD_DIR		:=	.build

#==============================SOURCES===========================#

# no duplicates

SRCS_FILES:=	main.c\
				parsing/checking.c\
				parsing/parsing.c\
				parsing/init.c\
				routine/routines.c\
				routine/activity.c\
				routine/monitor.c\
				routine/mutex_get.c\
				routine/mutex_set.c\
				utils/conv.c\
				utils/errors.c\
				utils/ft_itoa.c\
				utils/mem.c\
				utils/print.c\
				utils/strings.c\
				utils/time.c\
				debug.c\

SRCS_FILES_BONUS:= $(patsubst %.c, %_bonus.c, $(SRCS_FILES))\

SRCS:=			$(addprefix $(SRC_DIR)/, $(SRCS_FILES))
SRCS_BONUS:=	$(addprefix $(SRC_DIR)/$(SRC_BONUS_DIR)/, $(SRCS_FILES_BONUS))

#=============================OBJECTS===========================#

OBJS:=			${SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o}
OBJS_BONUS:=	${SRCS_BONUS:$(SRC_DIR)/bonus/%.c=$(BUILD_DIR)/bonus/%.o}

#===============================DEPS=============================#

DEPS:=			${SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.d}
DEPS_BONUS:=	${SRCS_BONUS:$(SRC_DIR)/bonus/%.c=$(BUILD_DIR)/bonus/%.d}

#=============================INCLUDES===========================#

INC			:=	-I $(INCLUDES_DIR)

#================================DIR=============================#

DIRS			:=	$(sort $(shell dirname $(OBJS))) #no duplicates
DIRS_BONUS		:=	$(sort $(shell dirname $(OBJS_BONUS))) #no duplicates

#===============================RULES============================#

all: $(NAME)

$(DIRS):
	@mkdir -p $@

$(DIRS_BONUS):
	@mkdir -p $@

$(NAME): $(OBJS)
	@echo "\n$(GREEN)Create binaries$(NOC)"
	@$(CC) $(CFLAGS) $(OBJS) $(INC) -o $@

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(OBJS_BONUS)
	@echo "\n$(GREEN)Create bonus binaries$(NOC)"
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(INC) -o $@

# $$@D gets directory from current target - pipe prevents from relink
# tput cols to get columns nb of terminal
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(DIRS)
	@mkdir -p $(BUILD_DIR)
	@if [ $(NB_COMP) -eq 1 ]; then echo "$(BOLD)Compilation of source files :$(NOC)";fi
	$(eval PERCENT=$(shell expr $(NB_COMP)00 "/" $(TO_COMP)))
	@if [ $(PERCENT) -le 30 ]; then echo -n "$(RED)"; elif [ $(PERCENT) -le 66 ]; then echo -n "$(YELLOW)"; elif [ $(PERCENT) -gt 66 ]; then echo -n "$(GREEN)"; fi
	@echo -n "\r"; for i in $$(seq 1 $$(/usr/bin/tput cols)); do echo -n " "; done
	@echo -n "\r"; for i in $$(seq 1 25); do if [ $$(expr $$i "*" 4) -le $(PERCENT) ]; then echo -n "█"; else echo -n " "; fi; done; echo -n "";
	@printf " $(NB_COMP)/$(TO_COMP) - Compiling $<"
	@echo -n "$(NOC)"
	@$(CC) $(CFLAGS) $(INC) $< -c -o $@
	$(eval NB_COMP=$(shell expr $(NB_COMP) + 1))

$(BUILD_DIR)/bonus/%.o: $(SRC_DIR)/bonus/%.c | $(DIRS_BONUS)
	@mkdir -p $(BUILD_DIR)/bonus/
	@if [ $(NB_COMP_BONUS) -eq 1 ]; then echo "$(BOLD)Compilation of source files :$(NOC)";fi
	$(eval PERCENT=$(shell expr $(NB_COMP_BONUS)00 "/" $(TO_COMP_BONUS)))
	@if [ $(PERCENT) -le 30 ]; then echo -n "$(RED)"; elif [ $(PERCENT) -le 66 ]; then echo -n "$(YELLOW)"; elif [ $(PERCENT) -gt 66 ]; then echo -n "$(GREEN)"; fi
	@echo -n "\r"; for i in $$(seq 1 $$(/usr/bin/tput cols)); do echo -n " "; done
	@echo -n "\r"; for i in $$(seq 1 25); do if [ $$(expr $$i "*" 4) -le $(PERCENT) ]; then echo -n "█"; else echo -n " "; fi; done; echo -n "";
	@printf " $(NB_COMP_BONUS)/$(TO_COMP_BONUS) - Compiling $<"
	@echo -n "$(NOC)"
	@$(CC) $(CFLAGS) $(INC) $< -c -o $@
	$(eval NB_COMP_BONUS=$(shell expr $(NB_COMP_BONUS) + 1))

clean:
	@echo "$(RED)Remove objects$(NOC)"
	@rm -rf $(BUILD_DIR)

fclean: clean
	@echo "$(RED)Remove binary$(NOC)"
	@rm -f $(NAME)
	@rm -f $(BONUS_NAME)

re: fclean
	@make

.PHONY: all clean fclean re clone

-include $(DEPS)

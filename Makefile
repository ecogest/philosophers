# ================================= PROJECT ================================== #

NAME = philo

all: $(NAME)

#  =========================== COMPILER AND FLAGS ===========================  #

CC        = clang
CXX       = clang++
CPPFLAGS  = -Iincludes
CFLAGS    = -Wall -Werror -Wextra
LDFLAGS   = -lpthread

#  ========================== SOURCES AND OBJECTS ===========================  #

SRCDIR  = src
OBJDIR  = obj
SRCS = src/timestamp.c \
			 src/philo_fork.c \
			 src/cleanup.c \
			 src/ft_atoi.c \
			 src/ft_isnumber.c \
			 src/f_malloc.c \
			 src/philo_do.c \
			 src/action_get_duration.c \
			 src/f_mutex.c \
			 src/ft_isint.c \
			 src/philo_job.c \
			 src/main.c \
			 src/ft_strlen.c \
			 src/main_philo.c \
			 src/root_init.c \
			 src/status_check_and_update.c \
			 src/ft_putstr_fd.c \
			 src/root_parse_av.c \
			 src/f_thread.c \
			 src/monitor_mealtime.c \
			 src/put_error_and_usage.c \
			 src/philo_print_action.c \
			 src/hello_world.c \
			 src/philos_init.c \
			 src/philo_ms_sleep.c
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

#  ============================ LINK EXECUTABLE =============================  #

$(NAME): $(OBJDIR) $(OBJS)
	@$(CC) $(OBJS) $(MAIN_OBJ) $(LDFLAGS) -o $@
	@printf "✨ $(BOLD)$(GREEN)%s$(NC)$(GREEN) has been successfully linked.\n$(NC)" $@

#  ============================ COMPILE OBJECTS =============================  #

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "$(YELLOW)Compiling: %s\n$(NC)" $<
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# ================================= CLEANING ================================= #

clean:
	@printf "$(MAGENTA)Cleaning objects.\n$(NC)"
	@rm -rf $(OBJDIR)

fclean: clean
	@printf "$(MAGENTA)Removing binary: $(BOLD)%s\n$(NC)" $(NAME)
	@rm -f $(NAME) $(NAME_TEST)

re: fclean all

#  ================================= .PHONY =================================  #

.PHONY: all link clean fclean re

#  ================================= COLORS =================================  #

CYAN    = "\\e[36m"
GREEN   = "\\e[32m"
MAGENTA = "\\e[35m"
GRAY    = "\\e[37m"
YELLOW  = "\\e[33m"

BOLD    = "\\e[1m"
NC      = "\\e[0m"

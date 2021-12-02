# ================================= PROJECT ================================== #

NAME = philo

all: $(NAME)

#  =========================== COMPILER AND FLAGS ===========================  #

CC        = clang
CXX       = clang++
CPPFLAGS  = -Iincludes
CPPFLAGS += -Ilibft/includes
CFLAGS    = -Wall -Werror -Wextra
CFLAGS   += -g
LDFLAGS   = -Llibft -lft -lpthread
# CFLAGS   += -fsanitize=address
# LDFLAGS  += -lasan
# CFLAGS   += -fsanitize=thread
# LDFLAGS  += -ltsan

#  ========================== SOURCES AND OBJECTS ===========================  #

SRCDIR  = src
OBJDIR  = obj
MAIN_SRC = $(SRCDIR)/main.c
MAIN_OBJ = $(OBJDIR)/main.o
SRCS = $(filter-out $(MAIN_SRC), $(wildcard $(SRCDIR)/*.c))
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# TODO: SET SOURCES MANUALLY BEFORE SUBMIT

#  ============================ LINK EXECUTABLE =============================  #

$(NAME): libft/libft.a $(OBJDIR) $(OBJS) $(MAIN_OBJ)
	@$(CC) $(OBJS) $(MAIN_OBJ) $(LDFLAGS) -o $@
	@printf "✨ $(BOLD)$(GREEN)%s$(NC)$(GREEN) has been successfully linked.\n$(NC)" $@

#  ============================== COMPILE LIBS ==============================  #

libft/libft.a: libft
libft:
	@$(MAKE) --silent -C libft $(filter $(MAKECMDGOALS),clean fclean re)

# TODO: if lib needed, add it to all, clean, fclean, and .PHONY's dependencies.

#  ============================ COMPILE OBJECTS =============================  #

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "$(YELLOW)Compiling: %s\n$(NC)" $<
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# ================================= CLEANING ================================= #

clean: libft
	@printf "$(MAGENTA)Cleaning objects.\n$(NC)"
	@rm -rf $(OBJDIR)

fclean: clean libft
	@printf "$(MAGENTA)Removing binary: $(BOLD)%s\n$(NC)" $(NAME)
	@rm -f $(NAME) $(NAME_TEST)

re: fclean all libft

fclean-nolibft:
	@printf "$(MAGENTA)Cleaning objects.\n$(NC)"
	@rm -rf $(OBJDIR)
	@printf "$(MAGENTA)Removing binary: $(BOLD)%s\n$(NC)" $(NAME)
	@rm -f $(NAME) $(NAME_TEST)

r: fclean-nolibft all

#  ================================= .PHONY =================================  #

.PHONY: all link clean fclean re libft test googletest

#  ================================= COLORS =================================  #

CYAN    = "\\e[36m"
GREEN   = "\\e[32m"
MAGENTA = "\\e[35m"
GRAY    = "\\e[37m"
YELLOW  = "\\e[33m"

BOLD    = "\\e[1m"
NC      = "\\e[0m"

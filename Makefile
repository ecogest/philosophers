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

#  ============================= COMPILE TESTS ==============================  #

NAME_TEST = UnitTests

GTEST_INCLUDE = googletest/googletest/include #/usr/local/opt/googletest/include
GTEST_LIB = googletest/build/lib #-L/usr/local/opt/googletest/lib

CXXFLAGS_TEST = -std=c++17 -I$(GTEST_INCLUDE)
LXXFLAGS_TEST = -std=c++17 -pthread -L$(GTEST_LIB) -lgtest -lgtest_main

SRCDIR_TEST = tests
OBJDIR_TEST = $(OBJDIR)/$(SRCDIR_TEST)
SRC_TEST    = $(wildcard $(SRCDIR_TEST)/*.cc)
OBJ_TEST    = $(patsubst $(SRCDIR_TEST)/%.cc, $(OBJDIR_TEST)/%.o, $(SRC_TEST))

compile-test: $(NAME) googletest $(NAME_TEST)

$(NAME_TEST): $(OBJDIR_TEST) $(OBJ_TEST)
	@$(CXX) $(OBJS) $(OBJ_TEST) $(LDFLAGS) $(LXXFLAGS_TEST) -o $(NAME_TEST)
	@printf "🧪 $(BOLD)$(CYAN)%s$(NC)$(CYAN) has been successfully linked.\n$(NC)" $@

$(OBJDIR_TEST):
	@mkdir -p $(OBJDIR_TEST)

$(OBJDIR_TEST)/%.o: $(SRCDIR_TEST)/%.cc
	@printf "$(GRAY)Compiling: %s\n$(NC)" $<
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS_TEST) -c $< -o $@

googletest: googletest/build
googletest/build:
	cmake -S googletest -B googletest/build
	cmake --build googletest/build
	#
#  =============================== RUN TESTS ================================  #

RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
RUN_ARGS := $(if $(RUN_ARGS),$(RUN_ARGS),*)
test: compile-test
	#./$(NAME_TEST) --gtest_color=yes --gtest_filter="$(RUN_ARGS)" # --gtest_brief=1 to run quietly

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

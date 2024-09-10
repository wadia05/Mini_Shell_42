# Colors
GREEN  := \033[0;32m
BLUE   := \033[0;34m
CYAN   := \033[0;36m
RESET  := \033[0m

# Name of the executable
NAME := minishell

# Path to libft directory
LIBFT_DIR := ./libft_42
LIBFT := $(LIBFT_DIR)/libft.a

# Source files
# Source files
FILS = \
    exec/child_status.c \
    exec/convert_2_arry.c \
    exec/execute_cmd.c \
    exec/execute_relative_or_bld_in.c \
    exec/execute_tools.c \
    exec/heredoc.c \
    exec/heredoc_tools_sig.c \
    exec/is_builtins.c \
    exec/pipe_setup.c \
    exec/pipe_setup_sig.c \
    exec/process_heredoc.c \
    exec/redirection.c \
    builtins/cd_commend.c \
    builtins/cd_commend_p2.c \
    builtins/echo_commend.c \
    builtins/env_commend.c \
    builtins/env_create.c \
    builtins/env_create_p2.c \
    builtins/exit.c \
    builtins/export_commend.c \
    builtins/export_tools.c \
    builtins/print_error.c \
    builtins/print_sort_env.c \
    builtins/pwd_commend.c \
    builtins/unset_commed.c \
    parsing/herdoc_parse.c \
    parsing/main.c \
    parsing/parsing.c \
    parsing/pipe_parse.c \
    parsing/redirection_parse.c \
    parsing/tokenized.c \
    parsing/utils.c \
    parsing/utils_complet_var.c \
    parsing/utils_main.c \
    parsing/utils_parsing.c \
    parsing/utils_var.c \
    parsing/utils_var_line.c \
    parsing/var_in_line.c \
    parsing/main_free.c \
# Compiler and flags
CC := cc
HEADER := minishell.h
RM := rm -f

# Automatically detect the readline prefix
READLINE_PREFIX := $(shell brew --prefix readline)
CFLAGS += -Wall -Wextra -Werror  
# Compiler flags
CFLAGS +=  -I$(READLINE_PREFIX)/include
READLINE =  -lreadline -lhistory -L$(READLINE_PREFIX)/lib

# Object files
OBJ := $(FILS:.c=.o)

# Progress variables
TOTAL_FILES := $(words $(FILS))
COMPILED_FILES := 0
BAR_LENGTH := 30

# Main target: Install dependencies and build the project
all: install_deps $(LIBFT) $(NAME)

# Rule to install dependencies
install_deps:
	@echo "$(CYAN)Installing dependencies...$(RESET)"
	@if [ "$$(uname)" = "Darwin" ]; then \
		echo "$(CYAN)Detected macOS, installing via Homebrew...$(RESET)"; \
		brew install readline; \
	elif [ -f /etc/debian_version ]; then \
		echo "$(CYAN)Detected Debian-based system, installing via apt-get...$(RESET)"; \
		sudo apt-get update && sudo apt-get install -y libreadline-dev; \
	elif [ -f /etc/redhat-release ]; then \
		echo "$(CYAN)Detected Red Hat-based system, installing via yum...$(RESET)"; \
		sudo yum install -y readline-devel; \
	else \
		echo "$(CYAN)Unsupported OS, please install readline manually.$(RESET)"; \
	fi

# Rule to make libft
$(LIBFT):
	@echo "$(CYAN)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null

# Rule to make minishell
$(NAME): $(OBJ) $(LIBFT)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(READLINE)
	@echo "$(GREEN)Build complete! 🚀$(RESET)"

# Compile objects
%.o: %.c $(HEADER)
	@$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES) + 1))))
	@printf "$(BLUE)Compiling [%-30s] %d/%d\r$(RESET)" "$$(printf '%0.s#' $$(seq 1 $$(($(COMPILED_FILES) * 30 / $(TOTAL_FILES)))))" $(COMPILED_FILES) $(TOTAL_FILES)
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean rules
clean:
	@echo "$(CYAN)Cleaning object files...$(RESET)"
	@$(RM) $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null

fclean: clean
	@echo "$(CYAN)Removing $(NAME)...$(RESET)"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null
	@echo "$(CYAN)Clean complete! 🧹$(RESET)"

re: fclean all

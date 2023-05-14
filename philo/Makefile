NAME = philo

SRCS =	$(wildcard ./srcs/*.c)

OBJS :=$(SRCS:.c=.o)

CFLAGS = -pthread -Wall -Wextra -Werror -g #-fsanitize=address

all: $(NAME)

$(NAME):  $(OBJS)
	@cc $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Successfully built --> $(YELLOW)$(NAME)$(DEFAULT)"

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	@echo "$(GREEN)Successfully cleaned --> $(YELLOW)$(NAME)$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re

#COLORS
GREEN = \033[1;32m
RED = \033[1;31m
DEFAULT = \033[0m
YELLOW = \033[1;33m

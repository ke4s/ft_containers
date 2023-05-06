NAME    = ft
NAME2	= std

NAME_TESTER = ft_containers-unit-test

CC      = c++

FLAGS   = -Wall -Werror -Wextra -std=c++98

SRCS    = intra_main_ft.cpp
SRCS2    = intra_main_std.cpp


all: $(NAME) $(NAME2)

$(NAME) : $(SRCS) $(SRCS2)
	$(CC) $(SRCS) $(FLAGS) -o  $(NAME)
	$(CC) $(SRCS2) $(FLAGS) -o $(NAME2)

clean:
	rm -rf $(NAME) $(NAME2)

fclean: clean
	@echo cleaning 100%

$(NAME_TESTER):
	git clone https://github.com/divinepet/ft_containers-unit-test

down_tester: $(NAME_TESTER)

del_tester:
	rm -rf $(NAME_TESTER)

re: clean $(NAME) $(NAME2)

.PHONY  : clean re
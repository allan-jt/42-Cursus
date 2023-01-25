CC		= c++

FLAGS	= -g -fsanitize=address -Wall -Wextra -Werror -std=c++98

FT		= -DFT

NAME_FT	= tester_ft

NAME_STD = tester_std

SOURCE	= main.cpp	vec_tester.cpp	stack_tester.cpp	map_tester.cpp	set_tester.cpp

$(NAME):
	$(CC) $(FLAGS) $(SOURCE) -o $(NAME_FT) $(FT)
	$(CC) $(FLAGS) $(SOURCE) -o $(NAME_STD)

all: $(NAME)

run:
	./$(NAME_FT) && ./$(NAME_STD)

check_vec:
	diff std_vec_test ft_vec_test

check_stack:
	diff std_stack_test ft_stack_test

check_set:
	diff std_set_test ft_set_test

check_map:
	diff std_map_test ft_map_test

check_all: check_vec check_stack check_map check_set

clean:
	rm -f $(NAME_FT) $(NAME_STD)

fclean: clean
	rm -f *_test

re: fclean all
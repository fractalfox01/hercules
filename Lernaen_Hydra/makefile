FLAGS= -Wall -Werror -Wextra

DEBUG= -g

SRC := $(addsuffix .c, server)

CLIENT := $(addsuffix .c, client)

all:
	gcc $(FLAGS) $(SRC) -o server
	gcc $(FLAGS) $(CLIENT) -o client

debug:
	gcc $(DEBUG) $(FLAGS) $(SRC) -o debugging

clean:
	@rm server || echo "\033[0;32mAlready removed.. server\n"
	@rm client|| echo "\033[0;32mAlready removed.. client\n"

fclean: clean

re: fclean all

NAME = libmachobj

STATIC = $(NAME).a
DYNAMIC = $(NAME).so

SRC = machobj.c machobj_open.c machobj_err.c machobj_parse.c \
	  machobj_header32.c machobj_header64.c
OBJ = $(SRC:.c=.o)
CC  = gcc
CFLAGS = -Wall -Werror -Wextra

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(STATIC): $(OBJ)
	ar -rc $(STATIC) $(OBJ)

all: $(STATIC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(STATIC)

re: fclean all

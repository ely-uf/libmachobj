NAME = libmachobj

STATIC = $(NAME).a
DYNAMIC = $(NAME).so

SRC = machobj.c machobj_open.c machobj_err.c machobj_parse.c \
	  machobj_header32.c machobj_header64.c machobj_load_commands.c \
	  machobj_lc_iter.c machobj_symtab.c machobj_symtab_strtable.c \
	  machobj_symbol.c machobj_section_get.c machobj_lc_spec_iter.c

OBJ = $(SRC:.c=.o)
CC	= gcc
CFLAGS = -Wall -Werror -Wextra
TARGET := $(STATIC)

ifdef DEBUG
	CFLAGS += -DDEBUG
endif

ifdef DYLIB
	CFLAGS += -fPIC
	TARGET = $(DYNAMIC)
endif

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(STATIC): $(OBJ)
	ar -rc $(STATIC) $(OBJ)

$(DYNAMIC): $(OBJ)
	$(CC) -shared $(OBJ) -o $(DYNAMIC)

compile: all

all: $(TARGET)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(STATIC)
	rm -f $(DYNAMIC)

re: fclean all

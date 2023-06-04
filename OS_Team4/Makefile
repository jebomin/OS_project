CC = gcc
RM = rm -rf
NAME = miniOS

C_DIR = cFile
OBJ_DIR = object
HEADER = Header

CFILES = directory.c instruction.c main.c cp.c \
		stack.c time.c user.c cat.c cd.c thread.c \
		chmod.c chown.c mkdir.c save.c find.c\
		rm.c pwd.c ls.c permission.c grep.c getInformation.c

OBJS = $(addprefix $(OBJ_DIR)/, $(CFILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -o $@ -I$(HEADER) -lpthread

$(OBJ_DIR)/%.o: $(C_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@ -I$(HEADER)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
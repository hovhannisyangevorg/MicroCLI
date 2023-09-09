NAME 			= 	minishell
SRC_DIR 		= 	src
OBJ_DIR			= 	obj
INC_DIR			=	include

LINKERS			= -L$(FT_LIB) -lft
FT_LIB			= libft
LIBS			= $(FT_LIB)/libft.a

CC				=	cc
INCS			=	-I$(INC_DIR) -I$(FT_LIB)/include
RM				=	rm -rf
MK				=	mkdir -p
CFLAGS			=	-Wall -Wextra -Werror $(SANIT_FLAG)
SANIT_FLAG		=	#-g3 #-fsanitize=address

SRCS			= 	$(wildcard $(SRC_DIR)/*.c)
OBJS			=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
HEADERS			=	$(wildcard $(INC_DIR)/*.h)
.DEFAULT_GOAL	=	all

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

all: $(LIBS) $(NAME) 

$(NAME):	$(OBJ_DIR) $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(INCS) -o $@ $(LINKERS)

$(LIBS):
	$(MAKE) -C $(FT_LIB)

$(OBJ_DIR):	$(SRC_DIR)
	$(MK) $(OBJ_DIR)

clean:
	$(RM) $(OBJ_DIR)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
.PHONY: all clean fclean re 
# .SILENT:
# Main Exercise Name
NAME 			= 	minishell


# Main Directories Name
SRC_DIR 		= 	Src
OBJ_DIR			= 	Obj
INC_DIR			=	Include
FT_LIB			=	libft


# Minishell Static Libraries File Name.
FT_ARX			=	libft.a


# Hierarchical Directories Path
EXEC_DIR		=	Executor
LEXR_DIR		=	Lexer
PARS_DIR		=	Parser
TOKS_DIR		=	Tokenizer


# Compiler and Linker Options Commands,
CC				=	cc
L_FLAG			=	-L
I_FLAG			=	-I
RM				=	rm -rf
MK				=	mkdir -p
HARD_FLAG		=	-Wall -Wextra -Werror
SANIT_FLAG		=	-g3 -fsanitize=address
READ_FLAG		=	-lreadline -lhistory

CFLAGS			=	$(HARD_FLAG) $(READ_FLAG) $(SANIT_FLAG)

# Common Targets Variables
ALL 		=	all
CLEAN 		=	clean
FCLEAN 		=	fclean
RE 			=	re


# File extension Variables
_C 				=	.c
_O 				=	.o
_H 				=	.h

#


# Hierarchical Directories Name
SRC_EXEC_DIR	=	$(SRC_DIR)/$(EXEC_DIR)
SRC_LEXR_DIR	=	$(SRC_DIR)/$(LEXR_DIR)
SRC_PARS_DIR	=	$(SRC_DIR)/$(PARS_DIR)
SRC_TOKS_DIR	=	$(SRC_DIR)/$(TOKS_DIR)


OBJ_EXEC_DIR	=	$(OBJ_DIR)/$(EXEC_DIR)
OBJ_LEXR_DIR	=	$(OBJ_DIR)/$(LEXR_DIR)
OBJ_PARS_DIR	=	$(OBJ_DIR)/$(PARS_DIR)
OBJ_TOKS_DIR	=	$(OBJ_DIR)/$(TOKS_DIR)


INC_EXEC_DIR	=	$(INC_DIR)/$(EXEC_DIR)
INC_LEXR_DIR	=	$(INC_DIR)/$(LEXR_DIR)
INC_PARS_DIR	=	$(INC_DIR)/$(PARS_DIR)
INC_TOKS_DIR	=	$(INC_DIR)/$(TOKS_DIR)


# List of all Source Files
SRCS_EXEC		=	$(wildcard $(SRC_EXEC_DIR)/*$(_C))
SRCS_LEXR		=	$(wildcard $(SRC_LEXR_DIR)/*$(_C))
SRCS_PARS		=	$(wildcard $(SRC_PARS_DIR)/*$(_C))
SRCS_TOKS		=	$(wildcard $(SRC_TOKS_DIR)/*$(_C))

# List of all Object Files
OBJS_EXEC		=	$(patsubst $(SRC_EXEC_DIR)/%$(_C), $(OBJ_EXEC_DIR)/%$(_O), $(SRCS_EXEC))
OBJS_LEXR		=	$(patsubst $(SRC_LEXR_DIR)/%$(_C), $(OBJ_LEXR_DIR)/%$(_O), $(SRCS_LEXR))
OBJS_PARS		=	$(patsubst $(SRC_PARS_DIR)/%$(_C), $(OBJ_PARS_DIR)/%$(_O), $(SRCS_PARS))
OBJS_TOKS		=	$(patsubst $(SRC_TOKS_DIR)/%$(_C), $(OBJ_TOKS_DIR)/%$(_O), $(SRCS_TOKS))
OBJS_ALL 		=	$(OBJS_EXEC) $(OBJS_LEXR) $(OBJS_PARS) $(OBJS_TOKS)

# List of all Header Files
INCS_EXEC		=	$(wildcard $(INC_EXEC_DIR)/*$(_H))
INCS_LEXR		=	$(wildcard $(INC_LEXR_DIR)/*$(_H))
INCS_PARS		=	$(wildcard $(INC_PARS_DIR)/*$(_H))
INCS_TOKS		=	$(wildcard $(INC_TOKS_DIR)/*$(_H))

# Path lists of objects, headers, and source files.
SRCS_ALL 		=	$(SRCS_EXEC) $(SRCS_LEXR) $(SRCS_PARS) $(SRCS_TOKS)
OBJS_ALL 		=	$(OBJS_EXEC) $(OBJS_LEXR) $(OBJS_PARS) $(OBJS_TOKS)
INCS_ALL 		=	$(INCS_EXEC) $(INCS_LEXR) $(INCS_PARS) $(INCS_TOKS)


.DEFAULT_GOAL	=	$(ALL)


$(ALL): $(FT_ARX) $(NAME)


$(FT_ARX):
	$(MAKE) -C $(FT_LIB) $(RE)


$(NAME): $(OBJ_DIR) $(OBJS_ALL)
	$(CC) $(CFLAGS) $(OBJS_ALL) $(INCS_ALL)


$(OBJ_DIR): $(SRC_DIR)
	$(MK) $(OBJ_DIR)


# test:
# 	@echo $(INCS_ALL) 









# test:
# 	@echo $(INC_EXEC_DIR) $(INC_LEXR_DIR) $(INC_PARS_DIR) $(INC_TOKS_DIR)


.PHONY: $(ALL) $(CLEAN) $(FCLEAN) $(RE)


































# TOKIZ_DIR		=	src

# LINKERS			= -L$(FT_LIB) -lft
# FT_LIB			= libft
# LIBS			= $(FT_LIB)/libft.a

# CC				=	cc
# INCS				=	-I$(INC_DIR) -I$(FT_LIB)/include
# RM				=	rm -rf
# MK				=	mkdir -p
# CFLAGS			=	-Wall -Wextra -Werror -lreadline -lhistory $(SANIT_FLAG)
# SANIT_FLAG		=	-g3 -fsanitize=address

# SRCS			= 	$(wildcard $(TOKIZ_DIR)/*.c)
# OBJS			=	$(patsubst $(TOKIZ_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
# HERS			=	$(wildcard $(INC_DIR)/*.h)



# .DEFAULT_GOAL	=	all

# $(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HEADERS)
# 	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# all: $(LIBS) $(NAME) 

# $(NAME):	$(OBJ_DIR) $(OBJS)
# 	$(CC) $(OBJS) $(CFLAGS) $(INCS) -o $@ $(LINKERS)

# $(LIBS):
# 	$(MAKE) -C $(FT_LIB)

# $(OBJ_DIR):	$(SRC_DIR)
# 	$(MK) $(OBJ_DIR)





# clean:
# 	$(RM) $(OBJ_DIR)

# fclean:	clean
# 	$(RM) $(NAME)

# re:	fclean all









# .SILENT:


# gcc -o myshell myshell.c -lreadline -lhistory
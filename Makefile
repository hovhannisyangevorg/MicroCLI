# Main Exercise Name
NAME 			= 	minishell

# Main Directories Name
SRC_DIR 		= 	Src
OBJ_DIR			= 	Obj
INC_DIR			=	Include
FT_LIB			=	Libft
INC_DIR_LIB		= 	include
READ_DIR 		=	readline
READ_UPDIR		=	readline_update
READ_ARX 		=	lib

OS				=	$(shell uname -s)
PREFIX			=	$(shell pwd)/$(READ_UPDIR)

# Minishell Static Libraries File Name.
FT_ARX			=	libft.a

# Hierarchical Directories Path
EXEC_DIR		=	Executor
LEXR_DIR		=	Lexer
PARS_DIR		=	Parser
TOKS_DIR		=	Tokenizer
SHELL_DIR 		=	Shell


# Hierarchical Directories Name
SRC_EXEC_DIR	=	$(SRC_DIR)/$(EXEC_DIR)
SRC_LEXR_DIR	=	$(SRC_DIR)/$(LEXR_DIR)
SRC_PARS_DIR	=	$(SRC_DIR)/$(PARS_DIR)
SRC_TOKS_DIR	=	$(SRC_DIR)/$(TOKS_DIR)
SRC_SHELL_DIR 	= 	$(SRC_DIR)/$(SHELL_DIR)
SRC_ALL_DIR		=	$(SRC_DIR) $(SRC_EXEC_DIR) $(SRC_LEXR_DIR) $(SRC_PARS_DIR) $(SRC_TOKS_DIR) $(SRC_SHELL_DIR)

OBJ_EXEC_DIR	=	$(OBJ_DIR)/$(EXEC_DIR)
OBJ_LEXR_DIR	=	$(OBJ_DIR)/$(LEXR_DIR)
OBJ_PARS_DIR	=	$(OBJ_DIR)/$(PARS_DIR)
OBJ_TOKS_DIR	=	$(OBJ_DIR)/$(TOKS_DIR)
OBJ_SHELL_DIR 	= 	$(OBJ_DIR)/$(SHELL_DIR)
OBJ_ALL_DIR		= 	$(OBJ_DIR) $(OBJ_EXEC_DIR) $(OBJ_LEXR_DIR) $(OBJ_PARS_DIR) $(OBJ_TOKS_DIR) $(OBJ_SHELL_DIR)

INC_EXEC_DIR	=	$(INC_DIR)/$(EXEC_DIR)
INC_LEXR_DIR	=	$(INC_DIR)/$(LEXR_DIR)
INC_PARS_DIR	=	$(INC_DIR)/$(PARS_DIR)
INC_TOKS_DIR	=	$(INC_DIR)/$(TOKS_DIR)
INC_SHELL_DIR 	= 	$(INC_DIR)/$(SHELL_DIR)
INC_ALL_DIR 	= 	$(INC_DIR) $(INC_EXEC_DIR) $(INC_LEXR_DIR) $(INC_PARS_DIR) $(INC_TOKS_DIR) $(INC_SHELL_DIR)


# # Single Flags
L_FLAG			=	-L
I_FLAG			=	-I
O_FLAG 			=	-o
C_FLAG 			=	-c

# # File extension Variables
_C 				=	.c
_O 				=	.o
_H 				=	.h

# Compiler and Linker Options Commands,
CC				=	cc
CD 				=	cd
RM				=	rm -rf
MK				=	mkdir -p
HARD_FLAG		=	-Wall -Wextra -Werror
SANIT_FLAG		=	-g3 -fsanitize=address
READ_FLAG		=	-lreadline -lhistory
CFLAGS			=	$(HARD_FLAG) $(SANIT_FLAG)

ifeq ($(OS),Darwin)
	LINKERS += $(L_FLAG)$(READ_UPDIR)/$(READ_ARX)
endif

LINKERS			+=	 $(READ_FLAG) $(L_FLAG)$(FT_LIB) -lft


# # Common Targets Variables
ALL 			=	all
CLEAN 			=	clean
FCLEAN 			=	fclean
RE 				=	re
RL 				=	readline



# List of all Source Files
SRCS_EXEC		=	$(wildcard	$(SRC_EXEC_DIR)/*$(_C))
SRCS_LEXR		=	$(wildcard	$(SRC_LEXR_DIR)/*$(_C))
SRCS_PARS		=	$(wildcard	$(SRC_PARS_DIR)/*$(_C))
SRCS_TOKS		=	$(wildcard	$(SRC_TOKS_DIR)/*$(_C))
SRCS_SHELL		=	$(wildcard	$(SRC_SHELL_DIR)/*$(_C))

# # List of all Object Files
OBJS_EXEC		=	$(patsubst 	$(SRC_EXEC_DIR)/%$(_C), 	$(OBJ_EXEC_DIR)/%$(_O),		$(SRCS_EXEC))
OBJS_LEXR		=	$(patsubst 	$(SRC_LEXR_DIR)/%$(_C), 	$(OBJ_LEXR_DIR)/%$(_O),		$(SRCS_LEXR))
OBJS_PARS		=	$(patsubst 	$(SRC_PARS_DIR)/%$(_C), 	$(OBJ_PARS_DIR)/%$(_O),		$(SRCS_PARS))
OBJS_TOKS		=	$(patsubst 	$(SRC_TOKS_DIR)/%$(_C), 	$(OBJ_TOKS_DIR)/%$(_O),		$(SRCS_TOKS))
OBJS_SHELL		=	$(patsubst 	$(SRC_SHELL_DIR)/%$(_C),	$(OBJ_SHELL_DIR)/%$(_O),	$(SRCS_SHELL))


# List of all Header Files
INCS_EXEC		=	$(wildcard 	$(INC_EXEC_DIR)/*$(_H))
INCS_LEXR		=	$(wildcard 	$(INC_LEXR_DIR)/*$(_H))
INCS_PARS		=	$(wildcard 	$(INC_PARS_DIR)/*$(_H))
INCS_TOKS		=	$(wildcard 	$(INC_TOKS_DIR)/*$(_H))
INCS_SHELL 		= 	$(wildcard 	$(INC_SHELL_DIR)/*$(_H))


# Path lists of objects, headers, and source files.
SRCS_ALL 		=	$(SRCS_EXEC) $(SRCS_LEXR) $(SRCS_PARS) $(SRCS_TOKS) $(SRCS_SHELL)
OBJS_ALL 		=	$(OBJS_EXEC) $(OBJS_LEXR) $(OBJS_PARS) $(OBJS_TOKS) $(OBJS_SHELL)
INCS_ALL 		=	$(INCS_EXEC) $(INCS_LEXR) $(INCS_PARS) $(INCS_TOKS) $(INCS_SHELL)


# # All include path
INCLUDES			=	$(I_FLAG)$(INC_DIR) $(I_FLAG)$(FT_LIB)/$(INC_DIR_LIB) $(I_FLAG)$(INC_EXEC_DIR) $(I_FLAG)$(INC_LEXR_DIR) $(I_FLAG)$(INC_PARS_DIR) $(I_FLAG)$(INC_TOKS_DIR) $(I_FLAG)$(INC_SHELL_DIR) $(I_FLAG)$(READ_UPDIR)/$(INC_DIR_LIB)


.DEFAULT_GOAL	=	$(ALL)


define generate_rule_hier
$(info Generated object dir for $(2) module)
$(1): $(2)
	@$$(MK) $$@
endef

define generate_obj_rule_hier
$(info Generated objects for $(2) module)
$(1)/%$(_O): $(2)/%$(_C) $(3)
	@$$(CC) $$(CFLAGS) $$(INCLUDES) $$(C_FLAG) $$< $$(O_FLAG) $$@ 
endef

$(eval $(call generate_rule_hier, $(OBJ_DIR), $(SRC_DIR)))
$(eval $(call generate_rule_hier, $(OBJ_EXEC_DIR), $(SRC_EXEC_DIR)))
$(eval $(call generate_rule_hier, $(OBJ_LEXR_DIR), $(SRC_LEXR_DIR)))
$(eval $(call generate_rule_hier, $(OBJ_PARS_DIR), $(SRC_PARS_DIR)))
$(eval $(call generate_rule_hier, $(OBJ_TOKS_DIR), $(SRC_TOKS_DIR)))
$(eval $(call generate_rule_hier, $(OBJ_SHELL_DIR), $(SRC_SHELL_DIR)))


$(eval $(call generate_obj_rule_hier, $(OBJ_DIR), $(SRC_DIR), $(INCS_ALL)))
$(eval $(call generate_obj_rule_hier, $(OBJ_EXEC_DIR), $(SRC_EXEC_DIR), $(INCS_ALL)))
$(eval $(call generate_obj_rule_hier, $(OBJ_LEXR_DIR), $(SRC_LEXR_DIR), $(INCS_ALL)))
$(eval $(call generate_obj_rule_hier, $(OBJ_PARS_DIR), $(SRC_PARS_DIR), $(INCS_ALL)))
$(eval $(call generate_obj_rule_hier, $(OBJ_TOKS_DIR), $(SRC_TOKS_DIR), $(INCS_ALL)))
$(eval $(call generate_obj_rule_hier, $(OBJ_SHELL_DIR), $(SRC_SHELL_DIR), $(INCS_ALL)))


$(ALL): $(FT_LIB)/$(FT_ARX) $(NAME) 


$(NAME): $(OBJ_DIR) $(OBJ_ALL_DIR) $(OBJS_ALL)
	@$(CC) $(INCLUDES) $(CFLAGS) $(O_FLAG) $@ $(OBJS_ALL) $(LINKERS)


$(FT_LIB)/$(FT_ARX):
	@$(MAKE) -C $(FT_LIB)


$(CLEAN):
	@$(MAKE) -C $(FT_LIB) $(CLEAN)
	@$(RM) $(OBJ_DIR)


$(FCLEAN): $(CLEAN)
	@$(MAKE) -C $(FT_LIB) $(FCLEAN)
	@$(RM) $(NAME)

$(RL):
	$(info Compiling readline library)
	@$(CD) $(READ_DIR) && ./configure --prefix=$(PREFIX) && $(MAKE) -s && $(MAKE) -s install

$(RE): $(FCLEAN) $(ALL)
	@$(MAKE) -C $(FT_LIB) $(RE)

.PHONY: $(ALL) $(CLEAN) $(FCLEAN) $(RE) $(RL)
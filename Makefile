# Contains a header file for the makefile.
include MakeFile.mk

.DEFAULT_GOAL	:=	$(ALL)

define generate_rule_hier
$(info ✅ Generated object dir for  $(2) module)
$(1): $(2)
	@$$(MK) $$@
endef

define generate_obj_rule_hier
$(info ✅ Generated objects for $(2) module)
$(1)/%$(_O): $(2)/%$(_C) $(3)
	$$(CC) $$(CFLAGS) $$(INCLUDES) $$(C_FLAG) $$< $$(O_FLAG) $$@ 
endef

$(eval $(call generate_rule_hier, $(OBJ_DIR),$(SRC_DIR)))
$(eval $(call generate_rule_hier, $(OBJ_EXEC_DIR),$(SRC_EXEC_DIR)))
$(eval $(call generate_rule_hier, $(OBJ_LEXR_DIR),$(SRC_LEXR_DIR)))
$(eval $(call generate_rule_hier, $(OBJ_PARS_DIR),$(SRC_PARS_DIR)))
$(eval $(call generate_rule_hier, $(OBJ_TOKS_DIR),$(SRC_TOKS_DIR)))
$(eval $(call generate_rule_hier, $(OBJ_SHELL_DIR),$(SRC_SHELL_DIR)))
$(eval $(call generate_rule_hier, $(OBJ_BILTIN_DIR),$(SRC_BILTIN_DIR)))
$(eval $(call generate_rule_hier, $(OBJ_SEMATIC_DIR),$(SRC_SEMATIC_DIR)))

$(eval $(call generate_obj_rule_hier, $(OBJ_DIR),$(SRC_DIR),$(INCS_ALL)))
$(eval $(call generate_obj_rule_hier, $(OBJ_EXEC_DIR),$(SRC_EXEC_DIR),$(INCS_ALL)))
$(eval $(call generate_obj_rule_hier, $(OBJ_LEXR_DIR),$(SRC_LEXR_DIR),$(INCS_ALL)))
$(eval $(call generate_obj_rule_hier, $(OBJ_PARS_DIR),$(SRC_PARS_DIR),$(INCS_ALL)))
$(eval $(call generate_obj_rule_hier, $(OBJ_TOKS_DIR),$(SRC_TOKS_DIR),$(INCS_ALL)))
$(eval $(call generate_obj_rule_hier, $(OBJ_SHELL_DIR),$(SRC_SHELL_DIR),$(INCS_ALL)))
$(eval $(call generate_obj_rule_hier, $(OBJ_BILTIN_DIR),$(SRC_BILTIN_DIR),$(INCS_ALL)))
$(eval $(call generate_obj_rule_hier, $(OBJ_SEMATIC_DIR),$(SRC_SEMATIC_DIR),$(INCS_ALL)))
 

$(ALL): $(FT_LIB)/$(FT_ARX) $(NAME) 


$(NAME): $(OBJ_DIR) $(OBJ_ALL_DIR) $(OBJS_ALL)
	@$(CC) $(INCLUDES) $(CFLAGS) $(O_FLAG) $@ $(OBJS_ALL) $(LINKERS)


$(FT_LIB)/$(FT_ARX):
	@$(MAKE) -s -C $(FT_LIB)


$(CLEAN):
	@$(MAKE) -s -C $(FT_LIB) $(CLEAN)
	@$(RM) $(OBJ_DIR)


$(FCLEAN): $(CLEAN)
	@$(MAKE) -s -C $(FT_LIB) $(FCLEAN)
	@$(RM) $(NAME)

$(RL):
	$(info Compiling readline library)
	@$(CD) $(READ_DIR) && ./configure --prefix=$(PREFIX) && $(MAKE) -s && $(MAKE) -s install

$(RE): $(FCLEAN) $(ALL)
	@$(MAKE) -s -C $(FT_LIB) $(RE)

.PHONY: $(ALL) $(CLEAN) $(FCLEAN) $(RE) $(RL)

.SILENT:

#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <stddef.h>
# include <fcntl.h>
# include <errno.h>

#ifndef  READLINE_LIBRARY
#define READLINE_LIBRARY 1
#endif

#include "readline/readline.h"
#include "readline/history.h"


# include 	"global_struct.h"
# include 	"libft.h"
# include 	"executor.h"
# include 	"lexer.h"
# include 	"parser.h"
# include 	"sematic.h"
# include 	"tokenizer.h"
# include	"builtins.h"


void lock_file(int fd, short type);
void unlock_file(int fd);

#endif

#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
// #include "rlstdc.h"
// # include <readline.h>
// # include "history.h"
#ifndef  READLINE_LIBRARY
#define READLINE_LIBRARY 1
#endif

#include "readline/readline.h"
#include "readline/history.h"
// #include "readline/rlstdc.h"


# include "libft.h"
# include "executor.h"
# include "prser.h"
# include "tokenizer.h"

#endif
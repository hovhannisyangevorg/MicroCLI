#include "shell.h"

int ft_test(t_command *command, t_symbol_table *table)
{
	(void)command;
	(void)table;
	char* line;
	char* buff = NULL;
	// printf("aaaa\n");
	while (1)
	{
		// printf("bb>\n");
		line = readline("");
		if (!line || !*line)
			break;
		buff = ft_gnl_strjoin(buff, line);
		// printf("%s\n", line);
		free(line);
	}
	printf("%s\n", buff);
	return 0;
}
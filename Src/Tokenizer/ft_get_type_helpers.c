#include "shell.h"

int	ft_is_redirect_type_map(int type)
{
	return (type == MREAD || type == MWRITE || \
			type == MAPPEND || type == MHEREDOC);
}

int	ft_is_operator_type_map(int type)
{
	return (type == MOR || type == MAND || type == MJOB || \
		type == MSEMI || type == MSEMITWO || type == MPIPE);
}

int	ft_is_command_type_map(int type)
{
	return (type == MOPBREK || type == MCLBREK || \
								type == MTEXT);
}

int	ft_is_redirect_type(t_token_type type)
{
	return (type == READ || type == WRITE || \
			type == APPEND || type == HEREDOC);
}

int	ft_is_operator_type(t_token_type type)
{
	return (type == OR || type == AND || type == JOB || \
		type == SEMI || type == SEMITWO || type == PIPE);
}

#include "../includes/21sh.h"

static int	open_file(char *r_value)
{
	int fd;

	if (access(r_value, F_OK))
		fd = creat(r_value, 0644);
	else if (access(r_value, W_OK))
	{
		perror("access W_OK error: ");
		return (-1);
	}
	else
		fd = open(r_value, 0644);
	if (fd < 0)
	{
		ft_putendl("error: negative fd.\n");
		return (fd);
	}
	return (fd);
}

static int	get_input_fd(char *l_value)
{
	if (!ft_strlen(l_value))
		return (1);
	else if (ft_isdigit(*l_value))
		return (ft_atoi(l_value));
	else
		return (-1);
}

static int	get_output_fd(char *r_value)
{
	if (ft_strlen(r_value) == 0)
	{
		ft_putendl("error: r_value is empty.");
		return (-1);
	}
	else if (r_value[0] == '&' && ft_isdigit(r_value[1]) && r_value[2] == '\0')
		return (r_value[1]);
	return (open_file(r_value));
}

int	apply_output_redir(char *operand, char *l_value, char *r_value)
{
	int output_fd;
	//int input_fd;

	output_fd = get_output_fd(r_value);
	//input_fd = get_input_fd(l_value);
	if (output_fd < 0)
	{
		ft_putendl("output_fd error!");
		return (0);
	}
	if (output_fd > 0)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
		return (0);
	}
	else
	{
		ft_putendl("output_fd is 0");
		return (0);
	}
	return (1);
}

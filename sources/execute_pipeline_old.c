eortrehgdhigurehgrohrhgpgdsùhpges<fOAàue
rz#include <fcntl.h>
#include <sys/wait.h>
#include "../includes/21sh.h"


static int err_handler(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}

static void execute(char **cmd_list)
{
	execvp(cmd_list[0], cmd_list);
	perror("exec error: ");
	exit(EXIT_FAILURE);
}
static void	execute_last(t_pnode *cmd)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
		err_handler("fork error");
	if (!pid)
	{
		execute(cmd->cmds);
		perror("exec error: ");
		exit(EXIT_FAILURE);
	}
	if (pid > 0)
		wait(&pid);
}
void execute_pipeline(t_pnode *cmd_list)
{
	pid_t	pid;
	t_pnode *curr;

	if (!cmd_list)
		return ;
	curr = cmd_list;
	while (curr->next) {
		int p[2];

		if (pipe(p) < 0)
			err_handler("pipe error: ");
		pid = fork();
		if (pid < 0) 
			err_handler("fork error: ");
		//child
		else if (pid == 0)
		{
			close(p[0]);
			dup2(p[1], 1);
			close(p[1]);
			execute(curr->cmds);
			perror("exec error: ");
			exit(EXIT_FAILURE);
		} 
		//parent
		else if (pid > 0)
		{
			close(p[1]);
			dup2(p[0], 0);
			close(p[0]);
			wait(&pid);
		}
		curr = curr->next;
	}
	execute_last(curr);
}

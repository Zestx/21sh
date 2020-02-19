#include <fcntl.h>
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

//loop through each node of the pipeline, pipe/dup the commands and execute them
//one after the other.
static void execute_pipeline(t_pnode *cmd_list)
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
			//close the read-end of the pipe, since it reads from stdin.
			close(p[0]);
			//duplicate stdout into the pipe and close it.
			dup2(p[1], 1);
			close(p[1]);
			//execute.
			execute(curr->cmds);
			perror("exec error: ");
			exit(EXIT_FAILURE);
		} 
		//parent
		else if (pid > 0)
		{
			//close the write-end of the pipe and duplicate stdin to the pipe.
			close(p[1]);
			dup2(p[0], 0);
			close(p[0]);
			wait(&pid);
		}
		curr = curr->next;
	}
	execute(curr->cmds);
}

//fork and execute the command if there's only one. If there's a real pipeline, 
//call execute_pipeline which will loop and fork for each command.
void execute_main(t_pnode *cmd_list)
{
	pid_t	pid;

	if (!cmd_list)
		return ;
	pid = fork();
	if (pid < 0)
		err_handler("fork error: ");
	else if (pid == 0)	//child
	{
		if (cmd_list->next == NULL)
		{
			execute(cmd_list->cmds);
			perror("exec error: ");
			exit(EXIT_FAILURE);
		}
		else
			execute_pipeline(cmd_list);
	}
	else if (pid > 0)	//parent
		wait(&pid);
}

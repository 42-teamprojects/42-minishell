#include "exec.h"

void	free_exec(t_shell *shell)
{
	free(shell->path);
	shell->path = NULL;
	free_split(shell->cmd.full_cmd);
	shell->cmd.full_cmd = NULL;
}
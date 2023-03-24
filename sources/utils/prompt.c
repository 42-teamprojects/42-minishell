#include "../../includes/utils.h"

char	*init_prompt(void)
{
	char	*user;
	char	cwd[1024];
	char	*line;
	char	*str;

	user = ft_strjoin(CYAN, getenv("USER"));
	getcwd(cwd, 1024);
	str = ft_strrchr(cwd, '/') + 1;
	if (str == NULL)
		exit (1);
	line = ft_strjoin_gnl(user, " " BRED);
	line = ft_strjoin_gnl(line, str);
	line = ft_strjoin_gnl(line, YELLOW " $ " CX);
	return (line);
}
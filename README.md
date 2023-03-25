# Minishell

## Snippets

```
	printf("%s \n", shell->cmd.name);
	for(int i=0; shell->cmd.args[i]; i++)
		printf("%s \n", shell->cmd.args[i]);
```
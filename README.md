# Minishell

## Snippets

```
	printf("%s %zu\n", shell->cmd.name, input_size);
	for(int i=0; shell->cmd.args[i]; i++)
		printf("%s %zu\n", shell->cmd.args[i], input_size);
```
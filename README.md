# Minishell

## Snippets

``` c
printf("%s \n", (*shell)->cmds[0]->name);
for(int i=0; (*shell)->cmds[0]->args[i]; i++)
	printf("%s \n", (*shell)->cmds[0]->args[i]);

print_lexer((*shell)->lexer);
```

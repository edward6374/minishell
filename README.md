# minishell

## Errores

Para el parsing

echo $NONEXIST  ""

echoecho
bash: echoecho: command not found

tiene que retornor 127


l====================
exit ""


SHLVL=1000
SHLVL=-20

shell-init: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
bash: warning: shell level (1001) too high, resetting to 1\


	int i;	// variable used to loop through str
	int sq; // single_quotes -> variable used to check if you are in a single quote
	int dq; // double_quotes -> variable used to check if you are in a double quote
	int oq; // out_quotes -> variable used to check if you are in any quotes
	// int nq;	   // number_quotes -> variable that is the number of quotes in a word
	int stp; // starting_point -> variable that is the starting point of a word
	// int count; // variable to used to checkk if a env variable is after another one
	char *s; // string -> variable that represent the string came fom readline
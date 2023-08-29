# minishell

## Errores

Para el parsing

echo $NONEXIST  ""

tiene que retornor 127

# bash: : command not found
# Tiene que ser NULL
""

# Esta es una cosa posible
export A+=uno

tk struct -> poner pwd y oldpwd

# Pipe abierto
cat | cat | cat | cat | ls

# Redireccion con un solo comando que es built-in
echo hola > out

====================
exit ""


SHLVL=1000
SHLVL=-20

shell-init: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
bash: warning: shell level (1001) too high, resetting to 1\


	int i;	// variable used to loop through str
	int sq; // single_quotes -> variable used to check if you are in a single quote
	int dq; // double_quotes -> variable used to check if you are in a double quote
	int oq; // out_quotes -> variable used to check if you are in any quotes
	int stp; // starting_point -> variable that is the starting point of a word
	char *s; // string -> variable that represent the string came fom readline
#include "shell.h"

char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
/**
 * error_env - function that creates an error message for shellby_env errors
 * @args: An array of arguments passed to the command
 *
 * Return: return the error string
 */
char *error_env(char **args)
{
	char *error, *str_hist;
	int len;

	str_hist = _itoa(hist);
	if (!str_hist)
		return (NULL);

	args--;
	len = _strlen(name) + _strlen(str_hist) + _strlen(args[0]) + 45;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(str_hist);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, str_hist);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Unable to add/remove from environment\n");

	free(str_hist);
	return (error);
}

/**
 * error_1 - this func creates an error message for shellby_alias errors
 * @args: An array of args passed to the command
 *
 * Return: This returns the error string
 */
char *error_1(char **args)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");

	return (error);
}

/**
 * error_2_exit - the function that creates an error message for
 * shellby_exit errors
 * @args: An array of arguments passed to the command
 *
 * Return: returns the error string
 */
char *error_2_exit(char **args)
{
	char *error, *str_hist;
	int len;

	str_hist = _itoa(hist);
	if (!str_hist)
		return (NULL);

	len = _strlen(name) + _strlen(str_hist) + _strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(str_hist);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, str_hist);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(str_hist);
	return (error);
}

/**
 * error_2_cd - Function that creates an error message for shellby_cd errors
 * @args: An array of arguments passed to the command
 *
 * Return: retun the error string
 */
char *error_2_cd(char **args)
{
	char *error, *str_hist;
	int len;

	str_hist = _itoa(hist);
	if (!str_hist)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	len = _strlen(name) + _strlen(str_hist) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(str_hist);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, str_hist);
	if (args[0][0] == '-')
		_strcat(error, ": cd: Illegal option ");
	else
		_strcat(error, ": cd: can't cd to ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(str_hist);
	return (error);
}

/**
 * error_2_syntax - this function creates an error message for syntax errors
 * @args: An array of arguments passed to the command
 *
 * Return: The error string
 */
char *error_2_syntax(char **args)
{
	char *error, *str_hist;
	int len;

	str_hist = _itoa(hist);
	if (!str_hist)
		return (NULL);

	len = _strlen(name) + _strlen(str_hist) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(str_hist);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, str_hist);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, args[0]);
	_strcat(error, "\" unexpected\n");

	free(str_hist);
	return (error);
}

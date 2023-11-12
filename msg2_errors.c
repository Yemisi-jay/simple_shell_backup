#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);

/**
 * error_126 - function that creates an error message for permission
 * denied failures
 * @args: the array of arguments passed to the command
 *
 * Return: returns the error string
 */
char *error_126(char **args)
{
	char *error, *str_hist;
	int len;

	str_hist = _itoa(hist);
	if (!str_hist)
		return (NULL);

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
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(str_hist);
	return (error);
}

/**
 * error_127 - this function creates an error message for command not
 * found failures
 * @args: this ia an array of arguments passed to the command
 *
 * Return: return the error string
 */
char *error_127(char **args)
{
	char *error, *str_hist;
	int len;

	str_hist = _itoa(hist);
	if (!str_hist)
		return (NULL);

	len = _strlen(name) + _strlen(str_hist) + _strlen(args[0]) + 16;
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
	_strcat(error, ": not found\n");

	free(str_hist);
	return (error);
}

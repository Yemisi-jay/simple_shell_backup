#include "shell.h"

int cant_open(char *file_path);
int proc_file_commands(char *file_path, int *exe_ret);

/**
 * cant_open - this function prints a cant open error, If the file
 *	doesn't exist or lacks proper permissions
 * @file_path: the path to the supposed file
 *
 * Return: 127
 */

int cant_open(char *file_path)
{
	char *error, *str_hist;
	int len;

	str_hist = _itoa(hist);
	if (!str_hist)
		return (127);

	len = _strlen(name) + _strlen(str_hist) + _strlen(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(str_hist);
		return (127);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, str_hist);
	_strcat(error, ": Can't open ");
	_strcat(error, file_path);
	_strcat(error, "\n");

	free(str_hist);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * proc_file_commands - function that takes a file and attempts to run
 * the commands stored within
 * @file_path: Path to the file
 * @exe_ret: Return value of the last executed command
 *
 * Return: If file couldn't be opened - 127
 *	   If malloc fails - -1
 *	   Otherwise the return value of the last command ran
 */
int proc_file_commands(char *file_path, int *exe_ret)
{
	ssize_t file, b_read, i;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exe_ret);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = _realloc(line, old_size, line_size);
		_strcat(line, buffer);
		old_size = line_size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	variable_replacement(&line, exe_ret);
	handle_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (args_checker(args) != 0)
	{
		*exe_ret = 2;
		args_free(args, args);
		return (*exe_ret);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = args_calls(args, front, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}

	ret = args_calls(args, front, exe_ret);

	free(front);
	return (ret);
}

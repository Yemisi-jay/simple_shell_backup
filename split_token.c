#include "shell.h"

int len_token(char *str, char *delim_char);
int tokens_count(char *str, char *delim_char);
char **_strtok(char *line, char *delim_char);

/**
 * len_token - function that locates the delimiter index marking the end
 *             of the first token contained within a string
 * @str: The string to be search for
 * @delim_char: The delimiter character
 *
 * Return: The delimiter index marking the end of
 *         the intitial token pointed to be str
 */
int len_token(char *str, char *delim_char)
{
	int index = 0, len = 0;

	while (*(str + index) && *(str + index) != *delim_char)
	{
		len++;
		index++;
	}

	return (len);
}

/**
 * tokens_count - this func counts the number of delimited
 *                words contained within a string
 * @str: The string to be searched for in the lines
 * @delim_char: The delimiter character
 *
 * Return: The number of words contained within string
 */
int tokens_count(char *str, char *delim_char)
{
	int index, tokens = 0, len = 0;

	for (index = 0; *(str + index); index++)
		len++;

	for (index = 0; index < len; index++)
	{
		if (*(str + index) != *delim_char)
		{
			tokens++;
			index += len_token(str + index, delim_char);
		}
	}

	return (tokens);
}

/**
 * _strtok - this tokenizes a string
 * @line: The string
 * @delim_char: The delimiter character to tokenize the string by
 *
 * Return: this is a pointer to an array containing the tokenized words
 */
char **_strtok(char *line, char *delim_char)
{
	char **ptr;
	int index = 0, tokens, t, letters, l;

	tokens = tokens_count(line, delim_char);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[index] == *delim_char)
			index++;

		letters = len_token(line + index, delim_char);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[index];
			index++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}

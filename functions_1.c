#include "main.h"

/**
 * _strcpy - copies source to dest
 * source: the source string
 * dest: the destination string
 *
 * Return: pointer to the dest string
 */
char *_strcpy(char *dest, char *src)
{
	int i, count = 0;

	while (src[count] != '\0')
		count++;
	for (i = 0; i < count; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcmp - compares two strings
 * s1: the first string
 * s2: the second string
 *
 * Return: 0 if they match, -1 otherwise
 */
int _strcmp(char *s1, char *s2)
{
	int count1 = 0, areequal = 0;

	while (s1[count1] != '\0' && s2[count1] != '\0')
	{
		if (s1[count1] != s2[count1])
		{
			areequal = s1[count1] - s2[count1];
			break;
		}
		count1++;
	}
	return (areequal);
}

/**
 * _getenv - fetches the value of a certain environment variable
 * env_var: name of the environment variable
 *
 * Return: pointer to the value in the environment or NULL if not found
 */
int _getenv(char *envp[])
{
	int i = 0;
	char **s = environ;
	char *var;
	(void)envp;

	for (; *s; s++)
	{
		var = strtok(*s, "=");
		if (strcmp(var, "PATH") == 0)
		{
			var = strtok(NULL, "=");
			break;
		}
		var = strtok(NULL, "=");
		i++;
	}
	printf("%s\n", environ[i]);
	return 0;
}

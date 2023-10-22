#include "main.h"

/**
 * prompt - prints the prompt and updates the line and status in data
 * @data: the data struct
 *
 * Returns: nothing
 */
void prompt(data_t *data)
{
	size_t size = 0;
	char *buf = NULL;

	printf("$ ");
	data->chars_read = getline(&buf, &size, stdin);
	if (data->chars_read == -1)
	{
		printf("\n");
		exit(data->status);
	}

	data->line = buf;
}

/**
 * parse - tokenizes the line
 * @data: the data struct
 *
 * Return: nothing
 */
void parse(data_t *data)
{
	char *token;
	int token_count = 0;
	int i;
	char *line_copy;

	/* first we need a copy of the line for strtok*/
	line_copy = malloc(sizeof(char)*(data->chars_read));
	if (line_copy == NULL)
	{
		exit(EXIT_FAILURE); /*TODO: find an appropriate error message?*/
	}
	strcpy(line_copy, data->line);

	/* loop to count the number of tokens/ words in the line*/
	token = strtok(line_copy, " \n");
	while (token != NULL)
	{
		token_count++;
		token = strtok(NULL, " \n");
	}
	token_count++;
	
	/* setting the argument vector to hold the tokens*/
	data->argv = malloc(sizeof(char*) * token_count);

	token = strtok(data->line, " \n");
	for (i = 0; token != NULL; i++)
	{
		data->argv[i] = malloc(sizeof(char*) * strlen(token));
		_strcpy(data->argv[i], token);
		token = strtok(NULL, " \n");
	}
	data->argv[i] = NULL;

	/* free everything */
	free(line_copy);

}

/**
 * execute - executes the command
 * @data: the data struct
 *
 * Return: nothing
 */
void execute(data_t *data)
{
	char *command, actual_command;

	if (data->argv)
	{
		command = data->argv[0];
		actual_command = locate(command);
		if (execve(command, data->argv, NULL) == -1)
			perror("Error");
	}

}

/**
 * locate - finds the command in the path
 * @command: the command
 *
 * Return:a pointer to the value in the environment/NULL if not found
 */
char *locate(char *command)
{
	char *path, *path_copy, path_token, *file_path;
	int command_length, directory_length;
	struct stat buffer;

	path = getenv("PATH");/*TODO: replace this with _getenv*/
	if (path)
	{
		path_copy = strdup(path); /*TODO: replace this with _strdup*/
		command_length = strlen(command); /*TODO: you guessed it! replace*/
		path_token = strtok(path_copy, ":");

		        while(path_token != NULL){
				            /* Get the length of the directory*/
				            directory_length = strlen(path_token);
					                /* allocate memory for storing the command name together with the directory name */
					                file_path = malloc(command_length + directory_length + 2); /* NB: we added 2 for the slash and null character we will introduce in the full command */
							            /* to build the path for the command, let's copy the directory path and concatenate the command to it */
							            strcpy(file_path, path_token);
								                strcat(file_path, "/");
										            strcat(file_path, command);
											                strcat(file_path, "\0");

													            /* let's test if this file path actually exists and return it if it does, otherwise try the next directory */
													            if (stat(file_path, &buffer) == 0){
															                    /* return value of 0 means success implying that the file_path is valid*/

															                    /* free up allocated memory before returning your file_path */
															                    free(path_copy);

																	                    return (file_path);
																			                }
														                else{
																	                /* free up the file_path memory so we can check for another path*/
																	                free(file_path);
																			                path_token = strtok(NULL, ":");

																					            }

																        }

			        /* if we don't get any file_path that exists for the command, we return NULL but we need to free up memory for path_copy */ 
			        free(path_copy);

				        /* before we exit without luck, let's see if the command itself is a file_path that exists */
				        if (stat(command, &buffer) == 0)
						        {
								            return (command);
									            }


					        return (NULL);

						    }


	    return (NULL);

}

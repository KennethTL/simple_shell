#include "main.h"

/**
 * get_env - grabing the location path of files
 * @cmd: command to be evaluated
 * Return: returns args
 */

char *get_env(char *cmd)
{
	char *location, *location_copy, *location_token, *file_path;
	int length_cmd, length_dir;
	struct stat buffer;
	/* we grab the path here using the getenv() */
	location = getenv("PATH");
	if (location)
	{
		/* remember "strdup" is used here to copy the new location path*/
		location_copy = strdup(location);
		/* getting the length of user cmd that was passed */
		length_cmd = strlen(cmd);
		/* breaking down the location variable to get all the directories */
		location_token = strtok(location_copy, ":");
		while (location_token != NULL)
		{
			length_dir = strlen(location_token);
			file_path = malloc(length_cmd + length_dir + 2);
			/* building the location path below */
			strcpy(file_path, location_token);
			strcat(file_path, "/");
			strcat(file_path, cmd);
			strcat(file_path, "\0");
			/* testing to know if the file path exists */
			if (stat(file_path, &buffer) == 0)
			{
				free(location_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				location_token = strtok(NULL, ":");
			}
		}
		free(location_copy);
		if (stat(cmd, &buffer) == 0)
		{
			return (cmd);
		}
		return (NULL);
	}
	return (NULL);
}

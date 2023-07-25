#include "main.h"

/**
 * get_env: Grab the location path of files
 * @cmd: Command for which to find the location path
 *
 * Return: Returns the location path of the command if found, NULL otherwise
 */
char *get_env(char *cmd)
{
    char *location, *location_copy, *file_path;
    int length_cmd, length_dir;
    struct stat buffer;
    char *start, *end;
    /* We grab the path here using the getenv() */
    location = getenv("PATH");
    if (location)
    {
        /* Remember "strdup" is used here to copy the new location path */
        location_copy = strdup(location);
        /* Getting the length of the user command that was passed */
        length_cmd = strlen(cmd);
        start = location_copy;
        while (*start != '\0')
        {
            /* Find the end of the directory path */
            end = start;
            while (*end != '\0' && *end != ':')
                end++;
            /* Calculate the length of the directory path */
            length_dir = end - start;
            /* Allocate space for the file path */
            file_path = malloc(length_dir + length_cmd + 2); /* +2 for the '/' and null terminator */
            if (file_path == NULL)
            {
                perror("sh: memory allocation error");
                free(location_copy);
                return NULL;
            }
            /* Copy the directory path */
            strncpy(file_path, start, length_dir);
            file_path[length_dir] = '/';
            /* Copy the command name */
            strcpy(file_path + length_dir + 1, cmd);
            /* Null-terminate the file path */
            file_path[length_dir + length_cmd + 1] = '\0';
            /* Testing to know if the file path exists */
            if (stat(file_path, &buffer) == 0)
            {
                free(location_copy);
                return file_path;
            }
            else
            {
                free(file_path);
                if (*end == '\0')
                    break;
                start = end + 1;
            }
        }
        free(location_copy);
        /* Check if the command is an absolute path */
        if (stat(cmd, &buffer) == 0)
        {
            return strdup(cmd);
        }
        return NULL;
    }
    return NULL;
}

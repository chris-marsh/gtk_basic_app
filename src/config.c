/******************************************************************************
 *                                                                            *
 *                   Copyright (C) 2016 Chris Marsh                           *
 *                                                                            *
 * This program is free software: you can redistribute it and/or modify it    *
 * under the terms of the GNU General Public License as published by the      *
 * Free Software Foundation, either version 3 of the License, or any later    *
 * version.                                                                   *
 *                                                                            *
 * This program is distributed in the hope that it will be useful, but        *
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY *
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License   *
 * at <http://www.gnu.org/licenses/> for more details.                        *
 *                                                                            *
 ******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "config.h"
#include "common.h"

#define APP_NAME "basic"
#define CONFIG_NAME APP_NAME "rc"

int push_option(Config **head, char *key, char *value)
{
    Config *stack = malloc(sizeof(*stack));
    if (stack) {
        Option option = { strdup(key), strdup(value) };
        stack->option = option;
        stack->next = *head;

        *head = stack;
        return TRUE;
    }
    else {
        return FALSE;
    }
}


Option pop_option(Config **head)
{
    Option option = {};
    if (*head) {
        Config *prevConfig;
        prevConfig = *head;
        *head = (*head)->next;

        option = prevConfig->option;
        free(prevConfig);
    }
    return option;
}


void free_option(Option option)
{
    free(option.key);
    free(option.value);
}


static int parse_line(const char *line, char **key, char **value)
{
    char *value_str;
    /*  Skip empty lines and comments */
    if ((line[0] == '#') || (line[0] == '\n'))
        return FALSE;
    /* Get pointer to position of '=' if present */
    if (!(value_str = strchr(line, '=')))
        return FALSE;

    /* Overwrite the leading '=' and inc pointer */
    value_str[0] = '\0';
    value_str++;
    *key = strdup(line);

    /* Overwrite '\n' with '\0' if '\n' present */
    char *temp_str;
    if ((temp_str = strchr(value_str, '\n')))
        temp_str[0] = '\0';
    *value = strdup(value_str);

    trim_spaces(*key);
    trim_spaces(*value);
    return TRUE;
}


char *expand_config_filename(const char *filename) {
    char *fn;

    if (filename != NULL)
        /* If user provided a filename then use it */
        fn = strdup(filename);
    else {
        /* otherwise get the default config filename */
        fn = strdup(CONFIG_NAME);
    }
    if (access(fn, R_OK) != -1 ) {
        /* if the file exists in the current directory then use it */
        return fn;
    } else {
        /* get the users config directory and use our folder
           eg /home/user/.config/APP_NAME        
           then look for the config file there */
        char *dir = user_config_dir();
        char *temp = malloc(strlen(dir)+strlen(APP_NAME)+5);
		sprintf(temp, "%s%s%s%s%s", dir, "/", APP_NAME, "/", fn);
		fn = strdup(temp);
        free(dir);
        free(temp);
        return fn;
    }
    return NULL;
}


Config *read_config_file(const char *filename)
{
    FILE *fp;
    char line[256];
    char *fn, *key, *value;
    Config *config = NULL;

    fn = expand_config_filename(filename);

    /* Return if cannot open the file */
    if ((fp = fopen(fn, "r")) == NULL)
        return NULL;

    /* Parse each line and store as key, value pair */
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (parse_line(line, &key, &value)) {
            push_option(&config, key, value);
            free(key);
            free(value);
        }
    }
    fclose(fp);
    free(fn);
    return config;
}

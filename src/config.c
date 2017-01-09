#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "common.h"


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


Config *read_config_file(const char *filename)
{
    FILE *fp;
    char line[256];
    char *key, *value;
    Config *config = NULL;

    /* Return if cannot open the file */
    if ((fp = fopen(filename, "r")) == NULL)
        return FALSE;

    /* Parse each line and store as key, value pair */
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (parse_line(line, &key, &value)) {
            push_option(&config, key, value);
            free(key);
            free(value);
        }
    }
    fclose(fp);
    return config;
}
